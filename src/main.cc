#define SIZE 10

#include <iostream>
#include <string>

#include "../include/LinkedList.h"

int main()
{ 
    LinkedList<std::string> lst;
    lst.push_tail("D");
    lst.push_tail("lab2");
    lst.push_tail("text.txt");
    lst.print_path();
    return 0;
}