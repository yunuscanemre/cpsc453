#ifndef CORE_H_
#define CORE_H_

class MainView;
class QImage;

class Core
{
public:
   Core();
   ~Core();

private: // Members
   MainView* view_;
   QImage* image_;
};

#endif
