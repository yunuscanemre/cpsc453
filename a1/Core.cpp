#include <MainView.h>
#include <Helpers.h>
#include <Core.h>
#include <RgbImage.h>
#include <QFileDialog>
#include <QImage>
#include <QColor>
#include <stdio.h>

Core::Core()
{
   view_ = new MainView();
   view_->show();
   QString fileName = "images/RedLeavesTexture.bmp";//QFileDialog::getOpenFileName();
   RgbImage* rgbImage = new RgbImage(fileName.toStdString().c_str());
   image_ = new QImage((uchar*)rgbImage->ImageData(), rgbImage->GetNumCols(), rgbImage->GetNumRows(),
         QImage::Format_RGB16);
//   double r=-1, g =-1 ,b=-1;
//   QColor c = QColor::fromRgb(image_->pixel(0, 0));
   unsigned char* pixel = rgbImage->GetRgbPixel(0, 0);
   fprintf(stderr, "RgbImage %c \n", *pixel);
   fprintf(stderr, "QImage %c \n", (image_->scanLine(0)[0]));
   if(*pixel == (image_->scanLine(0)[0]))
      fprintf(stderr, "TRUE \n");
   else
      fprintf(stderr, "False \n");
   view_->setOrigImage(image_);


}

Core::~Core()
{
   deletePointer(image_);
   deletePointer(view_);
}
