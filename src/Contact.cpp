#include "include/Contact.h"
#include <string>
using namespace std;
Contact::Contact(string &name, string &email, string &phone)
    : name(name), email(email), phone(phone) {}
string Contact::getName() 
{
    return name;
}

string Contact::getEmail() 
{
    return email;
}

string Contact::getPhone() 
{
    return phone;
}

void Contact::setName(string &newName)
{
    name = newName;
}

void Contact::setEmail(string &newEmail)
{
    email = newEmail;
}

void Contact::setPhone(string &newPhone)
{
    phone = newPhone;
}