
#include <Intersection.h>
#include <Helpers.h>
#include <math.h>

Intersection::Intersection()
{

}

Intersection::Intersection(glm::vec3 intersectionPoint, glm::vec3 normal,
                           Material material, double distance)
{
   intersection_ = intersectionPoint;
   normal_ = normal;
   material_ = material;
   distance_ = distance;
   obj_ = NULL;
}

Intersection::~Intersection()
{

}
