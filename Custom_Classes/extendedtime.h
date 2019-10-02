#ifndef EXTENDEDTIME_H
#define EXTENDEDTIME_H

#include <QTime>

//QTime cannot display hours over 23, this class can
class ExtendedTime : public QTime
{
    //Add a day counter to keep track of hours >= 24
    int m_days;

public:
    //Constructor/Destructor
    ExtendedTime(int p_hours = 0, int p_minutes = 0, int p_seconds = 0);
    ~ExtendedTime();

    //Override the isValid function : always true
    bool isValid();

    //Override the hour getter
    int hour() const;

    //Display function
    QString toString() const ;

    //Decrement one second
    void secondPassed();

    //Set time
    void setTime(int p_hours = 0, int p_minutes = 0, int p_seconds = 0);

    //Add time
    void addTime(int p_hours = 0, int p_minutes = 0, int p_seconds = 0);

    //Extended time uses the same assignment operator as QTime
    using QTime::operator=;

};

#endif // EXTENDEDTIME_H
