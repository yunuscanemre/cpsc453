
#include <QStringList>
#include <Sphere.h>
#include <Helpers.h>
#include <math.h>

Sphere::Sphere(glm::vec3 center, double radius)
{
   center_ = center;
   r_ = radius;
}

Sphere::~Sphere()
{
}

bool Sphere::intersect(Ray r, glm::vec3* intersection)
{
   glm::vec3 D = r.origin_ - center_;

   double discriminant = pow(2*glm::dot(r.direction_, D), 2) - 4*(pow(D.length(), 2) - pow(r_, 2));

   if(discriminant < 0)
   {
      fprintf(stderr, "no hit \n");
      intersection = NULL;
      return false;
   }

   double b = -1*2*glm::dot(r.direction_, D);
   double t1 = (b + sqrt(discriminant))/2;
   double t2 = (b - sqrt(discriminant))/2;
//   fprintf(stderr, "t1 %f, t2 %f \n", t1, t2);

   double minT = -1;
   if(t1 < 0)
   {
      fprintf(stderr, "t1 was < 0 \n");
      minT = t2;
   }
   else if (t2 < 0)
   {
      fprintf(stderr, "t2 was < 0 \n");
      minT = t1;
   }
   else
   {
      minT = qMin(t1, t2);
   }


   //   fprintf(stderr, "minT %f \n", minT);
//   fprintf(stderr, "r.direction before * %f, %f, %f \n", r.direction_.x, r.direction_.y, r.direction_.z);
//   r.direction_.operator *=(minT);
   *intersection = r.origin_ + (r.direction_.operator *=(minT));
//   fprintf(stderr, "r.direction after * %f, %f, %f \n", r.direction_.x, r.direction_.y, r.direction_.z);

//   fprintf(stderr, "intersection %f, %f, %f  \n", intersection->x, intersection->y, intersection->z);
   return true;
}
