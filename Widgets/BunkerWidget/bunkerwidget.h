#ifndef BUNKERWIDGET_H
#define BUNKERWIDGET_H

#include "Custom_Classes/enhancedtimer.h"

#include <QCheckBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>

//The widget handling the bunker
class BunkerWidget : public QWidget
{
    Q_OBJECT

    //----------------------------Variables----------------------------------//
    //Bunker upgrades
    bool m_has_equipment_upgrade, m_has_staff_upgrade;

    //Progress(current stock, research, research points until next unlock, supplies,
    //full stock, empty supplies)
    int m_stock, m_research, m_next_unlock, m_supplies;
    bool m_stock_is_full, m_supplies_are_empty;


    //Timers
    EnhancedTimer m_timer_stock, m_timer_research, m_timer_supplies;

    //----------------------------Constants-----------------------------------//
    //Progress caps
    const int
    m_max_stock = 100,
    m_max_research = 60,
    m_max_next_unlock = 100,
    m_max_supplies = 100;

    //Supplies bundle size
    const int m_supplies_bundle_size = 20;

public:
    //Constructor/Destructor
    BunkerWidget(QWidget *parent = nullptr);
    ~BunkerWidget();

signals:
    //Progress bar values changed
    void OnStockChanged(int p_new_stock_value);
    void OnSuppliesChanged(int p_new_supplies_value);

public slots:
    //Action buttons
    void StealSupplies();
    void StockSold();
    void ResetBunker();
};

#endif // BUNKERWIDGET_H
