#pragma once

#include <string>
#include <fstream>

class User
{
    std::string _name;                          //имя
    std::string _login;                         //логин
    std::string _pass;                          //пароль

public:
    User() = default;
    User(const std::string& name, const std::string& login, const std::string& pass);
    ~User() = default;

    User(const User& other);
    User& operator = (const User& other);
    bool operator == (const User& other);

    friend std::fstream& operator >> (std::fstream& is, User& obj);
    friend std::ostream& operator << (std::ostream& os, const User& obj);

    std::string getUserLogin() const;           //получить логин пользователя
    std::string getUserName() const;            //получить имя пользователя
};