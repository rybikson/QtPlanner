#include "eventtemplate.h"
#include "ui_eventtemplate.h"

EventTemplate::EventTemplate(QStringList initStringList, QListWidgetItem * newHolder, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EventTemplate),
    holder(newHolder)

{
    ui->setupUi(this);
    QString tmpDateString = initStringList.front();
    initStringList.pop_front();
    QString dateTimeFormatString = initStringList.front();
    initStringList.pop_front();
        QDateTime dateTime = QDateTime::fromString(tmpDateString,dateTimeFormatString);
        ui->labelDayOfWeek->setText(dateTime.toString("dddd"));
        ui->labelDate->setText(dateTime.toString("dd.MM.yyyy"));
        ui->labelTime->setText(dateTime.toString("hh:mm"));
    ui->labelType->setText(initStringList.front());
    initStringList.pop_front();
    ui->labelTitle->setText(initStringList.front());
    initStringList.pop_front();
    ui->labelRoom->setText(initStringList.front());
    initStringList.pop_front();
    ui->description->setText(initStringList.front());
    initStringList.pop_front();
}

EventTemplate::~EventTemplate()
{
    delete ui;
}
