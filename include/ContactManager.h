#include <string>
#include <vector>
#include "src/Contact.cpp"
using namespace std;
class ContactManager{
private:
	vector<Contact*> contacts;
    int curID;
public:
	ContactManager();
	void addContact(string &name, string &email, string &phone);
	bool editContact(const Contact& newContact);
	bool deleteContact(Contact contact);
	Contact searchContact(string query); 
	vector<Contact*> getAllContacts();
};
