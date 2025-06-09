#include <string>
using namespace std;
class Contact {
private:
    std::string name;
    std::string email;
    std::string phone;
    int ID;

public:
    Contact(string name, string email, string phone,int ID);
    string getName() const;
    string getEmail() const;
    string getPhone() const;
    string getID() const;
    void setName(string newName);
    void setEmail(string newEmail);
    void setPhone(string newPhone);
};
