#include <MainView.h>

MainView::MainView() 
{
   mainWindow_ = new QMainWindow();
   mainUi_ = new Ui::MainWindow();
   mainUi_->setupUi(mainWindow_);
}

MainView::~MainView() 
{
}

void MainView::show()
{
   mainWindow_->show();
}
