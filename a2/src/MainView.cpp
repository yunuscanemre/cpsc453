#include <MainView.h>
#include <GlWidget.h>
#include <QVBoxLayout>

#include <Helpers.h>

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

void MainView::setupUi()
{
   mainWindow_ = new QMainWindow();
   mainUi_ = new Ui::MainWindow();
   mainUi_->setupUi(mainWindow_);

   scene_ = new GlWidget(mainWindow_);
   QVBoxLayout* layout = new QVBoxLayout(mainUi_->containerWidget);
   layout->addWidget(scene_);
   mainUi_->containerWidget->setLayout(layout);
}



