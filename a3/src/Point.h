#ifndef POINT_H_
#define POINT_H_

struct Point
{
   Point();
   Point(double p);
   Point(double x, double y, double z);
   ~Point();

   double x_;
   double y_;
   double z_;
};

#endif
