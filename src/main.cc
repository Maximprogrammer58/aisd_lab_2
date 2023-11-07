#include "../include/LinkedList.h"

int main()
{ 
    LinkedList<std::string> lst;
    lst.pushTail("D");
    lst.pushTail("Python_lab");
    lst.pushTail("python_lab");
    lst.pushTail("datasets");
    lst.pushTail("dataset.csv");
    lst.printPath();
    lst.isCorrectPath();

    LinkedList<std::string> rand_lst1(5, "C", "main.cc");
    rand_lst1.printPath();
    rand_lst1.isCorrectPath();

    LinkedList<std::string> rand_lst2(3, "D", "example.cc");
    rand_lst2.createFileNotExist();
    rand_lst2.printPath();
    rand_lst2.isCorrectPath();
    return 0;
}