/****************************************************************************
**
** qutIM - instant messenger
**
** Copyright (C) 2011 Ruslan Nigmatullin <euroelessar@yandex.ru>
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
#ifndef IDLESTATUSWIDGET_H
#define IDLESTATUSWIDGET_H

#include <qutim/settingswidget.h>

namespace Ui {
class MacIdleWidget;
}

using namespace qutim_sdk_0_3;

class MacIdleWidget : public SettingsWidget
{
	Q_OBJECT
public:
	MacIdleWidget();
	~MacIdleWidget();

protected:
	virtual void loadImpl();
	virtual void saveImpl();
	virtual void cancelImpl();

protected:
	void changeEvent(QEvent *e);

private:
	Ui::MacIdleWidget *ui;
};

#endif // IDLESTATUSWIDGET_H

