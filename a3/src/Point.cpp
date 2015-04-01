
#include <Point.h>
#include <Helpers.h>

Point::Point()
{
   x_ = 0; y_ = 0; z_ = 0;
}

Point::Point(double p)
{
   x_ = p; y_ = p; z_ = p;
}

Point::Point(double x, double y, double z)
{
   x_ = x; y_ = y; z_ = z;
}

Point::~Point()
{}

