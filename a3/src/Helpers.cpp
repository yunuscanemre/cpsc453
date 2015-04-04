
#include <Helpers.h>

uint doubleToIntPixel(double val)
{
   uint v = qMin((int)(val*255.0 + 0.5), 255);
//   fprintf(stderr, "%f -> %d \n", val, v);
   return v;
}

double intToDoublePixel(uint val)
{
   return ((double)val - 0.5)/255.0;
}

