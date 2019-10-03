#include "enhancedtimer.h"

//Constructor
EnhancedTimer::EnhancedTimer(int p_hours, int p_minutes, int p_seconds, QObject* parent)
    : QTimer(parent)
{
    //Initialize the time left
    m_time_left = ExtendedTime(p_hours, p_minutes, p_seconds);

    //Since milliseconds aren't needed, the 1-second Timer will stock to seconds in terms of accuracy
    setTimerType(Qt::VeryCoarseTimer);
    setInterval(1000);

    //Call the NextSecond() slot for every active second passed
    connect(this, SIGNAL(timeout()), this, SLOT(NextSecond()));
}

//Destructor
EnhancedTimer::~EnhancedTimer()
{
}

//Override the display function
QString EnhancedTimer::toString() const
{
    if (isActive())return m_time_left.toString();
    else return "INACTIVE";
}

//Time left getter
ExtendedTime EnhancedTimer::getTimeLeft(){ return m_time_left; }

//Time left setter
void EnhancedTimer::setTimer(int p_hours, int p_minutes, int p_seconds)
{
    m_time_left.setTime(p_hours, p_minutes, p_seconds);
    emit onValueChanged(toString());
}

//Check if the timer is over
bool EnhancedTimer::isOver()
{
    return (m_time_left.hour() == 0 &&
            m_time_left.minute() == 0 &&
            m_time_left.second() == 0);
}

void EnhancedTimer::addTime(int p_hours, int p_minutes, int p_seconds)
{
    m_time_left.addTime(p_hours, p_minutes, p_seconds);
    emit onValueChanged(toString());
}

//Slot updating the timer every second
void EnhancedTimer::NextSecond()
{
    //If the timer is not over
    if (!isOver())
    {
        //Decrement the time left
        m_time_left.secondPassed();

        //Proceed to the next second
        start();
        emit onValueChanged(toString());
    }

    //If the timer is over, stop it
    else
    {
        stop();
        emit onTimeout();
    }
}
