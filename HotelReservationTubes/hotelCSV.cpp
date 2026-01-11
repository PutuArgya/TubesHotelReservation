#include <iostream>
#include <fstream>
#include <sstream>
#include "hotelreservation.h"

using namespace std;

//  CSV EXPORT/IMPORT FUNCTIONS 

void exportUsersToCSV(listUsers L, string filename){
    ofstream file(filename);
    
    if (!file.is_open()){
        cout << "Error: Could not create file " << filename << endl;
        return;
    }
    
    // Write header
    file << "UserID,Username,Password,Email,Phone,IsAdmin" << endl;
    
    //  User data
    adrUser user = L.firstUser;
    while (user != nullptr){
        file << user->userID << ","
             << user->username << ","
             << user->password << ","
             << user->email << ","
             << user->phone << ","
             << (user->isAdmin ? "Yes" : "No") << endl;
        user = user->next;
    }
    
    file.close();
    cout << "Users exported to " << filename << " successfully!" << endl;
}

void exportRoomsToCSV(listRooms L, string filename){
    ofstream file(filename);
    
    if (!file.is_open()){
        cout << "Error: Could not create file " << filename << endl;
        return;
    }
    
    // Headerr
    file << "RoomNumber,Type,Price,Available" << endl;
    
    // room data
    adrRoom room = L.firstRoom;
    while (room != nullptr){
        file << room->roomNumber << ","
             << room->type << ","
             << room->price << ","
             << (room->available ? "Yes" : "No") << endl;
        room = room->next;
    }
    
    file.close();
    cout << "Rooms exported to " << filename << " successfully!" << endl;
}

void exportReservationsToCSV(listUsers L, string filename){
    ofstream file(filename);
    
    if (!file.is_open()){
        cout << "Error: Could not create file " << filename << endl;
        return;
    }
    
    // For header
    file << "UserID,Username,RoomNumber,Nights" << endl;
    
    // inputing reservation data stuff
    adrUser user = L.firstUser;
    while (user != nullptr){
        adrReservation res = user->firstRes;
        while (res != nullptr){
            file << user->userID << ","
                 << user->username << ","
                 << res->roomNumber << ","
                 << res->nights << endl;
            res = res->next;
        }
        user = user->next;
    }
    
    file.close();
    cout << "Reservations exported to " << filename << " successfully!" << endl;
}

void importRoomsFromCSV(listRooms &R, string filename){
    ifstream file(filename);
    
    if (!file.is_open()){
        cout << "Error! Could not open file " << filename << endl;
        return;
    }
    
    string line;
    getline(file, line); // Skip header
    
    int count = 0;
    while (getline(file, line)){
        stringstream ss(line);
        string roomNoStr, type, priceStr, availableStr;
        
        getline(ss, roomNoStr, ',');
        getline(ss, type, ',');
        getline(ss, priceStr, ',');
        getline(ss, availableStr, ',');
        
        int roomNo = stoi(roomNoStr);
        int price = stoi(priceStr);
        
        adrRoom r = createRoom(roomNo, type, price);
        r->available = (availableStr == "Yes");
        insertRoom(R, r);
        count++;
    }
    
    file.close();
    cout << count << " rooms imported from " << filename << " successfully!" << endl;
}

void importUsersFromCSV(listUsers &L, string filename){
    ifstream file(filename);
    
    if (!file.is_open()){
        cout << "No user data found. Starting fresh.\n";
        return;
    }
    
    string line;
    getline(file, line); // Skip header
    
    int maxID = 0;
    while (getline(file, line)){
        stringstream ss(line);
        string idStr, username, password, email, phone, isAdminStr;
        
        getline(ss, idStr, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');
        getline(ss, isAdminStr, ',');
        
        int id = stoi(idStr);
        bool isAdmin = (isAdminStr == "Yes");
        
        adrUser u = new User;
        u->userID = id;
        u->username = username;
        u->password = password;
        u->email = email;
        u->phone = phone;
        u->isAdmin = isAdmin;
        u->next = nullptr;
        u->firstRes = nullptr;
        
        if (isEmptyUser(L)){
            L.firstUser = u;
            L.lastUser = u;
        } else {
            L.lastUser->next = u;
            L.lastUser = u;
        }
        
        if (id > maxID) maxID = id;
    }
    
    L.nextUserID = maxID + 1; // Continue ID sequence
    file.close();
    cout << "Users loaded from " << filename << endl;
}

void importReservationFromCSV(listUsers &L, string filename){
    ifstream file(filename);
    
    if (!file.is_open()){
        cout << "No reservation data found.\n";
        return;
    }
    
    string line;
    getline(file, line); // Skip header
    
    while (getline(file, line)){
        stringstream ss(line);
        string idStr, username, roomNoStr, nightsStr;
        
        getline(ss, idStr, ',');
        getline(ss, username, ',');
        getline(ss, roomNoStr, ',');
        getline(ss, nightsStr, ',');
        
        int userID = stoi(idStr);
        int roomNo = stoi(roomNoStr);
        int nights = stoi(nightsStr);
        
        // Find user  
        adrUser user = L.firstUser;
        while (user != nullptr){
            if (user->userID == userID){
                // Add reservation 
                adrReservation res = new Reservation;
                res->roomNumber = roomNo;
                res->nights = nights;
                res->next = nullptr;
                res->prev = nullptr;
                
                if (user->firstRes == nullptr){
                    user->firstRes = res;
                } else {
                    res->next = user->firstRes;
                    user->firstRes->prev = res;
                    user->firstRes = res;
                }
                break;
            }
            user = user->next;
        }
    }
    
    file.close();
    cout << "Reservations loaded from " << filename << endl;
}

void loadAllData(listUsers &L, listRooms &R){
    cout << "\n=== Loading existing data ===\n";
    importUsersFromCSV(L, "users.csv");
    importRoomsFromCSV(R, "rooms.csv");
    importReservationFromCSV(L, "reservations.csv");
    cout << "=== Data loading complete ===\n" << endl; 
}