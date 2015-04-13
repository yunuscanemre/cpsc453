#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <QObject>
#include <QString>
#include <A_Object.h>
#include <Ray.h>
#include <glm/glm.hpp>

class Intersection;

class Triangle : public A_Object
{
   Q_OBJECT

public:
   Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c);
   virtual ~Triangle();

public:
   virtual bool intersect(Ray r, Intersection* hit);

public:
   glm::vec3 a_;
   glm::vec3 b_;
   glm::vec3 c_;
   glm::vec3 n_;
};


#endif
