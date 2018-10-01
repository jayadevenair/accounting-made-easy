#ifndef GOOGLEDRIVE_H
#define GOOGLEDRIVE_H

#include <QObject>
#include <QtNetworkAuth>
#include <QDesktopServices>

class GoogleDrive : public QObject
{
    Q_OBJECT
public:
    explicit GoogleDrive(QObject *parent = nullptr);

signals:

public slots:
    void authReply(const QVariantMap &data);

    void postFinished(QNetworkReply *reply);

private:
    QOAuth2AuthorizationCodeFlow *google;
    QOAuthHttpServerReplyHandler *replyHandler;
    void doOAuth2Google(void);
};

#endif // GOOGLEDRIVE_H
