#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include <QObject>
#include <QString>
#include <A_Object.h>
#include <Material.h>
#include <glm/glm.hpp>

struct Intersection
{
   Intersection();
   Intersection(glm::vec3 intersectionPoint, glm::vec3 normal,
                Material material, double distance_);
   ~Intersection();

   glm::vec3 intersection_;
   glm::vec3 normal_;
   Material material_;
   double distance_;
   A_Object* obj_;

};


#endif
