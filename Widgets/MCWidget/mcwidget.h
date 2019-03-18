#ifndef MCWIDGET_H
#define MCWIDGET_H

#include <QWidget>

//The widget handling the MC businesses
class MCWidget : public QWidget
{
    Q_OBJECT


public:
    //Constructor/Destructor
    MCWidget(QWidget *parent = nullptr);
    ~MCWidget();
};

#endif // BUNKERWIDGET_H
