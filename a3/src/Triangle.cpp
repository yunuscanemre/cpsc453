
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
   n_ = -glm::normalize(glm::cross(b-a, c-a));
}

Triangle::~Triangle()
{
}

// Refer to http://geomalgorithms.com/a06-_intersect-2.html
bool Triangle::intersect(Ray ray, Intersection* hit)
{
   glm::vec3 u = b_ - a_; // triangle vectors
   glm::vec3 v = c_ - a_;

//   Vector dir, w0, w;           // ray vectors
   float r, a, b;              // params to calc ray-plane intersect

   glm::vec3 dir = ray.direction_;
//   w0 = R.P0 - T.V0;
   glm::vec3 w0 = ray.origin_ - a_;
   a = -glm::dot(n_, w0);
   b = glm::dot(n_, dir);
   if(fabs(b) < 0.00000001)
   {     // ray is  parallel to triangle plane
      if(a == 0)                 // ray lies in triangle plane
      {
         hit = NULL;
//         fprintf(stderr, "here 1");
         return false;
      }
      else
      {
         hit = NULL;
//         fprintf(stderr, "here 2");
         return false;              // ray disjoint from plane
      }
   }

   // get intersect point of ray with triangle plane
   r = a / b;
   if(r < 0.0)                    // ray goes away from triangle
   {
      hit = NULL;
//      fprintf(stderr, "here 3");
      return false;                   // => no intersect
   }
   // for a segment, also test if (r > 1.0) => no intersect

   hit->intersection_ = ray.origin_ + r * dir;            // intersect point of ray and plane

   // is I inside T?
   float uu, uv, vv, wu, wv, D;
   uu = glm::dot(u, u);
   uv = glm::dot(u, v);
   vv = glm::dot(v, v);
   glm::vec3 w = hit->intersection_ - a_;
   wu = dot(w, u);
   wv = dot(w, v);
   D = uv * uv - uu * vv;

   // get and test parametric coords
   float s, t;
   s = (uv * wv - vv * wu) / D;
   if(s < 0.0 || s > 1.0)         // I is outside T
   {
      hit = NULL;
//      fprintf(stderr, "here 4");
      return false;
   }
   t = (uv * wu - uu * wv) / D;
   hit->distance_ = t;
   if(t < 0.0 || (s + t) > 1.0)  // I is outside T
   {
      hit = NULL;
//      fprintf(stderr, "here 5");
      return false;
   }

   hit->normal_ = n_;

   return true;                       // I is in T
}
