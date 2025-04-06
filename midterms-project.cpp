#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

class InventoryItem {
private:
    int id;
    string name;
    string category;
    int quantity;
    double price;

public:
    InventoryItem(int id, string name, string category, int quantity, double price)
        : id(id), name(name), category(category), quantity(quantity), price(price) {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getCategory() const { return category; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }

    void setName(const string& newName) { name = newName; }
    void setCategory(const string& newCategory) { category = newCategory; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }
    void setPrice(double newPrice) { price = newPrice; }

    void display() const {
        cout << id << "\t" << name << "\t" << quantity << "\t\t" << price << "\t" << category << endl;
    }
};

void displayMenu() {
    cout << "\nMenu" << endl;
    cout << "1 - Add Item" << endl;
    cout << "2 - Update Item" << endl;
    cout << "3 - Remove Item" << endl;
    cout << "4 - Display All Items" << endl;
    cout << "5 - Search Item" << endl;
    cout << "6 - Sort Items" << endl;
    cout << "7 - Display Low Stock Items" << endl;
    cout << "8 - Exit" << endl;
}

void displayInventory(const vector<InventoryItem>& inventory) {
    cout << "\nID\tName\tQuantity\tPrice\tCategory" << endl;
    cout << "--------------------------------------------------" << endl;
    for (const auto& item : inventory) {
        item.display();
    }
}

void addItem(vector<InventoryItem>& inventory, int& id) {
    string name, category;
    int quantity;
    double price;

    cout << "Enter item name to add: ";
    getline(cin, name);

    cout << "Enter category: ";
    getline(cin, category);

    cout << "Enter quantity: ";
    cin >> quantity;

    cout << "Enter price: ";
    cin >> price;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    inventory.emplace_back(id++, name, category, quantity, price);
    cout << "Item added successfully!" << endl;
}

void updateItem(vector<InventoryItem>& inventory) {
    int productID;
    cout << "Enter product ID to update: ";
    cin >> productID;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    auto it = find_if(inventory.begin(), inventory.end(), [productID](const InventoryItem& item) {
        return item.getId() == productID;
    });

    if (it != inventory.end()) {
        int choice;
        cout << "1. Update Quantity\n2. Update Price\nEnter choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            int newQuantity;
            cout << "Enter new quantity: ";
            cin >> newQuantity;
            it->setQuantity(newQuantity);
            cout << "Quantity updated successfully!" << endl;
        }
        else if (choice == 2) {
            double newPrice;
            cout << "Enter new price: ";
            cin >> newPrice;
            it->setPrice(newPrice);
            cout << "Price updated successfully!" << endl;
        } else {
            cout << "Invalid choice!" << endl;
        }
    } else {
        cout << "Item not found!" << endl;
    }
}

void removeItem(vector<InventoryItem>& inventory) {
    int productID;
    cout << "Enter product ID to remove: ";
    cin >> productID;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    auto it = remove_if(inventory.begin(), inventory.end(), [productID](const InventoryItem& item) {
        return item.getId() == productID;
    });

    if (it != inventory.end()) {
        inventory.erase(it, inventory.end());
        cout << "Item removed successfully!" << endl;
    } else {
        cout << "Item not found!" << endl;
    }
}

void searchItem(const vector<InventoryItem>& inventory) {
    int productID;
    cout << "Enter product ID to search: ";
    cin >> productID;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    auto it = find_if(inventory.begin(), inventory.end(), [productID](const InventoryItem& item) {
        return item.getId() == productID;
    });

    if (it != inventory.end()) {
        cout << "\nItem found:" << endl;
        it->display();
    } else {
        cout << "Item not found!" << endl;
    }
}

void sortItems(vector<InventoryItem>& inventory) {
    int choice, order;
    cout << "1. Sort by Quantity\n2. Sort by Price\nEnter choice: ";
    cin >> choice;

    cout << "1. Ascending\n2. Descending\nEnter order: ";
    cin >> order;

    if (choice == 1) {
        if (order == 1) {
            sort(inventory.begin(), inventory.end(), [](const InventoryItem& a, const InventoryItem& b) {
                return a.getQuantity() < b.getQuantity();
            });
        } else {
            sort(inventory.begin(), inventory.end(), [](const InventoryItem& a, const InventoryItem& b) {
                return a.getQuantity() > b.getQuantity();
            });
        }
    } else if (choice == 2) {
        if (order == 1) {
            sort(inventory.begin(), inventory.end(), [](const InventoryItem& a, const InventoryItem& b) {
                return a.getPrice() < b.getPrice();
            });
        } else {
            sort(inventory.begin(), inventory.end(), [](const InventoryItem& a, const InventoryItem& b) {
                return a.getPrice() > b.getPrice();
            });
        }
    }

    cout << "Items sorted successfully!" << endl;
}

void displayLowStockItems(const vector<InventoryItem>& inventory) {
    cout << "\nLow Stock Items (Quantity <= 5):" << endl;
    for (const auto& item : inventory) {
        if (item.getQuantity() <= 5) {
            item.display();
        }
    }
}

int main() {
    vector<InventoryItem> inventory;
    int choice, id = 1;

    do {
        displayMenu();
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            addItem(inventory, id);
            break;
        case 2:
            updateItem(inventory);
            break;
        case 3:
            removeItem(inventory);
            break;
        case 4:
            displayInventory(inventory);
            break;
        case 5:
            searchItem(inventory);
            break;
        case 6:
            sortItems(inventory);
            break;
        case 7:
            displayLowStockItems(inventory);
            break;
        case 8:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 8);

    return 0;
}