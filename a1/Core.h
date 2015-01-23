#ifndef CORE_H_
#define CORE_H_

class MainView;
class RgbImage;

class Core
{
public:
   Core();
   ~Core();

private: // Members
   MainView* view_;
   RgbImage* image_;
};

#endif
