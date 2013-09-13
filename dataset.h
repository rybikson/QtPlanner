#ifndef DATASET_H
#define DATASET_H

#include <QString>
#include <QStringList>
#include <vector>

#include "filehandler.h"

class DataSet : public QObject
{
    Q_OBJECT
public:
    DataSet();
    DataSet(DataSet *);

    QString getName()const{return name;}
    void setName(QString newName){name = newName;};
    QString getParentName()const;

    QString getValueOf(QString, char dlmtr = ' ')const;
    QString getDateStartString()const;

    unsigned short int getLevel()const{return level;}
    void setLevel(unsigned short int newLevel){level=newLevel;}

    int size()const{return list.size();}

    unsigned short int getObjectsByName(std::vector <DataSet *> &, QString);

    bool import(QString &);

    QString toQString()const;

    static QString startTag;
    static QString getStartTag(){return startTag;}
    static void    setStartTag(QString newStartTag){startTag = newStartTag;}

    static QString endTag;
    static QString getEndTag(){return endTag;}
    static void    setEndTag(QString newEndTag){endTag = newEndTag;}

    ~DataSet();
private:
    QString name;
    DataSet * parent;
    unsigned short int level;
    FileHandler * fh;

    std::vector <QStringList> list;
    void addLine(QStringList);

    std::vector <DataSet *> children;

    DataSet * newChild(QString &);
    void purgeChildren();

    static char delimiter;

    static QStringList fromFile(QString &);

signals:
    void logmsg(QString);
public slots:
    void mainlog(QString);
};

#endif // DATASET_H
