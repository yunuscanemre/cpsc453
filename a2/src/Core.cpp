#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <MainView.h>
#include <Core.h>
#include <QFileDialog>
#include <QColor>
#include <Helpers.h>
#include <QMessageBox>
#include <algorithm>

Core::Core()
{
   view_ = new MainView();
   md2_ = new MD2();
   view_->show();

   qtConnect(view_, SIGNAL(exitSelected(bool)), this,
         SLOT(exit()));

//   QString fileToLoad = "models/faerie/weapon.md2";
   QString fileToLoad = QFileDialog::getOpenFileName(NULL, "Select an md2 file");
   if(fileToLoad != NULL)
   {
      md2_->LoadModel(fileToLoad.toStdString().c_str());
   }

   fprintf(stderr, "md2_->num_xyz %d\n", md2_->num_xyz);
   fprintf(stderr, "md2_->num_tris %d\n", md2_->num_tris);

   vertices_ = new QVector<GLfloat>();
   normals_ = new QVector<GLfloat>();
   map_ = new QMap<int, QList<triangle_t*>>();
   indices_ = new QVector<GLshort>();

   float max = md2_->m_vertices[0][0],
         xmax = md2_->m_vertices[0][0],
         ymax = md2_->m_vertices[0][1],
         xmin = md2_->m_vertices[0][0],
         ymin = md2_->m_vertices[0][0],
         value = 0;
   // Get vertices and find max, min
   for(int i = 0; i < md2_->num_xyz; i++)
   {
      for(int j = 0; j<3; j++)
      {
         value = md2_->m_vertices[i][j];
         max = (value > max ? value : max);
         vertices_->append(value);

         if(j==1)
         {
            xmax = value > xmax ? value : xmax;
            xmin = value < xmin ? value : xmin;
         }
         if(j==2)
         {
            ymax = value > ymax ? value : ymax;
            ymin = value < ymin ? value : ymin;
         }

      }
      vertices_->append(1.0f);
   }


   // Map values to range [-1, 1]
   xmax /= max; xmin /= max; ymax /= max; ymin /= max;
   float midx = (xmax+xmin)/2;
   float midy = (ymax+ymin)/2;
   mapVerticesBetweenMinusOneToOne(max);

   for(int i = 0; i < vertices_->size(); i++)
      fprintf(stderr, "%f \n", vertices_->at(i));

   for(int i = 0; i<md2_->num_tris; i++)
   {
      triangle_t* triangle = md2_->tris + i;
      for(int k = 0; k<3; k++)
      {
         int index = triangle->index_xyz[k];
         indices_->append(index);
         (*map_)[index].append(triangle);
      }
   }


   calculateAndAppendAverageNormals();

//   fprintf(stderr, "num vertices %d \n", vertices_->size());
//   fprintf(stderr, "num indices %d \n", indices_->size());
//   fprintf(stderr, "num normals %d \n", normals_->size());
   fprintf(stderr, "midx %f, midy %f \n", midx, midy);

   view_->createGlWidget(vertices_, indices_, normals_);

//   view_->setTranslation(0-midx, 0-midy, 0);
}

void Core::exit()
{
   QCoreApplication::exit();
}

Core::~Core()
{
   deletePointer(indices_);
   deletePointer(vertices_);
   deletePointer(normals_);
   deletePointer(md2_);
   deletePointer(view_);
}

void Core::mapVerticesBetweenMinusOneToOne(float max)
{
   int skip = 3;
   for(int i = 0; i<vertices_->size(); i++)
   {
      if(i!=skip)
      {
         vertices_->replace(i, vertices_->at(i)/max);
      }
      else
         skip+=4;
   }
}

void Core::calculateAndAppendAverageNormals()
{
   for(int vertex = 0; vertex < md2_->num_xyz; vertex++)
   {
      GLfloat totalx = 0.0, totaly = 0.0, totalz = 0.0;
      GLfloat avrgx = 0.0, avrgy = 0.0, avrgz = 0.0;

      foreach(triangle_t* triangle, (*map_)[vertex])
      {
         glm::vec3 normal = calculateNormal(triangle);
         totalx+=normal.x;
         totaly+=normal.y;
         totalz+=normal.z;
      }

      avrgx = totalx/(*map_)[vertex].size();
      avrgy = totaly/(*map_)[vertex].size();
      avrgz = totalz/(*map_)[vertex].size();

      glm::vec3 avrgNormal;
      avrgNormal = glm::normalize(glm::vec3(avrgx, avrgy, avrgz));

      normals_->append(avrgNormal.x);
      normals_->append(avrgNormal.y);
      normals_->append(avrgNormal.z);
   }
}

glm::vec3 Core::calculateNormal(triangle_t* triangle)
{
   float c_x = md2_->m_vertices[triangle->index_xyz[2]][0];
   float c_y = md2_->m_vertices[triangle->index_xyz[2]][1];
   float c_z = md2_->m_vertices[triangle->index_xyz[2]][2];
   glm::vec3 c(c_x, c_y, c_z);

   float b_x = md2_->m_vertices[triangle->index_xyz[1]][0];
   float b_y = md2_->m_vertices[triangle->index_xyz[1]][1];
   float b_z = md2_->m_vertices[triangle->index_xyz[1]][2];
   glm::vec3 b(b_x, b_y, b_z);

   float a_x = md2_->m_vertices[triangle->index_xyz[0]][0];
   float a_y = md2_->m_vertices[triangle->index_xyz[0]][1];
   float a_z = md2_->m_vertices[triangle->index_xyz[0]][2];
   glm::vec3 a(a_x, a_y, a_z);

   glm::vec3 cross = glm::cross(c-a, b-a);

   return -cross;
}
