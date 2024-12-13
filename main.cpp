#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Product {
    string id;
    string name;
    int quantity;
    double price;
    Product* next;
    Product(){};

};

Product* head = nullptr;

void addProduct() {
    auto* newProduct = new Product();
    home:

    // Check for duplicate ID
    Product* current = head;

        cout << "Enter product ID: ";
        cin >> newProduct->id;

        // Check for duplicate ID
        while (current != nullptr) {
            if (newProduct->id == current->id) {
                cout << "Product ID already exists. Please enter a unique ID." << endl;
               delete newProduct;
               return;

            }
            current = current->next;
        }


    cout << "Enter product name: ";
    cin.ignore();
    getline(cin, newProduct->name);

    cout << "Enter price: ";
    while (!(cin >> newProduct->price) || newProduct->price < 0 || cin.fail()) {
        cout << "Invalid input. Please enter a valid positive number for price: ";
        cin.clear();              // Clear the error flag
        cin.ignore(1000, '\n');   // Ignore the invalid input in the buffer
    }

    cout << "Enter quantity: ";
    while (!(cin >> newProduct->quantity) || newProduct->quantity <= 0 || cin.fail()) {
        cout << "Invalid input. Please enter a valid positive integer for quantity: ";
        cin.clear();              // Clear the error flag
        cin.ignore(1000, '\n');   // Ignore the invalid input in the buffer
    }

    newProduct->next = head;
    head = newProduct;
}
void removeProduct() {
    string id; // Assuming `Product::id` is of type int
    std::cout << "Enter the product ID to remove: ";
    std::cin >> id;

    // Check if the inventory is empty
    if (head == nullptr) {
        std::cout << "There are no products in the inventory.\n";
        return;
    }

    Product* current = head;
    Product* prev = nullptr;

    // Traverse the linked list to find the product
    while(current != nullptr) {
        if (current->id == id) {
            if (prev == nullptr) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            cout << "Product with ID " << id << " removed successfully." << endl;
            return;
        }
        prev = current;
        current = current->next;
    }
}
void updateProduct(){
    string id;
    cout << "Enter updateProduct ID: " ;
    cin >>id;
    int quantity;
    Product *current = head;
    bool found = false;
    while(current != nullptr){
        if (current->id ==id){
            cout << "Enter update price of product: " ;
            cin >> quantity;
            current->quantity = quantity;
            found = true;
            break;
        }
        current = current->next;
    }
    if (!found){
        cout << "Product not found." << endl;
    }
}
void displayProducts() {
    Product* current = head;
    if (current == nullptr) {
        cout << "No products available." << endl;
        return;
    }

    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
    while (current != nullptr) {
        cout << left << setw(10) << current->id << setw(20) << current->name << setw(10) << current->price << setw(10) << current->quantity << endl;
        current = current->next;
    }
}

void option() {
    cout << "1. Add product" << endl;
    cout << "2. Display products" << endl;
    cout << "3. Update product" << endl;
    cout << "4. Delete product" << endl;
    cout << "5. Exit" << endl;
    char choose;
    cout << "Enter choice: ";
    cin >> choose;
    switch (choose) {
        case '1':
            addProduct();
            break;
        case '2':
            displayProducts();
            break;
        case '3':
            updateProduct();
            break;
        case '4':
            removeProduct();
            break;
        default:
            cout << "Invalid option. Please choose again." << endl;
    }
}

int main() {
    while (true) {
        option();
        cout << "If you want to continue the program enter Y, otherwise enter N: ";
        char choose;
        cin >> choose;
        if (choose == 'n' || choose == 'N') {
            break;
        }
    }

    // Free allocated memory
    Product* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}