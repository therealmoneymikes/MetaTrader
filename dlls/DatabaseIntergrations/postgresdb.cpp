#include <cstdio>
#include <windows.h> 
#include <libpq-fe.h> //See the README.md For devices specific installation instructions 
#include <winscard.h>






//Query Executions and Fetch Results to give the EA Data to make
//Trade Decisions e.g Reversal Strategy, Entry Prices, Time Delays etc


__declspec(dllexport) const char* HandleEAQuery(const char* query, const char* connectionStr){
    //Store the data result in a static char variable so that the data can persist for the EA to use
    static char query_result[1024];

    PGconn* connection = PQconnectdb(connectionStr); 

    //Handle Error in connecting to PostgreSQL
    //You can add UI rendering by modifying the logic to return a variable that we can use 
    //To display either for example an MQL4/MQL5 Alert!

    if(PQstatus(connection) != CONNECTION_OK){
        snprintf(query_result, sizeof(query_result), "Connection Error: %s", PQerrorMessage(connection));
        PQfinish(connection); //End the connection
        return query_result;
        //You can add UI rendering by modifying the logic to return a variable that we can use 
    } 
    //If Our query command failes we can handle it gracefully
    PGresult* pg_result = PQexec(connection, query);
    if (PQresultStatus(pg_result) != PGRES_TUPLES_OK && PQresultStatus(pg_result) != PGRES_COMMAND_OK)  {
        snprintf(query_result, sizeof(query_result), "Query error: %s", PQerrorMessage(connection));
        PQclear(pg_result); //deallocate the memory of postgre query result 
        PQfinish(connection); //Close the DB connection and free up the connection variable
        return query_result;
    }

   if (PQresultStatus(pg_result) == PGRES_TUPLES_OK) {
    //Here we can print the result but Ideally for production we wouldn't need to do this!
    //But for testing it's okay to do 
        snprintf(query_result, sizeof(query_result), "Rows returned: %d", PQntuples(pg_result));
    } else {
        snprintf(query_result, sizeof(query_result), "Query executed successfully.");
    }

    // Cleanup
    PQclear(pg_result); //Here we deallocate the memory used for the cursor (statement object)
    PQfinish(connection); //Close the database when were done
    return query_result; //The Magic :) - We can use the return variable to verify the accounts

    }


