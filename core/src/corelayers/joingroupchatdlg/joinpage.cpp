/****************************************************************************
 *  joinpage.cpp
 *
 *  Copyright (c) 2010 by Sidorov Aleksey <sauron@citadelspb.com>
 *
 ***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************
*****************************************************************************/

#include "joinpage.h"
#include <qutim/event.h>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QAction>
#include <QApplication>
#include <qutim/dataforms.h>
#include <qutim/account.h>
#include <qutim/groupchatmanager.h>

using namespace qutim_sdk_0_3;

namespace Core {

JoinPage::JoinPage(QWidget *parent) :
	GroupChatPage(parent)
{
	QCheckBox *box = new QCheckBox(QT_TRANSLATE_NOOP("JoinGroupChat", "Save to bookmarks"),this);
	m_layout->addWidget(box);

	m_joinAction = new QAction(this);
	m_joinAction->setText(QT_TRANSLATE_NOOP("JoinGroupChat", "Join"));
	m_joinAction->setSoftKeyRole(QAction::NegativeSoftKey);
	connect(m_joinAction,SIGNAL(triggered()),SLOT(join()));
	addAction(m_joinAction);
}

void JoinPage::updateDataForm()
{
	if (m_dataForm)
		m_dataForm->deleteLater();
	m_joinAction->setEnabled(false);

	GroupChatManager *manager = account()->groupChatManager();
	if (!manager)
		return;

	DataItem item = manager->fields();
	m_dataForm = AbstractDataForm::get(item);
	if (m_dataForm) {
		m_dataForm->setParent(this);
		m_dataForm->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
		m_layout->insertWidget(0,m_dataForm.data());
		m_joinAction->setEnabled(m_dataForm->isComplete());
		connect(m_dataForm.data(), SIGNAL(completeChanged(bool)),
				m_joinAction, SLOT(setEnabled(bool)));
	}
}

void JoinPage::join()
{
	if (!m_dataForm)
		return;

	GroupChatManager *manager = account()->groupChatManager();
	if (!manager)
		return;

	DataItem item = m_dataForm->item();
	manager->join(item);
	emit joined();
}

void JoinPage::showEvent(QShowEvent *ev)
{
	updateDataForm();
	QScrollArea::showEvent(ev);
}

} // namespace Core