#include <iostream>
#include <fstream>
#include <sstream>
#include "hotelreservation.h"

using namespace std;

// User
void createuserList(listUsers &L){
    L.firstUser = nullptr; 
    L.lastUser = nullptr; 
    L.nextUserID = 1;
}

bool isEmptyUser (listUsers L){
    return (L.firstUser == nullptr); 
} 

adrUser registerUser(listUsers &L, string name, string pass, string email, string phone, bool admin){
    adrUser p = new User;
    p->userID = L.nextUserID;
    p->username = name; 
    p->password = pass;
    p->email = email;
    p->phone = phone;
    p->isAdmin = admin; 
    p->next = nullptr; 
    p->firstRes = nullptr; 
    return p; 
}

void insertUser(listUsers &L, adrUser p){ //insertlast
    if (isEmptyUser(L)){
        L.firstUser = p; 
        L.lastUser = p; 
    }else {
        L.lastUser->next = p; 
        L.lastUser = p; 
    }
    L.nextUserID++;

    exportUsersToCSV(L, "users.csv");
} 

void removeUser(listUsers &L, listRooms &R, string username){ //deleteAfter
    if (isEmptyUser(L)){
        cout << "No users in the system!\n";
        return;
    }
    
    adrUser user = L.firstUser;
    adrUser prev = nullptr;

    while (user != nullptr && user->username != username){
        prev = user;
        user = user->next;
    }
    
    if (user == nullptr){
        cout << "User not found!\n";
        return;
    }
    
    if (user->isAdmin){
        cout << "Cannot remove admin account!\n";
        return;
    }

    adrReservation res = user->firstRes;
    while (res != nullptr){
        adrReservation temp = res;
        res = res->next;
     
        adrRoom room = findRoom(temp->roomNumber, R);
        if (room != nullptr){
            room->available = true;
        }
        
        delete temp;
    }

    if (prev == nullptr){
        L.firstUser = user->next;
        if (L.firstUser == nullptr){
            L.lastUser = nullptr;
        }
    } else {
        prev->next = user->next;
        if (user == L.lastUser){
            L.lastUser = prev;
        }
    }
    
    delete user;
    cout << "User '" << username << "' removed successfully!\n";
    cout << "All reservations cancelled and rooms made available.\n";

    exportUsersToCSV(L, "users.csv");
    exportRoomsToCSV(R, "rooms.csv");
    exportReservationsToCSV(L, "reservations.csv");
}

adrUser login(listUsers &L, string name, string pass){
    adrUser user = L.firstUser; 
    while (user != nullptr){
        if (user->username == name && user->password == pass){
            return user; 
        }
        user = user->next; 
    }
    return nullptr;    
}

adrUser findUser(listUsers &L, string username){ //Linear Seacrh
    adrUser user = L.firstUser; 
    while (user != nullptr){
        if (user->username == username){
            return user; 
        }
        user = user->next; 
    }
    return nullptr; 
}


// Rooms 

void createRoomList(listRooms &R){
    R.firstRoom = nullptr; 
    R.lastRoom = nullptr; 
}

bool isEmptyRoom(listRooms R){
    return(R.firstRoom == nullptr); 
}

adrRoom createRoom(int no, string type, int price){
    adrRoom r = new Room;
    r->roomNumber = no;
    r->type = type; 
    r->price = price; 
    r->available = true; 
    r->next = nullptr; 
    return r; 
}

void insertRoom(listRooms &R, adrRoom r){ //InsertLast
    if (isEmptyRoom(R)){
        R.firstRoom = r;
        R.lastRoom = r;
    } else {
        R.lastRoom->next = r;
        R.lastRoom = r;
    }

    exportRoomsToCSV(R, "rooms.csv");
}

void deleteRoom(listRooms &R, int roomNumber){ //deleteAfter
    adrRoom r = R.firstRoom; 
    adrRoom prev = nullptr; 

    while(r != nullptr && r->roomNumber != roomNumber){
        prev = r;
        r = r->next; 
    } 
    
    if (r == nullptr){
        cout << "Room not found!\n";
        return; 
    }
    
    // Room is found 
    if (prev == nullptr){
        // Delete first room
        R.firstRoom = r->next; 
        if (R.firstRoom == nullptr){
            R.lastRoom = nullptr;  
        }
    } else {
        // Delete middle or last room
        prev->next = r->next;
        if (r == R.lastRoom){
            R.lastRoom = prev; 
        }
    }
    
    delete r; 
    cout << "Room " << roomNumber << " has been deleted!\n";

    exportRoomsToCSV(R, "rooms.csv");
}

void viewRooms(listRooms &R){
    if (isEmptyRoom(R)){
        cout << "\nNo rooms available.\n";
        return; 
    }
    cout << "\n========== ALL ROOMS ==========\n";
    adrRoom r = R.firstRoom; 
    while (r != nullptr){
        cout << "Room: " << r->roomNumber 
            << " | Type: " << r->type  
            << " | Price: " << r->price << " per night"
            << " | Available " << r->available << endl; 
        r = r->next; 
    }
     cout << "================================\n";
}

void viewAvailableRooms(listRooms R){
    if (isEmptyRoom(R)){
        cout << "\nNo rooms available.\n";
        return; 
    } 
    bool hasAvailable = false;
    cout << "\n===== AVAILABLE ROOMS =====\n";
    adrRoom r = R.firstRoom; 
    
    while (r != nullptr){
        if (r->available){ 
            cout << "Room: " << r->roomNumber 
                << " | Type: " << r->type  
                << " | Price: $" << r->price << "/night" << endl; 
            hasAvailable = true; 
        }
        r = r->next; 
    }
    if (!hasAvailable){
        cout << "Sorry, no rooms available for reservation right now!\n";
    }
    cout << "============================\n";
}

adrRoom findRoom(int no, listRooms &R){ //LinearSearch
    adrRoom r = R.firstRoom;  
    while (r != nullptr){
        if (r->roomNumber == no){
            return r; 
        }
        r = r->next; 
    }
    return nullptr; 
}

// Reservations

void makeReservation(listRooms &R, listUsers &L, adrUser u){
    int roomNo, nights;
    
    viewAvailableRooms(R);
    
    cout << "\nEnter room number to reserve: ";
    cin >> roomNo;
    
    adrRoom room = findRoom(roomNo, R);
    
    if (room == nullptr){
        cout << "Room not found!\n";
    } else if (!room->available){
        cout << "Room is not available!\n";
    } else {
        cout << "Enter number of nights: ";
        cin >> nights;
        
        // Create new reservation
        adrReservation newRes = new Reservation;
        newRes->roomNumber = roomNo;
        newRes->nights = nights;
        newRes->next = nullptr;
        newRes->prev = nullptr;
        
        // Insert reservation to user's list (insert first)
        if (u->firstRes == nullptr){
            u->firstRes = newRes;
        } else {
            newRes->next = u->firstRes;
            u->firstRes->prev = newRes;
            u->firstRes = newRes;
        }
        
        //  Room will become unavailable 
        room->available = false;
        
        int totalCost = room->price * nights;
        cout << "\n=== RESERVATION SUCCESS ===\n";
        cout << "Room: " << roomNo << " (" << room->type << ")\n";
        cout << "Nights: " << nights << "\n";
        cout << "Total Cost: $" << totalCost << "\n";
        cout << "===========================\n";
    }

    exportRoomsToCSV(R, "rooms.csv");
    exportReservationsToCSV(L, "reservations.csv");
}

void cancelReservation(listRooms &R, listUsers &L, adrUser u){ //delete after
    if (u->firstRes == nullptr){
        cout << "You have no reservations!\n";
    } else {
        viewUserReservations(u);
        
        int roomNo;
        cout << "\nEnter room number to cancel: ";
        cin >> roomNo;
        
        adrReservation res = u->firstRes;
        while (res != nullptr && res->roomNumber != roomNo){
            res = res->next;
        }
        
        if (res == nullptr){
            cout << "Reservation not found!\n";
        } else {
            // Remove from user's reservation list
            if (res->prev == nullptr){
                u->firstRes = res->next;
                if (u->firstRes != nullptr){
                    u->firstRes->prev = nullptr;
                }
            } else {
                res->prev->next = res->next;
                if (res->next != nullptr){
                    res->next->prev = res->prev;
                }
            }
            // Room will become available 
            adrRoom room = findRoom(roomNo, R);
            if (room != nullptr){
                room->available = true;
            }
            
            delete res;
            cout << "Reservation for room " << roomNo << " cancelled successfully!\n";
        }
    }
    exportRoomsToCSV(R, "rooms.csv");
    exportReservationsToCSV(L, "reservations.csv");
}

void viewUserReservations(adrUser u){
    if (u->firstRes == nullptr){
        cout << "\nYou have no reservations.\n";
    } else {
        cout << "\n===== YOUR RESERVATIONS =====\n";
        adrReservation res = u->firstRes;
        while (res != nullptr){
            cout << "Room: " << res->roomNumber 
                 << " | Nights: " << res->nights << endl;
            res = res->next;
        }
        cout << "==============================\n";
    }
}

void viewAllReservations(listUsers L){
    if (isEmptyUser(L)){
        cout << "\nNo users in the system.\n";
    } else {
        cout << "\n========== ALL RESERVATIONS ==========\n";
        adrUser user = L.firstUser;
        bool hasReservations = false;
        
        while (user != nullptr){
            if (user->firstRes != nullptr && !user->isAdmin){
                cout << "\nUser: " << user->username << "\n";
                adrReservation res = user->firstRes;
                while (res != nullptr){
                    cout << "  - Room: " << res->roomNumber 
                         << " | Nights: " << res->nights << endl;
                    res = res->next;
                    hasReservations = true;
                }
            }
            user = user->next;
        }
        
        if (!hasReservations){
            cout << "No reservations found.\n";
        }
        cout << "======================================\n";
    }
}
