
#include <QStringList>
#include <Ray.h>
#include <Helpers.h>

Ray::Ray(glm::vec3 origin, glm::vec3 direction)
{
   origin_ = origin;
   direction_ = direction;
}

Ray::~Ray()
{
}
