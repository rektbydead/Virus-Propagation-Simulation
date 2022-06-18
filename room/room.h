
#ifndef room_h
#define room_h

#define NO_ROOM -400
#define NO_CONNECTION -1 

#define MAX_CONNECTION 3

typedef struct room room, *pRoom;
struct room {
    int id; // id numérico do local
    int maxCapacity; // capacidade máxima
    int capacity;
    
    int connections[MAX_CONNECTION]; // id das ligações (-1 nos casos não usados)
};


room *readRoomsFile(char *nomeFich, int *total);

void printRoom(room r);

int verifyRooms(pRoom roomList, int total);

#endif

