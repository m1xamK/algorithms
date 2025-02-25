#ifndef TREENODE_API_HPP
#define TREENODE_API_HPP

#define TREENODE_API_HPP

template <typename T>
class TreeNode 
{
	public:
		TreeNode() = default;
		TreeNode(const T& value);
		T _value;
		TreeNode* _left;
		TreeNode* _right;
        int _height = -1; // height of empty tree = -1
};

template <typename T>
TreeNode<T>::TreeNode(const T& value)
{
    this->_value = value;
	this->_left = nullptr;
	this->_right = nullptr;
	this->_height = 0; // height of one element tree = 0
}

#endif //! TREENODE_API_HPP