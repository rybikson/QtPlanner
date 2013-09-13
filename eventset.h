#ifndef EVENTSET_H
#define EVENTSET_H

#include <QObject>
#include <QtAlgorithms>

#include "eventmodel.h"
#include "dataset.h"

class eventSet : public QObject
{
    Q_OBJECT
public:
    explicit eventSet(QObject *parent = 0);
    int fillData(std::vector<QStringList>&, int range=180);
    void prepareData();

    virtual ~eventSet();

public slots:
    void mainlog(QString);
private:
    std::vector<EventModel *> theEvents;
    DataSet * currDataSet;
    QString ownLog;

signals:
    void logmsg(QString);
};

#endif // EVENTSET_H
