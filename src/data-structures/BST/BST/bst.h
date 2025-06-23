#include <vector>
#include <string>
#include <iostream>
using namespace std;

template <typename T>
class BinaryTree
{
public:
	class TreeNode
	{
	public:
		T _value;
		TreeNode* _left;
		TreeNode* _right;

		TreeNode(T value) :_value(value), _left(nullptr), _right(nullptr) {};
		~TreeNode() {
			_value = NULL;
			_left = nullptr;
			_right = nullptr;
		};
	};

	TreeNode* _root = nullptr;

	BinaryTree() { _root = nullptr; };
	BinaryTree(vector<T> arr);
	BinaryTree(const BinaryTree& other);
	BinaryTree(BinaryTree&& other) noexcept;
	BinaryTree& operator=(const BinaryTree& other) = delete;
	BinaryTree& operator=(BinaryTree&& other) = delete;
	~BinaryTree();
	bool Insert(T value); 
	bool Insert(TreeNode* _node, T value);
	bool Empty() const;
	bool Contains(const T value);
	void Print();
	vector<T> ToVector() const;
	vector<T> RoundLrootR();
	vector<T> RoundRrootL();
	bool Remove(const T value);

private:
	void DestroyBinaryTree(TreeNode* node);
	bool Contains(TreeNode* node, const T value);
	void Print(TreeNode* node);
	vector<T> ToVector(TreeNode* node, vector<T>& _arr) const;
	vector<T> RoundLrootR(TreeNode* node, vector<T>& _arr);
	vector<T> RoundRrootL(TreeNode* node, vector<T>& _arr);
    bool RemoveWithNoChild(TreeNode* node, const T value, TreeNode* parent);
    bool RemoveWithOneChild(TreeNode* node, TreeNode* parent, bool isLeftChild);
    bool RemoveWithTwoChild(TreeNode* node, const T value);
	bool Remove(TreeNode* node, const T value, TreeNode* parent);
	T FindLargestInSubtree(const T value, TreeNode* base, TreeNode* pre);
	void printBT(const string& prefix, TreeNode* node, bool isRight);
};

template <typename T>
BinaryTree<T>::BinaryTree(vector<T> arr)
{
	for (size_t i = 0; i < arr.size(); ++i)
		this->Insert(arr[i]);
}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
	this->DestroyBinaryTree(_root);
}

template <typename T>
void BinaryTree<T>::DestroyBinaryTree(TreeNode* node)
{
	if (node)
	{
		this->DestroyBinaryTree(node->_left);
		this->DestroyBinaryTree(node->_right);
		delete node;
	}
}

template <typename T>
bool BinaryTree<T>::Insert(T value)
{
	if (this->Empty()) {
		TreeNode* node = new TreeNode(value);
		_root = node;
		return true;
	}

	return this->Insert(_root, value);
}

template <typename T>
bool BinaryTree<T>::Insert(TreeNode* _node, T value)
{
	bool result;
	if (_node->_value == value)
		return false;

	if (_node->_value > value) { //спускаемся в левое поддерево
		if (_node->_left == nullptr) {
			TreeNode* node = new TreeNode(value);
			_node->_left = node;
			result = true;
		} else {
			result = this->Insert(_node->_left, value);
		}
	} else {
		if (_node->_right == nullptr) {
			TreeNode* node = new TreeNode(value);
			_node->_right = node;
			result = true;
		} else {
			result = this->Insert(_node->_right, value);
		}
	}

	return result;
}

template <typename T>
bool BinaryTree<T>::Empty() const
{
	return _root == nullptr ?  true : false;
}

template <typename T>
bool BinaryTree<T>::Contains(const T value)
{
	if (this->Empty()) {
		return false;
	}
	return this->Contains(_root, value);
}

template <typename T>
bool BinaryTree<T>::Contains(TreeNode* node, const T value)
{
	bool result;
	if (node) {
		if (value == node->_value)
		{
			return true;
		}
		if (value < node->_value)
		{
			result = this->Contains(node->_left, value);
		}	else {
			result = this->Contains(node->_right, value);
		}
	}	else {
		result = false;
	}

	return result;
}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& other)
{
	vector<T> otherArr = other.ToVector();
	for (size_t i = 0; i < otherArr.size(); i++)
	{
		this->Insert(otherArr[i]);
	}
}

template <typename T>
BinaryTree<T>::BinaryTree(BinaryTree&& other) noexcept
{
	_root = other._root;
	other._root = nullptr;
}

template <typename T>
vector<T> BinaryTree<T>::ToVector() const
{
	vector<int> arr{};
	if (this->Empty()) {
		return arr;
	}
	arr.push_back(_root->_value);
	return ToVector(_root, arr);
}

template <typename T>
vector<T> BinaryTree<T>::ToVector(TreeNode* node, vector<T>& _arr) const
{
	if (node) {
		this->ToVector(node->_left, _arr);
		_arr.push_back(node->_value);
		this->ToVector(node->_right, _arr);
	}
	return _arr;
}

template <typename T>
vector<T> BinaryTree<T>::RoundLrootR()
{
	vector<int> arr{};
	return RoundLrootR(_root, arr);
}

template <typename T>
vector<T> BinaryTree<T>::RoundLrootR(TreeNode* node, vector<T>& _arr)
{
	if (node) {
		_arr.push_back(node->_value);
		this->ToVector(node->_right, _arr);
	}
	_arr.erase(_arr.begin());
	return _arr;
}

template <typename T>
vector<T> BinaryTree<T>::RoundRrootL()
{
	vector<int> arr{};
	return RoundRrootL(_root, arr);
}

template <typename T>
vector<T> BinaryTree<T>::RoundRrootL(TreeNode* node, vector<T>& _arr)
{
	if (node) {
		this->ToVector(node->_left, _arr);
		_arr.push_back(node->_value);
	}
	_arr.pop_back();
	return _arr;
}

template <typename T>
bool BinaryTree<T>::Remove(const T value)
{
	if (!this->Contains(value)) {
		return false;
	}
	return this->Remove(_root, value, nullptr);
}

template <typename T>
bool BinaryTree<T>::RemoveWithNoChild(TreeNode* node, const T value, TreeNode* parent)
{
    if (parent->_value < value) {
        parent->_right = nullptr;
        node->~TreeNode();
    }	else {
        parent->_left = nullptr;
        node->~TreeNode();
    }
    return true;
}

template <typename T>
bool BinaryTree<T>::RemoveWithOneChild(TreeNode* node, TreeNode* parent, bool isLeftChild)
{
    if (isLeftChild) {
        parent->_left = node->_left;
    } else {
        parent->_right = node->_right;
    }
    node->~TreeNode();

    return true;
}

template <typename T>
bool BinaryTree<T>::RemoveWithTwoChild(TreeNode* node, const T value)
{
    T newVal;
    newVal = FindLargestInSubtree(value, node->_left, nullptr);
    node->_value = newVal;

    return true;
}

template <typename T>
bool BinaryTree<T>::Remove(TreeNode* node, const T value, TreeNode* parent)
{
	if (value == node->_value)
	{
	    bool result;
		if (!node->_left && !node->_right)
		{
            result = RemoveWithNoChild(node, value, parent);
		}
		if (node->_left && !node->_right)
		{
			result = RemoveWithOneChild(node, parent, true);
		}
		if (!node->_left && node->_right)
		{
            result = RemoveWithOneChild(node, parent, false);
		}
		if (node->_left && node->_right)
		{
		    result = RemoveWithTwoChild(node, value);
		}

		return result;
	}

	if (value < node->_value)
	{
		return this->Remove(node->_left, value, node);
	}
	else {
		return this->Remove(node->_right, value, node);
	}
}

template <typename T>
T BinaryTree<T>::FindLargestInSubtree(const T value, TreeNode* base, TreeNode* pre)
{
	T res;
	while (base->_right)
	{
		return this->FindLargestInSubtree(value, base->_right, base);
	}
	res = base->_value;
	base->~TreeNode();
	pre->_right = nullptr;
	return res;
}

template <typename T>
void BinaryTree<T>::Print()
{
	cout << "---------------------------------------------------------------\n";
	Print(_root);
	cout << "---------------------------------------------------------------\n";
}

template <typename T>
void BinaryTree<T>::Print(TreeNode* node)
{
	printBT("", node, false);
}

template <typename T>
void BinaryTree<T>::printBT(const string& prefix, TreeNode* node, bool isRight)
{
	if (node != nullptr)
	{
		cout << prefix + (isRight ? "|---" :"`---");
		cout << "[" << node->_value << "]" << endl;
		printBT(prefix + (isRight ? "|   " : "    "), node->_right, true);
		printBT(prefix + (isRight ? "|   " : "    "), node->_left, false);
	}
}
