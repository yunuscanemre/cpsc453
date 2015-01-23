#include <MainView.h>
#include <Helpers.h>
#include <Core.h>
#include <RgbImage.h>
#include <QFileDialog>
#include <stdio.h>

Core::Core()
{
   view_ = new MainView();
   view_->show();
   QString fileName = QFileDialog::getOpenFileName();
   image_ = new RgbImage(fileName.toStdString().c_str());
   view_->setOrigImage(image_);

}

Core::~Core()
{
   deletePointer(image_);
   deletePointer(view_);
}
