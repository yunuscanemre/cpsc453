#include <QObject>
#include <QApplication>
#include <stdio.h>
#include <Core.h>

int main(int argc, char *argv[])
{

   QApplication app(argc, argv);

   Core core;

   return app.exec();
}
