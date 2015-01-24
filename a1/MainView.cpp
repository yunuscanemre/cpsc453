#include <MainView.h>
#include <GlWidget.h>
#include <QVBoxLayout>
#include <QImage>

MainView::MainView() 
{
   setupUi();
}

MainView::~MainView() 
{
}

void MainView::show()
{
   mainWindow_->show();
}

void MainView::setOrigImage(QImage* image)
{
   // opengl calls affect this widget
   original_->makeCurrent();
   original_->loadImage(image);
   modified_->makeCurrent();
   modified_->loadImage(image);
}

void MainView::setupUi()
{
   mainWindow_ = new QMainWindow();
   mainUi_ = new Ui::MainWindow();
   mainUi_->setupUi(mainWindow_);
   modified_ = new GlWidget(mainWindow_);
   original_ = new GlWidget(mainWindow_);
   QVBoxLayout* origImgLayout = new QVBoxLayout(mainUi_->origImgContainerWidget);
   origImgLayout->addWidget(original_);
   mainUi_->origImgContainerWidget->setLayout(origImgLayout);

   QVBoxLayout* modImgLayout = new QVBoxLayout(mainUi_->modImgContainerWidget);
   modImgLayout->addWidget(modified_);
   mainUi_->modImgContainerWidget->setLayout(modImgLayout);
}

void MainView::setQuantization(int level)
{
   // setup quantization matrix
   int quantize[255];
   std::fill_n(quantize, 255, 0);
   for (int i = 0; i < 256; i++)
   {
      int q = (int) floor(255 * floor(i * (level - 1) / 255.0) / (level - 1));
      quantize[i] = q;
   }
}

