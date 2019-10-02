#ifndef BUNKERWIDGET_H
#define BUNKERWIDGET_H

#include "Custom_Classes/enhancedtimer.h"

#include <QButtonGroup>
#include <QCheckBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QRadioButton>

//The widget handling the bunker
class BunkerWidget : public QWidget
{
    Q_OBJECT

    //----------------------------Variables----------------------------------//
    //Bunker upgrades
    bool m_has_equipment_upgrade, m_has_staff_upgrade;

    //Staff assigned in each domain
    bool m_staff_is_manufacturing, m_staff_is_both_manufacturing_research, m_staff_is_researching;

    //Progress(current stock, research and supplies,
    //full stock, empty supplies)
    int m_stock, m_research, m_supplies;
    bool m_stock_is_full, m_supplies_are_empty;

    //Boolean indicating if Manufacturing/Research is paused
    bool m_bunker_is_paused;

    //Buttons
    QPushButton* m_button_start_pause_manuf_research;
    QPushButton* m_button_supplies_bought_arrived;

    //Radio Buttons
    QRadioButton* m_rbutton_staff_manuf;
    QRadioButton* m_rbutton_staff_research;
    QRadioButton* m_rbutton_staff_both;

    //Timers
    EnhancedTimer* m_timer_next_stock;
    EnhancedTimer* m_timer_full_stock;
    EnhancedTimer* m_timer_next_research;
    EnhancedTimer* m_timer_research_unlock;
    EnhancedTimer* m_timer_next_supply;
    EnhancedTimer* m_timer_empty_supplies;
    EnhancedTimer* m_timer_supplies_bought;

    //----------------------------Constants-----------------------------------//
    //Progress caps
    const int
    m_max_stock = 100,
    m_max_research = 100,
    m_max_supplies = 100;

    //Supplies bundle size
    const int m_supplies_bundle_size = 20;

public:
    //Constructor/Destructor
    BunkerWidget(QWidget *parent = nullptr);
    ~BunkerWidget();

    //Start/Pause production
    void Start();
    void Pause();
    void StartManufacturing();
    void PauseManufacturing();
    void StartResearch();
    void PauseResearch();
    void StartSupplies();
    void PauseSupplies();

    //Timers
    void SetStockTimers();
    void SetResearchTimers();
    void SetSuppliesTimers();

signals:
    //Progress bar values changed
    void OnStockChanged(int p_new_stock_value);
    void OnResearchChanged(int p_new_research_value);
    void OnSuppliesChanged(int p_new_supplies_value);

public slots:

    //Action buttons
    void StartPause();
    void SuppliesBought();
    void SuppliesArrived();
    void StealSupplies();
    void StockSold();
    void SellMissionCancelled();
    void ResetBunker();

    //Stock/Research/Supplies Change;
    void StockUnitProduced();
    void ResearchUnitProduced();
    void SupplyUnitConsumed();

    //Checkboxes
    void setEquipmentUpgrade(int);
    void setStaffUpgrade(int);

    //Radio buttons
    void setStaffManagement();
};

#endif // BUNKERWIDGET_H
