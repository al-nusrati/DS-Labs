#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

class Record{
public:
    int recordID;
    string name;
    double value;
};

bool compareValue(Record a, Record b){
    return a.value < b.value;
}

void printRecord(Record r){
    cout << "ID: " << r.recordID << " Name: " << r.name << " Value: " << r.value << endl;
}

class RecordSetup{
private:
    vector<Record> dept1;
    vector<Record> dept2;
    vector<Record> mergedData;

public:

    void insertDept1(int id, string name, double val){
        Record temp;
        temp.recordID = id;
        temp.name = name;
        temp.value = val;
        dept1.push_back(temp);
    }    

    void insertDept2(int id, string name, double val){
        Record temp;
        temp.recordID = id;
        temp.name = name;
        temp.value = val;
        dept2.push_back(temp);
    }

    void mergeCollections(){
        if(dept1.empty() && dept2.empty())    {cout << "Both departments are empty." << endl;   return;}
        sort(dept1.begin(), dept1.end(), compareValue);
        sort(dept2.begin(), dept2.end(), compareValue);
        mergedData.resize(dept1.size() + dept2.size());
        merge(dept1.begin(), dept1.end(), dept2.begin(), dept2.end(), mergedData.begin(), compareValue);
        cout << "Collections merged successfully.\n" << endl;
    }

    void displayMerged(){ 
        if(mergedData.empty())     {cout << "Merged data is empty." << endl;   return;}
        cout <<"--- Display Merged Records --- \n";
        for_each(mergedData.begin(), mergedData.end(), printRecord);
        cout <<"\n";
    }

    void verifySorted(){
        if(mergedData.empty())     {cout << "Merged data is empty." << endl;   return;}
        bool check = is_sorted(mergedData.begin(), mergedData.end(), compareValue);
        
        if(check)    cout << "Verification: Merged data is correctly sorted by value.\n\n";
        else         cout << "Verification: Merged data is NOT sorted.\n\n";
    }

    void findDuplicates(){
        if(mergedData.empty())     {cout << "Merged data is empty." << endl;   return;}
        cout << "--- Checking for Duplicate IDs --- \n";
        
        bool found = false;
        for (int i = 0; i < mergedData.size(); i++){
            for (int j = i + 1; j < mergedData.size(); j++){
                if(mergedData[i].recordID == mergedData[j].recordID){
                    cout << "Duplicate ID found: " << mergedData[i].recordID << " (" << mergedData[i].name << " & " << mergedData[j].name << ")" << endl;
                    found = true;
                }
            }
        }
        if(!found)    cout << "no duplicate IDs found." << endl;
        cout << "\n";
    }

};

int main(){
    RecordSetup rec;
    
    rec.insertDept1(101, "Alpha", 50.5);
    rec.insertDept1(105, "Beta", 10.0);
    rec.insertDept1(102, "Gamma", 80.2);

    rec.insertDept2(103, "Delta", 30.0);
    rec.insertDept2(101, "Epsilon", 90.5); 
    rec.insertDept2(104, "Zeta", 20.5);

    rec.mergeCollections();
    rec.displayMerged();
    rec.verifySorted();
    rec.findDuplicates();

    cin.ignore();
    cin.get();    
    return 0;
}