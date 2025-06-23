#ifndef AVLTREE_H
#define AVLTREE_H

#include <vector>
#include <string>
#include <fstream>
#include "TreeNode.hpp"

template<typename T>
class AVLTree
{
    public:

    AVLTree() = default;

    AVLTree(T* arr, int n);

    ~AVLTree();

	bool Empty();

    void Insert(const T& value);

    bool Remove(const T& value);

    bool Find(const T& value);

    std::vector<T> Walk();

    void Output();

	TreeNode<T>* GetRoot();

	void MakeGVFile(std::string filename);

    private:

    int GetHeight(TreeNode<T>* node);

    int GetBalance(TreeNode<T>* node);

	void FixHeight(TreeNode<T>* node);

	TreeNode<T>* LeftRotate(TreeNode<T>* node);

	TreeNode<T>* RightRotate(TreeNode<T>* node);

	TreeNode<T>* Balance(TreeNode<T>* node);

	void Output(TreeNode<T>* node, int level);

    TreeNode<T>* FindParentNode(const T& value);

    void Delete(TreeNode<T>* node);

    void Rewrite(TreeNode<T>* node, TreeNode<T>* parentNode, TreeNode<T>* needNode = nullptr);

    TreeNode<T>* Insert(TreeNode<T>* node, const T& value);

	void Remove(TreeNode<T>* node, TreeNode<T>* parentNode);

	TreeNode<T>* Search(const T& value);

    TreeNode<T>* FindMinNodeRightSubtree();

	TreeNode<T>* FindMaxNodeLeftSubtree();

	std::vector<T> Walk(TreeNode<T>* node, std::vector<T>& result);

	void MakeStringToGV(std::string& str, TreeNode<T>* node);
	
    TreeNode<T>* _root = nullptr;

};

template<typename T>
AVLTree<T>::AVLTree(T* arr, int n)
{
	for(int i = 0; i < n; ++i)
	{
		this->Insert(arr[i]);
	}
}


template <typename T>
void  AVLTree<T>::Delete(TreeNode<T>* node)
{
    if (node) {
		Delete(node->_left);
		Delete(node->_right);
		delete node;
	}
}

template <typename T>
AVLTree<T>::~AVLTree()
{
    Delete(this->_root);
}


template <typename T>
int AVLTree<T>::GetHeight(TreeNode<T>* node)
{
    return !node ? -1 : node->_height;
}

template<typename T>
int AVLTree<T>::GetBalance(TreeNode<T>* node)
{
    return GetHeight(node->_left) - GetHeight(node->_right);
}

template <typename T>
void AVLTree<T>::FixHeight(TreeNode<T>* node)
{
	int h1 = GetHeight(node->_left);
	int h2 = GetHeight(node->_right);
	node->_height = (h1>h2 ? h1 : h2) + 1;
}

template <typename T>
TreeNode<T>* AVLTree<T>::RightRotate(TreeNode<T>* node)
{
	TreeNode<T>* leftNode = node->_left;
	node->_left = leftNode->_right;
	leftNode->_right = node;
	FixHeight(node);
	FixHeight(leftNode);

	if(node == this->_root)
		this->_root = leftNode;

	return leftNode;
}  

template <typename T>
TreeNode<T>* AVLTree<T>::LeftRotate(TreeNode<T>* node)
{
	TreeNode<T>* rightNode = node->_right;
	node->_right = rightNode->_left;
	rightNode->_left = node;
	FixHeight(node);
	FixHeight(rightNode);

	if(node == this->_root)
		this->_root = rightNode;

	return rightNode;
}

template <typename T>
TreeNode<T>* AVLTree<T>::Balance(TreeNode<T>* node)
{
	FixHeight(node);

	if (GetBalance(node) == -2)
	{
		if (GetBalance(node->_right) > 0)
			node->_right = RightRotate(node->_right);

		return LeftRotate(node);
	}

	if (GetBalance(node) == 2)
	{
		if (GetBalance(node->_left) < 0)
			node->_left = LeftRotate(node->_left);

		return RightRotate(node);
	}
	return node;
}

template<typename T>
TreeNode<T>* AVLTree<T>::Insert(TreeNode<T>* node, const T& value)
{
    
    if (!node)
	{
		TreeNode<T>* res = new TreeNode<T>(value);
		return res;
	}

	if (value < node->_value)
	{
		node->_left = Insert(node->_left, value);
	}
	else {
	
		node->_right = Insert(node->_right, value);
	}
	
	return Balance(node);
}

template <typename T>
void AVLTree<T>::Insert(const T& value)
{
    if(!this->_root)
    {
        _root = new TreeNode<T>(value);
        return;
    }
    
    this->Insert(this->_root, value);
}

template <typename T>
TreeNode<T>* AVLTree<T>::Search(const T& value)
{
	TreeNode<T>* current = _root;
		while (current) {
			if (value < current->_value)
				current = current->_left;
			else if (value > current->_value)
				current = current->_right;
			else if (value == current->_value)
				return current;
		}
		return nullptr;
}

template<typename T>
bool AVLTree<T>::Find(const T& value)
{
	return (bool)Search(value);
}


template <typename T>
TreeNode<T>* AVLTree<T>::FindParentNode(const T& value)
{
	TreeNode<T>* node = _root;
	TreeNode<T>* parent = _root;
	while (node != nullptr)
	{
		if (value < node->_value)
		{
			parent = node;
			node = node->_left;
		}

		else if (value > node->_value)
		{
			parent = node;
			node = node->_right;
		}

		else if (value == node->_value)
		{
            return parent;
		}
	}
    return nullptr;
}

template <typename T>
void AVLTree<T>::Rewrite(TreeNode<T>* node, TreeNode<T>* parentNode, TreeNode<T>* needNode) //function that rewrite child of parent node from node to need node
{
	if (parentNode->_right == node)
		parentNode->_right = needNode;
	else
		parentNode->_left = needNode;
}

template <typename T>
TreeNode<T>* AVLTree<T>::FindMinNodeRightSubtree()
{
	TreeNode<T>* current = _root->_right;
	while (current->_left != nullptr)
		current = current->_left;

	return current;
}

template <typename T>
TreeNode<T>* AVLTree<T>::FindMaxNodeLeftSubtree()
{
	TreeNode<T>* current = _root->_left;
	while (current->_right != nullptr)
		current = current->_right;

	return current;
}

template <typename T>
void AVLTree<T>::Remove(TreeNode<T>* node, TreeNode<T>* parentNode)
{
	if (!node->_left && !node->_right) {
		if (node->_value == parentNode->_value)
			_root = nullptr;
		Rewrite(node, parentNode);
	}
	else if (!node->_left) {
		Rewrite(node, parentNode, node->_right);
	}
	else if (!node->_right) {
		Rewrite(node, parentNode, node->_left);
	}
	else {
		TreeNode<T>* minNode = FindMaxNodeLeftSubtree();
		TreeNode<T>* minParent = FindParentNode(minNode->_value);
		T buffer = minNode->_value;
		Remove(minNode, minParent);
		node->_value = minNode->_value;
	}
	
	Balance(parentNode);
}

template <typename T>
bool AVLTree<T>::Remove(const T& value)
{
	TreeNode<T>* node = Search(value);
	TreeNode<T>* parentNode = FindParentNode(value);
	if (node) {
		Remove(node, parentNode);
		return true;
	}
		return false;
}

template <typename T>
void AVLTree<T>::Output()
{
	this->Output(this->_root, 0);
}

template <typename T>
void AVLTree<T>::Output(TreeNode<T>* node, int level)
{
	while (node) {
		Output(node->_right, level + 5);
		for (int i = 0; i < level; ++i)
		{
			std::cout << " ";
		}
		std::cout << node->_value << '\n';
		node = node->_left;
		level += 5;
	}
}

template <typename T>
std::vector<T> AVLTree<T>::Walk()
{
	std::vector<T> result;
	return this->Walk(_root, result);
}

template <typename T>
std::vector<T> AVLTree<T>::Walk(TreeNode<T>* node, std::vector<T>& result)
{
	if(node)
	{
		result.push_back(node->_value);
		result = this->Walk(node->_left, result);
		result = this->Walk(node->_right, result);
	}

	return result;
}

template <typename T>
bool AVLTree<T>::Empty()
{
	return !this->_root;
}

template <typename T>
TreeNode<T>* AVLTree<T>::GetRoot()
{
	return this->_root;
}

template<typename T>
void AVLTree<T>::MakeStringToGV(std::string& str, TreeNode<T>* node)
{
    if (!node)
        return;
    if (node->_left) {
        std::string left = std::to_string(node->_left->_value);
        str += std::to_string(node->_value) + "->" + left + "[color=black]\n";
    } else
        str += "inv" + std::to_string(node->_value) + " [style=invis]\n" + std::to_string(node->_value) + "->" + "inv" + std::to_string(node->_value) + " [style=invis]\n";
    if (node->_right) {
        std::string right = std::to_string(node->_right->_value);
        str += std::to_string(node->_value) + "->" + right + "[color=black]\n";
    } else
        str += "inv" + std::to_string(node->_value) + " [style=invis]\n" + std::to_string(node->_value) + "->" + "inv" + std::to_string(node->_value) + " [style=invis]\n";
    MakeStringToGV(str, node->_left);
    MakeStringToGV(str, node->_right);
}

template<typename T>
void AVLTree<T>::MakeGVFile(const std::string filepath)
{
    std::ofstream file(filepath);

    if(!file) {
        std::cout << "doesn't open " << filepath << std::endl;
        return;
    }

    file << "digraph G\n{\n";
    std::string buffer;
    this->MakeStringToGV(buffer, this->_root);
    file << buffer;
    file << "}";

    file.close();
}

#endif