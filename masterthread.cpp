#include "masterthread.h"
#include "QDebug"

MasterThread::MasterThread(QString s) : name(s)
{

}

// We overrides the QThread's run() method here
// run() will be called when a thread starts
// the code will be shared by all threads

void MasterThread::run()
{
//   qDebug() << this->name ;

   delay_ms(1);

}
