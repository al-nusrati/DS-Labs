#define TASK6_INCLUDE   // Prevents Task 5 main() from compiling
#include <iostream>
#include <string>
#include "T5.cpp"
using namespace std;

int main() {
    HashTable ht;

    ht.insert("al_nusrati", "Pass@1234");
    ht.insert("admin",       "admin123");
    ht.insert("destrox",    "Secure!99");
    ht.insert("al_nusrati", "duplicate");  

    ht.display();

    string users[]  = {"al_nusrati", "admin",     "ghost_user"};
    string inputs[] = {"Pass@1234",   "wrongpass", "Pass@1234" };

    for (int i = 0; i < 3; i++) {
        string stored = ht.search(users[i]);
        cout << "\nLogin attempt [" << users[i] << "]: ";
        if (stored.empty())
            cout << "Authentication failure - user not found.\n";
        else if (stored == inputs[i])
            cout << "Authentication successful. Welcome, " << users[i] << "!\n";
        else
            cout << "Authentication failure - incorrect password.\n";
    }

    cout << endl;
    ht.remove("destrox");
    ht.remove("nobody");

    ht.display();

    string uname, pass;
    cout << "\nEnter username: "; cin >> uname;
    cout << "Enter password: "; cin >> pass;

    string stored = ht.search(uname);
    if (stored.empty())
        cout << "Authentication failure - user not found.\n";
    else if (stored == pass)
        cout << "Authentication successful. Welcome, " << uname << "!\n";
    else
        cout << "Authentication failure - incorrect password.\n";

    cin.ignore();
    cin.get();
    return 0;
}