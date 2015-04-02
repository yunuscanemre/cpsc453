#ifndef PIXEL_H_
#define PIXEL_H_

#include <glm/glm.hpp>

struct Pixel
{
   Pixel();
   Pixel(double color);
   Pixel(glm::vec3 p);
   Pixel(double r, double g, double b);
   ~Pixel();

   Pixel blend(const Pixel& other, double scale);
   double luminance();
   Pixel luminancePixel();

   void setRedF(double r);
   void setRedI(int r);
   void setGreenF(double g);
   void setGreenI(int g);
   void setBlueF(double b);
   void setBlueI(int b);
   double redF();
   int redI();
   double greenF();
   int greenI();
   double blueF();
   int blueI();

   double red;
   double green;
   double blue;

};

#endif
