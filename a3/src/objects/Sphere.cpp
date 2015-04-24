
#include <QStringList>
#include <Sphere.h>
#include <Helpers.h>
#include <Intersection.h>
#include <math.h>

Sphere::Sphere(glm::vec3 center, double radius)
{
   center_ = center;
   r_ = radius;
}

Sphere::~Sphere()
{
}

bool Sphere::intersect(Ray r, Intersection* hit)
{
   glm::vec3 D = r.origin_ - center_;

   double discriminant = pow(glm::dot(r.direction_, D), 2.0) - (glm::dot(D, D) - pow(r_, 2.0));

   if(discriminant <= 0)
   {
      hit = NULL;
      return false;
   }

   double b = -1*glm::dot(r.direction_, D);
   double t1 = (b + sqrt(discriminant));
   double t2 = (b - sqrt(discriminant));

   double minT = qMin(t1, t2);

   if(t1 > 0)
   {
      if(t2 > 0)
      {
         minT = qMin(t1, t2);
      }
      else
         minT = t1;
   }
   else if (t2 > 0)
   {
      minT = t2;
   }
   else
   {
      hit = NULL;
      return false;
   }


   hit->intersection_ = (r.origin_ + (r.direction_ * (float) minT));
   hit->normal_ = glm::normalize(hit->intersection_ - center_);
   hit->distance_ = minT;
   hit->material_ = material_;
   hit->obj_ = this;
   return true;
}
