#include "include/Contact.h"
#include <string>
using namespace std;
Contact::Contact(string name, string email, string phone,int ID)
        : name(name), email(email), phone(phone), ID(ID) {};
string Contact::getName() const
{
    return name;
}

string Contact::getEmail () const
{
    return email;
}

string Contact::getPhone( ) const
{
    return phone;
}
string Contact::getID( ) const
{
    return phone;
}

void Contact::setName(string newName)
{
    name = newName;
}

void Contact::setEmail(string newEmail)
{
    email = newEmail;
}

void Contact::setPhone(string newPhone)
{
    phone = newPhone;
}