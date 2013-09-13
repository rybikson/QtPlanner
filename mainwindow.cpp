#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    aboutWindow(0),
    helpWindow(0),
    settingsWindow(0),
    theSet(0)
{
    ui->setupUi(this);
    mainlog("Start");
    addEvents(ui->listWidget, 1);
    addEvents(ui->listWidget_7, 7);
    addEvents(ui->listWidget_30, 30);
    ui->nowLabel->setText(QDateTime::currentDateTime().toString("dddd, d MMMM yyyy hh:mm"));
    ui->statusBar->addWidget(ui->nowLabel);
}

void MainWindow::addEvents(QListWidget * list, int range)
{
    mostCurrent = 0;
    someEventInstances.clear();
    if (theSet != 0)
        delete(theSet);
    theSet = new eventSet;
    connect(theSet,SIGNAL(logmsg(QString)),this,SLOT(mainlog(QString)));
    mostCurrent = theSet->fillData(someEventInstances, range);

    for(unsigned int i=0; i < someEventInstances.size(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem(list);
        EventTemplate * event = new EventTemplate(someEventInstances.at(i) ,item);
        connect(list,SIGNAL(destroyed()),event,SLOT(deleteLater()));
        item->setSizeHint(QSize(310,70));
        item->setBackgroundColor(QColor::fromRgb(250,230,230));
        list->setItemWidget(item,event);
    }
    if (list->count() > mostCurrent) mostCurrent++;
    list->setCurrentRow(mostCurrent);
    theSet->deleteLater();
}

void MainWindow::mainlog(QString msg)
{
    ui->textBrowser->append(msg);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionRefresh_triggered()
{
    ui->listWidget->setCurrentRow(mostCurrent);
    ui->listWidget->repaint();
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionAbout_triggered()
{
    if (aboutWindow == 0)
        aboutWindow = new About(this);
    aboutWindow->show();
}

void MainWindow::on_actionHelp_triggered()
{
    if (helpWindow == 0)
        helpWindow = new Help(this);
    helpWindow->show();
}

void MainWindow::on_actionSettings_triggered()
{
    if (settingsWindow == 0)
        settingsWindow = new Settings(this);
    settingsWindow->show();
}
