#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "eventtemplate.h"
#include "eventset.h"
#include "about.h"
#include "help.h"
#include "settings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void mainlog(QString);

private slots:


    void on_actionRefresh_triggered();
    void on_actionQuit_triggered();

    void on_actionAbout_triggered();

    void on_actionHelp_triggered();

    void on_actionSettings_triggered();

private:
    Ui::MainWindow *ui;

    About * aboutWindow;
    Help * helpWindow;
    Settings * settingsWindow;

    std::vector<QStringList> someEventInstances;
    eventSet * theSet;


    int mostCurrent;

    void addEvents(QListWidget * list, int range);
};

#endif // MAINWINDOW_H
