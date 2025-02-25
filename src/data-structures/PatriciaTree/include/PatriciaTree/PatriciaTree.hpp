#pragma once
#include <bitset>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#define N 8

template <typename T>
class TreeNode
{
public:
	char _key;
	int _index;
	T _value;
	TreeNode* _left = nullptr;
	TreeNode* _right = nullptr;
	TreeNode(char key, T value, int index) : _key(key), _value(value), _index(index) {};
	char GetKey() { if (this) return this->_key; };
};

template <typename T>
class PatriciaTree
{
friend class TreeNode<T>;
public:
	PatriciaTree();
	TreeNode<T>* GetRoot() { return this->_root; };
	friend std::bitset<N> BitsOfChar(char key);
	friend int FirstDiffIndex(std::bitset<N> a, std::bitset<N> b);
	friend std::bitset<N> ReverseBits(std::bitset<N> a);
	void Output();
	void Output(TreeNode<T>* node, int level);
	void Insert(char elem);
	void Insert(TreeNode<T>* currentNode, TreeNode<T>* prevNode, char elem);
	TreeNode<T>* Search(char elem);
	std::vector<char> Walk(TreeNode<T>* node, std::vector<char> res);
	std::string toString(char elem)
	{
		std::string res;
		if (elem == '\0')
			res = '0';
		else
			res = elem;

		return res;
	}
	std::string GenRelation(TreeNode<T>* node, std::string str)
	{
		if (node->_left->_value == node->_value || node->_right->_value == node->_value)
		{
			node->_left == node ? str += toString(node->_key) + "->" + toString(node->_left->_key) + "[color = green]" + '\n'
				: str += toString(node->_key) + "->" + toString(node->_right->_key) + "[color = red]" + '\n';
		}
		if (node->_left->_index < node->_index)
		{
			str += toString(node->_key) + "->" + toString(node->_left->_key) + "[color = green]" + '\n';
		}
		if (node->_right->_index < node->_index)
		{
			str += toString(node->_key) + "->" + toString(node->_right->_key) + "[color = red]" + '\n';
		}
		if (node->_right->_index > node->_index) {
			str = GenRelation(node->_right, str);
			str += toString(node->_key) + "->" + toString(node->_right->_key) + "[color = red]" + '\n';
		}
		if (node->_left->_index > node->_index) {
			str = GenRelation(node->_left, str);
			str += toString(node->_key) + "->" + toString(node->_left->_key) + "[color = green]" + '\n';
		}

		return str;
	}
	void Draw(std::string filename)
	{
		try
		{
			std::string sheme = "";
			std::ofstream file;
			file.open(filename);
			if (file.is_open())
			{
				sheme = "digraph G {\n" + GenRelation(_root, "") + "}";
				file << sheme;
			}
			file.close();
			std::string command = "dot" + filename + " -Tpng -o " + filename.substr(0, filename.length() - 3) + ".png ";
			system(command.c_str());
		}
		catch (...)
		{
			std::cout << "ERROR. GRAPHVIZ NOT FOUND";
		}
	}
private:
	TreeNode<T>* _root = nullptr;
};

std::bitset<N> BitsOfChar(char key)
{
	return std::bitset<N>(key);
}

int FirstDiffIndex(std::bitset<N> a, std::bitset<N> b)
{
	int ind = 0;
	for (int i = 0; i < N; ++i)
	{
		if (a[i] != b[i])
		{
			ind = i;
			break;
		}
	}

	return ind + 1;
}

std::bitset<N> ReverseBits(std::bitset<N> a)
{
	for (int i = 0; i < N / 2; ++i)
	{
		bool temp = a[i];
		a[i] = a[N - 1 - i];
		a[N - 1 - i] = temp;
	}

	return a;
}


template<typename T>
PatriciaTree<T>::PatriciaTree()
{
	TreeNode<T>* node = new TreeNode('\0', BitsOfChar('\0'), 0);
	node->_left = node;
	node->_right = node;
	this->_root = node;
}

template <typename T>
void PatriciaTree<T>::Insert(char elem)
{
	if (this->_root->_left == this->_root)
	{
		std::bitset<N> newKey = BitsOfChar(elem);
		int index = FirstDiffIndex(ReverseBits(newKey), ReverseBits(this->_root->_value));
		TreeNode<T>* newNode = new TreeNode(elem, newKey, index);
		this->_root->_left = newNode;
		if (ReverseBits(newKey)[index - 1] == 1) {
			newNode->_right = newNode;
			newNode->_left = this->_root;
		}
		else {
			newNode->_left = newNode;
			newNode->_right = this->_root;
		}
	}
	else {
		Insert(this->_root->_left, this->_root, elem);
	}
}

template <typename T>
void PatriciaTree<T>::Insert(TreeNode<T>* currentNode, TreeNode<T>* prevNode, char elem)
{
	std::bitset<N> bits = BitsOfChar(elem);
	while (currentNode->_index > prevNode->_index)
	{
		if (currentNode->_value == bits)
			return;
		prevNode = currentNode;
		ReverseBits(bits)[currentNode->_index - 1] == 1 ? currentNode = currentNode->_right : currentNode = currentNode->_left;
	}
	int diffInd = FirstDiffIndex(ReverseBits(currentNode->_value), ReverseBits(bits));
	TreeNode<T>* newNode = new TreeNode(elem, bits, diffInd);
	currentNode = this->_root->_left;
	prevNode = this->_root;
	while (currentNode->_index > prevNode->_index && diffInd > currentNode->_index)
	{
		prevNode = currentNode;
		ReverseBits(bits)[currentNode->_index - 1] == 1 ? currentNode = currentNode->_right : currentNode = currentNode->_left;
	}
	std::bitset<N> prevBits = BitsOfChar(prevNode->_key);
	ReverseBits(bits)[prevNode->_index - 1] == 1 ? prevNode->_right = newNode : prevNode->_left = newNode;
	if (ReverseBits(bits)[diffInd - 1] == 1)
	{
		newNode->_right = newNode;
		newNode->_left = currentNode;
	}
	else {
		newNode->_left = newNode;
		newNode->_right = currentNode;
	}
}

template<typename T>
void PatriciaTree<T>::Output()
{
	return Output(this->_root, 0);
}

template<typename T>
void PatriciaTree<T>::Output(TreeNode<T>* node, int level)
{
		if (node->_right->_index > node->_index){
			Output(node->_right, level + 3);
		}
		for (int i = 0; i < level; i++) std::cout << "   ";
		std::cout << node->_key << std::endl;
		if (node->_left->_index > node->_index){
			Output(node->_left, level + 3);
		}
}

template <typename T>
TreeNode<T>* PatriciaTree<T>::Search(char elem)
{
	std::bitset<N> bits = BitsOfChar(elem);
	TreeNode<T>* current = this->_root->_left;
	TreeNode<T>* prev = this->_root;
	TreeNode<T>* res = nullptr;
	while (current->_index > prev->_index)
	{
		if (current->_key == elem)
		{
			res = current;
			break;
		}
		else {
			prev = current;
			ReverseBits(bits)[current->_index - 1] == 1 ? current = current->_right : current = current->_left;
		}
	}

	return res;
}

template<typename T>
std::vector<char> PatriciaTree<T>::Walk(TreeNode<T>* node, std::vector<char> res)
{
	res.push_back(node->_key);
	if (node->_right->_index > node->_index) {
		res = Walk(node->_right, res);
	}
	if (node->_left->_index > node->_index) {
		res = Walk(node->_left, res);
	}

	return res;
}
