#include "../include/DB.hpp"

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../cpp-httplib/httplib.h"

#include "json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;

DB::DB(std::string url, std::string key)
{
    this->baseUrl = url;
    this->apiKey = key;
}

std::string DB::get(std::string tableName, std::string whereColSearch, std::string whereColValue, std::string returnColName)
{
    httplib::Client cli(baseUrl);

    cli.set_default_headers({{"apikey", apiKey},
                             {"Accept", "application/json"}});

    std::string path = "/" + tableName + "?select=" + returnColName + "&" + whereColSearch + "=eq." + whereColValue + "&limit=1";

    auto res = cli.Get(path);
    if (!res)
    {
        return "";
    }

    json parsedResponse = json::parse(res->body);
    if (parsedResponse.empty() || !parsedResponse[0].contains(returnColName) || parsedResponse[0][returnColName].is_null())
    {
        return "";
    }

    auto val = parsedResponse[0][returnColName];
    return val.is_string() ? val.get<std::string>() : val.dump();
}