#ifndef BUNKERWIDGET_H
#define BUNKERWIDGET_H

#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QWidget>

//The widget handling the bunker
class BunkerWidget : public QWidget
{
    Q_OBJECT

    //Progress bars (Stock, Research, Supplies)
    QProgressBar* m_stock_progress_bar;
    QProgressBar* m_research_progress_bar;
    QProgressBar* m_supplies_progress_bar;

public:
    //Constructor/Destructor
    BunkerWidget(QWidget *parent = nullptr);
    ~BunkerWidget();
};

#endif // BUNKERWIDGET_H
