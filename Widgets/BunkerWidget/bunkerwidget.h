#ifndef BUNKERWIDGET_H
#define BUNKERWIDGET_H

#include <QCheckBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QProgressBar>
#include <QTimer>

//The widget handling the bunker
class BunkerWidget : public QWidget
{
    Q_OBJECT

    //----------------------------Variables----------------------------------//
    //Bunker upgrades
    bool m_has_equipment_upgrade;
    bool m_has_staff_upgrade;

    //Progress(current stock, research, research points until next unlock, supplies)
    quint8 m_stock, m_research, m_next_unlock, m_supplies;

    //Timers
    QTimer m_timer_stock, m_timer_research, m_timer_supplies;

    //----------------------------Variables-----------------------------------//
    //Progress caps
    const quint8
    m_max_stock = 100,
    m_max_research = 60,
    m_max_next_unlock = 100,
    m_max_supplies = 100;

public:
    //Constructor/Destructor
    BunkerWidget(QWidget *parent = nullptr);
    ~BunkerWidget();
};

#endif // BUNKERWIDGET_H
