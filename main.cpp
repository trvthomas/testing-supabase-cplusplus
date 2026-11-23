#include "include/DB.hpp"
#include <iostream>
using namespace std;

int main()
{
    int option = -1;

    while (option != 0)
    {
        cout << "\n1 to get, 2 to insert: ";
        cin >> option;

        DB newDb("https://awaxerjylqgdkebavgqm.supabase.co", "sb_publishable_p4S0545Aj5OkgMcLdTITpg_7bessQXz");

        if (option == 1)
        {
            std::string balanceString = newDb.get("tickets", "attendee_code", "AB12345678", "wallet_amount");

            double balanceDouble = std::stod(balanceString);
            double performOperations = balanceDouble - 5.0;

            cout << "balance of code AB12345678: " << balanceDouble;
            cout << "\nperforming operations, new balance: " << performOperations;
        }
        else if (option == 2)
        {
            std::map<std::string, std::string> ticketData = {
                {"attendee_code", "ET12345678"}, //it should return error bc the code should be unique and this code is already inserted, so if u wanna test, just change the code
                {"ticket_tier", "GA"}};

            bool insertTicket = newDb.insert("tickets", ticketData);

            cout << "result of insertion: " << insertTicket;
        }
    }
}