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
   void selectDissolveImage();
   void saveModifiedImage();
   void exit();

   void setQuantization(int level);
   void setBrightness(double scale);
   void setSaturation(double scale);
   void setScale(int scale);
   void setRotation(int rotation);
   void setContrast(double scale); // BONUS
   void setDissolve(double distance); // BONUS

private:
   void reInitializeModifiedImage();
   void reinitializeDissolveImage(QString fileToLoadFrom);

private: // Members
   MainView* view_;
   RgbImage* image_;
   RgbImage* modifiedImage_;
   RgbImage* dissolveImage_;
};

#endif
