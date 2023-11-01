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

    return 0;
}