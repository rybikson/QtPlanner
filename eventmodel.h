#ifndef EVENTMODEL_H
#define EVENTMODEL_H

#include <QDateTime>
#include <QString>
#include <QStringList>
#include <vector>

class EventModel
{
public:
    EventModel(QStringList);
    QStringList getInstance()const;
    QStringList getOccurrences(int range=180, QDate dateFrom = QDate::currentDate())const;

private:
    QString dateTimeFormatString;
    QDateTime dateTime;
    QString type, title, room, description;
    int repeatPeriod, repeatEvery;
    void prepareOccurrences();


};

#endif // EVENTMODEL_H
