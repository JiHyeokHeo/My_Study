#pragma once
#include <iostream>

class Mage
{
private:
    std::string memoryLocation_;
    std::string num_;

public:
    Mage(std::string str);
    Mage();
    ~Mage();
    void setNum(std::string str) { num_ = str; }
    std::string getNum() { return (num_); }
};

