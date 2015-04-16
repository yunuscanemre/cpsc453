#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <MainView.h>
#include <Core.h>
#include <QImage>
#include <algorithm>
#include <QFileDialog>
#include <Intersection.h>
#include <QColor>
#include <Helpers.h>
#include <Pixel.h>
#include <Material.h>

#include <Sphere.h>
#include <Plane.h>
#include <Triangle.h>

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
   qtConnect(view_, SIGNAL(updateCamera()), this,
             SLOT(update()));

   A_Object* s = new Sphere(glm::vec3(0, 0, -5), 0.8);
   A_Object* s2 = new Sphere(glm::vec3(0.9, 0.3, -6), 0.3);
   A_Object* p = new Plane(glm::vec3(1, -5, 0), glm::vec3(0, -5, 1), glm::vec3(0, -5, -1));
   A_Object* t = new Triangle(glm::vec3(0, 0, -1), glm::vec3(0.3, 0.1, -1), glm::vec3(0.6, 0, -1));
   objects_ << s << s2 << p << t;

   raycast();
}

void Core::update()
{
   camera_ = view_->getCamera();
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

         Intersection hit;
         if(getIntersectionWithScene(r, &hit))
         {
            glm::vec3 lightDirection = glm::normalize(lightPosition_ - hit.intersection_);
            glm::vec3 color = calculateColor(&hit.material_, hit.normal_, direction, lightDirection);
            image_->setPixel(i, j, vec3ToQrgb(color));
         }
         else
         {
            image_->setPixel(i, j, qRgb(255, 255, 255));
         }

      }
   }

   view_->setImage(*image_);
}

bool Core::getIntersectionWithScene(Ray r, Intersection* hit)
{
   double minT = INT_MAX;
   A_Object* object = NULL;
   Intersection closestHit;
   bool intersectionFound = false;
   for(int i = 0; i < objects_.count(); i++)
   {
      Intersection h;
      A_Object* objToCheck = objects_[i];
      if(objToCheck->intersect(r, &h))
      {
         intersectionFound = true;
         if(h.distance_ < minT)
         {
            closestHit = h;
            minT = h.distance_;
         }
      }
   }

   if(intersectionFound)
   {
      *hit = closestHit;
      return true;
   }
   else
   {
      hit = NULL;
      return false;
   }
}

glm::vec3 Core::calculateColor(Material* material, glm::vec3 normal, glm::vec3 viewDirection,
                               glm::vec3 lightVector)
{
   glm::vec3 diffuse = material->d_*(float)(qMax((double) glm::dot(lightVector, normal), 0.0))*(float)lightIntensity_;
   glm::vec3 reflect = glm::normalize(glm::reflect(lightVector, normal));
   glm::vec3 specular = material->s_ * (float)lightIntensity_ * (float) pow((glm::dot(reflect, viewDirection)), material->n_);
   glm::vec3 ambient = ambientLight_;

   glm::vec3 color = diffuse + specular + ambient;
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

