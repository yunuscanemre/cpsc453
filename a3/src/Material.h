#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <glm/glm.hpp>

struct Material
{
   Material();
   Material(double d, double s, double n);
   Material(glm::vec3 d, double s, double n);
   Material(glm::vec3 d, glm::vec3 s, double n);
   ~Material();

   glm::vec3 d_; // diffuse
   glm::vec3 s_; // specular
   double n_; // power
//   double a_; // ambient
};

#endif
