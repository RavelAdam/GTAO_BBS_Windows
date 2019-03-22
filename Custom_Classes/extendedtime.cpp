#include "extendedtime.h"

//Constructor
ExtendedTime::ExtendedTime(int p_hours, int p_minutes, int p_seconds)
    : QTime(p_hours, p_minutes, p_seconds)
{
}

//Destructor
ExtendedTime::~ExtendedTime()
{
}

//In the QTime class, isValid is true if hours <= 23 and false otherwise
//Override it to always be true
bool ExtendedTime::isValid(){ return true; }

//Override the display function to display a number of hours > 23
QString ExtendedTime::toString() const
{
    //Add an extra zero next to each number if it is < 10
    QString extra_zero_hours = "", extra_zero_minutes = "", extra_zero_seconds = "";
    if (hour() < 10) extra_zero_hours = "0";
    if (minute() < 10) extra_zero_minutes = "0";
    if (second() < 10) extra_zero_seconds = "0";
    return extra_zero_hours + QString::number(hour()) + ":" +
           extra_zero_minutes + QString::number(minute()) + ":" +
           extra_zero_seconds + QString::number(second());
}
