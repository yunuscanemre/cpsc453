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
   for(int i = 0; i < md2_->num_xyz; i++)
      for(int j = 0; j<3; j++)
            vertices_->append(md2_->m_vertices[i][j]);


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

