#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <MainView.h>
#include <Core.h>
#include <QImage>
#include <QFileDialog>
#include <Intersection.h>
#include <QColor>
#include <Helpers.h>
#include <Pixel.h>
#include <Material.h>

#include <Sphere.h>
#include <Plane.h>

Core::Core() :
   image_(NULL),
   camera_(0, 0, 5),
   lightPosition_(0, 0, 0),
   ambientLight_(0.1, 0.1, 0.1),
   lightIntensity_(1),
   worldMinWidth_(-1),
   worldMaxWidth_(1),
   worldMinHeight_(-1),
   worldMaxHeight_(1),
   imgWidth_(1000),
   imgHeight_(1000)
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
   image_ = new QImage(imgHeight_, imgWidth_, QImage::Format_RGB32);

   Sphere s(glm::vec3(1, 0, -5), 0.8);
//   Plane s(glm::vec3(0, 2, 3), glm::vec3(0, 1, 0), glm::vec3(0, 0, -1));
   double dx = (worldMaxWidth_ - worldMinWidth_) / imgWidth_;
   double dy = (worldMaxHeight_ - worldMinHeight_) / imgHeight_;

   for(int i = 0; i< imgWidth_; i++)
   {
      for(int j = 0; j < imgHeight_; j++)
      {
         glm::vec3 worldPixel;
         worldPixel.x = worldMinWidth_ + i * dx;
         worldPixel.y = worldMaxHeight_ - j * dy; // Origin of an image is top-left, so invert y
         worldPixel.z = 0;
         glm::vec3 direction = glm::normalize(worldPixel - camera_);
         Ray r(camera_, direction);
//         Ray r = generateRay(i, j);
         Intersection hit;
         if(s.intersect(r, &hit))
         {
            glm::vec3 lightDirection = glm::normalize(lightPosition_ - hit.intersection_);
            glm::vec3 color = calculateColor(&hit.material_, hit.normal_, direction, lightDirection);
            image_->setPixel(j, i, vec3ToQrgb(color));
         }
         else
         {
            image_->setPixel(j, i, qRgb(255, 255, 255));
         }

      }
   }

   view_->setImage(*image_);
}

glm::vec3 Core::calculateColor(Material* material, glm::vec3 normal, glm::vec3 viewDirection,
                               glm::vec3 lightVector)
{
   // why qMax? it was in the shaders
   glm::vec3 diffuse = material->d_*(float)(qMax((double) glm::dot(normal, lightVector), 0.0))*(float)lightIntensity_;
   // qMax here too ?
   glm::vec3 reflect = glm::normalize(2 * (glm::dot(normal, lightVector)) * normal - lightVector);
   glm::vec3 specular = material->s_ * (float)lightIntensity_ * (float) pow((glm::dot(reflect, viewDirection)), material->n_);
   glm::vec3 ambient = ambientLight_;

   glm::vec3 color = diffuse + specular + ambient;
//   static int a = 0;
//   if(a++ % 20 == 0)
//   fprintf(stderr, "color x %f, y %f, z %f \n", color.x, color.y, color.z);
   return color;
}

QRgb Core::vec3ToQrgb(glm::vec3 c)
{
   int r = doubleToIntPixel(c.x);
   int g = doubleToIntPixel(c.y);
   int b = doubleToIntPixel(c.z);
   return qRgb(r, g, b);
}

Ray Core::generateRay(int i, int j)
{
   glm::vec3 lookat(0, 0, 0); // looking at origin
   glm::vec3 look = lookat - camera_;
   glm::vec3 up = glm::vec3(0, 1, 0);
   glm::vec3 du = glm::normalize(glm::cross(look, up));
   glm::vec3 dv = glm::normalize(glm::cross(look, du));
   double fov = 45;
   double f1 = ((double)2.0 / (2*tan((0.5*fov)*M_PI/180)));
   glm::vec3 vp = glm::normalize(look);
   vp.x = vp.x*f1 - 0.5*(2.0*du.x + 2.0*dv.x);
   vp.y = vp.y*f1 - 0.5*(2.0*du.y + 2.0*dv.y);
   vp.z = vp.z*f1 - 0.5*(2.0*du.z + 2.0*dv.z);

   glm::vec3 direction (i*du.x + j*dv.x + vp.x,
                        i*du.y + j*dv.y + vp.y,
                        i*du.z + j*dv.z + vp.z);
   return Ray(camera_, glm::normalize(direction));
}

void Core::saveImage()
{
   QString saveFile = QFileDialog::getSaveFileName(NULL,
         "Select save location and enter file name");
   if (saveFile.isNull())
      return;
//   image_->WriteBmpFile(saveFile.toStdString().c_str());
}

