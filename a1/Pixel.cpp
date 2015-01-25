
#include <Pixel.h>
#include <Helpers.h>

Pixel::Pixel()
{
   red = 0; green = 0; blue = 0;
}

Pixel::Pixel(double color)
{
   red = color; green = color; blue = color;
}

Pixel::Pixel(double r, double g, double b)
{
   red = r; green = g; blue = b;
}

Pixel::~Pixel()
{}

/*
 * will return new Pixel with blended rgb values
 */
Pixel Pixel::blend(const Pixel& other, double scale)
{
   Pixel newPixel;
   newPixel.red = (1-scale)*other.red + scale*this->red;
   newPixel.green = (1-scale)*other.green + scale*this->green;
   newPixel.blue = (1-scale)*other.blue + scale*this->blue;
   return newPixel;
}

double Pixel::luminance()
{
   return (red * 0.3 + green * 0.59 + blue * 0.11);
}

Pixel Pixel::luminancePixel()
{
   return Pixel(luminance());
}

void Pixel::setRedI(int r)
{
   red = intToDoublePixel(r);
}

void Pixel::setGreenI(int g)
{
   green = intToDoublePixel(g);
}

void Pixel::setBlueI(int b)
{
   blue = intToDoublePixel(b);
}

int Pixel::redI()
{
   return doubleToIntPixel(red);
}

int Pixel::greenI()
{
   return doubleToIntPixel(green);
}

int Pixel::blueI()
{
   return doubleToIntPixel(blue);
}
