#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Product {
    int id;
    string name;
    int quantity;
    double price;
};

vector<Product> inventory;
int productCount = 0;

void saveInventory() {
    ofstream file("inventory.txt");
    if (!file) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }
    for (const auto& product : inventory) {
        file << product.id << " " << product.name << " "
             << product.quantity << " " << product.price << endl;
    }
    file.close();
}

void loadInventory() {
    ifstream file("inventory.txt");
    if (!file) {
        cerr << "No previous inventory data found." << endl;
        return;
    }
    Product product;
    while (file >> product.id >> product.name >> product.quantity >> product.price) {
        inventory.push_back(product);
        productCount = max(productCount, product.id); // Keep track of the highest ID
    }
    file.close();
}

void addProduct() {
    Product newProduct;
    newProduct.id = ++productCount;
    cout << "Enter product name: ";
    cin >> newProduct.name;
    
    do {
        cout << "Enter quantity: ";
        cin >> newProduct.quantity;
    } while (newProduct.quantity < 0);

    do {
        cout << "Enter price: ";
        cin >> newProduct.price;
    } while (newProduct.price < 0);
    
    inventory.push_back(newProduct);
    cout << "Product added successfully!" << endl;
}

void removeProduct(int id) {
    auto it = remove_if(inventory.begin(), inventory.end(), [id](const Product& p) {
        return p.id == id;
    });
    if (it != inventory.end()) {
        inventory.erase(it, inventory.end());
        cout << "Product removed successfully." << endl;
    } else {
        cout << "Product not found." << endl;
    }
}

void updateProduct(int id) {
    for (auto& product : inventory) {
        if (product.id == id) {
            cout << "Enter new quantity: ";
            cin >> product.quantity;
            cout << "Enter new price: ";
            cin >> product.price;
            cout << "Product updated successfully!" << endl;
            return;
        }
    }
    cout << "Product not found." << endl;
}

void viewAllProducts() {
    if (inventory.empty()) {
        cout << "No products available." << endl;
        return;
    }
    cout << "\nInventory:\n";
    for (const auto& product : inventory) {
        cout << "ID: " << product.id << ", Name: " << product.name
             << ", Quantity: " << product.quantity << ", Price: $" << product.price << endl;
    }
}

void searchProduct() {
    string searchName;
    cout << "Enter product name to search: ";
    cin >> searchName;

    for (const auto& product : inventory) {
        if (product.name == searchName) {
            cout << "ID: " << product.id << ", Name: " << product.name
                 << ", Quantity: " << product.quantity << ", Price: $" << product.price << endl;
            return;
        }
    }
    cout << "Product not found." << endl;
}

void sortInventory() {
    sort(inventory.begin(), inventory.end(), [](const Product& a, const Product& b) {
        return a.name < b.name;
    });
    cout << "Inventory sorted by name." << endl;
}

void menu() {
    int choice;
    while (true) {
        cout << "\nInventory Management System\n";
        cout << "1. Add Product\n";
        cout << "2. View All Products\n";
        cout << "3. Remove Product\n";
        cout << "4. Update Product\n";
        cout << "5. Save Inventory\n";
        cout << "6. Load Inventory\n";
        cout << "7. Search Product\n";
        cout << "8. Sort Products\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addProduct(); break;
            case 2: viewAllProducts(); break;
            case 3: {
                int id;
                cout << "Enter product ID to remove: ";
                cin >> id;
                removeProduct(id);
                break;
            }
            case 4: {
                int id;
                cout << "Enter product ID to update: ";
                cin >> id;
                updateProduct(id);
                break;
            }
            case 5: saveInventory(); break;
            case 6: loadInventory(); break;
            case 7: searchProduct(); break;
            case 8: sortInventory(); break;
            case 9: return;
            default: cout << "Invalid choice. Try again." << endl;
        }
    }
}

int main() {
    loadInventory();
    menu();
    saveInventory();
    return 0;
}

