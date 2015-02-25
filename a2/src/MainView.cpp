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
}



