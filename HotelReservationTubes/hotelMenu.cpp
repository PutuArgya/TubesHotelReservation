#include <iostream>
#include <fstream>
#include <sstream>
#include "hotelreservation.h"

using namespace std;

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

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid! Please enter a number.\n";
            continue;
        }
        
        switch(choice){
            case 1: {
                string username, password, email, phone;
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
                    
                    if (adminKey != "ADMINPASSKEY"){
                        cout << "Invalid admin key!\n";
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
                    cout << "Enter email: ";
                    getline(cin, email);
                    cout << "Enter phone number: ";
                    getline(cin, phone);
                    
                    adrUser newUser = registerUser(L, username, password, email, phone, isAdmin);
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

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid! Please enter a number.\n";
            continue;
            }
        
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
                         << " Email: " << user->email
                         << " Phone Number: " << user->phone
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
        cout << "Welcome, " << user->username << "!\n";
        cout << "1. View Available Rooms\n";
        cout << "2. View All Rooms\n";
        cout << "3. Make Reservation\n";
        cout << "4. View My Reservations\n";
        cout << "5. Cancel Reservation\n";
        cout << "6. Logout\n";
        cout << "================================\n";
        cout << "Choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid! Please enter a number.\n";
            continue;
        }
        
        switch(choice){
            case 1:
                viewAvailableRooms(R);
                break;
            case 2:
                viewRooms(R);
                break;
            case 3:
                makeReservation(R, L, user);
                break;
            case 4:
                viewUserReservations(user);
                break;
            case 5:
                cancelReservation(R, L, user);
                break;
            case 6:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 6);
}