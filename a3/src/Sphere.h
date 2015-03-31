#ifndef SPHERE_H_
#define SPHERE_H_

#include <QObject>
#include <QString>
#include <A_Object.h>
#include <Ray.h>
#include <glm/glm.hpp>

class Sphere : public A_Object
{
   Q_OBJECT

public:
   Sphere(glm::vec3 center, double radius);
   virtual ~Sphere();

public:
   virtual bool intersect(Ray r, glm::vec3* intersection);

public:
   glm::vec3 center_;
   double r_;

};


#endif
