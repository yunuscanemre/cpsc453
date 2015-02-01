#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <MainView.h>
#include <Core.h>
#include <RgbImage.h>
#include <QFileDialog>
#include <QColor>
#include <Helpers.h>
#include <Pixel.h>
#include <QMessageBox>

Core::Core()
{
   image_ = NULL;
   modifiedImage_ = NULL;
   dissolveImage_ = NULL;
   view_ = new MainView();
   view_->show();
   selectAnImageToOpen();

   qtConnect(view_, SIGNAL(quantizationChanged(int)), this,
         SLOT(setQuantization(int)));

   qtConnect(view_, SIGNAL(brightnessChanged(double)), this,
         SLOT(setBrightness(double)));

   qtConnect(view_, SIGNAL(saturationChanged(double)), this,
         SLOT(setSaturation(double)));

   qtConnect(view_, SIGNAL(contrastChanged(double)), this,
         SLOT(setContrast(double)));

   qtConnect(view_, SIGNAL(scaleChanged(int)), this,
         SLOT(setScale(int)));

   qtConnect(view_, SIGNAL(rotationChanged(int)), this,
         SLOT(setRotation(int)));

   qtConnect(view_, SIGNAL(dissolveChanged(double)), this,
         SLOT(setDissolve(double)));

   qtConnect(view_, SIGNAL(dissolveSelected(bool)), this,
         SLOT(selectDissolveImage()));

   qtConnect(view_, SIGNAL(openImageSelected(bool)), this,
         SLOT(selectAnImageToOpen()));

   qtConnect(view_, SIGNAL(saveImageSelected(bool)), this,
         SLOT(saveModifiedImage()));

   qtConnect(view_, SIGNAL(exitSelected(bool)), this,
         SLOT(exit()));
}

void Core::exit()
{
   QCoreApplication::exit();
}

Core::~Core()
{
   deletePointer(dissolveImage_);
   deletePointer(modifiedImage_);
   deletePointer(image_);
   deletePointer(view_);
}

void Core::selectAnImageToOpen()
{
   QString fileToLoad = QFileDialog::getOpenFileName(NULL,
         "Select a bmp image to open");
   if (fileToLoad.isNull())
      return;

   deletePointer(modifiedImage_);
   deletePointer(image_);

   image_ = new RgbImage(fileToLoad.toStdString().c_str());
   modifiedImage_ = new RgbImage(fileToLoad.toStdString().c_str());
   view_->setModifiedImage(modifiedImage_);
   view_->setOrigImage(image_);
}

void Core::selectDissolveImage()
{
   QString fileToLoad = QFileDialog::getOpenFileName(NULL,
         "Select a bmp image to open");
   if (fileToLoad.isNull())
      return;

   reinitializeDissolveImage(fileToLoad);
   view_->setModifiedImage(image_);
   view_->enableDissolve();
}

void Core::reinitializeDissolveImage(QString fileToLoad)
{
   deletePointer(dissolveImage_);
   RgbImage aImage(fileToLoad.toStdString().c_str());
   if(aImage.GetNumRows() != image_->GetNumRows() ||
      aImage.GetNumCols() != image_->GetNumCols())
   {
      QMessageBox::warning(NULL, "NOTE",
                           "Note that dissolve image is not the same size"
                           "as the original image. Will NOT auto-scale.");
   }
   // set dissolve image to the max size the original image and dissolve image
   // can make combined.
   int rows = qMax(image_->GetNumRows(), aImage.GetNumRows());
   int cols = qMax(image_->GetNumCols(), aImage.GetNumCols());
   dissolveImage_ = new RgbImage(rows, cols, &aImage);

}

void Core::saveModifiedImage()
{
   QString saveFile = QFileDialog::getSaveFileName(NULL,
         "Select save location and enter file name");
   if (saveFile.isNull())
      return;
   modifiedImage_->WriteBmpFile(saveFile.toStdString().c_str());
}

void Core::setDissolve(double distance) // BONUS
{
   deletePointer(modifiedImage_);

   // modified image must be as big as the dissolve image, but
   // needs to contain the original image to begin with
   modifiedImage_ = new RgbImage(dissolveImage_->GetNumRows(),
         dissolveImage_->GetNumCols(), image_);

   for (int i = 0; i < dissolveImage_->GetNumRows(); i++)
   {
      for (int j = 0; j < dissolveImage_->GetNumCols(); j++)
      {
         Pixel src;
         if(image_->isValidPoint(i, j))
         {
            src = image_->GetRgbPixel(i, j);
         }
         Pixel dest = dissolveImage_->GetRgbPixel(i, j);
         Pixel blended = dest.blend(src, distance);
         modifiedImage_->SetRgbPixel(i, j, blended);

      }
   }
   view_->setModifiedImage(modifiedImage_);
}

void Core::setContrast(double scale) // BONUS
{
   reInitializeModifiedImage();

   for (int i = 0; i < modifiedImage_->GetNumRows(); i++)
   {
      for (int j = 0; j < modifiedImage_->GetNumCols(); j++)
      {
         Pixel p = image_->GetRgbPixel(i, j);
         double avrgLuminance = image_->GetAverageLuminance();
         Pixel blendedP = p.blend(Pixel(avrgLuminance), scale);
         modifiedImage_->SetRgbPixel(i, j, blendedP);
      }
   }
   view_->setModifiedImage(modifiedImage_);
}

void Core::setScale(int scale)
{
   if(scale <=1)
   {
      view_->setModifiedImage(image_);
      return;
   }

   reInitializeModifiedImage();

   for (uint currRow = 0; currRow < image_->GetNumRows(); currRow++)
   {
      for (uint currCol = 0; currCol < image_->GetNumCols(); currCol++)
      {
         uint scaledCol = scale*currCol;
         if(modifiedImage_->isValidPoint(currRow, scaledCol))
         {
            Pixel pToCopy =  image_->GetRgbPixel(currRow, currCol);
            modifiedImage_->SetRgbPixel(currRow, scaledCol, pToCopy);

            for(int j = scaledCol-1, count=1; count<scale && j>0; j--, count++)
            {
               modifiedImage_->SetRgbPixel(currRow, j, Pixel(0));
            }

         }
         else break; // if scale location out of bounds go onto next row
      }
   }
   view_->setModifiedImage(modifiedImage_);

}

void Core::setRotation(int rotation)
{
   if(rotation <= 0)
   {
      view_->setModifiedImage(image_);
      return;
   }

   reInitializeModifiedImage();
   double radRotation = (M_PI*(double)rotation)/180;
   for (int row = 0; row < image_->GetNumRows(); row++)
   {
      int newRow, newCol = 0;
      for (int col = 0; col < image_->GetNumCols(); col++)
      {
         newRow = trunc(row*cos(-radRotation) - col*sin(-radRotation)+0.5);
         newCol = trunc(row*sin(-radRotation) + col*cos(-radRotation)+0.5);
         if(modifiedImage_->isValidPoint(newRow, newCol))
         {
            Pixel p = image_->GetRgbPixel(row, col);
            modifiedImage_->SetRgbPixel(newRow, newCol, p);
         }
      }
   }
   view_->setModifiedImage(modifiedImage_);
}

void Core::setSaturation(double scale)
{
   reInitializeModifiedImage();

   for (int i = 0; i < modifiedImage_->GetNumRows(); i++)
   {
      for (int j = 0; j < modifiedImage_->GetNumCols(); j++)
      {
         Pixel p = image_->GetRgbPixel(i, j);
         Pixel blendedP = p.blend(p.luminancePixel(), scale);
         modifiedImage_->SetRgbPixel(i, j, blendedP);
      }
   }
   view_->setModifiedImage(modifiedImage_);
}

void Core::setBrightness(double scale)
{
   reInitializeModifiedImage();

   for (int i = 0; i < modifiedImage_->GetNumRows(); i++)
   {
      for (int j = 0; j < modifiedImage_->GetNumCols(); j++)
      {
         Pixel p = image_->GetRgbPixel(i, j);
         Pixel blendedP = p.blend(Pixel(0, 0, 0), scale);
         modifiedImage_->SetRgbPixel(i, j, blendedP);
      }
   }
   view_->setModifiedImage(modifiedImage_);
}

void Core::setQuantization(int level)
{
   reInitializeModifiedImage();

   // setup quantization matrix
   int quantize[256];
   std::fill_n(quantize, 256, 0);
   for (int i = 0; i < 256; i++)
   {
      int q = (int) floor(255 * floor(i * (level - 1) / 255.0) / (level - 1));
      quantize[i] = q;
   }

   // modify image and display it
   for (int i = 0; i < modifiedImage_->GetNumRows(); i++)
   {
      for (int j = 0; j < modifiedImage_->GetNumCols(); j++)
      {
         Pixel p = image_->GetRgbPixel(i, j);
         p.red = intToDoublePixel(quantize[p.redI()]);
         p.green = intToDoublePixel(quantize[p.greenI()]);
         p.blue = intToDoublePixel(quantize[p.blueI()]);

         modifiedImage_->SetRgbPixel(i, j, p);
      }
   }
   view_->setModifiedImage(modifiedImage_);
}

void Core::reInitializeModifiedImage()
{
   if (modifiedImage_ == NULL || image_ == NULL)
      return;
   deletePointer(modifiedImage_);

   // reinitialize modified image to just black
   modifiedImage_ = new RgbImage(image_->GetNumRows(), image_->GetNumCols());
}
