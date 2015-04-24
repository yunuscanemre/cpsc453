
#include <QStringList>
#include <Plane.h>
#include <Helpers.h>
#include <Intersection.h>
#include <math.h>

Plane::Plane(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
   p1_ = p1 ;
   p2_ = p2 ;
   p3_ = p3 ;
   n_ = glm::normalize(glm::cross(p1 - p3, p1 - p2));
}

Plane::~Plane()
{
}

bool Plane::intersect(Ray r, Intersection* hit)
{
   double d = -((n_.x * p1_.x) + (n_.y * p1_.y) + (n_.z * p1_.z));
   double t = -(glm::dot(n_, r.origin_) + d) / glm::dot(n_, r.direction_);
   if(t < 0)
   {
      hit = NULL;
      return false;
   }

   hit->intersection_ = r.origin_ + (float) t * r.direction_;
   hit->normal_ = glm::normalize(n_);
   hit->distance_ = t;
   hit->material_ = material_;
   hit->obj_ = this;
   return true;
}
