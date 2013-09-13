#include "eventmodel.h"

//QString EventModel::dateTimeFormatString = "dd.MM.yyyy hh:mm";

EventModel::EventModel(QStringList initStringList):
    repeatPeriod(0),
    repeatEvery(1)
{
    dateTimeFormatString = initStringList.front();
    initStringList.pop_front();
    dateTime = QDateTime::fromString(initStringList.front(),dateTimeFormatString);
    initStringList.pop_front();
    type = initStringList.front();
    initStringList.pop_front();
    title = initStringList.front();
    initStringList.pop_front();
    room = initStringList.front().replace('=',' ');
    initStringList.pop_front();
    description = initStringList.front();
    initStringList.pop_front();
    //description += initStringList.front();
    QString tmpRrule = initStringList.front().split(';').front().split('=').back();
    if (tmpRrule == "MONTHLY") {
        repeatPeriod=30;
    } else if (tmpRrule == "WEEKLY") {
        repeatPeriod=7;
    }

    initStringList.pop_front();
}

QStringList EventModel::getOccurrences(int range, QDate dateFrom)const
{
    int securityCounter = 1000;
    QStringList result;

    QDateTime tmpDateTime = dateTime;
    do
    {
        if ((tmpDateTime.date().daysTo(QDate::currentDate()) <=0) && (QDate::currentDate().daysTo(tmpDateTime.date()) <= range ))
        result.push_back(tmpDateTime.toString(dateTimeFormatString));
        switch(repeatPeriod)
        {
        case(1):
            tmpDateTime = tmpDateTime.addDays(repeatEvery);
            break;
        case(7):
            tmpDateTime = tmpDateTime.addDays(repeatEvery*7);
            break;
        case(30):
            tmpDateTime = tmpDateTime.addMonths(repeatEvery);
            break;
        case(0):
        default:
            break;
        }
        securityCounter--;

    } while ((securityCounter > 0) && (QDate::currentDate().daysTo(tmpDateTime.date()) <= range ) && (repeatPeriod!=0) );
    return result;
}

QStringList EventModel::getInstance()const
{
    QStringList result;
    result << dateTimeFormatString << type << title << room << description;
    return result;
}
