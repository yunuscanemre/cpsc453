#ifndef RAY_H_
#define RAY_H_

#include <QObject>
#include <QString>
#include <glm/glm.hpp>

class Ray
{
public:
   Ray(glm::vec3 origin, glm::vec3 direction);
   virtual ~Ray();

public: // public for convenience
   glm::vec3 origin_;
   glm::vec3 direction_;
};


#endif
