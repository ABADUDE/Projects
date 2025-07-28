// Final Fixed and Optimized Restaurant Management System with Improved Design
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const int MAX_DISHES = 30;
const int MAX_CUSTOMERS = 30;
const char registration_number[MAX_CUSTOMERS][6] = {
    "26110", "41207", "53642", "17345", "39474", "15873", "30972", "93279", "25676", "54120",
    "36021", "71223", "68123", "17129", "76128", "91724", "74354", "24632", "86521", "89652",
    "91645", "83213", "86473", "23637", "87546", "47364", "83746", "13874", "73898", "83827"
};

void drawLine(int length = 50, char ch = '=') {
    for (int i = 0; i < length; ++i) cout << ch;
    cout << endl;
}

void drawBoxHeader(const string &title) {
    drawLine();
    cout << "| " << setw(46) << left << title << "|" << endl;
    drawLine();
}

void View_Menu(int numDishes, char dishNames[][30], long dishPrices[]) {
    drawBoxHeader("USBLE YANGER MENU");
    cout << "|  No. | " << setw(30) << left << "DISH NAME" << "| PRICE (Rs)  |" << endl;
    drawLine();
    for (int i = 0; i < numDishes; ++i) {
        cout << "|  " << setw(3) << left << i + 1 << " | " << setw(30) << left << dishNames[i]
             << "| " << setw(11) << left << dishPrices[i] << "|" << endl;
    }
    drawLine();
}

void Edit_Menu(int &numDishes, char dishNames[][30], long dishPrices[]) {
    char choice;
    while (true) {
        drawBoxHeader("MENU EDITING");
        View_Menu(numDishes, dishNames, dishPrices);

        cout << "Options:\n(+) Add Dishes\n($) Edit Dish Price\n(*) Exit Editing\nEnter Choice: ";
        cin >> choice;

        if (choice == '+') {
            int addCount;
            cout << "\nHow many dishes to add? ";
            cin >> addCount;
            if (numDishes + addCount > MAX_DISHES) {
                cout << "Cannot exceed maximum limit of dishes.\n";
                continue;
            }
            cin.ignore();
            for (int i = 0; i < addCount; ++i) {
                cout << "\nEnter Dish Name: ";
                cin.getline(dishNames[numDishes], 30);
                cout << "Enter Price: ";
                cin >> dishPrices[numDishes];
                cin.ignore();
                numDishes++;
            }
        } else if (choice == '$') {
            int dishNum;
            cout << "\nEnter Dish Number to edit price: ";
            cin >> dishNum;
            if (dishNum >= 1 && dishNum <= numDishes) {
                cout << "New Price for " << dishNames[dishNum - 1] << ": ";
                cin >> dishPrices[dishNum - 1];
            } else {
                cout << "Invalid dish number.\n";
            }
        } else if (choice == '*') {
            break;
        } else {
            cout << "Invalid option.\n";
        }
    }
}

void Place_Order(int numDishes, char dishNames[][30], long dishPrices[], long &balance, int &totalCost) {
    totalCost = 0;
    drawBoxHeader("ORDER PLACEMENT");
    while (true) {
        int dishNum, qty;
        cout << "\nEnter Dish Number to order (0 to finish): ";
        cin >> dishNum;
        if (dishNum == 0) break;
        if (dishNum >= 1 && dishNum <= numDishes) {
            cout << "Quantity: ";
            cin >> qty;
            if (qty > 0) {
                int cost = qty * dishPrices[dishNum - 1];
                totalCost += cost;
                cout << "Ordered " << qty << " x " << dishNames[dishNum - 1] << " = Rs." << cost << endl;
            } else {
                cout << "Quantity must be positive.\n";
            }
        } else {
            cout << "Invalid dish number.\n";
        }
    }
    cout << "\nTotal Order Cost: Rs." << totalCost << endl;
    drawLine();
}

void Pay_Bill(long &balance, int totalCost) {
    drawBoxHeader("PAYMENT");
    cout << "Balance: Rs." << balance << endl;
    if (balance >= totalCost) {
        balance -= totalCost;
        cout << "Payment successful! Remaining Balance: Rs." << balance << endl;
    } else {
        cout << "Insufficient balance. Please recharge.\n";
    }
    drawLine();
}

void Create_Account(int index, int numDishes, char dishNames[][30], long dishPrices[], long long phone[], char usernames[][30], char passwords[][30], long balances[], int costs[]) {
    char choice;
    drawBoxHeader("CUSTOMER PORTAL");
    cout << "Login (^) or Sign Up (+): ";
    cin >> choice;

    if (choice == '+') {
        cout << "\nEnter Phone Number: ";
        cin >> phone[index];
        cout << "Enter Username: ";
        cin >> usernames[index];
        cout << "Enter Password: ";
        cin >> passwords[index];
        cout << "Initial Balance: ";
        cin >> balances[index];
        cout << "\nYour Registration Number: |" << registration_number[index] << "|\n";

        View_Menu(numDishes, dishNames, dishPrices);
        Place_Order(numDishes, dishNames, dishPrices, balances[index], costs[index]);
        Pay_Bill(balances[index], costs[index]);
    } else if (choice == '^') {
        string reg;
        cout << "\nEnter Registration Number: ";
        cin >> reg;
        for (int i = 0; i < MAX_CUSTOMERS; ++i) {
            if (reg == registration_number[i]) {
                View_Menu(numDishes, dishNames, dishPrices);
                Place_Order(numDishes, dishNames, dishPrices, balances[i], costs[i]);
                Pay_Bill(balances[i], costs[i]);
                return;
            }
        }
        cout << "Invalid Registration Number.\n";
    }
}

void Calculate_Revenue(int costs[], int size) {
    long revenue = 0;
    for (int i = 0; i < size; ++i) revenue += costs[i];
    drawBoxHeader("REVENUE REPORT");
    cout << "Total Revenue: Rs." << revenue << endl;
    drawLine();
}

int main() {
    int numDishes = 15, option, customerIndex = 0;
    char dishNames[MAX_DISHES][30] = {
        "Rolls", "Bruschetta", "Chicken Wings", "Spaghetti Bolognese", "Grilled Salmon",
        "Margherita Pizza", "Tiramisu", "Chocolate Fondue", "Cheesecake", "Fresh Orange Juice",
        "Cappuccino", "Iced Tea", "Crown Crust Pizza", "Chicken Lasagna", "Sausages Pasta"};
    long dishPrices[MAX_DISHES] = {
        1000, 800, 450, 900, 1200, 1700, 1300, 1100, 700, 150, 250, 200, 1500, 850, 1000};
    long long phone[MAX_CUSTOMERS];
    long balances[MAX_CUSTOMERS] = {};
    char usernames[MAX_CUSTOMERS][30] = {};
    char passwords[MAX_CUSTOMERS][30] = {};
    int costs[MAX_CUSTOMERS] = {};

    while (customerIndex < MAX_CUSTOMERS) {
        drawBoxHeader("WELCOME TO USBLE YANGER RESTAURANT");
        cout << "(1) Customer\n(2) Staff\nChoice: ";
        cin >> option;

        if (option == 1) {
            Create_Account(customerIndex, numDishes, dishNames, dishPrices, phone, usernames, passwords, balances, costs);
            customerIndex++;
        } else if (option == 2) {
            char uname[15], pw[15], op;
            drawBoxHeader("STAFF LOGIN");
            cout << "Username: "; cin >> uname;
            cout << "Password: "; cin >> pw;
            cout << "\n(+) Edit Menu\n(=) View Revenue\nEnter: ";
            cin >> op;
            if (op == '+') {
                Edit_Menu(numDishes, dishNames, dishPrices);
            } else if (op == '=') {
                Calculate_Revenue(costs, MAX_CUSTOMERS);
            }
        } else {
            cout << "Invalid selection.\n";
        }
    }
    return 0;
}
