#include "dataset.h"

char DataSet::delimiter=':';
QString DataSet::startTag="BEGIN";
QString DataSet::endTag="END";

DataSet::DataSet():
    name("custom"),
    parent(0),
    level(0),
    fh(0)
{
}

DataSet::DataSet(DataSet * newParent):
    name("custom"),
    parent(newParent),
    level(0),
    fh(0)
{

}

QString DataSet::getParentName()const
{
    if(0!=parent)
        return parent->getName();
    else
        return "none";
}

void DataSet::addLine(QStringList inputLine){
    list.push_back(inputLine);
}

QString DataSet::toQString()const{
    if (list.size())
    {
        QString output = QString(getLevel(),' ') + "[" + getName() + "] child of: " + getParentName() + "\n" ;

        for(unsigned int i = 0; i<list.size(); i++)
        {
            output += QString(getLevel(),' ');
            output += list[i].join(delimiter);
            output += "\n";
        }

        for(unsigned int i = 0; i<children.size(); i++)
        {
            output += "\n";
            output += children[i]->toQString();
        }

        return output;
    } else {
        return getName();
    }
}

bool DataSet::import(QString &fileName)
{
    DataSet * currObject = this;
    // tmpStringListContainer format:
    // (QString)TAG1:VALUE1,
    // (QString)TAG2:VALUE2,
    // ...
    fh = new FileHandler(fileName);
    connect(fh,SIGNAL(logmsg(QString)),SLOT(mainlog(QString)));
    fh->loadFile();
    QStringList tmpStringContainer = fh->toQStringList();
    fh->deleteLater();

    if (tmpStringContainer.isEmpty())
    {
        emit logmsg("File import general file error");
        return false;
    }

    // SIMPLE START/END TAG CHECK
    if( (tmpStringContainer.front().split(delimiter).front()!=getStartTag()) || (tmpStringContainer.back().split(delimiter).front()!=getEndTag())     ) {
        emit logmsg("File import fail - bad main tags");
        return false;
    }

    // SIMPLE INTEGRITY CHECK
    short int tagCounter = 0;
    for (unsigned short int i=0; i<tmpStringContainer.size();i++)
    {
        if (tmpStringContainer[i].split(delimiter).front()==getStartTag())
            tagCounter++;
        else if (tmpStringContainer[i].split(delimiter).front()==getEndTag())
            tagCounter--;

        if (tagCounter<0){
                emit logmsg("File import integrity fail - misplaced tags or too many endtags");
                return false;
            }
    }
    if (tagCounter>0)
    {
        emit logmsg("File import integrity fail - too many starttags");
        return false;
    }

    // REMOVE START/END MAIN TAGS
    setName("VCALENDAR");
    tmpStringContainer.pop_back();
    tmpStringContainer.pop_front();

    while(tmpStringContainer.size())
    {
        // tmpLine format
        // (QStringList) TAG1,VALUE1,leftovers
        QStringList tmpLine = tmpStringContainer.front().split(delimiter);
        if (tmpLine.size()<2) tmpLine.push_back("empty");
        tmpStringContainer.pop_front();

        if(getStartTag()==tmpLine.front())
        {
            // STARTTAG FOUND!

            // make new and set as current
            currObject = new DataSet(currObject);

            // set level
            currObject->level = currObject->parent->level +1;

            // add self to parent's children list
            currObject->parent->children.push_back(currObject);

            // set name from tag
            currObject->setName(tmpLine[1]);

        } else {
            if(getEndTag()==tmpLine.front())
            {
                // ENDTAG FOUND
                // let current be the parent again
                currObject = currObject->parent;
            } else {
                // NORMAL TAG
                currObject->list.push_back(tmpLine);
            }
        }

    }
    emit logmsg("file import finished");
    return true;
}

DataSet * DataSet::newChild(QString &newName)
{
    DataSet * childPointer = new DataSet(this);
    childPointer->setLevel(getLevel()+1);
    childPointer->setName(newName);
    children.push_back(childPointer);
    return childPointer;
}

unsigned short int DataSet::getObjectsByName(std::vector <DataSet *> &v, QString objName)
{
    unsigned short int result = 0;
    if(getName()==objName)
    {
        result++;
        v.push_back(this);
    }
    for (unsigned short int i=0; i<children.size(); i++)
    {
        result+=children[i]->getObjectsByName(v,objName);
    }
    return result;
}

QString DataSet::getValueOf(QString tagName, char dlmtr)const
{
    QString result = "none";
    for (unsigned short int i=0; i<list.size(); i++)
    {
        if (list[i].front()==tagName)
        {
            // dear future me, sorry for that mess
            QStringList tmpList = list[i];
            tmpList.pop_front();
            result = tmpList.join(dlmtr);
        }
    }
    return result;
}

QString DataSet::getDateStartString()const
{
    QString result = "nonedate";
    for (unsigned short int i=0; i<list.size(); i++)
    {
        if ( (list[i].front()=="DTSTART") || (list[i].front()=="DTSTART;TZID=Europe/Warsaw") || (list[i].front()=="DTSTART;VALUE=DATE") )
        {
            QStringList tmpList = list[i];
            tmpList.pop_front();
            result = tmpList.join("");
                result.remove('Z');
                result.remove('T');
        }
    }
    return result;
}


void DataSet::purgeChildren()
{
    while(children.size()){
      delete children.back();
      children.pop_back();
    }
}

void DataSet::mainlog(QString s)
{
    emit logmsg(s);
}

DataSet::~DataSet()
{
    purgeChildren();
}
