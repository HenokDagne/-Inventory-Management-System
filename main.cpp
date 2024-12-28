#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;

struct Product {
    string id;
    string name;
    int quantity;
    double price;
    string timestamp;
    Product* next;
    Product() {};
};

struct HistoryNode {
    string event;
    string id;
    string name;
    string timestamp;
    HistoryNode* next;
};

Product* head = nullptr;
HistoryNode* historyTop = nullptr;

// Utility to get the current timestamp
string getCurrentTimestamp() {
    time_t now = time(0);
    char* dt = ctime(&now);
    string timestamp(dt);
    timestamp.pop_back(); // Remove trailing newline
    return timestamp;
}

// Push an event into the history stack
void pushHistory(const string& event, const string& id, const string& name) {
    auto* newNode = new HistoryNode();
    newNode->event = event;
    newNode->id = id;
    newNode->name = name;
    newNode->timestamp = getCurrentTimestamp();
    newNode->next = historyTop;
    historyTop = newNode;
}

HistoryNode* popHistory() {
    if (historyTop == nullptr) {
        return nullptr;
    }
    HistoryNode* temp = historyTop;
    historyTop = historyTop->next;
    return temp;
}

void addProduct() {
    auto* newProduct = new Product();

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

    newProduct->timestamp = getCurrentTimestamp();
    newProduct->next = head;
    head = newProduct;

    // Push to history
    pushHistory("Added", newProduct->id, newProduct->name);
}

void removeProduct() {
    string id;
    cout << "Enter the product ID to remove: ";
    cin >> id;

    // Check if the inventory is empty
    if (head == nullptr) {
        cout << "There are no products in the inventory.\n";
        return;
    }

    Product* current = head;
    Product* prev = nullptr;

    // Traverse the linked list to find the product
    while (current != nullptr) {
        if (current->id == id) {
            if (prev == nullptr) {
                head = current->next;
            } else {
                prev->next = current->next;
                current->next = nullptr;
            }
            // Push to history
            pushHistory("Removed", current->id, current->name);
            delete current;
            cout << "Product with ID " << id << " removed successfully." << endl;
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "Product not found." << endl;
}

void updateProduct() {
    string id;
    cout << "Enter product ID to update: ";
    cin >> id;
    int quantity;
    Product* current = head;
    bool found = false;
    while (current != nullptr) {
        if (current->id == id) {
            cout << "Enter new quantity of product: ";
            cin >> quantity;
            current->quantity = quantity;
            current->timestamp = getCurrentTimestamp();
            // Push to history
            pushHistory("Updated", current->id, current->name);
            found = true;
            break;
        }
        current = current->next;
    }
    if (!found) {
        cout << "Product not found." << endl;
    }
}

void displayProducts() {
    Product* current = head;
    if (current == nullptr) {
        cout << "No products Available." << endl;
        return;
    }

    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << setw(20) << "Timestamp" << endl;
    while (current != nullptr) {
        cout << left << setw(10) << current->id << setw(20) << current->name << setw(10) << current->price << setw(10) << current->quantity << setw(20) << current->timestamp << endl;
        current = current->next;
    }
}

void displayOrderHistory() {
    if (historyTop == nullptr) {
        cout << "No order history available." << endl;
        return;
    }

    cout << "Order History:\n";
    cout << "--------------------------------------------------------------------------------\n";
    cout << left << setw(10) << "Event" << setw(10) << "ID" << setw(20) << "Name" << setw(20) << "Timestamp" << endl;
    cout << "---------------------------------------------------------------------------------\n";

    while (historyTop != nullptr) {
        HistoryNode* event = popHistory();

        // Display event details
        cout << left << setw(10) << event->event
             << setw(10) << event->id
             << setw(20) << event->name
             << setw(20) << event->timestamp << endl;

        delete event; // Free the memory of the history node
    }

    cout << "-------------------------------------------------------------\n";
}

void option() {
    cout << "1. Add product" << endl;
    cout << "2. Display products" << endl;
    cout << "3. Update product" << endl;
    cout << "4. Delete product" << endl;
    cout << "5. Display order history" << endl;
    cout << "6. Exit" << endl;
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
        case '5':
            displayOrderHistory();
            break;
        case '6':
            exit(0);
        default:
            cout << "Invalid option. Please choose again." << endl;
    }
}

int main() {
    while (true) {
        option();
        cout << "If you want to continue the program enter Y, otherwise enter N: " << endl;
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