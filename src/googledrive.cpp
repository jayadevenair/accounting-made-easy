#include "googledrive.h"
#include <QAbstractOAuth2>
#include <QMessageBox>

void GoogleDrive::authReply(const QVariantMap &data)
{
    qDebug() << "Successfully Completed google Authorization";


    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::RelatedType);

    QHttpPart metadataPart;
    //metadataPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    metadataPart.setRawHeader("Content-Type", "application/json; charset=UTF-8");

    //metadataPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"text\""));
    metadataPart.setBody("\"name\": \"myfile\"");


    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
    //imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\""));
    QFile *file = new QFile("/home/ejayadev/logo.png");
    file->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(file);
    file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart

    multiPart->append(metadataPart);
    multiPart->append(imagePart);

    QUrl driveUrl("https://www.googleapis.com/upload/drive/v3/files?uploadType=media");

    //QNetworkRequest request;
    //request.setUrl(driveUrl);
    //request.setHeader(QNetworkRequest::UserAgentHeader, userAgent);
    //const QString bearer = QStringLiteral("Bearer %1").arg(google->token());
    //qDebug() << "auth tocken " << bearer;
    //request.setRawHeader("Authorization", bearer.toUtf8());
    //request.setRawHeader("User-Agent", "MyApp 1.0");
    //request.setRawHeader("Content-Type", "multipart/form-data; boundary=" +
                         //multiPart->boundary());
    //request.setHeader(QNetworkRequest::ContentLengthHeader, QString::number(multiPart->size()).toAscii());

    QNetworkReply *reply = google->post(driveUrl, multiPart);
    //QNetworkReply *reply = networkManager->post(request, multiPart);
    multiPart->setParent(reply);
    connect(google, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(postFinished(QNetworkReply *)));
}

void GoogleDrive::postFinished(QNetworkReply *reply)
{
    qDebug() << "JAYADEV finished post good job man";
    QByteArray bts = reply->readAll();
    QString str(bts);
    qDebug() << "reply" << str;
}

void GoogleDrive::doOAuth2Google(void)
{
    google = new QOAuth2AuthorizationCodeFlow;
    google->setScope("https://www.googleapis.com/auth/drive");
    connect(google, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
        &QDesktopServices::openUrl);

    QFile file;
    file.setFileName("/home/ejayadev/j.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = file.readAll();
    file.close();
    qWarning() << val;
    QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());

    const auto object = document.object();
    const auto settingsObject = object["installed"].toObject();
    const QUrl authUri(settingsObject["auth_uri"].toString());
    const auto clientId = settingsObject["client_id"].toString();
    const QUrl tokenUri(settingsObject["token_uri"].toString());
    const auto clientSecret(settingsObject["client_secret"].toString());
    const auto redirectUris = settingsObject["redirect_uris"].toArray();
    const QUrl redirectUri(redirectUris[1].toString()); // Get the first URI
    const auto port = static_cast<quint16>(redirectUri.port()); // Get the port

    google->setAuthorizationUrl(authUri);
    google->setClientIdentifier(clientId);
    google->setAccessTokenUrl(tokenUri);
    google->setClientIdentifierSharedKey(clientSecret);

    qDebug() << authUri;
    qDebug() << clientId;
    qDebug() << tokenUri;
    qDebug() << clientSecret;
    qDebug() << redirectUri;
    qDebug() << port;
    replyHandler = new QOAuthHttpServerReplyHandler(port, this);
    google->setReplyHandler(replyHandler);

    google->grant();

    connect(google, SIGNAL(authorizationCallbackReceived(const QVariantMap &)),
            this, SLOT(authReply(const QVariantMap &)));
}

GoogleDrive::GoogleDrive(QObject *parent) : QObject(parent)
{
    doOAuth2Google();

}
