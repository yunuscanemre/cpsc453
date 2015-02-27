#ifndef CORE_H_
#define CORE_H_

#include <QObject>
#include <GL/gl.h>
#include <QVector>

class MainView;
class MD2;


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
   MD2* md2_;
   QVector<GLfloat>* vertices_;
};

#endif
