#include "header.h"
int main(int argc, char *argv[]) {
    LinkedList list;
    list.push_front(5);
    list.push_back(4);
    list.push_back(3);
    list.push_back(2);
    list.push_back(1);
    LinkedList::iterator it1 = list.begin();

    return 0;
}
