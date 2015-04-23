
#include <QStringList>
#include <Ray.h>
#include <Helpers.h>
#include <A_Object.h>

Ray::Ray(glm::vec3 origin, glm::vec3 direction)
{
   origin_ = origin;
   direction_ = direction;
   startingObj_ = NULL;
}
Ray::Ray(glm::vec3 origin, glm::vec3 direction, A_Object* startingObject)
{
   origin_ = origin;
   direction_ = direction;
   startingObj_ = startingObject;
}

Ray::~Ray()
{
}
