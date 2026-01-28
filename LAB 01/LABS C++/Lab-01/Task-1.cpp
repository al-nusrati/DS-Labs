#include <iostream>
using namespace std;

int main(){
    
    // Declare the variable fPtr to be a pointer to a variable of type double and initialize the pointer to nullptr
    float number1(5.6), number2;
    double *fptr = new double;
    fptr = nullptr;

    // Can you de-refer the above pointer and display its value?
    cout << "NO! fptr cannot be dereferenced yet. " << endl;

    // Assign the address of variable number1 to pointer variable fPtr
    double temp = static_cast<double>(number1);
    fptr = &temp;

    // Display the value of the variable pointed to by fPtr.
    cout << "Value of number 1 using fptr = " << *fptr << endl;

    // Assign the value of the variable pointed to by fPtr to variable number2
    number2 = *fptr;
    
    // Display the value of number2
    cout << "Value of number 2 = " << number2 << endl;

    // Display the value of address number 1
    cout << "Address of number 1: " << &number1 << endl;

    // Display th eaddress stored in fptr
    cout << "Address of stored fptr: " << &fptr << endl;

    delete fptr;
    fptr = nullptr;
    return 0;
}