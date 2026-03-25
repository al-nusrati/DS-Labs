#include <iostream>
#include <list>
#include <string>

using namespace std;

template<class t>
class myList:public list<t>
{
public:
    void display()
    {
         // node*temp
        typename list<t>::iterator temp;
        temp = (*this).begin();

        while (temp != (*this).end())
        {
            cout << (*temp)<<endl;
            temp++;
        }
    }

    bool operator==(myList<t>l){
        if (this->size() != l.size()) return false;

        typename list<t>::iterator temp1 = this->begin();
        typename list<t>::iterator temp2 = l.begin();

        while (temp1 != this->end()) {
            if (*temp1 != *temp2) return false;
            temp1++;
            temp2++;
        }

        return true;
    }
};

int main() {
    myList<int>l,l2;

    l.push_back(10);
    l.push_front(11);

    l.display();

    if (l == l2)    cout << "lists are equal" << endl;
    else cout << "lists are not equal" << endl;
    system("pause>0");
    return 0;
}
