#ifndef CORE_H_
#define CORE_H_

#include <QObject>
#include <glm/glm.hpp>
#include <QImage>
#include <QList>
#include <Ray.h>

class MainView;
class QImage;
class Material;
class A_Object;
class Intersection;

struct Light
{
   glm::vec3 pos_;
   float a_ = 1;
   float b_ = 0;
   float c_ = 0;

   inline Light(glm::vec3 pos, float a, float b, float c)
   {
      pos_ = pos; a_ = a; b_ = b; c_ = c;
   }
};



class Core : public QObject
{
   Q_OBJECT

public:
   Core();
   ~Core();

private slots:
   void saveImage();
   void exit();
   void update();
   inline void printvec(glm::vec3 a)
   {
      fprintf(stderr, "%f, %f, %f", a.x, a.y, a.z);
   }

private:
   void raycast();
   Ray generateRay(int i, int j);
   glm::vec3 calculateColor(Ray origRay, int depth);
   glm::vec3 phong(glm::vec3 lightVector, glm::vec3 viewDirection, glm::vec3 normal, Material m);
   QRgb vec3ToQrgb(glm::vec3 c);
   bool getIntersectionWithScene(Ray r,Intersection* object, A_Object* startingObject = NULL);
   bool checkForShadowObject(Ray r, A_Object* startingObject, Intersection* hit);

private: // Members
   MainView* view_;
   QImage* image_;
   glm::vec3 camera_;
   glm::vec3 ambientLight_;
   double lightIntensity_;
   double worldMinWidth_;
   double worldMaxWidth_;
   double worldMinHeight_;
   double worldMaxHeight_;
   glm::vec3 background_;
   int imgWidth_, imgHeight_;
   QList<A_Object*> objects_;
   QList<Light> lights_;
};

#endif
