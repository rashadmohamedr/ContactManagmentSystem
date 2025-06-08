#include <string>
using namespace std;
class Contact {
private:
    std::string name;
    std::string email;
    std::string phone;
public:
    Contact(string& name, string& email, string& phone) {}

    string getName();
    string getEmail();
    string getPhone();
    void setName(string& newName);
    void setEmail(string& newEmail);
    void setPhone(string& newPhone);
};
