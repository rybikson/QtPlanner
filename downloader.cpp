#include "downloader.h"

Downloader::Downloader(QUrl imageUrl, QObject *parent) :
    QObject(parent)
{
    m_WebCtrl = new QNetworkAccessManager(this);
    connect(m_WebCtrl, SIGNAL(finished(QNetworkReply*)), this, SLOT(fileDownloaded(QNetworkReply*)));
    connect(m_WebCtrl, SIGNAL(networkSessionConnected()), this, SLOT(throwErr()));
    QNetworkRequest request(imageUrl);
    m_WebCtrl->get(request);
    ownlog+= QString::number(m_WebCtrl->networkAccessible());
    ownlog+="downloader constructed";
}

Downloader::~Downloader()
{
    emit logmsg("downloader dead");
}

void Downloader::fileDownloaded(QNetworkReply* pReply)
{
    m_DownloadedData = pReply->readAll();
    //emit a signal
    pReply->deleteLater();
    emit downloaded();
    ownlog+="here";
}

QByteArray Downloader::downloadedData() const
{
    return m_DownloadedData;
}

QString Downloader::getLogContent()
{
    return ownlog;
}

void Downloader::throwErr()
{
    emit logmsg("err");
}
