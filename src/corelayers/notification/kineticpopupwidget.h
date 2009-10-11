//   Modern notifications, which use new Qt Statemachine and Animation framework
//   (c) by Sidorov "Sauron" Aleksey, sauron@citadelspb.com, 2009
//   This library is free software; you can redistribute it and/or
//   modify it under the terms of the GNU Library General Public
//   License version 2 or later as published by the Free Software Foundation.
//
//   This library is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//   Library General Public License for more details.
//
//   You should have received a copy of the GNU Library General Public License
//   along with this library; see the file COPYING.LIB.  If not, write to
//   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
//   Boston, MA 02110-1301, USA.

#ifndef KINETICPOPUPWIDGET_H
#define KINETICPOPUPWIDGET_H

#include <QTextBrowser>
#include "kineticpopupthemehelper.h"

class QTextBrowser;
class KineticPopupWidget : public QTextBrowser
{
    Q_OBJECT
public:
    KineticPopupWidget(const KineticPopupThemeHelper::PopupSettings &popupSettings);
    QSize setData(const QString& title,
				  const QString& body,
				  const QString &imagePath); //size of textbrowser
    void setTheme(const KineticPopupThemeHelper::PopupSettings &popupSettings);
    virtual void mouseReleaseEvent ( QMouseEvent* ev );
private:
	KineticPopupThemeHelper::PopupSettings popup_settings;
signals:
    void action1Activated();
    void action2Activated();
};

#endif // KINETICPOPUPWIDGET_H
