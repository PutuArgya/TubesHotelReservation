#ifndef HOTEL_H
#define HOTEL_H

#include <string>
using namespace std;

struct Reservation {
    int roomNumber;
    int nights;
    Reservation *next;
};

struct User {
    string username;
    string password;
    bool isAdmin;
    Reservation *firstRes;
    User *next;
};

struct Room {
    int roomNumber;
    string type;
    int price;
    bool available;
    Room *next;
};

// User
void insertUser(string u, string p, bool admin);
User* login(string u, string p);

// Room
void insertRoom(int no, string type, int price);
void viewRooms();
Room* findRoom(int no);

// Reservation
void makeReservation(User *u);
void viewAllReservations();

// Menu
void adminMenu();
void userMenu(User *u);

//Mungkin nambah lagi...

#endif
