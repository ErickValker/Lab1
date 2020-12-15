#include "LinkedList.h"

LinkedList::Node::Node() {
    data = 0;
    prev = next = nullptr;
}

LinkedList::Node::Node(const Node &other) {
    data = other.data;
    prev = other.prev;
    next = other.next;
}

LinkedList::Node::~Node() {

}

LinkedList::LinkedList() {
    tail = new Node();
    head = new Node();
    head->next = tail;
    tail->prev = head;
    head->prev = tail;
    tail->next = head;
    listSize = 2;
    capacity = 0;
}

LinkedList::LinkedList(const LinkedList &other) {
    tail = new Node();
    head = new Node();
    head->next = tail;
    tail->prev = head;
    head->prev = tail;
    tail->next = head;
    listSize = 2;
    capacity = 0;
    Node *temp = other.head;
    push_front(temp->data);
    temp = temp->next;
    while (temp != other.begin().curNode) {
        push_back(temp->data);
        temp = temp->next;
    }

}

LinkedList::LinkedList(LinkedList &&other) {
    tail = new Node();
    head = new Node();
    head->next = tail;
    tail->prev = head;
    head->prev = tail;
    tail->next = head;
    listSize = other.listSize;
    capacity = other.capacity;
    head = other.head;
    tail = other.tail;
}

LinkedList::~LinkedList() {

}

LinkedList::iterator::iterator() {
    curNode = nullptr;
};

LinkedList::iterator &LinkedList::iterator::operator=(const iterator &other) {
    this->curNode = other.curNode;
    return *this;
}

bool LinkedList::iterator::operator==(const iterator &other) const {
    return this->curNode == other.curNode;
}

bool LinkedList::iterator::operator!=(const iterator &other) const {
    return !(*this == other);
}

value_type &LinkedList::iterator::operator*() {
    return (this->curNode->data);
}

value_type *LinkedList::iterator::operator->() {
    return &(this->curNode->data);
}

LinkedList::iterator &LinkedList::iterator::operator++() {
    this->curNode->data++;
    return *this;
}

LinkedList::iterator LinkedList::iterator::operator++(int) {
    this->curNode = this->curNode->next;
    return *this;
}

LinkedList::iterator &LinkedList::iterator::operator--() {
    this->curNode->data--;
    return *this;
}

LinkedList::iterator LinkedList::iterator::operator--(int) {
    this->curNode = this->curNode->prev;
    return *this;
}

LinkedList::const_iterator::const_iterator() {
    curNode = nullptr;
};

LinkedList::const_iterator::const_iterator(const Node &other) {
    *(this->curNode) = other;
};

LinkedList::const_iterator &LinkedList::const_iterator::operator=(const const_iterator &other) {
    this->curNode = other.curNode;
    return *this;
}

bool LinkedList::const_iterator::operator==(const const_iterator &other) const {
    return this->curNode == other.curNode;
}

bool LinkedList::const_iterator::operator!=(const const_iterator &other) const {
    return !(*this == other);
}

const value_type &LinkedList::const_iterator::operator*() const {
    return (this->curNode->data);
}

const value_type *LinkedList::const_iterator::operator->() const {
    return &(this->curNode->data);
}

LinkedList::const_iterator &LinkedList::const_iterator::operator++() {
    this->curNode->data++;
    return *this;
}

LinkedList::const_iterator LinkedList::const_iterator::operator++(int) {
    this->curNode = this->curNode->next;
    return *this;
}

LinkedList::const_iterator &LinkedList::const_iterator::operator--() {
    this->curNode->data--;
    return *this;
}

LinkedList::const_iterator LinkedList::const_iterator::operator--(int) {
    this->curNode = this->curNode->prev;
    return *this;
}

LinkedList::iterator LinkedList::begin() {
    iterator it;
    it.curNode = head;
    return it;
}

LinkedList::const_iterator LinkedList::begin() const {
    const_iterator it;
    it.curNode = head;
    return it;
}

LinkedList::const_iterator LinkedList::cbegin() const {
    const_iterator it;
    it.curNode = head;
    return it;
}

LinkedList::iterator LinkedList::end() {
    iterator it;
    it.curNode = tail;
    return it;
}

LinkedList::const_iterator LinkedList::end() const {
    const_iterator it;
    it.curNode = tail;
    return it;
}

LinkedList::const_iterator LinkedList::cend() const {
    const_iterator it;
    it.curNode = tail;
    return it;
}

int LinkedList::size() const {
    return listSize;
}

bool LinkedList::empty() const {
    if ((capacity == 0) && (listSize == 2))
        return true;
    return false;
}

value_type &LinkedList::front() {
    return this->head->data;
}

const value_type &LinkedList::front() const {
    return this->head->data;
}

value_type &LinkedList::back() {
    return this->tail->data;
}

const value_type &LinkedList::back() const {
    return this->tail->data;
}

void LinkedList::changeSize(int i) {
    if (i == 0)
        listSize--;
    else
        listSize++;
}

void LinkedList::changeCapacity(int i) {
    if (i == 0)
        capacity--;
    else
        capacity++;
}

void LinkedList::push_back(const value_type &value) {
    if (tail->isEmpty == 1) {
        tail->data = value;
        tail->isEmpty = 0;
        changeCapacity(1);
        return;
    }
    Node *temp = new Node;
    temp->data = value;
    temp->next = head;
    temp->prev = tail;
    tail->next = temp;
    head->prev = temp;
    tail = temp;
    changeSize(1);
    changeCapacity(1);
    tail->isEmpty = 0;
}

void LinkedList::push_front(const value_type &value) {
    if (head->isEmpty == 1) {
        head->data = value;
        head->isEmpty = 0;
        changeCapacity(1);
        return;
    }
    Node *temp = new Node;
    temp->data = value;
    temp->next = head;
    temp->prev = tail;
    tail->next = temp;
    head->prev = temp;
    head = temp;
    changeSize(1);
    changeCapacity(1);
    head->isEmpty = 0;
}

LinkedList::iterator LinkedList::insert(iterator before, const value_type &value) {
    if (before.curNode == head)
        push_front(value);

    Node *temp = new Node;
    temp->data = value;
    iterator prevI = before;
    prevI--;

    prevI.curNode->next = temp;
    before.curNode->prev = temp;
    temp->prev = prevI.curNode;
    temp->next = before.curNode;
    changeSize(1);
    changeCapacity(1);
    return prevI;
}

LinkedList::iterator LinkedList::erase(iterator position) {
    position.curNode->prev->next = position.curNode->next;
    position.curNode->next->prev = position.curNode->prev;
    iterator beforePos = position;
    beforePos--;
    if(position.curNode->isEmpty == 0)
        changeCapacity(0);
    changeSize(0);
    free (position.curNode);
    return beforePos;
}

LinkedList::iterator LinkedList::erase(iterator begin, iterator end) {
    iterator beforeBegin = begin;
    beforeBegin--;
    iterator beforeEnd = end;
    beforeEnd--;
    beforeEnd.curNode->next = nullptr;
    beforeBegin.curNode->next = end.curNode;
    end.curNode->prev = beforeBegin.curNode;

    while (begin.curNode->next){
        begin++;
        if(begin.curNode->prev->isEmpty == 0)
            changeCapacity(0);
        changeSize(0);
        delete (begin.curNode->prev);
    }
    delete(begin.curNode);

    return end;
}

int LinkedList::remove(const value_type &value) {
    int size = listSize;
    int numOfDelNodes = 0;
    iterator it;
    it.curNode = head;

    for (int i = 0; i <= size; i++) {
        if (it.curNode->data == value) {
            it = erase(it);
            numOfDelNodes++;
        }
        it++;
    }
    return numOfDelNodes;
}

void LinkedList::clear() {
    iterator begI = begin();
    int size = listSize;
    for (int i = 0; i < size; i++) {
        begI = erase(begI);
    }
}

void LinkedList::pop_back() {
    iterator it;
    it.curNode = tail;
    it = erase(it);
    tail = it.curNode;
}

void LinkedList::pop_front() {
    iterator it;
    it.curNode = head;
   it = erase(it);
   head = it.curNode;
}

LinkedList &LinkedList::operator=(const LinkedList &other) {
    Node *temp = other.head;
    int size = other.listSize;
    push_front(temp->data);
    temp = temp->next;
    for (int i = 1; i < size; i++) {
        push_back(temp->data);
        temp = temp->next;
    }

    return *this;
}

LinkedList &LinkedList::operator=(LinkedList &&other) {
    listSize = other.listSize;
    head = other.head;
    tail = other.tail;
    return *this;
}

LinkedList &LinkedList::operator+=(const LinkedList &other) {
    Node *temp = other.head;
    int size = other.listSize;
    for(int i = 0; i < size; i++){
        push_back(temp->data);
        temp = temp->next;
    }
    return *this;
}

bool operator==(const LinkedList &left, const LinkedList &right){
    if(left.listSize != right.listSize)
        return false;
    int size = left.listSize;
    LinkedList::Node *leftNode = left.head;
    LinkedList::Node *rightNode = right.head;
    for(int i = 0; i < size; i++){
        if(leftNode->data != rightNode->data)
            return false;
    }
    return true;
}

bool operator!=(const LinkedList &left, const LinkedList &right){
    return !(left == right);
}

LinkedList operator+(const LinkedList &left, const LinkedList &right){
    LinkedList listToReturn;
    LinkedList::const_iterator itLeft = left.begin();
    LinkedList::const_iterator itRight = right.begin();
    listToReturn.push_front(itLeft.curNode->data);
    itLeft++;
    while(itLeft != left.begin()){
        listToReturn.push_back(itLeft.curNode->data);
        itLeft++;
    }
    while(itRight != right.end()){
        listToReturn.push_back(itRight.curNode->data);
        itRight++;
    }
    listToReturn.push_back(itRight.curNode->data);
    return listToReturn;
}