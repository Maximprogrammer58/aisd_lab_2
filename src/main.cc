#define SIZE 10

#include <iostream>

#include "../include/LinkedList.h"

int main()
{ 
    LinkedList<std::string> lst;
    lst.push_tail("D");
    lst.push_tail(generateRandomString(generateRandomNumber(1, 10)));
    lst.push_tail("text.txt");
    lst.print_path();
    return 0;
}