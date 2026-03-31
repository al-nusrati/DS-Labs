#include<iostream>
#include<stack>
#include<string>
using namespace std;

class ValidatorSetup{
public:

    void validate(string expr){
        stack<int> s; 
        int validPairs = 0;

        for (int i = 0; i < expr.length(); i++){
            char ch = expr[i];
            if(ch == '(' || ch == '{' || ch == '[')    s.push(i);
            else if(ch == ')' || ch == '}' || ch == ']'){
                if(s.empty())    {cout << "Unbalanced-> First mismatch at position: " << i << "\nValid pairs: " << validPairs << endl;   return;}
                char topChar = expr[s.top()];
                if((ch == ')' && topChar == '(') || (ch == '}' && topChar == '{') || (ch == ']' && topChar == '[')){    s.pop();    validPairs++;}
                else    {cout << "Unbalanced-> First mismatch at position: " << i << "\nValid pairs: " << validPairs << endl;   return;}
            }
        }
        if(!s.empty())    {cout << "Unbalanced! First mismatch at position: " << s.top() << " (Unclosed bracket)\nValid pairs: " << validPairs << endl;   return;}
        cout << "Expression is Balanced." << endl;
        cout << "Total valid pairs: " << validPairs << endl;
    }

};

int main(){
    ValidatorSetup val;
    
    string expr1 = "{[()]}";
    cout << "Testing: " << expr1 << endl;
    val.validate(expr1);

    cout << "\nTesting: {[(])}" << endl;
    val.validate("{[(])}");

    cout << "\nTesting: ((()" << endl;
    val.validate("((()");

    cin.ignore();
    cin.get();    
    return 0;
}