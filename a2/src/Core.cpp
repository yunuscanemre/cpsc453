#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <MainView.h>
#include <Core.h>
#include <QFileDialog>
#include <QColor>
#include <Helpers.h>
#include <QMessageBox>

Core::Core()
{
   view_ = new MainView();
   view_->show();
}

void Core::exit()
{
   QCoreApplication::exit();
}

Core::~Core()
{
   deletePointer(view_);
}
