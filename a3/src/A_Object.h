#ifndef A_OBJECT_H_
#define A_OBJECT_H_

#include <QObject>
#include <QString>
#include <glm/glm.hpp>
#include <Material.h>
#include <Ray.h>

class Intersection;

class A_Object : public QObject
{
   Q_OBJECT

public:
   A_Object();
   virtual ~A_Object();

public:
   virtual bool intersect(Ray ray, Intersection* intersection) = 0;
   virtual void setMaterial(const Material& m);

signals:

protected: // Inheriting classes need to access this
   Material material_;
   glm::vec3 normal_;
};


#endif
