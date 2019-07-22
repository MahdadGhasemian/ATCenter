#ifndef MASTERTHREAD_H
#define MASTERTHREAD_H

#include "QThread"
#include "QString"
#include "delay.h"

class MasterThread : public QThread
{
public:
    // constructor
    // set name using initializer
    explicit MasterThread(QString s);

    // overriding the QThread's run() method
    void run();
private:
    QString name;
};

#endif // MASTERTHREAD_H
