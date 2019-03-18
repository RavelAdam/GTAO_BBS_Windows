#ifndef BUNKERWIDGET_H
#define BUNKERWIDGET_H

#include <QWidget>

//The widget handling the bunker
class BunkerWidget : public QWidget
{
    Q_OBJECT


public:
    //Constructor/Destructor
    BunkerWidget(QWidget *parent = nullptr);
    ~BunkerWidget();
};

#endif // BUNKERWIDGET_H
