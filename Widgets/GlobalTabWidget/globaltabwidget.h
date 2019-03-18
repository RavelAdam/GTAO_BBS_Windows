#ifndef GLOBALTABWIDGET_H
#define GLOBALTABWIDGET_H

#include "Widgets/BunkerWidget/bunkerwidget.h"
#include "Widgets/MCWidget/mcwidget.h"
#include "Widgets/NightclubWidget/nightclubwidget.h"

#include <QTabBar>
#include <QTabWidget>

//The global widget containing all of the different tabs (Bunker, MC, Nightclub, etc.)
class GlobalTabWidget : public QTabWidget
{
    Q_OBJECT

    //The bunker tab
    BunkerWidget* m_bunker_widget;

    //The MC tab
    MCWidget* m_mc_widget;

    //The nightclub tab
    NightclubWidget* m_nightclub_widget;

public:
    //Constructor/Destructor
    GlobalTabWidget(QWidget *parent = nullptr);
    ~GlobalTabWidget();
};

#endif // GLOBALTABWIDGET_H
