#include <MainView.h>
#include <GlWidget.h>
#include <QVBoxLayout>
#include <RgbImage.h>
#include <QPixmap>
#include <Helpers.h>
#include <QGraphicsPixmapItem>

MainView::MainView() 
{
   setupUi();

   qtConnect(mainUi_->actionSaveImage, SIGNAL(triggered(bool)),
             this, SIGNAL(saveImageSelected(bool)));

   qtConnect(mainUi_->actionExit, SIGNAL(triggered(bool)),
             this, SIGNAL(exitSelected(bool)));
}

MainView::~MainView() 
{
}

void MainView::show()
{
   mainWindow_->show();
}

void MainView::setImage(QImage image)
{
//   glwidget_->makeCurrent();
//   glwidget_->setPixmap(QPixmap::fromImage(image));
   QGraphicsPixmapItem* i = new QGraphicsPixmapItem(QPixmap::fromImage(image));
   QGraphicsScene* s = new QGraphicsScene();
   s->addItem(i);
   mainUi_->imgContainerWidget->setScene(s);
//   glwidget_->updateGL();
//   mainUi_->imgContainerWidget->setPixmap(QPixmap::fromImage(image));
}


void MainView::setupUi()
{
   mainWindow_ = new QMainWindow();
   mainUi_ = new Ui::MainWindow();
   mainUi_->setupUi(mainWindow_);
//   glwidget_ = new GlWidget(mainWindow_);
//   QVBoxLayout* imgLayout = new QVBoxLayout(mainUi_->imgContainerWidget);
//   imgLayout->addWidget(glwidget_);
//   mainUi_->imgContainerWidget->setLayout(imgLayout);

}



