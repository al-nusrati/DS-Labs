#include <iostream>
using namespace std;

enum Severity { 
    Stable = 3,
    Serious = 2,
    Critical = 1
};

struct Patient {
    string name;
    int ID;
    Severity severity;
    Patient* next;
};

class PatientList {
private:
    Patient* head;

public:
    PatientList() : head(nullptr) {}

    ~PatientList() {
        Patient* current = head;
        while (current != nullptr) {
            Patient* next = current->next;
            delete current;
            current = next;
        }
    }

    void insertPatient(const string& name, int ID, Severity severity) {
        Patient* newPatient = new Patient{name, ID, severity, nullptr};
        if (head == nullptr || severity < head->severity) {
            newPatient->next = head; 
            head = newPatient;         
        } 
        else {
            Patient* current = head;
            while (current->next != nullptr && current->next->severity <= severity) {
                current = current->next;
            }
            newPatient->next = current->next;
            current->next = newPatient;
        }
    }

    void treatPatient() {
        if (head == nullptr) {
            cout << "No patients to treat." << endl;
            return;
        }
        Patient* patientToTreat = head;
        head = head->next;
        int treatedID = patientToTreat->ID;
        cout << "Treated patient ID: " << treatedID << endl;  
        delete patientToTreat;
    }

    void removePatient(int id) {
        if (head == nullptr) {
            cout << "No patients in the list." << endl;
            return;
        }
        if (head->ID == id) {
            Patient* temp = head;
            head = head->next;
            delete temp;
            cout << "Patient with ID " << id << " removed." << endl;
            return;
        }
        Patient* current = head;
        while (current->next != nullptr && current->next->ID != id) {
            current = current->next;
        }    
        if (current->next == nullptr) {
            cout << "Patient with ID " << id << " not found." << endl;
            return;
        }
        Patient* temp = current->next;
        current->next = temp->next;
        cout << "Patient with ID " << id << " removed." << endl; 
        delete temp;
        
    }

    void removeLast(){
        if (head == nullptr) {
            cout << "No patients in the list." << endl;
            return;
        }
        if (head->next == nullptr) {
            cout << "Last patient removed." << endl; 
            delete head;
            head = nullptr;
            return;
        }
        Patient* current = head;
        while (current->next->next != nullptr) {
            current = current->next;
        }
        cout << "Last patient removed." << endl;  
        delete current->next;
        current->next = nullptr;
    }

    void search(int id) {
        Patient* current = head;
        while (current != nullptr) {
            if (current->ID == id) {
                cout << "Patient Found: " << current->name << ", Severity: " << current->severity << endl;
                return;
            }
            current = current->next;
        }
        cout << "Patient with ID " << id << " not found." << endl;
    }

    PatientList* createBackup() {
        Patient* current = head;
        PatientList* backupList = new PatientList();
        while (current != nullptr) {
            backupList->insertPatient(current->name, current->ID, current->severity);
            current = current->next;
        }
        cout << "Backup created." << endl;  
        return backupList;
    }

    void display(){
        Patient* current = head;
        if (current == nullptr) {
            cout << "No patients in the list." << endl;
            return;
        }
        while (current != nullptr) {
            cout << "Name: " << current->name << ", ID: " << current->ID << ", Severity: " << current->severity << endl;
            current = current->next;
        }
    }

};

int main() {
    PatientList pl; // patient list -> pl
    pl.insertPatient("Alia", 101, Critical);
    pl.insertPatient("Saba", 102, Critical);
    pl.insertPatient("Ahmed", 103, Stable);
    pl.insertPatient("Ayesha", 104, Serious);
    pl.insertPatient("Babar", 105, Critical);    
    pl.insertPatient("Amir", 106, Stable);
    pl.treatPatient();
    pl.removePatient(104);
    pl.removeLast();
    pl.removePatient(999);
    pl.search(102);
    pl.search(888);
    PatientList* backup = pl.createBackup();
    pl.removePatient(102);
    cout << "Original list:" << endl;
    pl.display();
    cout << "Backup list:" << endl;
    backup->display();
    backup->insertPatient("Zara", 107, Serious);
    pl.removeLast();
    pl.removeLast();
    cout << "After modifications:" << endl;
    cout << "Original:" << endl;
    pl.display();
    cout << "Backup:" << endl;
    backup->display();
    delete backup;  
    cout << "System shutdown." << endl;  
    return 0;
}