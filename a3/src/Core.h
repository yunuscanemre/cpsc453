#ifndef CORE_H_
#define CORE_H_

#include <QObject>
#include <glm/glm.hpp>
#include <Ray.h>

class MainView;
class RgbImage;
class Material;

class Core : public QObject
{
   Q_OBJECT

public:
   Core();
   ~Core();

private slots:
   void saveImage();
   void exit();


private:
   void raycast();
   Ray generateRay(int i, int j);
   glm::vec3 calculateColor(Material* material, glm::vec3 normal, glm::vec3 viewDirection,
                       glm::vec3 lightVector);

private: // Members
   MainView* view_;
   RgbImage* image_;
   glm::vec3 camera_;
   glm::vec3 lightPosition_;
   glm::vec3 ambientLight_;
   double lightIntensity_;
   double worldMinWidth_;
   double worldMaxWidth_;
   double worldMinHeight_;
   double worldMaxHeight_;
   int imgWidth_, imgHeight_;

};

#endif
