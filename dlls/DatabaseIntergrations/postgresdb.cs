using System;
using System.Runtime.InteropServices;
using Npgsql; // Make sure to install the Npgsql library via NuGet

public class EAAuthorizationChecker
{
    [DllExport("CheckAccountAuthorization", CallingConvention = CallingConvention.Cdecl)]
    public static bool CheckAccountAuthorization(int accountNumber, string connectionStr)
    {
        try
        {
            // Create a connection to PostgreSQL
            using (var connection = new NpgsqlConnection(connectionStr))
            {
                connection.Open();

                // Query to check if the account number exists in the authorized_accounts table
                string query = "SELECT COUNT(*) FROM authorized_accounts WHERE account_number = @accountNumber";

                using (var command = new NpgsqlCommand(query, connection))
                {
                    // Add parameterized query to prevent SQL injection
                    command.Parameters.AddWithValue("@accountNumber", accountNumber);

                    // Execute the query
                    var count = (long)command.ExecuteScalar();

                    // Returns true if the account is "Authorized" or 
                    // Returns false if "Unauthorized" based on the result
                    return count > 0 ? true: false;
                }
            }
        }
        catch (Exception ex)
        {
            // Return the error message for debugging purposes
            return $"Error: {ex.Message}";
        }
    }
}
