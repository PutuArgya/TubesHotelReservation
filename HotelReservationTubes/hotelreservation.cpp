#include <iostream>
#include "hotelreservation.h"

using namespace std;

// User
void createuserList(listUsers &L){
    L.firstUser = nullptr; 
    L.lastUser = nullptr; 
}

bool isEmptyUser (listUsers L){
    return (L.firstUser == nullptr); 
} 

adrUser registerUser(string name, string pass, bool admin){
    adrUser p = new User; 
    p->username = name; 
    p->password = pass; 
    p->isAdmin = admin; 
    p->next = nullptr; 
    p->firstRes = nullptr; 
    return p; 
}

void insertUser(listUsers &L, adrUser p){
    if (isEmptyUser(L)){
        L.firstUser = p; 
        L.lastUser = p; 
    }else {
        L.lastUser->next = p; 
        L.lastUser = p; 
    }
}

void removeUser(listUsers &L, listRooms &R, string username){
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

adrUser findUsers(listUsers &L, string username){
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

void createRoomList(listRooms &L){
    L.firstRoom = nullptr; 
    L.lastRoom = nullptr; 
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

void insertRoom(listRooms &R, adrRoom r){
    if (isEmptyRoom(R)){
        R.firstRoom = r;
        R.lastRoom = r;
    } else {
        R.lastRoom->next = r;
        R.lastRoom = r;
    }
}

void deleteRoom(listRooms &R, int roomNumber){
    adrRoom r = R.firstRoom; 
    adrRoom prev = nullptr; 

    while(r != nullptr && r->roomNumber != roomNumber){
        prev = r;
        r = r->next; 
    } 
    
    if (r == nullptr){
        cout << "Room not found!";
    }else {
        if (prev == nullptr){
            R.firstRoom = r->next; 
            if (R.firstRoom == nullptr){
                R.lastRoom = prev; 
            }
        }
        delete r; 
        cout << "Room " << roomNumber << " Has been deleted!";
    }
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
            << " | Price: " << r->price << "per night"
            << " | Available " << r->available << endl; 
        r = r->next; 
    }
     cout << "================================\n";
}

void viewAvailableRooms(listRooms &R, bool available){
    if (isEmptyRoom(R)){
        cout << "\nNo rooms available.\n";
        return; 
    }
    bool isAvailable = false;
    cout << "\n===== AVAILABLE ROOMS =====\n";
    adrRoom r = R.firstRoom; 
    while (r != nullptr){
        if (r->available){
            cout << "Sorry, there are no available rooms right now!"; 
        }else {
            cout << "Room: " << r->roomNumber 
                << " | Type: " << r->type  
                << " | Price: " << r->price << "per night"
                << " | Available " << r->available << endl; 
            isAvailable = true; 
        }
        r = r->next; 
    }
    if (!isAvailable){
        cout << "Sorry, there are no room available for reservation right now!\n";
    }
    cout << "============================\n";
}

adrRoom findRoom(int no, listRooms &L){
    adrRoom r = L.firstRoom; 
    while (r != nullptr){
        if (r->roomNumber == no){
            return r; 
        }
        r = r->next; 
    }
    return nullptr; 
}

// Reservations

void makeReservation(listRooms &L, adrUser u){

}

void cancelReservation(listRooms &L, adrUser u){

}

void viewUserReservations(adrUser u){

}

void viewAllReservations(listUsers L){

}

// Menus

void mainMenu(listUsers &L, listRooms &R){
     int choice;
    
    do {
        cout << "\n========== HOTEL RESERVATION SYSTEM ==========\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "==============================================\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice){
            case 1: {
                string username, password;
                char type;
                cout << "\n=== REGISTRATION ===\n";
                cout << "Register as (U)ser or (A)dmin? ";
                cin >> type;
                cin.ignore();
                
                bool isAdmin = (type == 'A' || type == 'a');
                
                if (isAdmin){
                    string adminKey;
                    cout << "Enter admin key: ";
                    getline(cin, adminKey);
                    
                    if (adminKey != "ADMIN2025"){
                        cout << "Invalid admin key! Registration failed.\n";
                        break;
                    }
                }
                
                cout << "Enter username: ";
                getline(cin, username);
                
                if (findUser(L, username) != nullptr){
                    cout << "Username has been taken!\n";
                } else {
                    cout << "Enter password: ";
                    getline(cin, password);
                    
                    adrUser newUser = registerUser(username, password, isAdmin);
                    insertUser(L, newUser);
                    cout << (isAdmin ? "Admin" : "User") << " registration successful!\n";
                }
                break;
            }
            case 2: {
                string username, password;
                cout << "\n=== LOGIN ===\n";
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                
                adrUser user = login(L, username, password);
                if (user == nullptr){
                    cout << "Invalid username or password!\n";
                } else {
                    cout << "Login successful!\n";
                    if (user->isAdmin){
                        adminMenu(L, R, user);
                    } else {
                        userMenu(L, R, user);
                    }
                }
                break;
            }
            case 3:
                cout << "Thank you and good bye!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 3);
}

void adminMenu(listUsers &L, listRooms &R, adrUser admin){
    int choice;
    
    do {
        cout << "\n========== ADMIN MENU ==========\n";
        cout << "1. Add Room\n";
        cout << "2. Delete Room\n";
        cout << "3. View All Rooms\n";
        cout << "4. View All Reservations\n";
        cout << "5. View All Users\n";
        cout << "6. Remove User\n";
        cout << "7. Logout\n";
        cout << "================================\n";
        cout << "Choice: ";
        cin >> choice;
        
        switch(choice){
            case 1: {
                int no, price;
                string type;
                cout << "Enter room number: ";
                cin >> no;
                cin.ignore();
                cout << "Enter room type: ";
                getline(cin, type);
                cout << "Enter price per night: $";
                cin >> price;
                
                adrRoom r = createRoom(no, type, price);
                insertRoom(R, r);
                cout << "Room added!\n";
                break;
            }
            case 2: {
                int no;
                viewRooms(R);
                cout << "Enter room number to delete: ";
                cin >> no;
                deleteRoom(R, no);
                break;
            }
            case 3:
                viewRooms(R);
                break;
            case 4:
                viewAllReservations(L);
                break;
            case 5: {
                cout << "\n========== ALL USERS ==========\n";
                adrUser user = L.firstUser;
                while (user != nullptr){
                    cout << "Username: " << user->username 
                         << " | Type: " << (user->isAdmin ? "Admin" : "User") << endl;
                    user = user->next;
                }
                cout << "================================\n";
                break;
            }
            case 6: {
                string username;
                cin.ignore();
                cout << "Enter username to remove: ";
                getline(cin, username);
                removeUser(L, R, username);
                break;
            }
            case 7:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 7);
}

void userMenu(listUsers &L, listRooms &R, adrUser user){
    int choice;
    
    do {
        cout << "\n========== USER MENU ==========\n";
        cout << "Welcome, " << user->username << "\n";
        cout << "1. View Available Rooms\n";
        cout << "2. Make Reservation\n";
        cout << "3. View My Reservations\n";
        cout << "4. Cancel Reservation\n";
        cout << "5. Logout\n";
        cout << "================================\n";
        cout << "Choice: ";
        cin >> choice;
        
        switch(choice){
            case 1:
                viewAvailableRooms(R);
                break;
            case 2:
                makeReservation(R, user);
                break;
            case 3:
                viewUserReservations(user);
                break;
            case 4:
                cancelReservation(R, user);
                break;
            case 5:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 5);
}