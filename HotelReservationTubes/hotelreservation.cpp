#include <iostream>
#include "hotel.h"
using namespace std;

// ===== HEAD POINTERS =====
User *userHead = NULL;
Room *roomHead = NULL;

// ===== USER FUNCTIONS =====
void insertUser(string u, string p, bool admin) {
    User *newUser = new User;
    newUser->username = u;
    newUser->password = p;
    newUser->isAdmin = admin;
    newUser->firstRes = NULL;
    newUser->next = NULL;

    if (userHead == NULL)
        userHead = newUser;
    else {
        User *temp = userHead;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newUser;
    }
}

User* login(string u, string p) {
    User *temp = userHead;
    while (temp != NULL) {
        if (temp->username == u && temp->password == p)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// ===== ROOM FUNCTIONS =====
void insertRoom(int no, string type, int price) {
    Room *newRoom = new Room;
    newRoom->roomNumber = no;
    newRoom->type = type;
    newRoom->price = price;
    newRoom->available = true;
    newRoom->next = NULL;

    if (roomHead == NULL)
        roomHead = newRoom;
    else {
        Room *temp = roomHead;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newRoom;
    }
}

Room* findRoom(int no) {
    Room *temp = roomHead;
    while (temp != NULL) {
        if (temp->roomNumber == no)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void viewRooms() {
    Room *temp = roomHead;
    cout << "\n--- ROOM LIST ---\n";
    while (temp != NULL) {
        cout << "Room " << temp->roomNumber
             << " | " << temp->type
             << " | Rp" << temp->price
             << " | " << (temp->available ? "Available" : "Booked")
             << endl;
        temp = temp->next;
    }
}

// ===== RESERVATION FUNCTIONS =====
void makeReservation(User *u) {
    int roomNo, nights;
    viewRooms();
    cout << "Choose room number: ";
    cin >> roomNo;

    Room *r = findRoom(roomNo);
    if (r != NULL && r->available) {
        cout << "Number of nights: ";
        cin >> nights;

        Reservation *newRes = new Reservation;
        newRes->roomNumber = roomNo;
        newRes->nights = nights;
        newRes->next = NULL;

        if (u->firstRes == NULL)
            u->firstRes = newRes;
        else {
            Reservation *temp = u->firstRes;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newRes;
        }

        r->available = false;
        cout << "Reservation successful!\n";
    } else {
        cout << "Room not available!\n";
    }
}

void viewAllReservations() {
    User *u = userHead;
    cout << "\n--- ALL RESERVATIONS ---\n";
    while (u != NULL) {
        Reservation *r = u->firstRes;
        while (r != NULL) {
            cout << "User: " << u->username
                 << " | Room: " << r->roomNumber
                 << " | Nights: " << r->nights
                 << endl;
            r = r->next;
        }
        u = u->next;
    }
}

// ===== MENUS =====
void adminMenu() {
    int ch;
    do {
        cout << "\n--- ADMIN MENU ---\n";
        cout << "1. View Rooms\n";
        cout << "2. View All Reservations\n";
        cout << "0. Logout\n";
        cout << "Choice: ";
        cin >> ch;

        if (ch == 1) viewRooms();
        else if (ch == 2) viewAllReservations();
    } while (ch != 0);
}

void userMenu(User *u) {
    int ch;
    do {
        cout << "\n--- USER MENU ---\n";
        cout << "1. View Rooms\n";
        cout << "2. Make Reservation\n";
        cout << "0. Logout\n";
        cout << "Choice: ";
        cin >> ch;

        if (ch == 1) viewRooms();
        else if (ch == 2) makeReservation(u);
    } while (ch != 0);
}
