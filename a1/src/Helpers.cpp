
#include <Helpers.h>

uint doubleToIntPixel(double val)
{
   return (val*255.0 + 0.5);
}

double intToDoublePixel(uint val)
{
   return ((double)val - 0.5)/255.0;
}

