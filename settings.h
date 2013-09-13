#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT
    
public:
    int updateEvery();
    bool autoupdate();
    QString filterRules();
    explicit Settings(QWidget *parent = 0);
    ~Settings();
    
private slots:
    void on_checkBoxAutoActualize_stateChanged(int arg1);

private:
    Ui::Settings *ui;

    QSettings cfg;
};

#endif // SETTINGS_H
