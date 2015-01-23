#include <MainView.h>
#include <Helpers.h>
#include <Core.h>

Core::Core()
{
   view_ = new MainView();
   view_->show();
}

Core::~Core()
{
   deletePointer(view_);
}
