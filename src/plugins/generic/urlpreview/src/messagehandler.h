/****************************************************************************
**
** qutIM - instant messenger
**
** Copyright © 2011 Alexander Kazarin <boiler@co.ru>
** Copyright © 2011 Aleksey Sidorov <gorthauer87@yandex.ru>
**
*****************************************************************************
**
** $QUTIM_BEGIN_LICENSE$
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see http://www.gnu.org/licenses/.
** $QUTIM_END_LICENSE$
**
****************************************************************************/


#ifndef URLPREVIEW_MESSAGEHANDLER_H
#define URLPREVIEW_MESSAGEHANDLER_H
#include <qutim/messagehandler.h>
#include <QSslError>
#include <QSize>
#include <QStringList>
#include <qutim/config.h>

class QNetworkAccessManager;
class QNetworkReply;
class QAuthenticator;
namespace UrlPreview {

enum PreviewFlag
{
	PreviewImages = 0x1,
	PreviewYoutube = 0x2,
	DisableTextHtml = 0x4
};
Q_DECLARE_FLAGS(PreviewFlags, PreviewFlag)
Q_DECLARE_OPERATORS_FOR_FLAGS(UrlPreview::PreviewFlags)

class UrlHandler : public QObject, public qutim_sdk_0_3::MessageHandler
{
	Q_OBJECT
public:
	explicit UrlHandler();

protected:
	qutim_sdk_0_3::MessageHandlerAsyncResult doHandle(qutim_sdk_0_3::Message &message) override;

private slots:
	void netmanFinished(QNetworkReply *);
	void authenticationRequired(QNetworkReply *, QAuthenticator *);
	void netmanSslErrors(QNetworkReply *, const QList<QSslError> &);

private:
	void checkLink(const QStringRef &originalLink, QString &url, qutim_sdk_0_3::ChatUnit *from, qint64 id);
	void updateData(qutim_sdk_0_3::ChatUnit *unit, const QString &uid, const QString &html);

	QNetworkAccessManager *m_netman;
	qutim_sdk_0_3::ConfigValue<PreviewFlags> m_flags;
	QString m_template;
	QString m_imageTemplate;
	QString m_youtubeTemplate;
	QString m_html5AudioTemplate;
	QString m_html5VideoTemplate;
	QString m_yandexRichContentTemplate;
	qutim_sdk_0_3::ConfigValue<quint64> m_maxImageHeight;
	qutim_sdk_0_3::ConfigValue<quint64> m_maxImageWidth;

	qutim_sdk_0_3::ConfigValue<quint64> m_maxFileSize;
	qutim_sdk_0_3::ConfigValue<bool> m_enableYoutubePreview;
	qutim_sdk_0_3::ConfigValue<bool> m_enableImagesPreview;
	qutim_sdk_0_3::ConfigValue<bool> m_enableHTML5Audio;
	qutim_sdk_0_3::ConfigValue<bool> m_enableHTML5Video;
	qutim_sdk_0_3::ConfigValue<bool> m_enableYandexRichContent;
	qutim_sdk_0_3::ConfigValue<QStringList> m_exceptionList;
};

} // namespace UrlPreview

#endif // URLPREVIEW_MESSAGEHANDLER_H

