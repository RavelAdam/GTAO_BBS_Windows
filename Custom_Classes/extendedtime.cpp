#include "extendedtime.h"
#include <QtDebug>

//Constructor
ExtendedTime::ExtendedTime(int p_hours, int p_minutes, int p_seconds)
{
    m_days = 0;
    while (p_hours >= 24)
    {
        p_hours -= 24;
        m_days++;
    }
    setHMS(p_hours, p_minutes, p_seconds);
}

//Destructor
ExtendedTime::~ExtendedTime()
{
}

//In the QTime class, isValid is true if hours <= 23 and false otherwise
//Override it to always be true
bool ExtendedTime::isValid(){ return true; }

//Override the hour getter
int ExtendedTime::hour() const{ return QTime::hour() + 24 * m_days; }

//Decrement one second
void ExtendedTime::secondPassed()
{
    if (m_days > 0 && hour() == 0 && minute() == 0 && second() == 0)
    {
        m_days--;
        setHMS(23, 59, 59);
    }
    else setTime(hour(), minute(), second() - 1);
}

//Set Time
void ExtendedTime::setTime(int p_hours, int p_minutes, int p_seconds)
{
    if (p_seconds < 0)
    {
        p_seconds += 60;
        p_minutes--;
    }

    if (p_minutes < 0)
    {
        p_minutes += 60;
        p_hours--;
    }

    m_days = 0;
    while (p_hours >= 24)
    {
        p_hours -= 24;
        m_days++;
    }
    setHMS(p_hours, p_minutes, p_seconds);
}

//Add Time
void ExtendedTime::addTime(int p_hours, int p_minutes, int p_seconds)
{
    p_seconds += second();
    if (p_seconds >= 60)
    {
        p_seconds -= 60;
        p_minutes++;
    }

    p_minutes += minute();
    if (p_minutes >= 60)
    {
        p_minutes -= 60;
        p_hours++;
    }

    p_hours += QTime::hour();
    while (p_hours >= 24)
    {
        p_hours -= 24;
        m_days++;
    }
    setHMS(p_hours, p_minutes, p_seconds);
}

//Override the display function to display a number of hours > 23
QString ExtendedTime::toString() const
{
    return QString::number(hour()) + ":" + QString::number(minute()) + ":" + QString::number(second());
}
