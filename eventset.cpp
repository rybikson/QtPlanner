#include "eventset.h"

eventSet::eventSet(QObject *parent) :
    QObject(parent),
    currDataSet(0),
    ownLog("log empty\n")
{
    prepareData();
}

bool compareByDate(const QStringList &a, const QStringList &b )
{
    QString dateTimeFormatString = a.at(1);
    return QDateTime::fromString(a.front(),dateTimeFormatString) < QDateTime::fromString(b.front(),dateTimeFormatString);
}

int eventSet::fillData(std::vector<QStringList> &workSpace, int range)
{
    int mostCurrent = 0;
    for (unsigned int i=0; i<theEvents.size(); i++)
    {
        QStringList instance = theEvents.at(i)->getInstance();
        QStringList occurrences = theEvents.at(i)->getOccurrences(range);
        for(int j=0; j < occurrences.size() ; j++)
            workSpace.push_back(QStringList(occurrences.at(j))+instance);

        instance.clear();
        occurrences.clear();
    }

    std::sort(workSpace.begin(), workSpace.end(), compareByDate);
    for(unsigned int i=0; i<workSpace.size(); i++)
    {
        if (QDateTime::fromString(workSpace.at(i).front(),workSpace.at(i).at(1)) < QDateTime::currentDateTime())
            mostCurrent=i;
    }
    emit logmsg(ownLog+"Data filled!");
    return mostCurrent;
}

void eventSet::prepareData()
{
    currDataSet = new DataSet(0);
    QString fileName = "basic.ics";
    connect(currDataSet,SIGNAL(logmsg(QString)),SLOT(mainlog(QString)));
    currDataSet->import(fileName);

    std::vector<DataSet *> vEvents;

    unsigned short int eventsCount = currDataSet->getObjectsByName(vEvents,"VEVENT");

    for (unsigned short int i=0; i<eventsCount; i++)
    {
        QDateTime tmpDateStart = QDateTime::fromString(vEvents[i]->getDateStartString(),"yyyyMMdd");
        if (!tmpDateStart.isValid())
            tmpDateStart = QDateTime::fromString(vEvents[i]->getDateStartString(),"yyyyMMddhhmmss");

        QString tmpTitle = vEvents[i]->getValueOf("SUMMARY");

        QStringList tmp;
        tmp
                << "dd.MM.yyyy hh:mm"
                << tmpDateStart.toString("dd.MM.yyyy hh:mm")
                << tmpTitle.split("=").front()
                << tmpTitle.split("=").back()
                << vEvents[i]->getValueOf("LOCATION")
                << vEvents[i]->getValueOf("DESCRIPTION")
                << vEvents[i]->getValueOf("RRULE");
        theEvents.push_back(new EventModel(tmp));
        tmp.clear();
        //vEvents[i]->getDateStart()
    }
    ownLog+="data prepared\n";
}

void eventSet::mainlog(QString msg)
{
    ownLog+=msg + "\n";
    emit logmsg(ownLog);
}

eventSet::~eventSet()
{
    while(!theEvents.empty())
    {
        delete(theEvents.back());
        theEvents.back()=0;
        theEvents.pop_back();
    }
    theEvents.clear();

}
