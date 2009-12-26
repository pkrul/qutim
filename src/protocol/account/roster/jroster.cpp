#include "jroster.h"
#include <qutim/debug.h>

namespace Jabber
{
	struct JRosterPrivate
	{
		JAccount *account;
		RosterManager *rosterManager;
		QHash<QString, JContact*> contacts;
	};

	JRoster::JRoster(JAccount *account) : p(new JRosterPrivate)
	{
		p->account = account;
		p->rosterManager = p->account->connection()->client()->rosterManager();
		p->rosterManager->registerRosterListener(this, false);
		p->account->connection()->client()->registerPresenceHandler(this);
	}

	JRoster::~JRoster()
	{
	}

	void JRoster::handleItemAdded(const JID &jid)
	{
		/*QString key(QString::fromStdString(jid.bare()));
		QString resource(QString::fromStdString(jid.resource()));
		if (!p->contacts.contains(key)) {
			//p->contacts.value(key)->addResource(resource);
		//} else {
			if (key != p->account->jid()) {
				JContact *contact = new JContact(p->account);
				contact->setName(QString::fromStdString(jid.username()));
				RosterItem *item = p->rosterManager->getRosterItem(jid);
				QSet<QString> tags;
				StringList groups = item->groups();
				StringList::const_iterator group = groups.begin();
				for(; group != groups.end(); ++group)
					tags.insert(QString::fromStdString(*group));
				contact->setTags(tags);
				//contact->addResource(key);
				contact->addToList();
				ContactList::instance()->addContact(contact);
				p->contacts.insert(key, contact);
			}
		}*/
		debug() << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~item added";
	}

	void JRoster::handleItemSubscribed(const JID &jid)
	{
		debug() << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~item subscribed";
	}

	void JRoster::handleItemRemoved(const JID &jid)
	{
		/*QString key(QString::fromStdString(jid.bare()));
		QString resource(QString::fromStdString(jid.resource()));
		if (p->contacts.contains(key)) {
			if (!resource.isEmpty()) {
				p->contacts.value(key)->removeResource(resource);
				if (p->contacts.value(key)->resources().isEmpty())
					delete p->contacts.take(key);
			} else {
				delete p->contacts.take(key);
			}
		}*/
		debug() << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~item removed";
	}

	void JRoster::handleItemUpdated(const JID &jid)
	{
		/*RosterItem *item = p->rosterManager->getRosterItem(jid);
		QString key(QString::fromStdString(jid.bare()));
		if (p->contacts.contains(key)) {
			JContact *contact = p->contacts.value(key);
			contact->setName(QString::fromStdString(item->name()));
			QSet<QString> tags;
			StringList groups = item->groups();
			StringList::const_iterator group = groups.begin();
			for(; group != groups.end(); ++group)
				tags.insert(QString::fromStdString(*group));
			contact->setTags(tags);
		}*/
		debug() << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~item updated";
	}

	void JRoster::handleItemUnsubscribed(const JID &jid)
	{
		debug() << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~item unsubscribed";
	}

	void JRoster::handleRoster(const Roster &roster)
	{
		p->contacts.clear();
		std::map<const std::string, RosterItem *>::const_iterator items = roster.begin();
		for(; items != roster.end(); ++items) {
			std::string key = items->first;
			QString jid(QString::fromStdString(JID(key).bare()));
			if (jid == p->account->jid()) {
					continue;
			} else if (!p->contacts.contains(jid)) {
				JContact *contact = new JContact(p->account);
				RosterItem *item = items->second;
				contact->setName(QString::fromStdString(item->name()));
				QSet<QString> tags;
				StringList groups = item->groups();
				StringList::const_iterator group = groups.begin();
				for(; group != groups.end(); ++group)
					tags.insert(QString::fromStdString(*group));
				contact->setTags(tags);
				//QMap<std::string, Resource *> resources(item->resources());
				//foreach (std::string key, resources.keys())
				/*std::map<std::string, Resource *>::const_iterator resource = item->resources().begin();
				for(; resource != item->resources().end(); ++resource) {
					debug() << QString::fromStdString(resource->first);
					contact->addResource(QString::fromStdString(resource->first));
				}*/
				contact->addToList();
				ContactList::instance()->addContact(contact);
				p->contacts.insert(jid, contact);
				debug() << QString::fromStdString(item->name()) << contact->resources();
			}
		}
		debug() << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~roster";
	}

	void JRoster::handleRosterPresence(const RosterItem &item,
			const std::string &resource, Presence::PresenceType presence,
			const std::string &msg)
	{
		//debug() << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~roster presence";
	}

	void JRoster::handlePresence(const Presence &presence)
	{
		QString jid(QString::fromStdString(presence.from().bare()));
		QString resource(QString::fromStdString(presence.from().resource()));
		if (!p->contacts.contains(jid)) {
			JContact *contact = new JContact(p->account);
			contact->setName(QString::fromStdString(presence.from().username()));
			RosterItem *item = p->rosterManager->getRosterItem(presence.from());
			QSet<QString> tags;
			StringList groups = item->groups();
			StringList::const_iterator group = groups.begin();
			for(; group != groups.end(); ++group)
				tags.insert(QString::fromStdString(*group));
			contact->setTags(tags);
			contact->addToList();
			ContactList::instance()->addContact(contact);
			p->contacts.insert(jid, contact);
		}
		if (!resource.isEmpty())
			p->contacts.value(jid)->setStatus(resource,
					presence.presence(), presence.priority());
	}

	void JRoster::handleSelfPresence(const RosterItem &item, const std::string &resource,
			Presence::PresenceType presence, const std::string &msg)
	{
		debug() << QString::fromStdString(item.jid()) << QString::fromStdString(resource) << presence << QString::fromStdString(msg);
		debug() << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~self presence";
	}

	bool JRoster::handleSubscriptionRequest(const JID &jid, const std::string &msg)
	{
		debug() << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~subscription request";
		return false;
	}

	bool JRoster::handleUnsubscriptionRequest(const JID &jid, const std::string &msg)
	{
		debug() << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~unsubscription request";
		return true;
	}

	void JRoster::handleNonrosterPresence(const Presence &presence)
	{
		//debug() << QString::fromStdString(presence.tag()->xml());
		debug() << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~nonroster presence";
	}

	void JRoster::handleRosterError(const IQ &iq)
	{
		debug() << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~roster error";
	}
}
