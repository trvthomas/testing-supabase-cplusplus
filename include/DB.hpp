#ifndef DB_HPP
#define DB_HPP

#include <string>
#include <map>

class DB
{
private:
    std::string baseUrl;
    std::string apiKey;

public:
    DB(std::string url, std::string key);

    std::string get(std::string tableName, std::string whereColSearch, std::string whereColValue, std::string returnColName);

    bool insert(std::string tableName, std::map<std::string, std::string> data);
};

#endif