#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QDateTime>
#include <QFileInfo>
#include "downloader.h"

// TODO UTF!!!

enum eFileStatus {unknown = 0, exists = 1, loaded = 2, good = 3, outdated = 4, missing = 5};

class FileHandler : public QObject
{
    Q_OBJECT
public:
    // common public interface
    explicit FileHandler(QString, QObject * = 0);
    QStringList toQStringList();

    void downloadNewFile();


    eFileStatus getFileStatus()const{return fileStatus;}
    void setFileStatus(eFileStatus fs){fileStatus = fs;}
    QString getFileStatusString();

    static void setDaysToExpire(unsigned int i){daysToExpire = i;}
    static unsigned int getDaysToExpire(){return daysToExpire;}

private:
    QString const fileName;
    QDateTime fileDateCreated;
    QFile fileObject;
    eFileStatus fileStatus;
    QFileInfo * fileInfos;
    static unsigned int daysToExpire;
    bool isOutdated()const;
    unsigned int fileAge()const;
    Downloader * m_Downloader;

public slots:
        void loadFile();

private slots:
    void mainlog(QString);

signals:
    void logmsg(QString);
};

#endif // FILEHANDLER_H
