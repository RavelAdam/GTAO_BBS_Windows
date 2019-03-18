#include "bunkerwidget.h"

//Constructor
BunkerWidget::BunkerWidget(QWidget *parent)
    : QWidget(parent)
{
    //----------------------------Variable initializations----------------------------------//
    //Set the variables values
    m_has_equipment_upgrade = m_has_staff_upgrade = false;
    m_stock = m_research = m_next_unlock = m_supplies = 0;


    //-----------------------------------Main Layout----------------------------------------//
    //Set main layout of the bunker widget
    QGridLayout* bunker_widget_layout = new QGridLayout();
    setLayout(bunker_widget_layout);

    //------------------------------------Upgrades------------------------------------------//
    //Set the GroupBox containing the bunker upgrades
    QGroupBox* upgrades_groupbox = new QGroupBox(tr("Upgrades"));
    bunker_widget_layout->addWidget(upgrades_groupbox, 0, 0, 1, 2);
    QVBoxLayout* upgrades_groupbox_layout = new QVBoxLayout();
    upgrades_groupbox->setLayout(upgrades_groupbox_layout);

    //Add the upgrades checkboxes
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
    stock_progress_bar->setFormat(QString::number(m_stock) + "/" + QString::number(m_max_stock));
    progress_bar_groupbox_layout->addRow(tr("Stock"), stock_progress_bar);

    //Research bar
    QProgressBar* research_progress_bar = new QProgressBar();
    research_progress_bar->setMinimum(0);
    research_progress_bar->setMaximum(m_max_research);
    research_progress_bar->setValue(m_research);
    research_progress_bar->setFormat(QString::number(m_research) + "/" + QString::number(m_max_research));
    progress_bar_groupbox_layout->addRow(tr("Research"), research_progress_bar);

    //Next unlock bar
    QProgressBar* next_unlock_progress_bar = new QProgressBar();
    next_unlock_progress_bar->setMinimum(0);
    next_unlock_progress_bar->setMaximum(m_max_next_unlock);
    next_unlock_progress_bar->setValue(m_next_unlock);
    next_unlock_progress_bar->setFormat(QString::number(m_next_unlock) + "/" + QString::number(m_max_next_unlock));
    progress_bar_groupbox_layout->addRow(tr("Next Research Unlock"), next_unlock_progress_bar);

    //Supplies bar
    QProgressBar* supplies_progress_bar = new QProgressBar();
    supplies_progress_bar->setMinimum(0);
    supplies_progress_bar->setMaximum(m_max_supplies);
    supplies_progress_bar->setValue(m_supplies);
    supplies_progress_bar->setFormat(QString::number(m_supplies) + "/" + QString::number(m_max_supplies));
    progress_bar_groupbox_layout->addRow(tr("Supplies"), supplies_progress_bar);

    //------------------------------------Timers------------------------------------------//
    //Set the GroupBox containing the timers
    QGroupBox* timers_groupbox = new QGroupBox(tr("Timers"));
    bunker_widget_layout->addWidget(timers_groupbox, 1, 1, 1, 1);
    QFormLayout* timers_groupbox_layout = new QFormLayout();
    timers_groupbox->setLayout(timers_groupbox_layout);

    //-----Add the timers to the progress GroupBox-----/
    //Full Stock Timer
    QLabel* label_timer_full_stock = new QLabel("00:00");
    timers_groupbox_layout->addRow(tr("Stock full:"), label_timer_full_stock);

    //Next Research Unlock Timer
    QLabel* label_timer_next_unlock = new QLabel("00:00");
    timers_groupbox_layout->addRow(tr("Next research unlock:"), label_timer_next_unlock);

    //Empty Supplies Timer
    QLabel* label_timer_empty_supplies = new QLabel("00:00");
    timers_groupbox_layout->addRow(tr("Empty supplies:"), label_timer_empty_supplies);
}

//Destructor
BunkerWidget::~BunkerWidget()
{
}
