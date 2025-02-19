#ifndef LINKEDLIST_LINKEDLIST_H
#define LINKEDLIST_LINKEDLIST_H

#include <LinkedList/LinkedListNode.hpp>

template<typename T>
class LinkedList {
public:
    LinkedList();

    LinkedList(const LinkedList<T>& other);

    LinkedList(LinkedList<T>&& other);

    ~LinkedList();

    LinkedList<T>& operator=(const LinkedList<T>& other);

    LinkedList<T>& operator=(LinkedList<T>&& other);

    LinkedListNode<T>* GetHead();

    LinkedListNode<T>* GetTail();

    void PushBack(T value);

    void PushFront(T value);

    LinkedListNode<T>* Find(T value);

    void Remove(T value);

    void Clear();

private:
    LinkedListNode<T>* _head;
    LinkedListNode<T>* _tail;

    void PushAfter(LinkedListNode<T>* where, T value);

    void RemoveBeginning();

    void InitializeFrom(const LinkedList<T>& other);
};

template<typename T>
LinkedList<T>::LinkedList() {
    _head = _tail = nullptr;
};

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) {
    InitializeFrom(other);
};

template<typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) {
    _head = other._head;
    _tail = other._tail;
};

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if (this == other)
        return *this;

    Clear();
    InitializeFrom();

    return *this;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) {
    if (this == other)
        return *this;

    _head = other._head;
    _tail = other._tail;

    return *this;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    Clear();
};

template<typename T>
LinkedListNode<T>* LinkedList<T>::GetHead() {
    return _head;
};

template<typename T>
LinkedListNode<T>* LinkedList<T>::GetTail() {
    return _tail;
};

template<typename T>
void LinkedList<T>::InitializeFrom(const LinkedList<T>& other) {
    _head = _tail = nullptr;

    LinkedListNode<T>* it = other._head;
    while (it) {
        PushBack(it->_value);
        it = it->_next;
    }
}

template<typename T>
void LinkedList<T>::PushAfter(LinkedListNode<T>* where, T value) {
    if (!_head) {
        _head = _tail = new LinkedListNode<T>(nullptr, value);
        return;
    }

    if (!where) {
        _head = new LinkedListNode<T>(_head, value);
        return;
    }

    LinkedListNode<T>* temp = new LinkedListNode<T>(where->_next, value);
    if (!where->_next)
        _tail = temp;
    where->_next = temp;
}

template<typename T>
void LinkedList<T>::PushFront(T value) {
    PushAfter(nullptr, value);
}

template<typename T>
void LinkedList<T>::PushBack(T value) {
    PushAfter(_tail, value);
}

template<typename T>
LinkedListNode<T>* LinkedList<T>::Find(T value) {
    LinkedListNode<T>* it = _head;
    while (it) {
        if (it->_value == value)
            return it;
        it = it->_next;
    }
    return it;
}

template<typename T>
void LinkedList<T>::Remove(T value) {
    if (_head == _tail) {
        delete _head;
        _head = _tail = nullptr;
        return;
    }

    LinkedListNode<T>* prev = _head;
    if (!prev)
        return;
    LinkedListNode<T>* current = prev;
    while (current) {
        if (current->_value == value)
            break;
        prev = current;
        current = current->_next;
    }
    
    if (!current) {
        return;
    }
    if (current == _head) {
        _head = current->_next;
    }
    if (current == _tail) {
        _tail = prev;
    }

    prev->_next = prev->_next->_next;
    delete current;
}

template<typename T>
void LinkedList<T>::Clear() {
    while (_head) {
        RemoveBeginning();
    }
}

template<typename T>
void LinkedList<T>::RemoveBeginning() {
    if (!_head)
        return;
    LinkedListNode<T>* temp = _head;
    _head = _head->_next;
    delete temp;
}

#endif //LINKEDLIST_LINKEDLIST_H
