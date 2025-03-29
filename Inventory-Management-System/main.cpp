#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Product {
    string name;
    int quantity;
    double price;
};

void addProduct(Product inventory[], int& count) {
    // Add product to inventory
    cout << "Enter product name: ";
    cin >> inventory[count].name;
    cout << "Enter quantity: ";
    cin >> inventory[count].quantity;
    cout << "Enter price: ";
    cin >> inventory[count].price;
    
    count++; // Increment the product count
}

void viewAllProducts(const Product inventory[], int count) {
    cout << "Inventory:\n";
    for (int i = 0; i < count; i++) {
        cout << "Product " << i + 1 << ": " << inventory[i].name << ", Quantity: " << inventory[i].quantity << ", Price: $" << inventory[i].price << endl;
    }
}

int main() {
    Product inventory[100]; // Inventory can hold up to 100 products
    int productCount = 0;
    
    addProduct(inventory, productCount);
    viewAllProducts(inventory, productCount);

    return 0;
}

