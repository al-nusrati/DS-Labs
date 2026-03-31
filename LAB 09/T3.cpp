#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

struct Product{
    int productID;
    string name;
    double price;
    string category;
};

bool comparePrice(Product a, Product b){
    return a.price < b.price;
}

void printProduct(Product p){
    cout << p.productID << " " << p.name << " (" << p.category << ") - PKR" << p.price << endl;
}

class ProductSetup{
private:
    vector<Product> products; // Stores products dynamically

public:

    void insert(int id, string name, double price, string category){
        Product temp;
        temp.productID = id;
        temp.name = name;
        temp.price = price;
        temp.category = category;
        products.push_back(temp);
    }    

    void sortByPrice(){
        if(products.empty())    {cout << "Products are empty." << endl;   return;}
        sort(products.begin(), products.end(), comparePrice);
        cout << "Products sorted by price successfully.\n" << endl;
    }

    void search(int id){
        if(products.empty())    {cout << "Products are empty." << endl;    return;}
        for (int i = 0; i < products.size();i++)    {
            if(products[i].productID==id)
            {    cout <<"Data for:"<<id<<" -> " <<products[i].name << " " << products[i].category <<" Price: PKR"<< products[i].price<< endl;     return;    }
        }
        cout << "Product not found" << endl;
    }

    int getCount(string category){
        int count = 0;
        for (int i = 0; i < products.size();i++)  {if(products[i].category==category)    count++;}        return count;
    }

    void increasePrice(double amount){
        if(products.empty())    {cout << "Products are empty." << endl;   return;}
        transform(products.begin(), products.end(), products.begin(), [amount](Product p){
            p.price += amount;
            return p;
        });
        cout << "Price increased by PKR" << amount << " for all products.\n" << endl;
    }

    void display(){ 
        if(products.empty())     {cout << "Products are empty." << endl;   return;}
        cout <<"--- Display Products --- \n";
        for_each(products.begin(), products.end(), printProduct);
        cout <<"\n";
    }

};

int main(){
    ProductSetup prod;
    
    prod.insert(101, "Laptop", 100000, "Electronics");
    prod.insert(102, "Desk", 15000, "Furniture");
    prod.insert(103, "Mouse", 500, "Electronics");
    prod.insert(104, "Chair", 2000, "Furniture");

    prod.display();

    cout << "Total products in Electronics: " << prod.getCount("Electronics") << "\n\n";

    int id;
    cout << "Enter id to search: ";
    cin >> id;
    prod.search(id);
    cout << "\n";

    prod.sortByPrice();
    prod.display();

    prod.increasePrice(50.00); 
    prod.display();

    cin.ignore();
    cin.get();    
    return 0;
}