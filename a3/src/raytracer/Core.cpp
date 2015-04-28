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
#include <Material.h>

#include <Sphere.h>
#include <Plane.h>
#include <Triangle.h>

static bool debug = false;

Core::Core() :
   image_(NULL),
   camera_(0, 0, 60),
   ambientLight_(0.1, 0.1, 0.1),
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
   qtConnect(view_, SIGNAL(saveImageSelected(bool)), this,
             SLOT(saveImage()));

   // Spheres

   // Yellow sphere, 0% reflective
   A_Object* s5 = new Sphere(glm::vec3(1, -4, 0), 2);
   s5->setMaterial(Material(glm::vec3(0.8588, 0.949, 0.02745), glm::vec3(0.7), 128, 1));

   // Red sphere, 80% reflective
   A_Object* s = new Sphere(glm::vec3(-4, -2, 5), 3.0);
   s->setMaterial(Material(glm::vec3(1, 0, 0), glm::vec3(0.7), 128, 0.2));

   // Green sphere, 40% reflective
   A_Object* s2 = new Sphere(glm::vec3(-4, 6, 7), 2.5);
   s2->setMaterial(Material(glm::vec3(0, 1, 0), glm::vec3(0.7), 128, 0.6));

   // Blue sphere, 10% reflective
   A_Object* s3 = new Sphere(glm::vec3(3, 7, 10), 1);
   s3->setMaterial(Material(glm::vec3(0, 0, 1), glm::vec3(0.7), 128, 0.9));

   // Pink sphere, 10% reflective
   A_Object* s4 = new Sphere(glm::vec3(12, -8, -35), 2);
   s4->setMaterial(Material(glm::vec3(0.5, 0, 0.3), glm::vec3(0.7), 32, 0.9));

   // Plane
   A_Object* p = new Plane(glm::vec3(1, -10, 0), glm::vec3(0, -10, 1), glm::vec3(0, -10, -1));
   p->setMaterial(Material(glm::vec3(0, 0.2166, 0.25), glm::vec3(0.7), 128, 0));

   // Triangles
   // Pink triangle, 70% reflective
   A_Object* t = new Triangle(glm::vec3(-6, 4, -7), glm::vec3(0, 8, -7), glm::vec3(6, 4, -7));
   t->setMaterial(Material(glm::vec3(0.5, 0.2, 0.7), glm::vec3(0.7), 128, 0.3));

   // Orange triangle, 30% reflective
   A_Object* t2 = new Triangle(glm::vec3(-10, -10, -80), glm::vec3(-10, 10, -80), glm::vec3(10, -10, -80));
   t2->setMaterial(Material(0.3f*glm::vec3(1.0, 0.537, 0.16078), glm::vec3(0.7), 128, 0.7));

   // Dark Green Triangle, 0% reflective
   A_Object* t3 = new Triangle(glm::vec3(12, -5, -80), glm::vec3(14.5, 5, -80), glm::vec3(17, -3, -90));
   t3->setMaterial(Material(0.3f*glm::vec3(0.12549, 0.470588, 0), glm::vec3(0.7), 128, 1));


   objects_  << s << s2 << s3 << s4 << s5 << t << t2 << t3 << p ;

   // Lights
   Light l1 (glm::vec3(0, 30, 30), 1, 0.00002, 0.000030, 0.00005);
   Light l2 (glm::vec3(-60, 30, -30), 1, 0.00002, 0.00003, 0.00005);
   Light l3 (glm::vec3(60, 30, -30), 1.5, 0.00002, 0.00003, 0.00005);
   lights_ << l1 << l2 << l3;

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
      spec *= (1 - hit.material_.o_);
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

         float attenuation = 1.0f/(l.c_*pow(hitToLight, 2.0f) + l.b_*hitToLight + l.a_);
         local += shadowColor*attenuation;
//         local += shadowColor;

      }
      else
      {
         local += (phong(lightVector, viewDirection, hit.normal_, hit.material_, l.intensity_));
      }
   }

//   local += ambientLight_;
   return local + spec;
}

glm::vec3 Core::phong(glm::vec3 lightVector, glm::vec3 viewDirection, glm::vec3 normal, Material m, float lightIntensity)
{
   glm::vec3 diffuse = m.d_*(float)(qMax((double) glm::dot(lightVector, normal), 0.0))*lightIntensity;
   glm::vec3 reflect = glm::normalize(glm::reflect(lightVector, normal));
   glm::vec3 specular = (float)pow(qMax(glm::dot(reflect, viewDirection), 0.0f), m.n_) * m.s_ * lightIntensity;

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
   image_->save(saveFile, 0, 100);
}

