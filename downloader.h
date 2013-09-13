#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QUrl imageUrl, QObject *parent = 0);

    virtual ~Downloader();

    QByteArray downloadedData() const;
    QString getLogContent();

signals:
        void downloaded();
        void logmsg(QString);

private slots:

    void fileDownloaded(QNetworkReply* pReply);
    void throwErr();

private:

    QNetworkAccessManager * m_WebCtrl;

    QByteArray m_DownloadedData;

    QString ownlog;

};

#endif // DOWNLOADER_H
