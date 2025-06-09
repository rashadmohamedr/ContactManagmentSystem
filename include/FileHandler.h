#include "include/ContactManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
class FileHandler
{
private:
    string filename;

public:
    FileHandler(const string &file) : filename(file) {}

    bool saveContacts(const vector<Contact *> &contacts)
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error opening file for writing: " << filename << endl;
            return false;
        }
        for (const auto &contact : contacts)
        {
            file << contact->getID() << ","
                 << contact->getName() << ","
                 << contact->getEmail() << ","
                 << contact->getPhone() << endl;
        }
        file.close();
        return true;
    }

    vector<Contact *> loadContacts()
    {
        vector<Contact *> contacts;
        ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error opening file for reading: " << filename << endl;
            return contacts; // Return empty vector on failure
        }
        string line;
        while (getline(file, line))
        {
            istringstream iss(line);
            int id;
            string name, email, phone;
            char delimiter; // To consume the commas
            if (iss >> id >> delimiter >> ws && 
                getline(iss, name, ',') &&
                getline(iss, email, ',') && 
                getline(iss, phone))
            {
                contacts.push_back(new Contact(name, email, phone, id));
            }
        }
        file.close();
        return contacts;
    }
};