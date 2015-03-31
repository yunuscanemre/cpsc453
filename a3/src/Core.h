#ifndef CORE_H_
#define CORE_H_

#include <QObject>
#include <glm/glm.hpp>

class MainView;
class RgbImage;

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
//   void castRay(glm::vec3 camera, int i, int j);

private: // Members
   MainView* view_;
   RgbImage* image_;
   glm::vec3 camera_;
   int width_, height_;

};

#endif
