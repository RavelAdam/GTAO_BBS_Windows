#include "mainwindow.h"

//Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    //Set the global TabWidget as the main window's central widget
    m_global_tab_widget = new GlobalTabWidget(this);
    setCentralWidget(m_global_tab_widget);

}

//Destructor
MainWindow::~MainWindow()
{
}
