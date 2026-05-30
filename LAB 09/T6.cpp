#include "Hash.cpp"

void regUser(HashMap& hm) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    hm.insert(username, password);
}

void loginUser(HashMap& hm) {
    string username, password, retrievedPassword;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    hm.search(username, retrievedPassword);  // search returns true/false, fills retrievedPassword
    if (retrievedPassword == password)   cout << "Authentication successful: " << username << "!\n";
    else                                 cout << "Authentication failure: Wrong password.\n";
    
}

int main() {
    HashMap hm;
    int choice;

    do {
        cout << "\n--- Login System ---\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Display Table\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: regUser(hm);            break;
        case 2: loginUser(hm);          break;
        case 3: hm.display();           break;
        case 4: cout << "Exiting.\n";   break;
        default: cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    system("pause>0");
    return 0;
}