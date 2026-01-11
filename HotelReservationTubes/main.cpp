#include <iostream> 
#include "hotelreservation.h"

using namespace std; 

int main(){
    listUsers userList;
    listRooms roomList;
    
    createuserList(userList);
    createRoomList(roomList);

    loadAllData(userList, roomList);
    
    cout << "===========================================\n";
    cout << "   WELCOME TO HOTEL RESERVATION SYSTEM    \n";
    cout << "===========================================\n";

    mainMenu(userList, roomList);
    
    return 0;
}