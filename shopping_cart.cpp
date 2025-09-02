#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// Product class
class Product {
public:
    int id;
    string name;
    double price;

    Product(int id, string name, double price) {
        this->id = id;
        this->name = name;
        this->price = price;
    }
};

// Cart Item (Product + Quantity)
class CartItem {
public:
    Product product;
    int quantity;

    CartItem(Product product, int quantity) : product(product), quantity(quantity) {}
};

// Shopping Cart
class ShoppingCart {
private:
    vector<CartItem> items;

public:
    // Add product to cart
    void addItem(Product product, int quantity) {
        for (auto &item : items) {
            if (item.product.id == product.id) {
                item.quantity += quantity;
                cout << "Updated quantity of " << product.name << " to " << item.quantity << endl;
                return;
            }
        }
        items.push_back(CartItem(product, quantity));
        cout << product.name << " added to cart." << endl;
    }

    // Remove product from cart
    void removeItem(int productId) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->product.id == productId) {
                cout << it->product.name << " removed from cart." << endl;
                items.erase(it);
                return;
            }
        }
        cout << "Product not found in cart!" << endl;
    }

    // View all items in cart
    void viewCart() {
        if (items.empty()) {
            cout << " Cart is empty!" << endl;
            return;
        }

        cout << "\n Shopping Cart \n";
        cout << left << setw(5) << "ID" << setw(15) << "Product" 
             << setw(10) << "Price" << setw(10) << "Quantity" 
             << setw(10) << "Total" << endl;

        double total = 0;
        for (auto &item : items) {
            double itemTotal = item.product.price * item.quantity;
            total += itemTotal;
            cout << left << setw(5) << item.product.id 
                 << setw(15) << item.product.name
                 << setw(10) << item.product.price 
                 << setw(10) << item.quantity
                 << setw(10) << itemTotal << endl;
        }
        cout << "-----------------------------\n";
        cout << "Total Bill: $" << total << "\n";
    }
};

// Main Function
int main() {
    // Sample product list
    vector<Product> products = {
        Product(1, "Laptop", 75000.0),
        Product(2, "Smartphone", 25000.0),
        Product(3, "Headphones", 2000.0),
        Product(4, "Keyboard", 1500.0)
    };

    ShoppingCart cart;
    int choice;

    while (true) {
        cout << "\n Shopping Cart Menu \n";
        cout << "1. View Products\n";
        cout << "2. Add to Cart\n";
        cout << "3. Remove from Cart\n";
        cout << "4. View Cart\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\nAvailable Products:\n";
            for (auto &p : products) {
                cout << p.id << ". " << p.name << " - $" << p.price << endl;
            }
        }
        else if (choice == 2) {
            int pid, qty;
            cout << "Enter Product ID: ";
            cin >> pid;
            cout << "Enter Quantity: ";
            cin >> qty;

            bool found = false;
            for (auto &p : products) {
                if (p.id == pid) {
                    cart.addItem(p, qty);
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Invalid Product ID!\n";
        }
        else if (choice == 3) {
            int pid;
            cout << "Enter Product ID to remove: ";
            cin >> pid;
            cart.removeItem(pid);
        }
        else if (choice == 4) {
            cart.viewCart();
        }
        else if (choice == 5) {
            cout << "Thank you for shopping! \n";
            break;
        }
        else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
