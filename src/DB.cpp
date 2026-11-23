#include "../include/DB.hpp"

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../cpp-httplib/httplib.h"

#include "../json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;

DB::DB(std::string url, std::string key)
{
    this->baseUrl = url;
    this->apiKey = key;
}

// Get a column
std::string DB::get(std::string tableName, std::string whereColSearch, std::string whereColValue, std::string returnColName)
{
    httplib::Client cli(baseUrl);

    // Set the API Headers
    cli.set_default_headers({{"apikey", apiKey},
                             {"Accept", "application/json"}});

    std::string path = "/rest/v1/" + tableName + "?select=" + returnColName + "&" + whereColSearch + "=eq." + whereColValue + "&limit=1";

    // Call HTTP GET
    auto res = cli.Get(path);
    
    // If there's an error return empty
    if (!res)
    {
        std::cerr << "Request failed: " << httplib::to_string(res.error()) << "\n";
        return "";
    }

    // Debug, get the received status and body
    std::cout << "Status: " << res->status << "\n";
    std::cout << "Raw Body: " << res->body << "\n\n";

    // Supabase returns a JSON, so we use this library to convert it to a c++ object
    json parsedResponse = json::parse(res->body, nullptr, false);

    // If the key we are looking for doesnt exist return empty
    if (parsedResponse.empty() || !parsedResponse[0].contains(returnColName) || parsedResponse[0][returnColName].is_null())
    {
        return "";
    }

    // If the key exists then return it as a string
    auto val = parsedResponse[0][returnColName];
    return val.is_string() ? val.get<std::string>() : val.dump();
}

bool DB::insert(std::string tableName, std::map<std::string, std::string> data)
{
    httplib::Client cli(baseUrl);

    cli.set_default_headers({{"apikey", apiKey},
                             {"Accept", "application/json"}});

    std::string path = "/rest/v1/" + tableName;

    // We use this library to convert the received map to a json, easy!
    json body = data;

    // Call HTTP POST
    auto res = cli.Post(path, body.dump(), "application/json");

    // Failed request
    if (!res)
    {
        std::cerr << "Request failed: " << httplib::to_string(res.error()) << "\n";
        return false;
    }

    // Logs
    std::cout << "Status: " << res->status << "\n";
    std::cout << "Raw Body: " << res->body << "\n\n";

    // Supabase doesn't return anything, so check the status instead, 201 is successful (optional: add a header: prefer: return=representation and it will return the newly inserted row, then use the same method as the get function to check if the key exists and make sure the row was properly inserted)
    if (res->status != 201) {
        return false;
    }

    return true;
}