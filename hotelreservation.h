#ifndef HOTEL_H
#define HOTEL_H
#include <iostream>
#include <string>

using namespace std;

typedef struct User *adrUser; 
typedef struct Reservation *adrReservation;
typedef struct Room *adrRoom; 

struct Reservation {
    int roomNumber;
    int nights;
    adrReservation next; 
    adrReservation prev; 
};

struct User {
    string username;
    string password;
    bool isAdmin;
    adrReservation firstRes;
    adrUser next;
};

struct Room {
    int roomNumber;
    string type;
    int price;
    bool available;
    adrRoom next;
};

struct listUsers {
    adrUser firstUser; 
    adrUser lastUser;
};

struct listRooms {
    adrRoom firstRoom; 
    adrRoom lastRoom; 
}; 

struct listReservation {
    adrReservation firstReserve; 
    adrReservation lastReserve; 
};

// User
void createuserList(listUsers &L); 
adrUser registerUser(string name, string pass, bool admin);
void insertUser(listUsers &L, adrUser p);
void removeUser(listUsers &L, listRooms &R, string username);
adrUser login(string u, string p);
bool isEmptyUser(listUsers L); 
adrUser findUser(listUsers &L, string username);

// Room
void createRoomList(listRooms &L);
adrRoom createRoom(int no, string type, int price); 
void insertRoom(listRooms &L, adrRoom r);
void deleteRoom(listRooms &L, int roomNumber);
void viewRooms(listRooms &R);
void viewAvailableRooms(listRooms L);
adrRoom findRoom(int no, listRooms &L);
bool isEmptyRoom(listRooms R); 

// Reservation
void makeReservation(listRooms &L, adrUser u);
void cancelReservation(listRooms &L, adrUser u);
void viewUserReservations(adrUser u);
void viewAllReservations(listUsers L);

// Menu
void mainMenu(listUsers &L, listRooms &R); 
void adminMenu(listUsers &L, listRooms &R, adrUser Admin);
void userMenu(listUsers &L, listRooms &R, adrUser User);

//Mungkin nambah lagi...

#endif
