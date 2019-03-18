#include "bunkerwidget.h"

//Constructor
BunkerWidget::BunkerWidget(QWidget *parent)
    : QWidget(parent)
{
    //Set main layout of the bunker widget
    QVBoxLayout* bunker_widget_layout = new QVBoxLayout();
    setLayout(bunker_widget_layout);

    //Set the GroupBox containing the progress bars
    QGroupBox* progress_bar_groupbox = new QGroupBox(tr("Progress"));
    bunker_widget_layout->addWidget(progress_bar_groupbox);
    QFormLayout* progress_bar_groupbox_layout = new QFormLayout();
    progress_bar_groupbox->setLayout(progress_bar_groupbox_layout);

    //Add the progress bars to the progress GroupBox
    m_stock_progress_bar = new QProgressBar();
    progress_bar_groupbox_layout->addRow(tr("Stock"), m_stock_progress_bar);
    m_research_progress_bar = new QProgressBar();
    progress_bar_groupbox_layout->addRow(tr("Research"), m_research_progress_bar);
    m_supplies_progress_bar = new QProgressBar();
    progress_bar_groupbox_layout->addRow(tr("Supplies"), m_supplies_progress_bar);
}

//Destructor
BunkerWidget::~BunkerWidget()
{
}
