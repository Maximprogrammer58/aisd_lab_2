#include "../include/LinkedList.h"

std::string createPath(Node<std::string>* head) {
    std::string path;
    Node<std::string>* tmp = head;
    if (!tmp) {
        std::cout << "List is empty" << std::endl;
        return "";
    }
    path += tmp->data + ":\\";
    tmp = tmp->next;
    while (tmp) {
        if (!tmp->next) {
            path += tmp->data;
            break;
        }
        path += tmp->data + "\\";
        tmp = tmp->next;
    }
    return path;
}

bool isCorrectPath(std::string path) {
    if (std::filesystem::exists(path)) {
        std::cout << "File exists" << std::endl;
        return true;
    }
    std::cout << "File doesn't exist" << std::endl;
    return false;
}

void createFileNotExist(Node<std::string>* head) {
    std::string filepath;
    Node<std::string>* tmp = head;
    if (!tmp) {
        std::cout << "List is empty" << std::endl;
        return;
    }
    filepath += tmp->data + ":\\";
    tmp = tmp->next;
    while (tmp) {
        if (!tmp->next)
            break;
        filepath += tmp->data + "\\";
        tmp = tmp->next;
    }
    std::filesystem::path path{ filepath };
    path /= tmp->data;
    std::filesystem::create_directories(path.parent_path());
    std::ofstream ofs(path);
    ofs.close();
}

int main()
{ 
    LinkedList<std::string> lst;
    lst.pushTail("D");
    lst.pushTail("Python_lab");
    lst.pushTail("python_lab");
    lst.pushTail("datasets");
    lst.pushTail("dataset.csv");
    std::cout << createPath(lst.head()) << std::endl;
    isCorrectPath(createPath(lst.head()));

    LinkedList<std::string> rand_lst1(5, "C", "main.cc");
    std::cout << createPath(rand_lst1.head()) << std::endl;
    isCorrectPath(createPath(rand_lst1.head()));

    LinkedList<std::string> rand_lst2(3, "D", "example.cc");
    createFileNotExist(rand_lst2.head());
    std::cout << createPath(rand_lst2.head()) << std::endl;
    isCorrectPath(createPath(rand_lst2.head()));

    return 0;
}