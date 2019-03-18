#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Widgets/GlobalTabWidget/globaltabwidget.h"

#include <QHBoxLayout>
#include <QMainWindow>

//Main application window
class MainWindow : public QMainWindow
{
    Q_OBJECT
    //The global TabWidget
    GlobalTabWidget* m_global_tab_widget;

public:
    //Constructor/Destructor
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif // MAINWINDOW_H
