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
   void selectAnImageToOpen();
   void saveModifiedImage();

   void setQuantization(int level);
   void setBrightness(double scale);
   void setSaturation(double scale);
   void setContrast(double scale);

private:
   void reInitializeModifiedImage();

private: // Members
   MainView* view_;
   RgbImage* image_;
   RgbImage* modifiedImage_;
};

#endif
