#include "LinkedList.h"

LinkedList::Node::Node() {
    data = 0;
    prev = next = nullptr;
}

LinkedList::Node::Node(const Node& other) {
    data = other.data;
    prev = other.prev;
    next = other.next;
}

LinkedList::Node::~Node() {

}

LinkedList::LinkedList() {
    tail = new Node();
    tail->next = tail;
    tail->prev = tail;
    listSize = 0;
}

LinkedList::LinkedList(const LinkedList& other) {
    tail = new Node();
    tail->next = tail;
    tail->prev = tail;
    listSize = 0;
    for (value_type it : other) {
        insert(end(), it);
    }
}

LinkedList::LinkedList(LinkedList&& other) {
    tail = other.tail;
    listSize = other.listSize;
}

LinkedList::~LinkedList() {
    clear();
    delete(tail);
}

LinkedList::iterator::iterator() {
    curNode = nullptr;
};

LinkedList::iterator& LinkedList::iterator::operator=(const iterator& other) {
    this->curNode = other.curNode;
    return *this;
}

bool LinkedList::iterator::operator==(const iterator& other) const {
    return this->curNode == other.curNode;
}

bool LinkedList::iterator::operator!=(const iterator& other) const {
    return !(*this == other);
}

value_type& LinkedList::iterator::operator*() {
    return (this->curNode->data);
}

value_type* LinkedList::iterator::operator->() {
    return &(this->curNode->data);
}

LinkedList::iterator& LinkedList::iterator::operator++() {
    this->curNode = this->curNode->next;
    return *this;
}

LinkedList::iterator LinkedList::iterator::operator++(int) {
    iterator it = *this;
    it.curNode = it.curNode->next;
    return it;
}

LinkedList::iterator& LinkedList::iterator::operator--() {
    this->curNode = this->curNode->prev;
    return *this;
}

LinkedList::iterator LinkedList::iterator::operator--(int) {
    iterator it = *this;
    it.curNode = it.curNode->prev;
    return it;
}

LinkedList::const_iterator::const_iterator() {
    curNode = nullptr;
};

LinkedList::const_iterator::const_iterator(const Node& other) {
    *(this->curNode) = other;
};

LinkedList::const_iterator& LinkedList::const_iterator::operator=(const const_iterator& other) {
    this->curNode = other.curNode;
    return *this;
}

bool LinkedList::const_iterator::operator==(const const_iterator& other) const {
    return this->curNode == other.curNode;
}

bool LinkedList::const_iterator::operator!=(const const_iterator& other) const {
    return !(*this == other);
}

const value_type& LinkedList::const_iterator::operator*() const {
    return (this->curNode->data);
}

const value_type* LinkedList::const_iterator::operator->() const {
    return &(this->curNode->data);
}

LinkedList::const_iterator& LinkedList::const_iterator::operator++() {
    const_iterator& it = *this;
    it.curNode = it.curNode->next;
    return it;
}

LinkedList::const_iterator LinkedList::const_iterator::operator++(int) {
    this->curNode = this->curNode->next;
    return *this;
}

LinkedList::const_iterator& LinkedList::const_iterator::operator--() {
    const_iterator& it = *this;
    it.curNode = it.curNode->prev;
    return it;
}

LinkedList::const_iterator LinkedList::const_iterator::operator--(int) {
    this->curNode = this->curNode->prev;
    return *this;
}

LinkedList::iterator LinkedList::begin() {
    iterator it;
    it.curNode = tail->next;
    return it;
}

LinkedList::const_iterator LinkedList::begin() const {
    const_iterator it;
    it.curNode = tail->next;
    return it;
}

LinkedList::const_iterator LinkedList::cbegin() const {
    const_iterator it;
    it.curNode = tail->next;
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
    if (listSize == 0)
        return true;
    return false;
}

value_type& LinkedList::front() {
    return this->tail->next->data;
}

const value_type& LinkedList::front() const {
    return this->tail->next->data;
}

value_type& LinkedList::back() {
    return this->tail->prev->data;
}

const value_type& LinkedList::back() const {
    return this->tail->prev->data;
}

void LinkedList::push_back(const value_type& value) {
    insert(end(), value);
}

void LinkedList::push_front(const value_type& value) {
    insert(begin(), value);
}

LinkedList::iterator LinkedList::insert(iterator before, const value_type& value) {
    Node* temp = new Node;
    temp->data = value;
    iterator prevI = before--;
    prevI.curNode->next = temp;
    before.curNode->prev = temp;
    temp->prev = prevI.curNode;
    temp->next = before.curNode;
    listSize++;
    return ++before;
}

LinkedList::iterator LinkedList::erase(iterator position) {
    position.curNode->prev->next = position.curNode->next;
    position.curNode->next->prev = position.curNode->prev;
    iterator nextI = position++;
    free(position.curNode);
    listSize--;
    return nextI;
}

LinkedList::iterator LinkedList::erase(iterator begin, iterator end) {
    iterator it = begin;
    while (begin != end) {
        begin = erase(begin);
    }
    return end;
}

int LinkedList::remove(const value_type& value) {
    int size = listSize;
    int numOfDelNodes = 0;
    iterator it;
    it.curNode = tail->next;
    for (int i = 0; i <= size; i++) {
        if (it.curNode->data == value) {
            it = erase(it);
            numOfDelNodes++;
        }
        else
            ++it;
    }
    return numOfDelNodes;
}

void LinkedList::clear() {
    erase(begin(), end());
}

void LinkedList::pop_back() {
    erase(--end());
}

void LinkedList::pop_front() {
    erase(begin());
}

LinkedList& LinkedList::operator=(const LinkedList& other) {
    if (*this == other)
        return *this;
    clear();
    for (value_type it : other) {
        insert(end(), it);
    }
    return *this;
}

LinkedList& LinkedList::operator=(LinkedList&& other) {
    other.clear();
    delete(other.tail);
    listSize = other.listSize;
    tail = other.tail;
    return *this;
}

LinkedList& LinkedList::operator+=(const LinkedList& other) {
    Node* temp = other.tail->next;
    int size = other.listSize;
    for (int i = 0; i < size; i++) {
        push_back(temp->data);
        temp = temp->next;
    }
    return *this;
}

bool operator==(const LinkedList& left, const LinkedList& right) {
    if (left.listSize != right.listSize)
        return false;
    LinkedList::const_iterator itRight = right.cbegin();
    for (value_type it : left) {
        if (it != itRight.curNode->data)
            return false;
        itRight++;
    }
    return true;
}

bool operator!=(const LinkedList& left, const LinkedList& right) {
    return !(left == right);
}

LinkedList operator+(const LinkedList& left, const LinkedList& right) {
    LinkedList newList = left;
    newList += right;
    return newList;
}