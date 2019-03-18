#ifndef NIGHTCLUBWIDGET_H
#define NIGHTCLUBWIDGET_H

#include <QWidget>

//The widget handling the nightclub
class NightclubWidget : public QWidget
{
    Q_OBJECT


public:
    //Constructor/Destructor
    NightclubWidget(QWidget *parent = nullptr);
    ~NightclubWidget();
};

#endif // NIGHTCLUBWIDGET_H
