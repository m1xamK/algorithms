#ifndef LINKEDLISTNODE_LINKEDLIST_H
#define LINKEDLISTNODE_LINKEDLIST_H

template<typename T>
struct LinkedListNode {
    LinkedListNode* _next;
    T _value;

    LinkedListNode() {
        _next = nullptr;
        _value = T();
    }

    LinkedListNode(LinkedListNode* next, T value) {
        _next = next;
        _value = value;
    }

    LinkedListNode(const LinkedListNode<T>& other) = delete;
};

#endif //LINKEDLISTNODE_LINKEDLIST_H
