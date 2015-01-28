#include <MainView.h>
#include <Core.h>
#include <RgbImage.h>
#include <QFileDialog>
#include <QColor>
#include <stdio.h>
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

   qtConnect(view_, SIGNAL(dissolveChanged(double)), this,
         SLOT(setDissolve(double)));

   qtConnect(view_, SIGNAL(dissolveSelected(bool)), this,
         SLOT(selectDissolveImage()));

   qtConnect(view_, SIGNAL(openImageSelected(bool)), this,
         SLOT(selectAnImageToOpen()));

   qtConnect(view_, SIGNAL(saveImageSelected(bool)), this,
         SLOT(saveModifiedImage()));
}

Core::~Core()
{
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
   view_->setOrigImage(image_);
   view_->setModifiedImage(modifiedImage_);
}

void Core::selectDissolveImage()
{
   QString fileToLoad = QFileDialog::getOpenFileName(NULL,
         "Select a bmp image to open");
   if (fileToLoad.isNull())
      return;

   deletePointer(dissolveImage_);
   dissolveImage_ = new RgbImage(fileToLoad.toStdString().c_str());
   if(dissolveImage_->GetNumRows() != image_->GetNumRows() ||
      dissolveImage_->GetNumCols() != image_->GetNumCols())
   {
      QMessageBox::warning(NULL, "Images Are Not Same Size",
                           "Dissolve image must be the same size as the original image");
      return;
   }
   view_->setModifiedImage(image_);
   view_->enableDissolve();
}

void Core::saveModifiedImage()
{
   QString saveFile = QFileDialog::getSaveFileName(NULL,
         "Select save location");
   if (saveFile.isNull())
      return;
   modifiedImage_->WriteBmpFile(saveFile.toStdString().c_str());
}

void Core::setDissolve(double distance) // BONUS
{
   // FIX ? Images need to be the same size
   reInitializeModifiedImage();
   for (int i = 0; i < modifiedImage_->GetNumRows(); i++)
   {
      for (int j = 0; j < modifiedImage_->GetNumCols(); j++)
      {
         Pixel src = image_->GetRgbPixel(i, j);
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
         Pixel p = modifiedImage_->GetRgbPixel(i, j);
         double avrgLuminance = image_->GetAverageLuminance();
         Pixel blendedP = p.blend(Pixel(avrgLuminance), scale);
         modifiedImage_->SetRgbPixel(i, j, blendedP);
      }
   }
   view_->setModifiedImage(modifiedImage_);
}

void Core::setScale(int scale)
{
   reInitializeModifiedImage();

   for (uint i = 0; i < modifiedImage_->GetNumRows(); i++)
   {
      for (uint j = 0; j < modifiedImage_->GetNumCols(); j++)
      {
         uint scaledCol = scale*j;
         if(modifiedImage_->isValidPoint(i, scaledCol))
         {
            Pixel p = image_->GetRgbPixel(i, j);
            modifiedImage_->SetRgbPixel(i, scaledCol, p);
//            modifiedImage_->SetRgbPixel(i, j, Pixel(0));
//            for(uint s = j; j < scaledCol; j++)
//               modifiedImage_->SetRgbPixel(i, s, p);

         }
         else break; // if scale location out of bounds go onto next row
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
         Pixel p = modifiedImage_->GetRgbPixel(i, j);
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
         Pixel p = modifiedImage_->GetRgbPixel(i, j);
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
         Pixel p = modifiedImage_->GetRgbPixel(i, j);
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

   // reinitialize modified image
   modifiedImage_ = new RgbImage(image_);
}
