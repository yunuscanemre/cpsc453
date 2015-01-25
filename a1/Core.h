#ifndef CORE_H_
#define CORE_H_

#include <QObject>

class MainView;
class RgbImage;

class Core : public QObject
{
   Q_OBJECT

public:
   Core();
   ~Core();

private slots:
   void setQuantization(int level);
   void selectAnImageToOpen();
   void saveModifiedImage();

private: // Members
   MainView* view_;
   RgbImage* image_;
   RgbImage* modifiedImage_;
};

#endif
