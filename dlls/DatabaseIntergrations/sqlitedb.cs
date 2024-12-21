using System;
using System.Data.SQLite; //You can find SQLite packages via NuGet in Visual Studio Code

public class EALicenseChecker
{
    public static bool CheckEALicense(int accountNumber)
    {
        string connectionString = "Data Source=ea_accounts.db;Version=3;";
        string db_query = "SELECT COUNT(*) FROM authorised_client_accounts WHERE account_number = @accountNumber"; 

        try
        {
            using (SQLiteConnection connection = new SQLiteConnection(connectionString))
            {
                connection.Open();

                using (SQLiteCommand command = new SQLiteCommand(db_query, connection))
                {
                    // Bind the account number parameter
                    command.Parameters.AddWithValue("@accountNumber", accountNumber);

                    // Execute the query and get the result
                    object result = command.ExecuteScalar();
                    int count = Convert.ToInt32(result);

                    // Return true if the account exists
                    return count > 0;
                }
            }
        }
        catch (Exception ex)
        {
            Console.Error.WriteLine($"Database error: {ex.Message}");
            return false;
        }
    }
}
