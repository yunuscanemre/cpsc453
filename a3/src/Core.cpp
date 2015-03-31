#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <MainView.h>
#include <Core.h>
#include <RgbImage.h>
#include <QFileDialog>
#include <QColor>
#include <Helpers.h>
#include <Pixel.h>
#include <Ray.h>
#include <Sphere.h>

Core::Core() :
   image_(NULL),
   camera_(0, 0, -5),
   width_(5),
   height_(5)
{
   view_ = new MainView();
   view_->show();

   qtConnect(view_, SIGNAL(exitSelected(bool)), this,
         SLOT(exit()));

   raycast();
}

void Core::exit()
{
   QCoreApplication::exit();
}

Core::~Core()
{
   deletePointer(image_);
   deletePointer(view_);
}

void Core::raycast()
{
   image_ = new RgbImage(height_, width_);
   Sphere s(glm::vec3(0, 0, 2), 1);

   int lowerWidth = -width_/2;
   int upperWidth = width_/2;
   int lowerHeight = -height_/2;
   int upperHeight = height_/2;

   for(int i = lowerWidth; i<upperWidth; i++)
   {
      for(int j = lowerHeight; j < upperHeight; j++)
      {
         glm::vec3 dir(i-camera_.x, j-camera_.y, 0-camera_.z);
         dir = glm::normalize(dir);
         Ray r(camera_, dir);
         glm::vec3 intersection(0);
         if(s.intersect(r, &intersection))
         {
            image_->SetRgbPixel(j+upperHeight, i+upperWidth, Pixel(0.3, 0, 0));
         }
         else
         {
            image_->SetRgbPixel(j+upperHeight, i+upperWidth, Pixel(1));
         }

      }
   }
   view_->setImage(image_);
}

//void Core::castRay(glm::vec3 camera, int i, int j)
//{
//}

void Core::saveImage()
{
   QString saveFile = QFileDialog::getSaveFileName(NULL,
         "Select save location and enter file name");
   if (saveFile.isNull())
      return;
   image_->WriteBmpFile(saveFile.toStdString().c_str());
}

