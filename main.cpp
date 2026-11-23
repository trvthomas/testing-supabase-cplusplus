#include "include/DB.hpp"
#include <iostream>
using namespace std;

int main()
{
    int option = -1;

    while (option != 0)
    {
        cout << "1 to get, 2 to insert";
        cin >> option;

        DB newDb("https://awaxerjylqgdkebavgqm.supabase.co/rest/v1", "sb_publishable_p4S0545Aj5OkgMcLdTITpg_7bessQXz");

        if (option == 1)
        {
            std::string balance = newDb.get("tickets", "attendee_code", "AB12345678", "wallet_amount");

            cout << "balance of code AB12345678: " << balance;
        }
        else if (option == 2)
        {
            // bool = newDb.insert();
            return -1;
        }
    }
}