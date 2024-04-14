// shopping.h

#ifndef SHOPPING_H
#define SHOPPING_H

#include <iostream>
#include <fstream>

class shopping {
private:
    int pcode;
    float price;
    float dis;
    std::string pname;

public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

#endif

