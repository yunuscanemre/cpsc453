
#include <QStringList>
#include <Triangle.h>
#include <Helpers.h>
#include <Intersection.h>
#include <math.h>

Triangle::Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
   a_ = a;
   b_ = b;
   c_ = c;
   n_ = glm::normalize(glm::cross(b-a, c-a));
}

Triangle::~Triangle()
{
}

bool Triangle::intersect(Ray ray, Intersection* hit)
{
   glm::vec3 E1 = a_ - b_;
   glm::vec3 E2 = a_ - c_;
   glm::vec3 V = ray.direction_;
   glm::vec3 T = a_ - ray.origin_;

   glm::mat3 e1e2v(E1, E2, V);
   float e1e2vDet = glm::determinant(e1e2v);

   glm::mat3 te2v(T, E2, V);
   float te2vDet = glm::determinant(te2v);

   float beta = te2vDet / e1e2vDet;

   glm::mat3 e1tv(E1, T, V);
   float e1tvDet = glm::determinant(e1tv);

   float gamma = e1tvDet / e1e2vDet;

   glm::mat3 e1e2t(E1, E2, T);
   float e1e2tDet = glm::determinant(e1e2t);

   float t = e1e2tDet / e1e2vDet;

   if((beta + gamma < 1.0) && (beta > 0.0) && (gamma > 0.0))
   {
      hit->material_ = material_;
      hit->obj_ = this;
      hit->distance_ = t;
      hit->intersection_ = ray.origin_ + t * ray.direction_;
      hit->normal_ = -n_;

      return true;
   }
   else
      return false;
}
