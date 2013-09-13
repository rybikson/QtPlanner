#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_checkBoxAutoActualize_stateChanged(int arg1)
{
    this->ui->spinBoxActualizeDelay->setEnabled(arg1==2?true:false);
}


bool Settings::autoupdate()
{
    return(this->ui->checkBoxAutoActualize->isChecked());
}
