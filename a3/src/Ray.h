#ifndef RAY_H_
#define RAY_H_

#include <QObject>
#include <QString>
#include <glm/glm.hpp>

class A_Object;
class Ray
{
public:
   Ray(glm::vec3 origin, glm::vec3 direction);
   Ray(glm::vec3 origin, glm::vec3 direction, A_Object* startingObject);
   virtual ~Ray();

public: // public for convenience
   glm::vec3 origin_;
   glm::vec3 direction_;
   A_Object* startingObj_;
};


#endif
