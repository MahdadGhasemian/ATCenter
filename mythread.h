#ifndef MYTHREAD_H
#define MYTHREAD_H

#include "QThread"
#include "delay.h"

class MyThread : public QThread
{
public:
    MyThread();
};

#endif // MYTHREAD_H
