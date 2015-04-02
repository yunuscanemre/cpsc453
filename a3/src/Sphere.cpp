
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

bool Sphere::intersect(Ray r, Intersection* intersection)
{
   glm::vec3 D = r.origin_ - center_;

   double discriminant = pow(glm::dot(r.direction_, D), 2.0) - (glm::dot(D, D) - pow(r_, 2.0));

   static int c = 0;
   if(c++ % 13 == 0)
   {
//	   fprintf(stderr, "discriminant %f \n", discriminant);
//	   fprintf(stderr, "dot %f \n", glm::dot(r.direction_, D));
//	   fprintf(stderr, "D: x %f, y %f, z %f \n", D.x, D.y, D.z);
//	   fprintf(stderr, "direction_: x %f, y %f, z %f \n", r.direction_.x, r.direction_.y, r.direction_.z);
   }

   if(discriminant <= 0)
   {
//      fprintf(stderr, "no hit \n");
      intersection = NULL;
      return false;
   }

   double b = -1*glm::dot(r.direction_, D);
   double t1 = (b + sqrt(discriminant))/2;
   double t2 = (b - sqrt(discriminant))/2;

   double minT = -1;
   if(t1 < 0)
   {
//      fprintf(stderr, "t1 was < 0 \n");
      minT = t2;
   }
   else if (t2 < 0)
   {
//      fprintf(stderr, "t2 was < 0 \n");
      minT = t1;
   }
   else
   {
      minT = qMin(t1, t2);
   }


   //   fprintf(stderr, "minT %f \n", minT);
//   fprintf(stderr, "r.direction before * %f, %f, %f \n", r.direction_.x, r.direction_.y, r.direction_.z);
//   r.direction_.operator *=(minT);
   intersection->intersection_ = (r.origin_ + (r.direction_ * (float) minT));
   intersection->normal_ = glm::normalize(center_ - intersection->intersection_);
//   fprintf(stderr, "r.direction after * %f, %f, %f \n", r.direction_.x, r.direction_.y, r.direction_.z);

//   fprintf(stderr, "intersection %f, %f, %f  \n", intersection->x, intersection->y, intersection->z);
   return true;
}
