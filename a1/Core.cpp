#include <MainView.h>
#include <Core.h>
#include <RgbImage.h>
#include <QFileDialog>
#include <QColor>
#include <stdio.h>
#include <Helpers.h>

Core::Core()
{
   image_ = NULL;
   modifiedImage_ = NULL;
   view_ = new MainView();
   view_->show();
   selectAnImageToOpen();

   qtConnect(view_, SIGNAL(quantizationChanged(int)),
             this, SLOT(setQuantization(int)));

   qtConnect(view_, SIGNAL(openImageSelected(bool)),
             this, SLOT(selectAnImageToOpen()));

   qtConnect(view_, SIGNAL(saveImageSelected(bool)),
             this, SLOT(saveModifiedImage()));
}

Core::~Core()
{
   deletePointer(modifiedImage_);
   deletePointer(image_);
   deletePointer(view_);
}

void Core::selectAnImageToOpen()
{
   QString fileToLoad = QFileDialog::getOpenFileName(NULL, "Select a bmp image to open");
   if(fileToLoad.isNull())
      return;

   deletePointer(modifiedImage_);
   deletePointer(image_);

   image_ = new RgbImage(fileToLoad.toStdString().c_str());
   modifiedImage_ = new RgbImage(fileToLoad.toStdString().c_str());
   view_->setOrigImage(image_);
   view_->setModifiedImage(modifiedImage_);
}

void Core::saveModifiedImage()
{
   QString saveFile = QFileDialog::getSaveFileName(NULL, "Select save location");
   if(saveFile.isNull())
      return;
   modifiedImage_->WriteBmpFile(saveFile.toStdString().c_str());
}

void Core::setQuantization(int level)
{
   if(modifiedImage_==NULL || image_==NULL)
      return;
   deletePointer(modifiedImage_);

   // reinitialize modified image
   modifiedImage_ = new RgbImage(image_);

   // setup quantization matrix
   int quantize[256];
   std::fill_n(quantize, 256, 0);
   for(int i = 0; i < 256; i++)
   {
      int q = (int) floor(255 * floor(i * (level - 1) / 255.0) / (level - 1));
      quantize[i] = q;
   }

   // modify image and display it
   for(int i = 0; i < modifiedImage_->GetNumRows(); i++)
   {
      for(int j = 0; j < modifiedImage_->GetNumCols(); j++)
      {
          double r=-1, g=-1, b=-1;
          modifiedImage_->GetRgbPixel(i, j, &r, &g, &b);
          double newRed = intToDoublePixel(quantize[doubleToIntPixel(r)]);
          double newGreen = intToDoublePixel(quantize[doubleToIntPixel(g)]);
          double newBlue = intToDoublePixel(quantize[doubleToIntPixel(b)]);

          modifiedImage_->SetRgbPixelf(i, j, newRed, newGreen, newBlue);
      }
   }
    view_->setModifiedImage(modifiedImage_);
}
