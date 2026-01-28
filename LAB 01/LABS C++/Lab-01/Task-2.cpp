#include <iostream>
using namespace std;

class IntStaticPointer {

private:
    int *ptr;

public:

    //•	default constructor Initializes pointer to some initial value (NULL)
    IntStaticPointer(  ){
        ptr = nullptr;
    }

    //•	voidAllocMem(int a) allocate memory to the pointer using static memory
    void AllocMem(int a){
        int *temp = &a;
    }

    //•	void setValue(intval) Assigns the pointer to val
    void setValue( int val ){
        *ptr = val;
    }

    //•	int getValue() returns the contents of memory to which pointer is pointing
    int getValue(){
        return *ptr;
    }

    //•	Destructor that displays the address and value of the location pointed by ptr
    ~IntStaticPointer(){
        cout << "Address of pointer: " << &ptr << endl;
        cout << "Value of pointer: " << *ptr << endl;
        delete ptr;
        ptr = nullptr;
    }


};

void mystery(IntStaticPointer &b){
    int a = 100;
    b.AllocMem(a);
    cout << b.getValue();
}

int main(){
    IntStaticPointer b;
    int z = 8;
    b.AllocMem(z);
    cout << b.getValue() << endl;           //value of z=8
    mystery(b);                             //value of a=100
    cout << "\n"<< b.getValue() << endl;    //value of a=100

    
    return 0;
}