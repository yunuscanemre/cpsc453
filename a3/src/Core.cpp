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

#include <Sphere.h>

Core::Core() :
   image_(NULL),
   camera_(0, 0, 5),
   width_(21),
   height_(21)
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


   Sphere s(glm::vec3(0, 0, -20), 1);

   int lowerWidth = -width_/2;
   fprintf(stderr, "lw %d \n", lowerWidth);
   int upperWidth = width_/2;
   int lowerHeight = -height_/2;
   int upperHeight = height_/2;

   for(int i = lowerWidth; i<=upperWidth; i++)
   {
      for(int j = lowerHeight; j <= upperHeight; j++)
      {
//         glm::vec3 dir(i-camera_.x, j-camera_.y, 0-camera_.z);
//         dir = glm::normalize(dir);
         Ray r = generateRay(i, j);
         glm::vec3 intersection(0);
         if(s.intersect(r, &intersection))
         {
            fprintf(stderr, "setting %d, %d \n", j+upperHeight, i+upperWidth);
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

Ray Core::generateRay(int i, int j)
{
   glm::vec3 lookat(0, 0, 0); // looking at origin
   glm::vec3 look = lookat - camera_;
   glm::vec3 up = glm::vec3(0, 1, 0);
   glm::vec3 du = glm::normalize(glm::cross(look, up));
   glm::vec3 dv = glm::normalize(glm::cross(look, du));
   double fov = 45;
   double f1 = ((double)width_ / (2*tan((0.5*fov)*M_PI/180)));
   glm::vec3 vp = glm::normalize(look);
   vp.x = vp.x*f1 - 0.5*(width_*du.x + height_*dv.x);
   vp.y = vp.y*f1 - 0.5*(width_*du.y + height_*dv.y);
   vp.z = vp.z*f1 - 0.5*(width_*du.z + height_*dv.z);

   glm::vec3 direction (i*du.x + j*dv.x + vp.x,
                        i*du.y + j*dv.y + vp.y,
                        i*du.z + j*dv.z + vp.z);
   return Ray(camera_, direction);
}

void Core::saveImage()
{
   QString saveFile = QFileDialog::getSaveFileName(NULL,
         "Select save location and enter file name");
   if (saveFile.isNull())
      return;
   image_->WriteBmpFile(saveFile.toStdString().c_str());
}

