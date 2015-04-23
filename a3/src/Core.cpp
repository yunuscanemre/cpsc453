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

static bool debug = false;

Core::Core() :
   image_(NULL),
   camera_(0, 0, 30),
   ambientLight_(0.2, 0.2, 0.2),
   lightIntensity_(1),
   worldMinWidth_(-10),
   worldMaxWidth_(10),
   worldMinHeight_(-10),
   worldMaxHeight_(10),
   background_(0),
   imgWidth_(800),
   imgHeight_(800)
{
   view_ = new MainView();
   view_->show();

   qtConnect(view_, SIGNAL(exitSelected(bool)), this,
         SLOT(exit()));
   qtConnect(view_, SIGNAL(updateCamera()), this,
             SLOT(update()));

   // Spheres
   A_Object* s = new Sphere(glm::vec3(-1.0, 0, 5), 3.0);
   A_Object* s2 = new Sphere(glm::vec3(-4, 6, 7), 2.5);
   A_Object* s3 = new Sphere(glm::vec3(4, 1.5, 10), 1);
   A_Object* s4 = new Sphere(glm::vec3(4, -1.5, 10), 1);
   s4->setMaterial(Material(glm::vec3(0.01), glm::vec3(0.5), 32));

   // Plane
   A_Object* p = new Plane(glm::vec3(1, -10, 0), glm::vec3(0, -10, 1), glm::vec3(0, -10, -1));
   p->setMaterial(Material(0.3f*glm::vec3(0, 0.835, 1), glm::vec3(0), 300));

   // Triangles
   A_Object* t = new Triangle(glm::vec3(-6, 4, -7), glm::vec3(0, 8, -7), glm::vec3(6, 4, -7));

   // Floor from 2 triangles
   A_Object* tf1 = new Triangle(glm::vec3(-10, -10, -5), glm::vec3(-10, -10, -45), glm::vec3(10, -10, -45));
   tf1->setMaterial(Material(0.3f*glm::vec3(0, 0.835, 1), glm::vec3(0.7), 300));
   A_Object* tf2 = new Triangle(glm::vec3(10, -10, -5), glm::vec3(-10.01, -10, -5), glm::vec3(10, -10, -45.01));
   tf2->setMaterial(Material(0.3f*glm::vec3(0, 0.835, 1), glm::vec3(0.7), 128));
   objects_  << s << s2 << s3 << s4 << t << tf1 << tf2;

   // Lights
   Light l1 (glm::vec3(0, 30, 30), 0.5, 1, 2);
   Light l2 (glm::vec3(-60, 30, 0), 0.5, 1, 2);
   Light l3 (glm::vec3(60, 30, 0), 0.5, 1, 2);
   Light l4 (glm::vec3(0, 50, 0), 0.5, 1, 2);
   lights_ << l1 << l2 << l3 << l4;

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

         glm::vec3 color = calculateColor(r, 3);
         image_->setPixel(i, j, vec3ToQrgb(color));
      }
   }

   view_->setImage(*image_);
}

bool Core::getIntersectionWithScene(Ray r, Intersection* hit, A_Object* startingObject)
{
   double minT = INT_MAX;
   A_Object* object = NULL;
   Intersection closestHit;
   bool intersectionFound = false;
   for(int i = 0; i < objects_.count(); i++)
   {
      Intersection h;
      A_Object* objToCheck = objects_[i];

      if(objToCheck->intersect(r, &h) && h.distance_ > 0.2)
      {
         if(startingObject!= NULL && startingObject == objToCheck)
         {
            continue;
         }
         intersectionFound = true;
//         if(debug)
//         {
//            fprintf(stderr, "%f \n", h.distance_);
//            debug = false;
//         }
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

bool Core::checkForShadowObject(Ray r, A_Object* startingObject, Intersection* hit)
{
   double minT = INT_MAX;
   A_Object* object = NULL;
   Intersection closestHit;
   bool intersectionFound = false;
   for(int i = 0; i < objects_.count(); i++)
   {
      Intersection h;
      A_Object* objToCheck = objects_[i];
      if(startingObject != objToCheck && objToCheck->intersect(r, &h) && h.distance_ < 1000)
      {
         intersectionFound = true;
//         if(debug)
//         {
//            fprintf(stderr, "%f \n", h.distance_);
//            debug = false;
//         }
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

glm::vec3 Core::calculateColor(Ray ray, int depth)
{
   if(depth < 0)
      return background_;

   Intersection hit;
   if(!getIntersectionWithScene(ray, &hit, ray.startingObj_))
   {
      return background_;
   }

   glm::vec3 spec(0);
   if(hit.material_.s_.x > 0 || hit.material_.s_.y > 0 || hit.material_.s_.z > 0)
   {
//      glm::vec3 reflectDir = glm::normalize(ray.direction_ - 2*(glm::dot(ray.direction_, hit.normal_)) * hit.normal_);
      glm::vec3 reflectDir = glm::normalize(glm::reflect(ray.direction_, hit.normal_));
      Ray reflection(hit.intersection_, reflectDir, hit.obj_);
      debug = true;
      glm::vec3 c = calculateColor(reflection, depth-1);
      spec.x = hit.material_.s_.x * c.x;
      spec.y = hit.material_.s_.y * c.y;
      spec.z = hit.material_.s_.z * c.z;
   }
   else
   {
      spec = glm::vec3(0);
   }

   glm::vec3 viewDirection = glm::normalize(hit.intersection_ - camera_);
   glm::vec3 local(0);
   for(int i = 0; i < lights_.count(); i++)
   {
      Light l = lights_[i];
      glm::vec3 lightPosition = l.pos_;
      glm::vec3 lightVector = glm::normalize(lightPosition - hit.intersection_);


      // check shadow
      double hitToLight = glm::length(lightPosition - hit.intersection_);
      Ray shadowRay(hit.intersection_, lightVector);
      Intersection shadowHit;

      if(checkForShadowObject(shadowRay, hit.obj_, &shadowHit) &&
        (hitToLight > glm::length(lightPosition - shadowHit.intersection_)  ))
      {
         glm::vec3 d = hit.material_.d_;
         glm::vec3 shadowColor = glm::vec3(ambientLight_.x*d.x, ambientLight_.y*d.y, ambientLight_.z*d.z);
         local += shadowColor;
      }
      else
      {
         float attenuation = 1;//1.0f/(l.a_*pow(hitToLight, 2.0f) + l.b_*hitToLight + l.c_);
//         fprintf(stderr, "att %f \n", attenuation);
//         fprintf(stderr, "htl %f \n", hitToLight);
         local += (attenuation*phong(lightVector, viewDirection, hit.normal_, hit.material_));
      }
   }

   local += ambientLight_;
   return local + spec;
}

glm::vec3 Core::phong(glm::vec3 lightVector, glm::vec3 viewDirection, glm::vec3 normal, Material m)
{
   glm::vec3 diffuse = m.d_*(float)(qMax((double) glm::dot(lightVector, normal), 0.0))*(float)lightIntensity_;
   glm::vec3 reflect = glm::normalize(glm::reflect(lightVector, normal));
   glm::vec3 specular = (float)pow(qMax(glm::dot(reflect, viewDirection), 0.0f), m.n_) * m.s_ * (float)lightIntensity_;

   glm::vec3 color = diffuse + specular;
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

