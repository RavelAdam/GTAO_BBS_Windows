#include "bunkerwidget.h"

//Constructor
BunkerWidget::BunkerWidget(QWidget *parent)
    : QWidget(parent)
{
    //----------------------------Variable initializations----------------------------------//
    //Set the variables values
    m_has_equipment_upgrade = m_has_staff_upgrade = false;
    m_staff_manufacturing = 1.0;
    m_staff_research = 0.0;
    m_bunker_is_paused = true;
    m_stock = m_research = m_supplies = 0;
    m_stock_is_full = false;
    m_supplies_are_empty = true;

    //Set the timers
    m_timer_supplies_bought = new EnhancedTimer(0, 0, 0);
    m_timer_next_stock = new EnhancedTimer(70, 0, 0);

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
    //Staff Management Layout
    QHBoxLayout* staff_management_rbuttons_layout = new QHBoxLayout();
    upgrades_staff_management_groupbox_layout->addLayout(staff_management_rbuttons_layout);
    QButtonGroup* staff_management_bgroup = new QButtonGroup();

    //Manufacturing only button
    QRadioButton* rbutton_staff_manuf = new QRadioButton(tr("Manufacturing only"));
    rbutton_staff_manuf->setChecked(m_staff_manufacturing == 1.0);
    staff_management_rbuttons_layout->addWidget(rbutton_staff_manuf);
    staff_management_bgroup->addButton(rbutton_staff_manuf);

    //Both Manufacturing and Research
    QRadioButton* r_button_staff_both = new QRadioButton(tr("Both Manufacturing / Research"));
    rbutton_staff_manuf->setChecked(m_staff_manufacturing == 0.5 && m_staff_research == 0.5);
    staff_management_rbuttons_layout->addWidget(r_button_staff_both);
    staff_management_bgroup->addButton(r_button_staff_both);

    //Research only button
    QRadioButton* r_button_staff_research = new QRadioButton(tr("Research only"));
    rbutton_staff_manuf->setChecked(m_staff_research == 1.0);
    staff_management_rbuttons_layout->addWidget(r_button_staff_research);
    staff_management_bgroup->addButton(r_button_staff_research);

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
    //Full Stock Timer
    QLabel* label_timer_full_stock = new QLabel(m_timer_next_stock->getTimeLeft().toString());
    timers_groupbox_layout->addRow(tr("Stock full:"), label_timer_full_stock);

    //Next Research Unlock Timer
    QLabel* label_timer_next_unlock = new QLabel("00:00");
    timers_groupbox_layout->addRow(tr("Next Research Unlock:"), label_timer_next_unlock);

    //Empty Supplies Timer
    QLabel* label_timer_empty_supplies = new QLabel("00:00");
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
    connect(this, SIGNAL (OnSuppliesChanged(int)), supplies_progress_bar, SLOT(setValue(int)));

    //-----Action buttons-----/
    connect(m_button_start_pause_manuf_research, SIGNAL(released()), this, SLOT(StartPause()));
    connect(m_button_supplies_bought_arrived, SIGNAL(released()), this, SLOT(SuppliesBought()));
    connect(button_supplies_stolen, SIGNAL (released()),this, SLOT (StealSupplies()));
    connect(button_stock_sold, SIGNAL (released()),this, SLOT (StockSold()));
    connect(button_sell_canceled, SIGNAL (released()),this, SLOT (SellMissionCancelled()));
    connect(button_reset_bunker, SIGNAL (released()),this, SLOT (ResetBunker()));

    //----Timer displays-----/
    connect(m_timer_next_stock, SIGNAL(onValueChanged(QString)), label_timer_full_stock, SLOT(setText(QString)));
    connect(m_timer_supplies_bought, SIGNAL(onValueChanged(QString)), label_timer_supplies_bought, SLOT(setText(QString)));
    connect(m_timer_supplies_bought, SIGNAL(onTimeout()), this, SLOT(SuppliesArrived()));


}

//Destructor
BunkerWidget::~BunkerWidget()
{
}

//Start/Pause Manufacturing/Research
void BunkerWidget::StartPause()
{
    //Start Manufacturing/Research
    if (m_bunker_is_paused)
    {
        m_timer_next_stock->start();
        m_bunker_is_paused = false;
        m_button_start_pause_manuf_research->setText("Pause Manufacturing/Research");
    }

    //Pause Manufacturing/Research
    else
    {
        m_timer_next_stock->stop();
        m_bunker_is_paused = true;
        m_button_start_pause_manuf_research->setText("Start Manufacturing/Research");
    }
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
