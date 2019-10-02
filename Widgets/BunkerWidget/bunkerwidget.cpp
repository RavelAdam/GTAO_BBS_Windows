#include "bunkerwidget.h"

//Constructor
BunkerWidget::BunkerWidget(QWidget *parent)
    : QWidget(parent)
{
    //----------------------------Variable initializations----------------------------------//
    //Variables
    m_has_equipment_upgrade = m_has_staff_upgrade = false;
    m_staff_is_manufacturing = true;
    m_staff_is_researching = m_staff_is_both_manufacturing_research = false;
    m_bunker_is_paused = true;
    m_stock = m_research = 0;
    m_supplies = 100;
    m_stock_is_full = false;
    m_supplies_are_empty = true;

    //Timers
    m_timer_next_stock = new EnhancedTimer();
    m_timer_full_stock = new EnhancedTimer();
    m_timer_next_research = new EnhancedTimer();
    m_timer_research_unlock = new EnhancedTimer();
    m_timer_next_supply = new EnhancedTimer();
    m_timer_empty_supplies = new EnhancedTimer();
    m_timer_supplies_bought = new EnhancedTimer();

    //-----------------------------------Main Layout----------------------------------------//
    //Set main layout of the bunker widget
    QGridLayout* bunker_widget_layout = new QGridLayout();
    setLayout(bunker_widget_layout);

    //------------------------------------Upgrades/Staff------------------------------------------//
    //Set the GroupBox containing the bunker upgrades and the staff management
    QGroupBox* upgrades_staff_management_groupbox = new QGroupBox(tr("Upgrades / Staff Management"));
    bunker_widget_layout->addWidget(upgrades_staff_management_groupbox, 2, 0, 1, 2);
    QVBoxLayout* upgrades_staff_management_groupbox_layout = new QVBoxLayout();
    upgrades_staff_management_groupbox->setLayout(upgrades_staff_management_groupbox_layout);

    //Add the upgrades checkboxes to the upgrades/staff GroupBox
    QCheckBox* equipment_upgrade_checkbox = new QCheckBox(tr("Equipment Upgrade"));
    equipment_upgrade_checkbox->setChecked(m_has_equipment_upgrade);
    upgrades_staff_management_groupbox_layout->addWidget(equipment_upgrade_checkbox);
    QCheckBox* staff_upgrade_checkbox = new QCheckBox(tr("Staff Upgrade"));
    staff_upgrade_checkbox->setChecked(m_has_staff_upgrade);
    upgrades_staff_management_groupbox_layout->addWidget(staff_upgrade_checkbox);

    //-----Add staff management RadioButtons to the upgrades/staff Groupbox-----//
    //Staff Management Layout / Button Group
    QHBoxLayout* staff_management_rbuttons_layout = new QHBoxLayout();
    upgrades_staff_management_groupbox_layout->addLayout(staff_management_rbuttons_layout);
    QButtonGroup* staff_management_bgroup = new QButtonGroup();

    //Manufacturing only button
    m_rbutton_staff_manuf = new QRadioButton(tr("Manufacturing only"));
    m_rbutton_staff_manuf->setChecked(m_staff_is_manufacturing);
    staff_management_rbuttons_layout->addWidget(m_rbutton_staff_manuf);
    staff_management_bgroup->addButton(m_rbutton_staff_manuf);

    //Both Manufacturing and Research
    m_rbutton_staff_both = new QRadioButton(tr("Both Manufacturing / Research"));
    m_rbutton_staff_both->setChecked(m_staff_is_both_manufacturing_research);
    staff_management_rbuttons_layout->addWidget(m_rbutton_staff_both);
    staff_management_bgroup->addButton(m_rbutton_staff_both);

    //Research only button
    m_rbutton_staff_research = new QRadioButton(tr("Research only"));
    m_rbutton_staff_research->setChecked(m_staff_is_researching);
    staff_management_rbuttons_layout->addWidget(m_rbutton_staff_research);
    staff_management_bgroup->addButton(m_rbutton_staff_research);

    //------------------------------------Progress------------------------------------------//
    //Set the GroupBox containing the progress bars
    QGroupBox* progress_bar_groupbox = new QGroupBox(tr("Progress"));
    bunker_widget_layout->addWidget(progress_bar_groupbox, 1, 0, 1, 1);
    QFormLayout* progress_bar_groupbox_layout = new QFormLayout();
    progress_bar_groupbox->setLayout(progress_bar_groupbox_layout);

    //-----Add the progress bars to the progress GroupBox-----/
    //Stock bar
    QProgressBar* stock_progress_bar = new QProgressBar();
    stock_progress_bar->setMinimum(0);
    stock_progress_bar->setMaximum(m_max_stock);
    stock_progress_bar->setValue(m_stock);
    stock_progress_bar->setFormat("%v/" + QString::number(m_max_stock));
    stock_progress_bar->setAlignment(Qt::AlignCenter);
    progress_bar_groupbox_layout->addRow(tr("Stock"), stock_progress_bar);

    //Research bar
    QProgressBar* research_progress_bar = new QProgressBar();
    research_progress_bar->setMinimum(0);
    research_progress_bar->setMaximum(m_max_research);
    research_progress_bar->setValue(m_research);
    research_progress_bar->setFormat("%v/" + QString::number(m_max_research));
    research_progress_bar->setAlignment(Qt::AlignCenter);
    progress_bar_groupbox_layout->addRow(tr("Research"), research_progress_bar);

    //Supplies bar
    QProgressBar* supplies_progress_bar = new QProgressBar();
    supplies_progress_bar->setMinimum(0);
    supplies_progress_bar->setMaximum(m_max_supplies);
    supplies_progress_bar->setValue(m_supplies);
    supplies_progress_bar->setFormat("%v/" + QString::number(m_max_supplies));
    supplies_progress_bar->setAlignment(Qt::AlignCenter);
    progress_bar_groupbox_layout->addRow(tr("Supplies"), supplies_progress_bar);

    //------------------------------------Timers------------------------------------------//
    //Set the GroupBox containing the timers
    QGroupBox* timers_groupbox = new QGroupBox(tr("Timers"));
    bunker_widget_layout->addWidget(timers_groupbox, 1, 1, 1, 1);
    QFormLayout* timers_groupbox_layout = new QFormLayout();
    timers_groupbox->setLayout(timers_groupbox_layout);

    //-----Add the timers to the timer GroupBox-----/

    //Next Stock Unit Timer
    QLabel* label_timer_next_stock = new QLabel(m_timer_next_stock->getTimeLeft().toString());
    timers_groupbox_layout->addRow(tr("Next stock unit in:"), label_timer_next_stock);

    //Full Stock Timer
    QLabel* label_timer_full_stock = new QLabel(m_timer_full_stock->getTimeLeft().toString());
    timers_groupbox_layout->addRow(tr("Stock full:"), label_timer_full_stock);

    //Next Research Unit Timer
    QLabel* label_timer_next_research = new QLabel(m_timer_next_research->getTimeLeft().toString());
    timers_groupbox_layout->addRow(tr("Next research unit in:"), label_timer_next_research);

    //Next Research Unlock Timer
    QLabel* label_timer_next_unlock = new QLabel(m_timer_research_unlock->getTimeLeft().toString());
    timers_groupbox_layout->addRow(tr("Next Research Unlock:"), label_timer_next_unlock);

    //Next Supply Consumption Timer
    QLabel* label_timer_next_supply = new QLabel(m_timer_next_supply->getTimeLeft().toString());
    timers_groupbox_layout->addRow(tr("Next supply consumed in:"), label_timer_next_supply);

    //Empty Supplies Timer
    QLabel* label_timer_empty_supplies = new QLabel(m_timer_empty_supplies->getTimeLeft().toString());
    timers_groupbox_layout->addRow(tr("Supplies empty:"), label_timer_empty_supplies);

    //Supplies Bought Timer
    QLabel* label_timer_supplies_bought = new QLabel(m_timer_supplies_bought->getTimeLeft().toString());
    timers_groupbox_layout->addRow(tr("Supplies arrive in:"), label_timer_supplies_bought);

    //------------------------------------Action buttons------------------------------------------//
    //Set the GroupBox containing the action buttons
    QGroupBox* actions_groupbox = new QGroupBox(tr("Actions"));
    bunker_widget_layout->addWidget(actions_groupbox, 0, 0, 1, 2);
    QGridLayout* actions_groupbox_layout = new QGridLayout();
    actions_groupbox->setLayout(actions_groupbox_layout);

    //-----Add the actions buttonsto the action GroupBox-----/
    //Start/Pause Manufacturing/Research Button
    m_button_start_pause_manuf_research = new QPushButton(tr("Start Manufacturing / Research"));
    actions_groupbox_layout->addWidget(m_button_start_pause_manuf_research, 0, 0, 1, 2);

    //Supplies Bought/Arrived Button
    m_button_supplies_bought_arrived = new QPushButton(tr("Supplies Bought"));
    actions_groupbox_layout->addWidget(m_button_supplies_bought_arrived, 1, 0, 1, 1);

    //Supplies Stolen Button
    QPushButton* button_supplies_stolen = new QPushButton(tr("Supplies Stolen") + " (+" + QString::number(m_supplies_bundle_size) + tr(" supplies)"));
    actions_groupbox_layout->addWidget(button_supplies_stolen, 1, 1, 1, 1);

    //Stock Sold Button
    QPushButton* button_stock_sold = new QPushButton(tr("Stock Sold"));
    actions_groupbox_layout->addWidget(button_stock_sold, 2, 0, 1, 1);

    //Sell Mission Canceled Sold Button
    QPushButton* button_sell_canceled = new QPushButton(tr("Sell Mission Cancelled"));
    actions_groupbox_layout->addWidget(button_sell_canceled, 2, 1, 1, 1);

    //Reset Bunker Button (whenever the player fails a raid mission)
    QPushButton* button_reset_bunker = new QPushButton(tr("Reset Bunker (Raided)"));
    actions_groupbox_layout->addWidget(button_reset_bunker, 3, 0, 1, 2);

    //------------------------------------Connections------------------------------------------//
    //-----Progress bars-----/
    connect(this, SIGNAL (OnStockChanged(int)), stock_progress_bar, SLOT(setValue(int)));
    connect(this, SIGNAL (OnSuppliesChanged(int)), supplies_progress_bar, SLOT(setValue(int)));

    //-----Action buttons-----/
    connect(m_button_start_pause_manuf_research, SIGNAL(released()), this, SLOT(StartPause()));
    connect(m_button_supplies_bought_arrived, SIGNAL(released()), this, SLOT(SuppliesBought()));
    connect(button_supplies_stolen, SIGNAL (released()),this, SLOT (StealSupplies()));
    connect(button_stock_sold, SIGNAL (released()),this, SLOT (StockSold()));
    connect(button_sell_canceled, SIGNAL (released()),this, SLOT (SellMissionCancelled()));
    connect(button_reset_bunker, SIGNAL (released()),this, SLOT (ResetBunker()));

    //----Timer displays-----/
    connect(m_timer_next_stock, SIGNAL(onValueChanged(QString)), label_timer_next_stock, SLOT(setText(QString)));
    connect(m_timer_full_stock, SIGNAL(onValueChanged(QString)), label_timer_full_stock, SLOT(setText(QString)));
    connect(m_timer_next_research, SIGNAL(onValueChanged(QString)), label_timer_next_research, SLOT(setText(QString)));
    connect(m_timer_research_unlock, SIGNAL(onValueChanged(QString)), label_timer_next_unlock, SLOT(setText(QString)));
    connect(m_timer_next_supply, SIGNAL(onValueChanged(QString)), label_timer_next_supply, SLOT(setText(QString)));
    connect(m_timer_empty_supplies, SIGNAL(onValueChanged(QString)), label_timer_empty_supplies, SLOT(setText(QString)));
    connect(m_timer_supplies_bought, SIGNAL(onValueChanged(QString)), label_timer_supplies_bought, SLOT(setText(QString)));
    connect(m_timer_supplies_bought, SIGNAL(onTimeout()), this, SLOT(SuppliesArrived()));

    //----Checkboxes-----/
    connect(equipment_upgrade_checkbox, SIGNAL(stateChanged(int)), this, SLOT(setEquipmentUpgrade(int)));
    connect(staff_upgrade_checkbox, SIGNAL(stateChanged(int)), this, SLOT(setStaffUpgrade(int)));

    //----Radio Buttons-----/
    connect(staff_management_bgroup, SIGNAL(buttonClicked(int)), this, SLOT(setStaffManagement()));

    //------------------------------------Set the timers------------------------------------------//
    SetStockTimers();
    SetResearchTimers();
    SetSuppliesTimers();
}

//Destructor
BunkerWidget::~BunkerWidget()
{
}

//Start Manufacturing/Research
void BunkerWidget::Start()
{
    if (m_staff_is_manufacturing || m_staff_is_both_manufacturing_research)
    {
        StartManufacturing();
        if (m_staff_is_both_manufacturing_research) StartResearch();
        else PauseResearch();
    }
    else
    {
        StartResearch();
        PauseManufacturing();
    }
    m_bunker_is_paused = false;
    m_button_start_pause_manuf_research->setText("Pause Manufacturing/Research");
}

//Pause Manufacturing/Research
void BunkerWidget::Pause()
{
    PauseManufacturing();
    PauseResearch();
    PauseSupplies();
    m_bunker_is_paused = true;
    m_button_start_pause_manuf_research->setText("Start Manufacturing/Research");
}

//Start Manufacturing
void BunkerWidget::StartManufacturing()
{
    m_timer_next_stock->start();
    m_timer_full_stock->start();
    StartSupplies();
}

//Pause Manufacturing
void BunkerWidget::PauseManufacturing()
{
    m_timer_next_stock->stop();
    m_timer_full_stock->stop();
}

//Start Research
void BunkerWidget::StartResearch()
{
    m_timer_next_research->start();
    m_timer_research_unlock->start();
    StartSupplies();
}

//Pause Manufacturing
void BunkerWidget::PauseResearch()
{
    m_timer_next_research->stop();
    m_timer_research_unlock->stop();
}

//Start Supplies consumption
void BunkerWidget::StartSupplies()
{
    m_timer_next_supply->start();
    m_timer_empty_supplies->start();
}

//Pause Supplies consumption
void BunkerWidget::PauseSupplies()
{
    m_timer_next_supply->stop();
    m_timer_empty_supplies->stop();
}

//Set both next stock unit / full stock timers
void BunkerWidget::SetStockTimers()
{
    //Manufacturing only
    if (m_staff_is_manufacturing)
    {

        //Both upgrades = 1 unit / 7 Minutes
        if (m_has_equipment_upgrade && m_has_staff_upgrade) m_timer_next_stock->setTimer(0, 7, 0);

        //No upgrade = 1 unit / 10 Minutes
        else if (!m_has_equipment_upgrade && !m_has_staff_upgrade) m_timer_next_stock->setTimer(0, 10, 0);

        //1 Upgrade only = 1 unit / 8:30 Minutes
        else m_timer_next_stock->setTimer(0, 8, 30);
    }

    //Both Manufacturing and Research (twice as long)
    else if (m_staff_is_both_manufacturing_research)
    {

        //Both upgrades = 1 unit / 14 Minutes
        if (m_has_equipment_upgrade && m_has_staff_upgrade) m_timer_next_stock->setTimer(0, 14, 0);

        //No upgrade = 1 unit / 20 Minutes
        else if (!m_has_equipment_upgrade && !m_has_staff_upgrade) m_timer_next_stock->setTimer(0, 20, 0);

        //1 Upgrade only = 1 unit / 17 Minutes
        else m_timer_next_stock ->setTimer(0, 17, 0);
    }

    //Research only (Stop Timers)
    else Pause();

    //Update full stock timer
    m_timer_full_stock->setTimer(0, 0, 0);
    int
            h = m_timer_next_stock->getTimeLeft().hour(),
            m = m_timer_next_stock->getTimeLeft().minute(),
            s = m_timer_next_stock->getTimeLeft().second();

    for (int i = 0; i < m_max_stock - m_stock; i++) m_timer_full_stock->addTime(h, m, s);
}

//Set both next research unit / unlock timers
void BunkerWidget::SetResearchTimers()
{
    //Research only
    if (m_staff_is_researching)
    {

        //Both upgrades = 1 unit / 3:30 Minutes
        if (m_has_equipment_upgrade && m_has_staff_upgrade) m_timer_next_research->setTimer(0, 3, 30);

        //No upgrade = 1 unit / 5 Minutes
        else if (!m_has_equipment_upgrade && !m_has_staff_upgrade) m_timer_next_research->setTimer(0, 5, 0);

        //1 Upgrade only = 1 unit / 4:15 Minutes
        else m_timer_next_research->setTimer(0, 4, 15);
    }

    //Both Manufacturing and Research (twice as long)
    else if (m_staff_is_both_manufacturing_research)
    {

        //Both upgrades = 1 unit / 7 Minutes
        if (m_has_equipment_upgrade && m_has_staff_upgrade) m_timer_next_research->setTimer(0, 7, 0);

        //No upgrade = 1 unit / 10 Minutes
        else if (!m_has_equipment_upgrade && !m_has_staff_upgrade) m_timer_next_research->setTimer(0, 10, 0);

        //1 Upgrade only = 1 unit / 8:30 Minutes
        else m_timer_next_research->setTimer(0, 8, 30);
    }

    //Manufacturing only (Stop Timers)
    else Pause();

    //Update next unlock timer
    m_timer_research_unlock->setTimer(0, 0, 0);
    int
            h = m_timer_next_research->getTimeLeft().hour(),
            m = m_timer_next_research->getTimeLeft().minute(),
            s = m_timer_next_research->getTimeLeft().second();

    for (int i = 0; i < m_max_research - m_research; i++) m_timer_research_unlock->addTime(h, m, s);
}

//Set both next supply unit consumed / empty supplies timers
void BunkerWidget::SetSuppliesTimers()
{
    //Research only
    if (m_staff_is_researching)
    {

        //Both upgrades = 1 unit / 1 Minutes
        if (m_has_equipment_upgrade && m_has_staff_upgrade) m_timer_next_supply->setTimer(0, 1, 0);

        //No upgrade = 1 unit / 1:24 Minutes
        else if (!m_has_equipment_upgrade && !m_has_staff_upgrade) m_timer_next_supply->setTimer(0, 1, 24);

        //1 Upgrade only = 1 unit / 1:12 Minutes
        else m_timer_next_supply->setTimer(0, 1, 12);
    }

    //Both Manufacturing and Research
    else if (m_staff_is_both_manufacturing_research)
    {

        //Both upgrades = 1 unit / 1:45 Minutes
        if (m_has_equipment_upgrade && m_has_staff_upgrade) m_timer_next_supply->setTimer(0, 1, 45);

        //No upgrade = 1 unit / 2:27 Minutes
        else if (!m_has_equipment_upgrade && !m_has_staff_upgrade) m_timer_next_supply->setTimer(0, 2, 27);

        //1 Upgrade only = 1 unit / 2:06 Minutes
        else m_timer_next_supply->setTimer(0, 2, 06);
    }

    //Manufacturing only
    else
    {
        //Both upgrades = 1 unit / 2:30 Minutes
        if (m_has_equipment_upgrade && m_has_staff_upgrade) m_timer_next_supply->setTimer(0, 2, 30);

        //No upgrade = 1 unit / 3:30 Minutes
        else if (!m_has_equipment_upgrade && !m_has_staff_upgrade) m_timer_next_supply->setTimer(0, 3, 30);

        //1 Upgrade only = 1 unit / 3 Minutes
        else m_timer_next_supply->setTimer(0, 3, 0);
    }

    //Update next unlock timer
    m_timer_empty_supplies->setTimer(0, 0, 0);
    int
            h = m_timer_next_supply->getTimeLeft().hour(),
            m = m_timer_next_supply->getTimeLeft().minute(),
            s = m_timer_next_supply->getTimeLeft().second();

    for (int i = 0; i < m_supplies; i++) m_timer_empty_supplies->addTime(h, m, s);
}

//--------------------------------------Slots--------------------------------------------//

//Start/Pause Manufacturing/Research
void BunkerWidget::StartPause()
{
    if (m_bunker_is_paused) Start();
    else Pause();
}

//Supplies Bought (Arrive in the bunker in 15 minutes)
void BunkerWidget::SuppliesBought()
{
    m_timer_supplies_bought->setTimer(0, 15, 0);
    m_timer_supplies_bought->start();
    m_button_supplies_bought_arrived->setText("Supplies inbound...");
    m_button_supplies_bought_arrived->setEnabled(false);
}

//Supplies Arrived
void BunkerWidget::SuppliesArrived()
{
    m_button_supplies_bought_arrived->setText("Supplies bought");
    m_button_supplies_bought_arrived->setEnabled(true);
    m_supplies = m_max_supplies;
    emit OnSuppliesChanged(m_supplies);
}

//Steal supplies (add a bundle of supplies to the total supplies level)
void BunkerWidget::StealSupplies()
{
    if (m_supplies + m_supplies_bundle_size > m_max_supplies) m_supplies = m_max_supplies;
    else m_supplies += m_supplies_bundle_size;
    emit OnSuppliesChanged(m_supplies);
}

//Sell stock (reset the stock level)
void BunkerWidget::StockSold()
{
    m_stock = 0;
    emit OnStockChanged(m_stock);
}

//Cancel the Sell mission (lose 3 stock units)
void BunkerWidget::SellMissionCancelled()
{
    if ((m_stock - 3) < 0) m_stock = 0;
    else m_stock -= 3;
    emit OnStockChanged(m_stock);
}

//Reset bunker (whenever the player fails a raid mission, they lose all of their stock and supplies)
void BunkerWidget::ResetBunker()
{
    m_stock = m_supplies = 0;
    emit OnStockChanged(m_stock);
    emit OnSuppliesChanged(m_supplies);
}

//Each time a stock unit is produced
void BunkerWidget::StockUnitProduced()
{
    m_stock++;
    if (m_stock == m_max_stock)
    {
        m_stock_is_full = true;
        //stock full
    }
    SetStockTimers();
    emit OnStockChanged(m_stock);
}

//Each time a research unit is produced
void BunkerWidget::ResearchUnitProduced()
{
    m_research++;
    if (m_research == m_max_research)
    {
        //research notif
    }
    SetResearchTimers();
    emit OnResearchChanged(m_research);
}

//Each time a research unit is produced
void BunkerWidget::SupplyUnitConsumed()
{
    m_supplies--;
    if (m_supplies == 0)
    {
        //research notif
    }
    SetSuppliesTimers();
    emit OnSuppliesChanged(m_supplies);
}

//When the equipment upgrade radio button is checked
void BunkerWidget::setEquipmentUpgrade(int p_equipment_checkbox_state)
{
    if (p_equipment_checkbox_state == Qt::CheckState::Checked) m_has_equipment_upgrade = true;
    else m_has_equipment_upgrade = false;
    SetStockTimers();
    SetResearchTimers();
    SetSuppliesTimers();
}

//When the staff upgrade radio button is checked
void BunkerWidget::setStaffUpgrade(int p_staff_checkbox_state)
{
    if (p_staff_checkbox_state == Qt::CheckState::Checked) m_has_staff_upgrade = true;
    else m_has_staff_upgrade = false;
    SetStockTimers();
    SetResearchTimers();
    SetSuppliesTimers();
}

//When the radio buttons are clicked
void BunkerWidget::setStaffManagement()
{
    if (m_rbutton_staff_manuf->isChecked()) m_staff_is_manufacturing = true;
    else m_staff_is_manufacturing = false;

    if (m_rbutton_staff_research->isChecked()) m_staff_is_researching = true;
    else m_staff_is_researching = false;

    if (m_rbutton_staff_both->isChecked()) m_staff_is_both_manufacturing_research = true;
    else m_staff_is_both_manufacturing_research = false;

    SetStockTimers();
    SetResearchTimers();
    SetSuppliesTimers();
}
