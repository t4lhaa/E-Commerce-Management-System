#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #define CLEAR_SCREEN() system("cls")
#else
    #define CLEAR_SCREEN() system("clear")
#endif

#define MAX_ITEMS 20
#define MAX_CART_ITEMS 100
#define TAX_RATE 0.15  // 15% Tax Rate

int i;

// Global variables for items
char item_names[MAX_ITEMS][50] = {
    "Polo-Shirt", "Sweat-shirts", "Dress-shirt", "Jeans", "Sneakers", 
    "Cap", "Hoodie", "Watch", "Backpack", "Sunglasses",
    "Laptop", "Mouse", "Keyboard", "Headphones", "Charger"
};
float item_prices[MAX_ITEMS] = {
    1500, 1200, 3000, 2500, 5000,
    500, 2500, 8000, 4500, 3500,
    60000, 1500, 2000, 4000, 1200
};
int item_stock[MAX_ITEMS] = {
    10, 5, 2, 8, 6,
    20, 3, 4, 6, 7,
    5, 10, 12, 8, 15
};

int item_count = 15;  // Initial number of items
float total_sales = 0.0;  // Track total sales

struct CartItem {
    char name[50];
    float price;
    int quantity;
};

struct CartItem cart[MAX_CART_ITEMS];
int cart_count = 0;
float total_price = 0.0;

// Function Prototypes
void admin_panel();
void customer_panel();
void view_low_stock();
void restock_item();
void remove_stock();
void add_new_item();
void view_all_stock();
void display_items();
void add_to_cart();
void view_cart();
void remove_from_cart();
void finalize_order();
void print_bill(char customer_name[], char customer_address[], char customer_phone[]);

// Main function
int main() {
    int user_option;
    do {
        CLEAR_SCREEN();
        printf("--------------------------------------------------\n");
        printf("Welcome to the E-commerce Management System\n");
        printf("--------------------------------------------------\n");
        printf("1. Admin Panel\n");
        printf("2. Customer Panel\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &user_option);

        switch (user_option) {
            case 1:
                admin_panel();
                break;
            case 2:
                customer_panel();
                break;
            case 3:
                printf("\nThank you for using the system. Goodbye!\n");
                break;
            default:
                printf("\nInvalid option! Please try again.\n");
                break;
        }
    } while (user_option != 3);
    return 0;
}

// Admin Panel
void admin_panel() {
    int admin_option;
    do {
        CLEAR_SCREEN();
        printf("--------------------------------------------------\n");
        printf("Admin Panel\n");
        printf("--------------------------------------------------\n");
        printf("1. View Low Stock Items\n");
        printf("2. View All Stock\n");
        printf("3. Restock Item\n");
        printf("4. Remove Stock\n");
        printf("5. Add New Item\n");
        printf("6. View Total Sales\n");
        printf("7. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &admin_option);

        switch (admin_option) {
            case 1:
                view_low_stock();
                break;
            case 2:
                view_all_stock();
                break;
            case 3:
                restock_item();
                break;
            case 4:
                remove_stock();
                break;
            case 5:
                add_new_item();
                break;
            case 6:
                printf("\nTotal Sales: %.2f PKR\n", total_sales);
                printf("\nPress Enter to continue...");
                getchar();
                getchar();
                break;
            case 7:
                printf("\nLogging out...\n");
                break;
            default:
                printf("\nInvalid option! Please try again.\n");
                break;
        }
    } while (admin_option != 7);
}

// View items with low stock
void view_low_stock() {
    CLEAR_SCREEN();
    printf("--------------------------------------------------\n");
    printf("Low Stock Items\n");
    printf("--------------------------------------------------\n");
    int found = 0;
    for (i = 0; i < item_count; i++) {
        if (item_stock[i] < 5) {
            printf("%d. %-20s - Stock: %d\n", i + 1, item_names[i], item_stock[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("No items with low stock.\n");
    }
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

// View all stock details
void view_all_stock() {
    CLEAR_SCREEN();
    printf("--------------------------------------------------\n");
    printf("All Stock Items\n");
    printf("--------------------------------------------------\n");
    for (i = 0; i < item_count; i++) {
        printf("%d. %-20s - Price: %.2f PKR - Stock: %d\n", i + 1, item_names[i], item_prices[i], item_stock[i]);
    }
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

// Restock an item
void restock_item() {
    int choice, quantity;
    CLEAR_SCREEN();
    printf("--------------------------------------------------\n");
    printf("Restock Item\n");
    printf("--------------------------------------------------\n");
    for (i = 0; i < item_count; i++) {
        printf("%d. %-20s - Stock: %d\n", i + 1, item_names[i], item_stock[i]);
    }
    printf("\nEnter the number of the item to restock (0 to cancel): ");
    scanf("%d", &choice);

    if (choice == 0) {
        return;
    }

    if (choice >= 1 && choice <= item_count) {
        printf("Enter quantity to add: ");
        scanf("%d", &quantity);
        if (quantity > 0) {
            item_stock[choice - 1] += quantity;
            printf("\nStock updated! %s now has %d units.\n", item_names[choice - 1], item_stock[choice - 1]);
        } else {
            printf("\nInvalid quantity! Must be positive.\n");
        }
    } else {
        printf("\nInvalid item choice.\n");
    }
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

// Remove stock of an item
void remove_stock() {
    int choice, quantity;
    CLEAR_SCREEN();
    printf("--------------------------------------------------\n");
    printf("Remove Stock\n");
    printf("--------------------------------------------------\n");
    for (i = 0; i < item_count; i++) {
        printf("%d. %-20s - Stock: %d\n", i + 1, item_names[i], item_stock[i]);
    }
    printf("\nEnter the number of the item to remove stock (0 to cancel): ");
    scanf("%d", &choice);

    if (choice == 0) {
        return;
    }

    if (choice >= 1 && choice <= item_count) {
        printf("Enter quantity to remove: ");
        scanf("%d", &quantity);
        if (quantity > 0 && quantity <= item_stock[choice - 1]) {
            item_stock[choice - 1] -= quantity;
            printf("\nStock updated! %s now has %d units.\n", item_names[choice - 1], item_stock[choice - 1]);
        } else {
            printf("\nInvalid quantity! Must be between 1 and %d.\n", item_stock[choice - 1]);
        }
    } else {
        printf("\nInvalid item choice.\n");
    }
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

// Add a new item
void add_new_item() {
    if (item_count >= MAX_ITEMS) {
        printf("\nInventory full! Cannot add more items.\n");
        return;
    }
    CLEAR_SCREEN();
    printf("--------------------------------------------------\n");
    printf("Add New Item\n");
    printf("--------------------------------------------------\n");
    printf("Enter item name: ");
    getchar();
    fgets(item_names[item_count], sizeof(item_names[item_count]), stdin);
    item_names[item_count][strcspn(item_names[item_count], "\n")] = 0; // Remove newline

    printf("Enter item price: ");
    scanf("%f", &item_prices[item_count]);

    printf("Enter initial stock: ");
    scanf("%d", &item_stock[item_count]);

    item_count++;
    printf("\nItem added successfully!\n");
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

// Customer Panel
void customer_panel() {
    int choice;
    do {
        CLEAR_SCREEN();
        printf("--------------------------------------------------\n");
        printf("Customer Panel\n");
        printf("--------------------------------------------------\n");
        printf("1. View Items\n");
        printf("2. Add Item to Cart\n");
        printf("3. View Cart\n");
        printf("4. Remove Item from Cart\n");
        printf("5. Finalize Order\n");
        printf("6. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_items();
                break;
            case 2:
                add_to_cart();
                break;
            case 3:
                view_cart();
                break;
            case 4:
                remove_from_cart();
                break;
            case 5:
                finalize_order();
                break;
            case 6:
                printf("\nLogging out...\n");
                break;
            default:
                printf("\nInvalid option! Please try again.\n");
                break;
        }
    } while (choice != 6);
}

// Display all items
void display_items() {
    CLEAR_SCREEN();
    printf("--------------------------------------------------\n");
    printf("Items Available\n");
    printf("--------------------------------------------------\n");
    for (i = 0; i < item_count; i++) {
        printf("%d. %-20s - Price: %.2f PKR - Stock: %d\n", i + 1, item_names[i], item_prices[i], item_stock[i]);
    }
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

// Add item to cart
void add_to_cart() {
    int item_number, quantity;
    CLEAR_SCREEN();
    display_items();

    printf("\nEnter the item number to add to cart (0 to cancel): ");
    scanf("%d", &item_number);

    if (item_number == 0) return;

    if (item_number >= 1 && item_number <= item_count) {
        printf("Enter quantity: ");
        scanf("%d", &quantity);

        if (quantity <= item_stock[item_number - 1] && quantity > 0) {
            cart[cart_count].price = item_prices[item_number - 1];
            cart[cart_count].quantity = quantity;
            strcpy(cart[cart_count].name, item_names[item_number - 1]);
            cart_count++;

            item_stock[item_number - 1] -= quantity;
            printf("\nItem added to cart!\n");
        } else {
            printf("\nInsufficient stock or invalid quantity!\n");
        }
    } else {
        printf("\nInvalid item number!\n");
    }
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

// View items in cart
void view_cart() {
    CLEAR_SCREEN();
    if (cart_count == 0) {
        printf("No items in cart!\n");
    } else {
        printf("--------------------------------------------------\n");
        printf("Your Cart\n");
        printf("--------------------------------------------------\n");
        total_price = 0.0;
        for (i = 0; i < cart_count; i++) {
            float item_total = cart[i].price * cart[i].quantity;
            total_price += item_total;
            printf("%d. %-20s - %.2f PKR x %d = %.2f PKR\n", i + 1, cart[i].name, cart[i].price, cart[i].quantity, item_total);
        }
        printf("\nTotal Price: %.2f PKR\n", total_price);
    }
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

// Remove item from cart
void remove_from_cart() {
    int cart_index;
    CLEAR_SCREEN();
    view_cart();

    if (cart_count == 0) return;

    printf("\nEnter the item number to remove from cart (0 to cancel): ");
    scanf("%d", &cart_index);

    if (cart_index == 0) return;

    if (cart_index >= 1 && cart_index <= cart_count) {
        // Find the index of the item in the item_names array
        int item_index = -1;
        for (i = 0; i < item_count; i++) {
            if (strcmp(cart[cart_index - 1].name, item_names[i]) == 0) {
                item_index = i;
                break;
            }
        }

        // If the item was found in item_names
        if (item_index != -1) {
            item_stock[item_index] += cart[cart_index - 1].quantity;  // Add the quantity back to stock
            printf("\nItem removed from cart!\n");

            // Shift cart items to remove the item from cart
            for (i = cart_index - 1; i < cart_count - 1; i++) {
                cart[i] = cart[i + 1];
            }
            cart_count--;
        } else {
            printf("\nItem not found in inventory!\n");
        }
    } else {
        printf("\nInvalid item number!\n");
    }

    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

// Finalize order
void finalize_order() {
    char name[50], address[100], phone[15];
    CLEAR_SCREEN();
    if (cart_count == 0) {
        printf("Your cart is empty! Cannot proceed with the order.\n");
        return;
    }
    printf("--------------------------------------------------\n");
    printf("Finalize Order\n");
    printf("--------------------------------------------------\n");
    printf("Enter your name: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Enter your address: ");
    fgets(address, sizeof(address), stdin);
    address[strcspn(address, "\n")] = 0;

    printf("Enter your phone number: ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = 0;

    print_bill(name, address, phone);

    total_sales += total_price;
    cart_count = 0;
    total_price = 0.0;
    printf("\nOrder finalized! Thank you for shopping.\n");
    printf("\nPress Enter to continue...");
    getchar();
}

// Print the final bill
void print_bill(char customer_name[], char customer_address[], char customer_phone[]) {
    CLEAR_SCREEN();
    printf("--------------------------------------------------\n");
    printf("Receipt\n");
    printf("--------------------------------------------------\n");
    printf("Customer Name: %s\n", customer_name);
    printf("Address: %s\n", customer_address);
    printf("Phone: %s\n", customer_phone);
    printf("--------------------------------------------------\n");
    for (i = 0; i < cart_count; i++) {
        float item_total = cart[i].price * cart[i].quantity;
        printf("%d. %-20s - %.2f PKR x %d = %.2f PKR\n", i + 1, cart[i].name, cart[i].price, cart[i].quantity, item_total);
    }
    printf("\nTotal Price: %.2f PKR\n", total_price);
    printf("\n--------------------------------------------------\n");
    printf("Thank you for your order!\n");
}

