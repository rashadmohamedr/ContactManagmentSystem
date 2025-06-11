#pragma once
#include <string>
#include <vector>
#include "include/Contact.h"
using namespace std;
class ContactManager{
private:
	vector<Contact*> contacts;
    int curID;
public:
	ContactManager();
	~ContactManager();
	void addContact(const string &name,const string &email,const string &phone);
	bool editContact(const Contact& newContact);
	bool deleteContact(Contact contact);
	Contact searchContact(string query); 
	vector<Contact*> getAllContacts();
	int size() const { return contacts.size(); }
	//Contact* getContact(int index) const { return contacts.at(index); }
};
