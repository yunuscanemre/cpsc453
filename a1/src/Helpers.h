#ifndef HELPERS_H_
#define HELPERS_H_

#include <QObject>

uint doubleToIntPixel(double val);

double intToDoublePixel(uint val);

// Taking a refence to the pointer allows the original pointer to be set to null.
// Otherwise a copy of the pointer would be made and you would be setting the copy
// to null.
template<typename T>
void deletePointer(T*& toBeDeleted)
{
   if(toBeDeleted!=NULL)
   {
      delete toBeDeleted;
      toBeDeleted = NULL;
   }
}

template<typename T, typename B>
bool qtConnect(T& sender, const char* signal, B& receiver, const char* member,
               Qt::ConnectionType type = Qt::AutoConnection)
{
   return QObject::connect(dynamic_cast<QObject*>(&sender), signal,
                           dynamic_cast<QObject*>(&receiver), member, type);
}

template<typename T, typename B>
bool qtConnect(T& sender, const char* signal, B* receiver, const char* member,
               Qt::ConnectionType type = Qt::AutoConnection)
{
   return QObject::connect(dynamic_cast<QObject*>(&sender), signal,
                           dynamic_cast<QObject*>(receiver), member, type);
}

template<typename T, typename B>
bool qtConnect(T* sender, const char* signal, B& receiver, const char* member,
               Qt::ConnectionType type = Qt::AutoConnection)
{
   return QObject::connect(dynamic_cast<QObject*>(sender), signal,
                           dynamic_cast<QObject*>(&receiver), member, type);
}

template<typename T, typename B>
bool qtConnect(T* sender, const char* signal, B* receiver, const char* member,
               Qt::ConnectionType type = Qt::AutoConnection)
{
   return QObject::connect(dynamic_cast<QObject*>(sender), signal,
                           dynamic_cast<QObject*>(receiver), member, type);
}

#endif /* HELPERS_H_ */
