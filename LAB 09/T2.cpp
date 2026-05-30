#include<iostream>
#include<string>
#include<stack>

using namespace std;

void validation(string& text){

    int index = 0;
    int valid = 0;
    stack<char> st;

    for(char ch: text){
        if(ch=='(' || ch=='[' || ch=='{'){
            st.push(ch);
        }
        else if(ch == ')'){
            if (st.empty() || st.top() != '('){
                cout << "Error @ index " << index << endl;
                return;
            }
            st.pop();
            valid++;
        }
        else if(ch == '}'){
            if (st.empty() || st.top() != '{'){
                cout << "Error @ index " << index << endl;
                return;
            }
            st.pop();
            valid++;
        }
        else if(ch == ']'){
            if (st.empty() || st.top() != '['){
                cout << "Error @ index " << index << endl;
                return;
            }
            st.pop();
            valid++;
        }
        index++;
    }

    if(st.empty()){
        cout << "Balanced valid pairs: " << valid << endl;
    }
    else {
        cout << "Unbalanced " << endl;
    }
}

int main(){
    string text;
    cout << "Enter expression: ";
    
    getline(cin, text); 
    
    validation(text);
    
    cout << "Input processed: " << text << endl;

    system("pause>0");
    return 0;
}