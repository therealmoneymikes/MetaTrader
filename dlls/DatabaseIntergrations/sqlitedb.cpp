#include <iostream>
#include <sqlite3.h>


using namespace std;


const char* authorised_ea_accounts_query = "SELECT COUNT(*) FROM authorised_client_accounts WHERE account_number = ?";

extern "C" __declspec(dllexport) bool CheckEALicense(int accountNumber) {
    sqlite3* db; //Create a sqlite pointer variable for the db
    sqlite3_stmt* cursor; //Create a pointer variable to hold the stmt object for our sql queries
    int db_return_code; //Return code for SQLite functions

    //Here we open the database connection with sqlite
    //Download SQLite  https://www.sqlite.org/download.html
    db_return_code = sqlite3_open("ea_accounts.db", &db);
    if(db_return_code != SQLITE_OK){
        cerr << "Unable to open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return false;
    }

    
    //Here I am passing the pre-written query for the ea account client search here
    //Also I deferencing the cursor (statement object) so that we can store the result from the db
    db_return_code = sqlite3_prepare_v2(db, authorised_ea_accounts_query, -1, &cursor, 0);
    if (db_return_code != SQLITE_OK) {
        //Checking the query statement fails for some reason
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return false;
    }

    // Here we simply binding the account number to the SQL query
    //Specfiically to the ?
    sqlite3_bind_int(cursor, 1, accountNumber);

    // Execute the query and check if the account number exists
    db_return_code = sqlite3_step(cursor); //Step functio is to execute the authroized_ea_accounts_query
    
    bool isAuthorized = false; 
    //Simple boolean to check if user is authorised or not
    //We use this in mql4/mql5 as the returned data from our function which can further process
    //e.g we can use to call ExpertRemove() if our function returns false to remove the bot from
    //The chart for unauthorised users



    if (db_return_code == SQLITE_ROW) {
        int count = sqlite3_column_int(cursor, 0); //Returns the first result column if the account is found
        isAuthorized = (count > 0);
        //if there is authorized account i.e count = 1 then we isAuthorized is try
        //Note that we only a confirmation we don't the actually data returned
    } else {
        cerr << "Failed to execute query: " << sqlite3_errmsg(db) << std::endl;
    }

    
    sqlite3_finalize(cursor); //Here we deallocate the memory used for the cursor (statement object)
    sqlite3_close(db); //Close the database when were done

    return isAuthorized;//The Magic :) - We can use the return variable to verify the accounts
}


