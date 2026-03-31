#include<iostream>
#include<deque>
using namespace std;

struct Ticket{
    int ticketId;
    string customerName;
    string issueType;
    int priority;   //1-normal & 2-urgent
};


class TicketSetup{
private:
    deque<Ticket> tickets;


public:

    void insert(int id, string name, string type, int prio){
        Ticket temp;
        temp.ticketId = id;
        temp.customerName = name;
        temp.issueType = type;
        temp.priority = prio;
        if(prio==2)    tickets.push_front(temp);
        else           tickets.push_back(temp);
    }    

    void remove(){
        if(tickets.empty())     {cout << "Tickets are empty." << endl;   return;}
        else                   tickets.pop_front();
    }

    void display(){ 
        if(tickets.empty())     {cout << "Tickets are empty." << endl;   return;}
        cout <<"Display \n";
        for (int i = 0; i < tickets.size();i++){
            cout << tickets[i].ticketId << " " << tickets[i].customerName << endl;
        }
        cout <<"\n\n";
    }

    void currTicket(){
        if(tickets.empty())    {cout << "Tickets are empty." << endl;   return;}
            cout << "Current Ticket: " << tickets.front().ticketId << " " << tickets.front().customerName << endl;
    }


    int getCount(string type){
        int count = 0;
        for (int i = 0; i < tickets.size();i++)  {if(tickets[i].issueType==type)    count++;}        return count;
    }

    
    void search(int id){
        if(tickets.empty())    {cout << "Tickets are empty." << endl;    return;}
        for (int i = 0; i < tickets.size();i++)    {
            if(tickets[i].ticketId==id)
            {    cout <<"Data for:"<<id<<" -> " <<tickets[i].ticketId << " " << tickets[i].customerName << " " << tickets[i].issueType <<" Priotity: "<< tickets[i].priority << endl;     return;    }
        }
        cout << "Ticket not found" << endl;
    }


};

int main(){
    TicketSetup tick;
    tick.insert(101, "Jawad Ahmed", "Type1", 2);
    tick.insert(102, "Ashir Ahmed", "Type2", 1);
    tick.insert(103, "Amna Ahmed", "Type2", 2);
    tick.insert(103, "Ahmed kamal", "Type2", 2);

    tick.remove();
    tick.display();

    cout << "Total tickets of Type2: "<<tick.getCount("Type2") << endl;

    tick.currTicket();
    int id;
    cout << "\nEnter id to search: ";
    cin >> id;
    tick.search(id);

    cin.ignore();
    cin.get();    
    return 0;
}