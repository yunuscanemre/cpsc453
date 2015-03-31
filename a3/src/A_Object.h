#ifndef A_OBJECT_H_
#define A_OBJECT_H_

#include <QObject>
#include <QString>
#include <glm/glm.hpp>
#include <Ray.h>

class A_Object : public QObject
{
   Q_OBJECT

public:
   A_Object();
   virtual ~A_Object();

public:
   virtual bool intersect(Ray ray, glm::vec3* intersection) = 0;

signals:

protected: // Inheriting classes need to access this
   double d_, s_, n_;
   glm::vec3 normal_;
};


#endif
