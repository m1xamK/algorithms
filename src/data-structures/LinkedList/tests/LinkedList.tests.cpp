#include <gtest/gtest.h>
#include <vector>
#include <LinkedList/LinkedList.hpp>

void FillLinkedList(LinkedList<int>* other) {
    for (size_t i = 0; i < 10; ++i)
        other->PushBack(i);
}

TEST(
        PushBackLinkedListTests,
        GiveEmptyLinkedList_WhenAddValueToBackAndFindIt_ShouldReturnIt
) {
    LinkedList<int> list = LinkedList<int>();
    list.PushBack(42);
    LinkedListNode<int>* result = list.Find(42);
    ASSERT_EQ(result->_value, 42);
    ASSERT_TRUE(result->_next == nullptr);
}

TEST(
        PushBackLinkedListTests,
        GiveLinkedList_WhenAddValueToBackAndFindIt_ShouldReturnIt
) {
    LinkedList<int> list = LinkedList<int>();
    list.PushBack(142);
    list.PushBack(42);
    LinkedListNode<int>* beforeResult = list.Find(142);
    LinkedListNode<int>* result = list.Find(42);

    ASSERT_EQ(beforeResult->_value, 142);
    ASSERT_EQ(beforeResult->_next, result);
    ASSERT_EQ(result->_value, 42);
    ASSERT_TRUE(result->_next == nullptr);
}

TEST(
        PushFrontLinkedListTests,
        GiveEmptyLinkedList_WhenAddValueToFrontAndFindIt_ShouldReturnIt
) {
    LinkedList<int> list = LinkedList<int>();
    list.PushFront(42);
    LinkedListNode<int>* result = list.Find(42);
    ASSERT_EQ(list.GetHead(), result);
    ASSERT_EQ(result->_value, 42);
    ASSERT_TRUE(result->_next == nullptr);
}

TEST(
        PushFrontLinkedListTests,
        GiveLinkedList_WhenAddValueToFrontAndFindIt_ShouldReturnIt
) {
    LinkedList<int> list = LinkedList<int>();
    list.PushFront(142);
    list.PushFront(42);
    LinkedListNode<int>* afterResult = list.Find(142);
    LinkedListNode<int>* result = list.Find(42);

    ASSERT_EQ(afterResult->_value, 142);
    ASSERT_EQ(afterResult, list.GetTail());
    ASSERT_EQ(result->_value, 42);
    ASSERT_TRUE(result->_next == afterResult);
    ASSERT_EQ(result, list.GetHead());
}

TEST(
        FindLinkedListTests,
        GiveLinkedListWithNumbers_WhenFindMissingNumber_ShouldReturnNull
) {
    LinkedList<int>* list = new LinkedList<int>();
    FillLinkedList(list);

    ASSERT_TRUE(list->Find(42) == nullptr);

    delete list;
}

TEST(
        FindLinkedListTests,
        GiveLinkedListWithNumbers_WhenFindAll_ShouldFindEach
) {
    LinkedList<int>* list = new LinkedList<int>();
    FillLinkedList(list);

    for (size_t i = 0; i < 10; ++i)
        ASSERT_EQ(list->Find(i)->_value, i);

    delete list;
}

TEST(
        RemoveLinkedListTests,
        GiveLinkedListWithNumbers_WhenRemoveMiddlePositionNumber_ShouldRemoveIt
) {
    LinkedList<int>* list = new LinkedList<int>();
    FillLinkedList(list);

    ASSERT_EQ(list->Find(3)->_value, 3);
    list->Remove(3);
    ASSERT_TRUE(list->Find(3) == nullptr);

    delete list;
}

TEST(
        RemoveLinkedListTests,
        GiveLinkedList_WhenRemoveFirstNumber_ShouldRemoveItAndChangeHead
) {
    LinkedList<int>* list = new LinkedList<int>();
    FillLinkedList(list);
    LinkedListNode<int>* firstNode = list->Find(0);

    ASSERT_EQ(firstNode, list->GetHead());
    ASSERT_EQ(firstNode->_value, 0);

    list->Remove(0);
    LinkedListNode<int>* oldFirstNode = list->Find(0);
    firstNode = list->Find(1);

    ASSERT_TRUE(oldFirstNode == nullptr);
    ASSERT_EQ(firstNode, list->GetHead());
    ASSERT_EQ(firstNode->_value, 1);

    delete list;
}

TEST(
        RemoveLinkedListTests,
        GiveLinkedList_WhenRemoveLastNumber_ShouldRemoveItAndChangeTail
) {
    LinkedList<int>* list = new LinkedList<int>();
    FillLinkedList(list);
    std::vector<int> reference = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    LinkedListNode<int>* lastNode = list->Find(9);

    ASSERT_EQ(lastNode, list->GetTail());
    ASSERT_EQ(lastNode->_value, 9);

    list->Remove(9);
    LinkedListNode<int>* oldNode = list->Find(9);
    lastNode = list->Find(8);

    ASSERT_TRUE(oldNode == nullptr);
    ASSERT_EQ(lastNode, list->GetTail());
    ASSERT_EQ(lastNode->_value, 8);

    delete list;
}

TEST(
        RemoveLinkedListTests,
        GiveEmptyLinkedList_WhenRemoveNotExistNumber_ShouldStayTheSame
) {
    LinkedList<int>* list = new LinkedList<int>();
    list->Remove(42);

    ASSERT_TRUE(list->GetHead() == nullptr);
    ASSERT_TRUE(list->GetTail() == nullptr);

    delete list;
}

TEST(
        RemoveLinkedListTests,
        GiveLinkedList_WhenRemoveNotExistNumber_ShouldStayTheSame
) {
    LinkedList<int>* list = new LinkedList<int>();

    FillLinkedList(list);
    list->Remove(42);

    for (size_t i = 0; i < 10; ++i)
        ASSERT_EQ(list->Find(i)->_value, i);

    delete list;
}

TEST(
        RemoveLinkedListTests,
        GiveLinkedList_WhenRemoveAllNodes_ShouldResetHeadAndTail
) {
    LinkedList<int>* list = new LinkedList<int>();

    FillLinkedList(list);
    for (size_t i = 0; i < 10; ++i)
        list->Remove(i);

    ASSERT_TRUE(list->GetHead() == nullptr);
    ASSERT_TRUE(list->GetTail() == nullptr);

    delete list; 
}

TEST(
        CopyLinkedListTests,
        GiveLinkedList_WhenCopyList_ShouldFindAllNumbersInNewList
) {
    LinkedList<int> list = LinkedList<int>();

    FillLinkedList(&list);
    for (size_t i = 0; i < 10; ++i)
        ASSERT_EQ(list.Find(i)->_value, i);
    LinkedList<int> listCopy(list);
    for (size_t i = 0; i < 10; ++i)
        ASSERT_EQ(listCopy.Find(i)->_value, i);
}

TEST(
        CopyLinkedListTests,
        GiveLinkedList_WhenCopyListByOperator_ShouldFindAllNumbersInNewList
) {
    LinkedList<int> list = LinkedList<int>();

    FillLinkedList(&list);
    for (size_t i = 0; i < 10; ++i)
        ASSERT_EQ(list.Find(i)->_value, i);
    LinkedList<int> listCopy = list;
    for (size_t i = 0; i < 10; ++i)
        ASSERT_EQ(listCopy.Find(i)->_value, i);
}

template<typename T>
LinkedList<T> GetEmptyLinkedList()
{
    LinkedList<T> list;
    return list;
}

TEST(
        MoveLinkedListTests,
        GiveLinkedList_WhenMoveList_ShouldFindAllNumbersInNewList
) {
    LinkedList<int> list = GetEmptyLinkedList<int>();

    FillLinkedList(&list);
    for (size_t i = 0; i < 10; ++i)
        ASSERT_EQ(list.Find(i)->_value, i);
}