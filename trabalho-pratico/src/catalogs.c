#include "../include/catalogs.h"
#include "../include/dataTypes.h"
#include "../include/dataStructs.h"
#include <glib.h>


#define BUFFERSIZE 1000



// Init usersDatabase
UsersDatabase initUsers(){
    UsersDatabase users = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)g_free,(GDestroyNotify)g_hash_table_destroy);
    return users;
}

// Insert User
void insertUser(void * table,User * user){
    g_hash_table_insert((UsersDatabase) table,(gpointer) getUserId(user),(gpointer) user);
}

// Returns the user that is supposed to be identified by the ID, that is on the TABLE
User * lookupUser(void * table ,const char * id){
    User * user = g_hash_table_lookup((UsersDatabase) table,(gconstpointer) id);
    return user;
}








// Inits the flights database
FlightsDatabase initFlights(){
    FlightsDatabase flights = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)g_free,(GDestroyNotify)g_hash_table_destroy);
    return flights;
}

// Inserts the flight on the database by the flight id
void insertFlight(void * structs,Flight * flight){
    g_hash_table_insert((FlightsDatabase)structs,(gpointer)getFlightId(flight),(gpointer) flight);
}

// Returns the flight based on the id
Flight * lookupFlight(void * table ,const char * id){
    Flight * flight = g_hash_table_lookup((FlightsDatabase) table,(gconstpointer) id);
    return flight;
}

























typedef struct passangersDB {
    Passanger ** passangers;
    unsigned int max;
    unsigned int numPassangers;
} PassangersDatabase;


PassangersDatabase * createPassangerDatabase(){
    PassangersDatabase * db = malloc(sizeof(struct passangersDB));
    db->passangers = NULL;
    db->max = BUFFERSIZE;
    db->numPassangers = 0;
    return db;
}

void insertPassanger(void * dataStruct, void * passangerData){
    PassangersDatabase * table = (PassangersDatabase *) dataStruct;
    Passanger * passanger = (Passanger *) passangerData;
    if(table->numPassangers == 0){
        table->passangers = malloc(getPassangerSize() * BUFFERSIZE);
        if(!table->passangers){
            free(table);
            return;
        }
        table->passangers[table->numPassangers] = passanger;
        table->numPassangers++;
        return;
    } else {
        if(table->numPassangers >= table->max){
            Passanger *temp = realloc(table->passangers, (table->max * 2) * getPassangerSize());
                if (!temp) {
                    for(int i = 0;i < table->max;i++){
                        free(table->passangers[i]);
                    }
                    free(table);
                    return;
                }
                table->passangers = temp;
                table->max *= 2;
                table->passangers[table->numPassangers] = passanger;
                table->numPassangers++;
            }
        }
    table->passangers[table->numPassangers] = passanger;
    table->numPassangers++;

}

int getNumAllPassangers(const PassangersDatabase * database){
    return database->numPassangers;
}

// Returns a filter
Passanger ** getAllPassages(const PassangersDatabase * database,char * userId){
    Passanger ** list = malloc(getPassangerSize() * database->numPassangers);
    int iList = 0;
    for(int iPdb = 0;iPdb < database->numPassangers;iPdb++){
        if(strcmp(getPassangerUserId(database->passangers[iPdb]),userId)){
            list[iList] = database->passangers[iPdb];
            iList++;
        } 
    }
    return list;
}

void destroyPassangersDB(PassangersDatabase * database){
    for(int i = 0;i < database->numPassangers;i++){
        free(database->passangers[i]);
    }
    free(database);
}































// Inits the reservations database
ReservationsDatabase initReservations(){
    ReservationsDatabase reservs = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)g_free,(GDestroyNotify)g_hash_table_destroy);
    return reservs;
}

// Inserts the reservations based on the reservations id
void insertReserv(void * structs,Reservation * reserv){
    g_hash_table_insert((ReservationsDatabase) structs,(gpointer) getReservId(reserv),(gpointer) reserv);
}

// Returns the reservations by the reservations id
Reservation * lookupReserv(void * table,const char * reservId){
    Reservation * reserv = g_hash_table_lookup((ReservationsDatabase ) table,(gconstpointer) reservId);
    return reserv;
}



























//                             *** Get Hotel Reservations ***

typedef struct hotelDatabase{
    struct reservation ** _hotelReservs;
    char * hotel_id;
    int sumRatings;
    int numReservas;
} HotelDatabase;



int getSumRatings(void * hReservs){
    HotelDatabase * reservs = (HotelDatabase *) hReservs;
    return reservs->sumRatings;
}

int getNumReservas(void * hReservs){
    HotelDatabase * reservs = (HotelDatabase *) hReservs;
    return reservs->numReservas;
}

Reservation ** getAllHotelReservs(const HotelDatabase * hotelData){
    return hotelData->_hotelReservs;
}

// Returns the reservations by the hotel id
HotelDatabase * getHotelDataBase(void * dataStruct,const char * hotelId){
    HotelDatabase * reservs = malloc(sizeof(struct hotelDatabase));
    reservs->hotel_id = strdup(hotelId);
    reservs->numReservas = 0;
    reservs->sumRatings = 0;
    reservs->_hotelReservs = malloc(getReservSize() * g_hash_table_size((GHashTable *) dataStruct));
    g_hash_table_foreach((GHashTable *)dataStruct,allHotelReservs,reservs);
    return reservs;
}

// Function to iterate and get the reservations on the list
void allHotelReservs(gpointer key, gpointer value, gpointer hotelData) {
    HotelDatabase * array = (HotelDatabase *) hotelData;
    Reservation * reservation = (Reservation *)value;
    static int i = 0;

    if (!g_strcmp0(getReservHotelId(reservation),array->hotel_id)) {
          array->_hotelReservs[i] = reservation;
          array->sumRatings += getReservRating(reservation);
          array->numReservas++;
          i++;
    }  
}

void destroyHotelDatabase(HotelDatabase * hotel){
    free(hotel->hotel_id);
    for(int i = 0;i < hotel->numReservas;i++){
        destroyReservation(hotel->_hotelReservs[i]);
    }
    free(hotel);
}

//                                  *** End block ***



//                      *** Get all the reservations of a user ***

typedef struct userReservsDB{
    struct reservation ** _userReservs;
    char * userId;
    int size;
} UserReservsDB;


UserReservsDB * getUserReservsDB(void * table,const char * userId){
    UserReservsDB * reservs = malloc(sizeof(struct userReservsDB));
    reservs->userId = strdup(userId);
    reservs->size = 0;
    reservs->_userReservs = malloc(getReservSize() * g_hash_table_size((UsersDatabase) table));
    g_hash_table_foreach((UsersDatabase) table,allUserReservs,reservs);
    return reservs;
}

Reservation ** getUserReservs(const UserReservsDB * userData){
    return userData->_userReservs;
}

int getNumReservs(const UserReservsDB * userData){
    return userData->size;
}


void allUserReservs(gpointer key ,gpointer value,gpointer userData){
  UserReservsDB * array = (UserReservsDB *) userData;
  Reservation * reserv = (Reservation *) value;
  static int i = 0;
 
  if(!g_strcmp0(getReservUserId(reserv),array->userId)){
      array->_userReservs[i] = reserv;
      array->size++;
      i++;
  }
}


void destroyUserReservsDB(UserReservsDB * database){
    for(int i = 0;i < database->size;i++){
        destroyReservation(database->_userReservs[i]);
    }
    free(database->_userReservs);
    free(database->userId);
    free(database);
}

//                                  *** End block ***












// Destroys User, Reservation or Flight database
void destroyDataBase(void * structs){
    g_hash_table_destroy((GHashTable *) structs);
}











