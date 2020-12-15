#include "pch.h"
#include "..\oop1\LinkedList.cpp"
#include "test.h"

TEST(LinkedList, sizeCheck) {
    LinkedList list;
    list.push_front(5);
    list.push_back(4);
    list.push_back(3);
    list.push_back(2);
    list.push_back(1);

    ASSERT_EQ(5, list.size());
}

TEST(LinkedList, clearSizeCheck) {
    LinkedList list;
    list.push_front(5);
    list.push_back(4);
    list.push_back(3);
    list.push_back(2);
    list.push_back(1);
    list.clear();

    ASSERT_EQ(0, list.size());
}

TEST(LinkedList, insertDataCheck) {
    LinkedList list;
    list.push_front(5);
    list.push_back(4);
    list.push_back(3);
    list.push_back(2);
    list.push_back(1);
    LinkedList::iterator it = list.begin();
    for (int i = 0; i < 3; i++) 
        it++;
    list.insert(it, 9);

    EXPECT_EQ(9, it.curNode->prev->data);
}

TEST(LinkedList, eraseCheck) {
    LinkedList list;
    list.push_front(5);
    list.push_back(4);
    list.push_back(3);
    list.push_back(2);
    list.push_back(1);
    LinkedList::iterator it1 = list.begin();
    for (int i = 0; i < 3; i++)
        it1++;
    LinkedList::iterator itPrev = it1;
    itPrev--;
    LinkedList::iterator itPrevCopy = itPrev;
    LinkedList::iterator itNext = it1;
    itNext++;
    LinkedList::iterator itNextCopy = itNext;
    list.erase(it1);

    EXPECT_TRUE((itPrevCopy++ == itNext) && (itNextCopy-- == itPrev));
}

TEST(LinkedList, iteratorAccessCheck) {
    LinkedList list;
    list.push_front(5);
    list.push_back(4);
    list.push_back(3);
    list.push_back(2);
    list.push_back(1);
    LinkedList::iterator it = list.begin();
    for (int i = 0; i < 3; i++) 
        it++;     

    EXPECT_EQ(2, it.curNode->data);
}

TEST(LinkedList, const_iteratorAccessCheck) {
    LinkedList list;
    list.push_front(5);
    list.push_back(4);
    list.push_back(3);
    list.push_back(2);
    list.push_back(1);
    LinkedList::const_iterator it = list.cbegin();
    for (int i = 0; i < 3; i++) 
        it++;     

    EXPECT_EQ(2, it.curNode->data);
}

TEST(LinkedList, iterator—onstructorCheck) {
    LinkedList::iterator it;

    EXPECT_EQ(nullptr, it.curNode);
}

TEST(LinkedList, const_iterator—onstructorCheck) {
    LinkedList::const_iterator it;

    EXPECT_EQ(nullptr, it.curNode);
}

TEST(LinkedList, list—onstructorCheck1) {
    LinkedList list;
    LinkedList::iterator it1 = list.begin();
    LinkedList::iterator it2 = list.end();
    
    EXPECT_TRUE((it1.curNode->data == 0) && (it2.curNode->data == 0));
}

TEST(LinkedList, list—onstructorCheck2) {
    LinkedList list;
    list.push_front(5);
    list.push_back(4);
    list.push_back(3);
    list.push_back(2);
    list.push_back(1);
    LinkedList list2(list);

    EXPECT_TRUE(list2 == list);
}

TEST(LinkedList, listOperatorAssignmentCheck) {
    LinkedList list;
    list.push_front(5);
    list.push_back(4);
    list.push_back(3);
    list.push_back(2);
    list.push_back(1);
    LinkedList list2;
    list2 = list;

    EXPECT_TRUE(list2 == list);
}

TEST(LinkedList, listOperatorAddCheck) {
    LinkedList list;
    list.push_front(5);
    list.push_back(4);
    list.push_back(3);
    list.push_back(2);
    list.push_back(1);

    LinkedList list2;
    list2.push_front(6);
    list2.push_front(7);
    list2.push_front(8);
    int size1 = list.size();
    int size2 = list2.size();
    list += list2;
    int size3 = list.size();

    EXPECT_TRUE(size3 == size1 + size2);
}

TEST(LinkedList, iteratorOperatorAssignmentCheck) {
    LinkedList list;
    list.push_front(5);
    list.push_back(4);
    list.push_back(3);
    list.push_back(2);
    list.push_back(1);
    LinkedList::iterator it1;
    for (int i = 0; i < 3; i++) {
        it1++;
    }
    LinkedList::iterator it2 = it1;

    EXPECT_TRUE(it2 == it1);
}

TEST(LinkedList, const_iteratorOperatorAssignmentCheck) {
    LinkedList list;
    list.push_front(5);
    list.push_back(4);
    list.push_back(3);
    list.push_back(2);
    list.push_back(1);
    LinkedList::const_iterator it1;
    for (int i = 0; i < 3; i++) {
        it1++;
    }
    LinkedList::const_iterator it2 = it1;

    EXPECT_TRUE(it2 == it1);
}

TEST(LinkedList, iteratorOperatorAddCheck) {
    LinkedList list;
    list.push_front(5);
    list.push_back(4);
    list.push_back(3);
    list.push_back(2);
    list.push_back(1);
    LinkedList::iterator it1;
    for (int i = 0; i < 3; i++) {
        it1++;
    }
    LinkedList::iterator it2 = it1;

    EXPECT_TRUE(it2 == it1);
}


