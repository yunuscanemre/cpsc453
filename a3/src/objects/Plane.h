#ifndef PLANE_H_
#define PLANE_H_

#include <QObject>
#include <QString>
#include <A_Object.h>
#include <Ray.h>
#include <glm/glm.hpp>

class Intersection;

class Plane : public A_Object
{
   Q_OBJECT

public:
   Plane(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
   virtual ~Plane();

public:
   virtual bool intersect(Ray r, Intersection* hit);

public:
   glm::vec3 p1_;
   glm::vec3 p2_;
   glm::vec3 p3_;
   glm::vec3 n_;
};


#endif
