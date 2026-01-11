#ifndef HOTEL_H
#define HOTEL_H
#include <iostream>
#include <fstream>
#include <sstream>
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
    int userID;
    string username;
    string password;
    string email;
    string phone;
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
    int nextUserID;
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
adrUser registerUser(listUsers &L, string name, string pass, string email, string phone, bool admin);
void insertUser(listUsers &L, adrUser p);
void removeUser(listUsers &L, listRooms &R, string username);
adrUser login(listUsers &L, string username, string pass);
bool isEmptyUser(listUsers L); 
adrUser findUser(listUsers &L, string username);

// Room
void createRoomList(listRooms &R);
adrRoom createRoom(int no, string type, int price); 
void insertRoom(listRooms &R, adrRoom r);
void deleteRoom(listRooms &R, int roomNumber);
void viewRooms(listRooms &R);
void viewAvailableRooms(listRooms R);
adrRoom findRoom(int no, listRooms &R);
bool isEmptyRoom(listRooms R); 

// Reservation
void makeReservation(listRooms &R, listUsers  &L, adrUser u);
void cancelReservation(listRooms &R, listUsers &L, adrUser u);
void viewUserReservations(adrUser u);
void viewAllReservations(listUsers L);

// Menu
void mainMenu(listUsers &L, listRooms &R); 
void adminMenu(listUsers &L, listRooms &R, adrUser Admin);
void userMenu(listUsers &L, listRooms &R, adrUser User);

// CSV
void exportUsersToCSV(listUsers L, string filename);
void exportRoomsToCSV(listRooms L, string filename);
void exportReservationsToCSV(listUsers L, string filename);
void importRoomsFromCSV(listRooms &R, string filename);
void importUsersFromCSV(listUsers &L, string filename); 
void importReservationFromCSV(listUsers &L, string filename); 
void loadAllData(listUsers &L, listRooms &R); 

#endif
