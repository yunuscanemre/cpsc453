
#include <QStringList>
#include <A_Object.h>
#include <Intersection.h>
#include <Helpers.h>

A_Object::A_Object()
{
   material_ = Material();
   normal_ = glm::vec3(0);
}

A_Object::~A_Object()
{
}

void A_Object::setMaterial(const Material& m)
{
   material_ = m;
}
