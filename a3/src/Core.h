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
   glm::vec3 calculateColor(Ray origRay);
   QRgb vec3ToQrgb(glm::vec3 c);
   bool getIntersectionWithScene(Ray r, Intersection* object);
   bool checkForShadowObject(Ray r, A_Object* startingObject, Intersection* hit);

private: // Members
   MainView* view_;
   QImage* image_;
   glm::vec3 camera_;
   glm::vec3 lightPosition_;
   glm::vec3 ambientLight_;
   double lightIntensity_;
   double worldMinWidth_;
   double worldMaxWidth_;
   double worldMinHeight_;
   double worldMaxHeight_;
   int imgWidth_, imgHeight_;
   QList<A_Object*> objects_;
};

#endif
