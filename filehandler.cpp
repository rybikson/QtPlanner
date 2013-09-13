#include "filehandler.h"

unsigned int FileHandler::daysToExpire = 30;

FileHandler::FileHandler(QString newFileName, QObject * parent):
    QObject(parent),
    fileName(newFileName),
    fileObject(fileName),
    fileStatus(unknown)
{
    if (fileObject.exists())
    {
        setFileStatus(exists);

        fileInfos = new QFileInfo(fileName);
        fileDateCreated = fileInfos->created();
        delete fileInfos;

        if (isOutdated())
        {
            setFileStatus(outdated);
        } else {
            setFileStatus(good);
        }

    } else {
        setFileStatus(missing);
    }
    QUrl fileUrl("http://www.netmark.pl/templates/portal/images/whmcslogo.png");
    m_Downloader = new Downloader(fileUrl, this);
    connect(m_Downloader, SIGNAL(downloaded()), this, SLOT(loadFile()));
    connect(m_Downloader, SIGNAL(logmsg(QString)),this,SLOT(mainlog(QString)));
}

bool FileHandler::isOutdated()const
{
    return (fileAge()>daysToExpire)? true : false;
}

unsigned int FileHandler::fileAge()const
{
    return (fileDateCreated.daysTo(QDateTime::currentDateTime()));
}

QStringList FileHandler::toQStringList()
{
    emit logmsg(fileName+" ["+getFileStatusString()+"] "+QString::number(fileAge()));
    QStringList tmpStringContainer;

    if(
        (  (getFileStatus() == good) || (getFileStatus() == exists)    )
       &&
        (   fileObject.open(QIODevice::ReadOnly | QIODevice::Text)  )
      )
    {
        QTextStream tmpFileStream(&fileObject);
        QString tmpLine = tmpFileStream.readLine();

        while (!tmpLine.isNull())
        {
            tmpStringContainer.push_back(tmpLine);
            tmpLine = tmpFileStream.readLine();
        }
        emit logmsg("FH: parsed:" + QString::number(tmpStringContainer.size()) + " lines" );
        fileObject.close();
        emit logmsg(m_Downloader->getLogContent());
    }
    return tmpStringContainer;
}

void FileHandler::downloadNewFile()
{

}

QString FileHandler::getFileStatusString()
{
    switch(fileStatus)
    {
    case 0:
        return "unknown";
        break;
    case 1:
        return "exists";
        break;
    case 2:
        return "loaded";
        break;
    case 3:
        return "good";
        break;
    case 4:
        return "outdated";
        break;
    case 5:
        return "missing";
        break;
    default:
        return "not-set";
        break;
    }
}

void FileHandler::mainlog(QString msg)
{
    emit logmsg(msg);
}

void FileHandler::loadFile()
{
    QFile freshFile("testfile.txt");
    freshFile.open(QIODevice::WriteOnly);
        if (!freshFile.isWritable())
            emit logmsg("FH: file unwritable");
    freshFile.write((m_Downloader->downloadedData()));
    freshFile.close();
    emit logmsg("FH: File downloaded, size: " + QString::number(freshFile.size()) + " Bytes." );
}

