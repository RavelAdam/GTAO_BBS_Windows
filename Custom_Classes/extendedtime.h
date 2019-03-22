#ifndef EXTENDEDTIME_H
#define EXTENDEDTIME_H

#include <QTime>

//QTime cannot display hours over 23, this class can
class ExtendedTime : public QTime
{

public:
    //Constructor/Destructor
    ExtendedTime(int p_hours = 0, int p_minutes = 0, int p_seconds = 0);
    ~ExtendedTime();

    //Override the isValid function : always true
    bool isValid();

    //Display function
    QString toString() const ;

    //Extended time uses the same assignment operator as QTime
    using QTime::operator=;

};

#endif // EXTENDEDTIME_H
