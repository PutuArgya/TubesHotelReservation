#include <iostream>
#include "hotel.h"
using namespace std;

int main() {
    // Initial data
    insertUser("admin", "admin123", true);
    insertUser("user", "user123", false);

    insertRoom(101, "Single", 300000);
    insertRoom(102, "Single", 300000);
    insertRoom(201, "Double", 500000);
    insertRoom(301, "Suite", 800000);

    string u, p;
    cout << "=== HOTEL RESERVATION SYSTEM (MLL) ===\n";
    cout << "Username: ";
    cin >> u;
    cout << "Password: ";
    cin >> p;

    User *current = login(u, p);
    if (current != NULL) {
        cout << "Login successful!\n";
        if (current->isAdmin)
            adminMenu();
        else
            userMenu(current);
    } else {
        cout << "Login failed!\n";
    }

    return 0;
}


