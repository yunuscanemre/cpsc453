#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <MainView.h>
#include <Core.h>
#include <QFileDialog>
#include <QColor>
#include <Helpers.h>
#include <QMessageBox>

Core::Core()
{
   view_ = new MainView();
   md2_ = new MD2();
   view_->show();

   qtConnect(view_, SIGNAL(exitSelected(bool)), this,
         SLOT(exit()));

   QString fileToLoad = "models/faerie/weapon.md2";
//   QString fileToLoad = QFileDialog::getOpenFileName(NULL, "Select an md2 file");
   if(fileToLoad != NULL)
   {
      md2_->LoadModel(fileToLoad.toStdString().c_str());
   }

   fprintf(stderr, "md2_->num_xyz %d\n", md2_->num_xyz);
   fprintf(stderr, "md2_->num_tris %d\n", md2_->num_tris);

   vertices_ = new QVector<GLfloat>();
   normals_ = new QVector<GLfloat>();

   for(int i = 0; i < md2_->num_tris; i++)
   {
      triangle_t* triangle = md2_->tris + i;
      glm::vec3 normal = calculateNormal(triangle);
//      fprintf(stderr, "normal: %f, %f, %f \n", normal.x, normal.y, normal.z);
      normals_->append(normal.x);
      normals_->append(normal.y);
      normals_->append(normal.z);

      for(int j = 0; j<3; j++)
      {
         for(int k = 0; k < 3; k++)
         {
            vertices_->append(md2_->m_vertices[triangle->index_xyz[j]][k]);
         }
      }
   }

   fprintf(stderr, "num normals %d \n", normals_->size());

   view_->createGlWidget(vertices_, normals_);
}

void Core::exit()
{
   QCoreApplication::exit();
}

Core::~Core()
{
   deletePointer(vertices_);
   deletePointer(normals_);
   deletePointer(md2_);
   deletePointer(view_);
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

   glm::vec3 cross = glm::cross(c-a, c-b);
   if(glm::dot((c-a), cross) > 0.0001)
      fprintf(stderr, "c-a DOT cross didnt = 0\n");
   if(glm::dot((c-b), cross) > 0.0001)
      fprintf(stderr, "c-b DOT cross didnt = 0 \n");
   if(glm::dot((b-a), cross) > 0.0001)
      fprintf(stderr, "b-a DOT cross didnt = 0 \n");

   return cross;
}
