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
    /* 
    D:\Python_lab\python_lab\datasets\dataset.csv
    File exists
    */

    LinkedList<std::string> rand_lst1(5, "D", "main.cc");
    rand_lst1.printPath();
    rand_lst1.isCorrectPath();
    /*
    D:\ifgxmqa\wjnynroqe\uiwcayr\main.cc
    File doesn't exist
    */

    LinkedList<std::string> rand_lst2(7);
    rand_lst2.printPath();
    rand_lst2.isCorrectPath();
    /*
    C:\clj\keejfbujqo\noaaboqfyu\pzjabs\q\lj.cc
    File doesn't exist
    */

    return 0;
}