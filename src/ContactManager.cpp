#include "include/ContactManager.h"
#include <iostream>
#include <algorithm>
using namespace std;
ContactManager::ContactManager() {
	curID = 0;
}
void ContactManager::addContact(const string &name,const string &email,const string &phone)
{
	Contact *newContact = new Contact(name, email, phone,curID++);
	contacts.push_back(newContact);
}
bool ContactManager::editContact(const Contact& newContact)
{
	for (vector<Contact *>::iterator it = contacts.begin(); it != contacts.end(); ++it)
	{
		if ((*it)->getID() == newContact.getID())
		{
			(*it)->setName(newContact.getName());
			(*it)->setPhone(newContact.getPhone());
			(*it)->setEmail(newContact.getEmail());
			return true;
		}
	}
	return false;
}
bool ContactManager::deleteContact(Contact contact)
{
	for (vector<Contact *>::iterator it = contacts.begin(); it != contacts.end(); ++it)
	{
		if ((*it)->getID() == contact.getID())
		{
			delete *it; // Free memory
			contacts.erase(it);
			return true; 
		}
	}
	return false; 
}
Contact ContactManager::searchContact(string query)
{
	for (vector<Contact *>::iterator it = contacts.begin(); it != contacts.end(); ++it)
	{
		if ((*it)->getName() == query)
		{
			return **it; 
		}
	}
	return Contact("","","",-1); // Return nullptr if not found
}
vector<Contact *> ContactManager::getAllContacts()
{
	return contacts;
}
ContactManager::~ContactManager()
{
	for (auto contact : contacts)
	{
		delete contact; // Free memory for each contact
	}
	contacts.clear(); // Clear the vector
}