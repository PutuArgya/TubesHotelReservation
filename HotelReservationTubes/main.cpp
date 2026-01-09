#include <iostream> 
#include "hotelreservation.h"

using namespace std; 

main(){
    listUsers userList;
    listRooms roomList;
    
    createuserList(userList);
    createRoomList(roomList);
    
    cout << "===========================================\n";
    cout << "   WELCOME TO HOTEL RESERVATION SYSTEM    \n";
    cout << "===========================================\n";
    cout << "\nNote: Admin registration requires key: ADMIN2025\n";

    mainMenu(userList, roomList);
    
    return 0;
}