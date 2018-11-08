#include "sleeper.h"
 void Sleeper::delay()
 {
     QTime dieTime= QTime::currentTime().addMSecs(200);
     while (QTime::currentTime() < dieTime)
         QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
 }
