#ifndef ENHANCEDTIMER_H
#define ENHANCEDTIMER_H

#include <QTimer>

//An enhanced QTimer, with the ability to be paused,
class EnhancedTimer : public QTimer
{
    Q_OBJECT

public:
    //Constructor/Destructor
    EnhancedTimer(QObject  *parent = nullptr);
    ~EnhancedTimer();
};

#endif // ENHANCEDTIMER_H
