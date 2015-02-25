#ifndef CORE_H_
#define CORE_H_

#include <QObject>

class MainView;

class Core : public QObject
{
   Q_OBJECT

public:
   Core();
   ~Core();

private slots:
   void exit();


private:

private: // Members
   MainView* view_;
};

#endif
