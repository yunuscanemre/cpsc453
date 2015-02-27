#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <MainView.h>
#include <Core.h>
#include <QFileDialog>
#include <QColor>
#include <Helpers.h>
#include <QMessageBox>

#include <md2.h>

Core::Core()
{
   view_ = new MainView();
   md2_ = new MD2();
   view_->show();

   qtConnect(view_, SIGNAL(exitSelected(bool)), this,
         SLOT(exit()));

   QString fileToLoad = QFileDialog::getOpenFileName(NULL,
         "Select an md2 file");
   if(fileToLoad != NULL)
   {
      md2_->LoadModel(fileToLoad.toStdString().c_str());
   }

   vertices_ = new QVector<GLfloat>(md2_->num_xyz*3);
   for(int i = 0; i < md2_->num_tris; i++)
      for(int j = 0; j<3; j++)
         for(int k = 0; k < 3; k++)
            vertices_->append(md2_->m_vertices[md2_->tris[i].index_xyz[j]][k]);

   fprintf(stderr, "got %d \n", vertices_->size());
   for(int i = 0; i < vertices_->size(); i++)
      fprintf(stderr, " val %f ", vertices_->at(i));

   view_->createGlWidget(vertices_);
}

void Core::exit()
{
   QCoreApplication::exit();
}

Core::~Core()
{
   deletePointer(md2_);
   deletePointer(view_);
}

