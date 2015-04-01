
#include <Material.h>
#include <Helpers.h>

Material::Material()
{
   d_ = glm::vec3(0.5, 0.2, 0.7);
   s_ = glm::vec3(0.7);
   n_ = 128.0;
}

Material::Material(double d, double s, double n)
{
   d_ = glm::vec3(d); s_ = glm::vec3(s); n_ = n;
}

Material::Material(glm::vec3 d, double s, double n)
{
   d_ = d; s_ = glm::vec3(s); n_ = n;
}

Material::Material(glm::vec3 d, glm::vec3 s, double n)
{
   d_ = d; s_ = s; n_ = n;
}

Material::~Material()
{

}
