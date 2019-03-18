#include "bunkerwidget.h"

//Constructor
BunkerWidget::BunkerWidget(QWidget *parent)
    : QWidget(parent)
{
    //Set the variables value
    m_stock = m_research = m_next_unlock = m_supplies = 0;

    //Set main layout of the bunker widget
    QVBoxLayout* bunker_widget_layout = new QVBoxLayout();
    setLayout(bunker_widget_layout);

    //Set the GroupBox containing the progress bars
    QGroupBox* progress_bar_groupbox = new QGroupBox(tr("Progress"));
    bunker_widget_layout->addWidget(progress_bar_groupbox);
    QFormLayout* progress_bar_groupbox_layout = new QFormLayout();
    progress_bar_groupbox->setLayout(progress_bar_groupbox_layout);

    //Add the progress bars to the progress GroupBox
    //Stock bar
    m_stock_progress_bar = new QProgressBar();
    m_stock_progress_bar->setMinimum(0);
    m_stock_progress_bar->setMaximum(m_max_stock);
    m_stock_progress_bar->setValue(m_stock);
    m_stock_progress_bar->setFormat(QString::number(m_stock) + "/" + QString::number(m_max_stock));
    progress_bar_groupbox_layout->addRow(tr("Stock"), m_stock_progress_bar);

    //Research bar
    m_research_progress_bar = new QProgressBar();
    m_research_progress_bar->setMinimum(0);
    m_research_progress_bar->setMaximum(m_max_research);
    m_research_progress_bar->setValue(m_research);
    m_research_progress_bar->setFormat(QString::number(m_research) + "/" + QString::number(m_max_research));
    progress_bar_groupbox_layout->addRow(tr("Research"), m_research_progress_bar);

    //Next unlock bar
    m_next_unlock_progress_bar = new QProgressBar();
    m_next_unlock_progress_bar->setMinimum(0);
    m_next_unlock_progress_bar->setMaximum(m_max_next_unlock);
    m_next_unlock_progress_bar->setValue(m_next_unlock);
    m_next_unlock_progress_bar->setFormat(QString::number(m_next_unlock) + "/" + QString::number(m_max_next_unlock));
    progress_bar_groupbox_layout->addRow(tr("Next Unlock"), m_next_unlock_progress_bar);

    //Supplies bar
    m_supplies_progress_bar = new QProgressBar();
    m_supplies_progress_bar->setMinimum(0);
    m_supplies_progress_bar->setMaximum(m_max_supplies);
    m_supplies_progress_bar->setValue(m_supplies);
    m_supplies_progress_bar->setFormat(QString::number(m_supplies) + "/" + QString::number(m_max_supplies));
    progress_bar_groupbox_layout->addRow(tr("Supplies"), m_supplies_progress_bar);
}

//Destructor
BunkerWidget::~BunkerWidget()
{
}
