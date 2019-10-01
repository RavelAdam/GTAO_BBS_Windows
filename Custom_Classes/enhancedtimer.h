#ifndef ENHANCEDTIMER_H
#define ENHANCEDTIMER_H

#include "extendedtime.h"

#include <QTime>
#include <QTimer>

//An enhanced timer, represented by a 1-second QTimer passing every second and a
//QTime containing the time left
class EnhancedTimer : public QTimer
{
    Q_OBJECT

    //The time left on the actual timer
    ExtendedTime m_time_left;

public:
    //Constructor/Destructor
    EnhancedTimer(int p_hours = 0, int p_minutes = 0, int p_seconds = 0, QObject* parent = nullptr);
    ~EnhancedTimer();

    //Time left getter
    ExtendedTime getTimeLeft();

    //Time left setter
    void setTimer(int p_hours = 0, int p_minutes = 0, int p_seconds = 0);

    //Check if the timer is over
    bool isOver();

signals:
    //Signal called every second (send a QString with the time left)
    void onValueChanged(QString);

    //Signal called on timeout
    void onTimeout();

public slots:

    //Update the timer every second
    void NextSecond();
};

#endif // ENHANCEDTIMER_H
