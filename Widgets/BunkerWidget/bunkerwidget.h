#ifndef BUNKERWIDGET_H
#define BUNKERWIDGET_H

#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QProgressBar>
#include <QWidget>

//The widget handling the bunker
class BunkerWidget : public QWidget
{
    Q_OBJECT

    //Variables (current stock, research, research points until next unlock, supplies)
    quint8 m_stock, m_research, m_next_unlock, m_supplies;

    //Constants
    const quint8
    m_max_stock = 100,
    m_max_research = 60,
    m_max_next_unlock = 100,
    m_max_supplies = 100;

    //Progress bars (Stock, Research, Research points until next unlock, Supplies)
    QProgressBar* m_stock_progress_bar;
    QProgressBar* m_research_progress_bar;
    QProgressBar* m_next_unlock_progress_bar;
    QProgressBar* m_supplies_progress_bar;

public:
    //Constructor/Destructor
    BunkerWidget(QWidget *parent = nullptr);
    ~BunkerWidget();
};

#endif // BUNKERWIDGET_H
