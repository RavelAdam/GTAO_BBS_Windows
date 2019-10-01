#include "extendedtime.h"
#include <QtDebug>

//Constructor
ExtendedTime::ExtendedTime(int p_hours, int p_minutes, int p_seconds)
{
    m_days = 0;
    while (p_hours >= 24){
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

//Override the display function to display a number of hours > 23
QString ExtendedTime::toString() const
{
    return QString::number(hour()) + ":" + QString::number(minute()) + ":" + QString::number(second());
}
