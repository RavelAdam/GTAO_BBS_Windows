#include "bunkerwidget.h"

//Constructor
BunkerWidget::BunkerWidget(QWidget *parent)
    : QWidget(parent)
{
    //----------------------------Variable initializations----------------------------------//
    //Set the variables values
    m_has_equipment_upgrade = m_has_staff_upgrade = false;
    m_stock = m_research = m_next_unlock = m_supplies = 0;
    m_stock_is_full = false;
    m_supplies_are_empty = true;

    //-----------------------------------Main Layout----------------------------------------//
    //Set main layout of the bunker widget
    QGridLayout* bunker_widget_layout = new QGridLayout();
    setLayout(bunker_widget_layout);

    //------------------------------------Upgrades------------------------------------------//
    //Set the GroupBox containing the bunker upgrades
    QGroupBox* upgrades_groupbox = new QGroupBox(tr("Upgrades"));
    bunker_widget_layout->addWidget(upgrades_groupbox, 2, 0, 1, 2);
    QVBoxLayout* upgrades_groupbox_layout = new QVBoxLayout();
    upgrades_groupbox->setLayout(upgrades_groupbox_layout);

    //Add the upgrades checkboxes to the upgrade groupBox
    QCheckBox* equipment_upgrade_checkbox = new QCheckBox(tr("Equipment Upgrade"));
    equipment_upgrade_checkbox->setChecked(m_has_equipment_upgrade);
    upgrades_groupbox_layout->addWidget(equipment_upgrade_checkbox);
    QCheckBox* staff_upgrade_checkbox = new QCheckBox(tr("Staff Upgrade"));
    staff_upgrade_checkbox->setChecked(m_has_staff_upgrade);
    upgrades_groupbox_layout->addWidget(staff_upgrade_checkbox);

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

    //Next unlock bar
    QProgressBar* next_unlock_progress_bar = new QProgressBar();
    next_unlock_progress_bar->setMinimum(0);
    next_unlock_progress_bar->setMaximum(m_max_next_unlock);
    next_unlock_progress_bar->setValue(m_next_unlock);
    next_unlock_progress_bar->setFormat("%v/" + QString::number(m_max_next_unlock));
    next_unlock_progress_bar->setAlignment(Qt::AlignCenter);
    progress_bar_groupbox_layout->addRow(tr("Next Research Unlock"), next_unlock_progress_bar);

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
    QLabel* label_timer_full_stock = new QLabel("00:00");
    timers_groupbox_layout->addRow(tr("Stock full:"), label_timer_full_stock);

    //Next Research Unlock Timer
    QLabel* label_timer_next_unlock = new QLabel("00:00");
    timers_groupbox_layout->addRow(tr("Next research unlock:"), label_timer_next_unlock);

    //Empty Supplies Timer
    QLabel* label_timer_empty_supplies = new QLabel("00:00");
    timers_groupbox_layout->addRow(tr("Empty supplies:"), label_timer_empty_supplies);

    //------------------------------------Action buttons------------------------------------------//
    //Set the GroupBox containing the action buttons
    QGroupBox* actions_groupbox = new QGroupBox(tr("Actions"));
    bunker_widget_layout->addWidget(actions_groupbox, 0, 0, 1, 2);
    QGridLayout* actions_groupbox_layout = new QGridLayout();
    actions_groupbox->setLayout(actions_groupbox_layout);

    //-----Add the actions buttonsto the action GroupBox-----/
    //Start/Pause Production/Research Button
    QPushButton* button_start_pause_prod_research = new QPushButton(tr("Start Production/Research"));
    actions_groupbox_layout->addWidget(button_start_pause_prod_research, 0, 0, 1, 2);

    //Supplies Bought/Arrived Button
    QPushButton* button_supplies_bought_arrived = new QPushButton(tr("Supplies Bought"));
    actions_groupbox_layout->addWidget(button_supplies_bought_arrived, 1, 0, 1, 1);

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
    connect(button_supplies_stolen, SIGNAL (released()),this, SLOT (StealSupplies()));
    connect(button_stock_sold, SIGNAL (released()),this, SLOT (StockSold()));
    connect(button_reset_bunker, SIGNAL (released()),this, SLOT (ResetBunker()));


}

//Destructor
BunkerWidget::~BunkerWidget()
{
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

//Reset bunker (whenever the player fails a raid mission, they lose all of their stock and supplies)
void BunkerWidget::ResetBunker()
{
    m_stock = m_supplies = 0;
    emit OnStockChanged(m_stock);
    emit OnSuppliesChanged(m_supplies);
}
