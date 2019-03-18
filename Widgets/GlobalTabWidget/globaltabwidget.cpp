#include "globaltabwidget.h"

//Constructor
GlobalTabWidget::GlobalTabWidget(QWidget *parent)
    : QTabWidget(parent)
{
    //Add bunker tab
    m_bunker_widget = new BunkerWidget();
    addTab(m_bunker_widget, tr("Bunker"));

    //Add MC tab
    m_mc_widget = new MCWidget();
    addTab(m_mc_widget, tr("MC"));

    //Add Nightclub tab
    m_nightclub_widget = new NightclubWidget();
    addTab(m_nightclub_widget, tr("Nightclub"));
}

//Destructor
GlobalTabWidget::~GlobalTabWidget()
{
}
