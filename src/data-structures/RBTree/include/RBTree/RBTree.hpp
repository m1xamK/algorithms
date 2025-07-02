#ifndef RBTREE
#define RBTREE
#include <vector>
#include <iostream>
#include <tuple>
#include <stack>
#include <fstream>

typedef enum {BLACK, RED} Color;

template<typename T>
class RBTree {
    private:
        class TreeNode {
            public:
                T _value;
                TreeNode* _left   = nullptr;
                TreeNode* _right  = nullptr;
                TreeNode* _parent = nullptr;
                Color _color = RED;
                TreeNode(T value, TreeNode* left, TreeNode* right, TreeNode* parent, Color color) :
                 _value(value), _left(left), _right(right), _parent(parent), _color(color) {}
                TreeNode(T value): _value(value){};
                TreeNode(TreeNode& other) {
                    _value = other._value;
                    _right = other._right ? new TreeNode(*(other._right)) : nullptr;
                    _left = other._left ? new TreeNode(*(other._left)) : nullptr;
                }
        };
        TreeNode* _root;

        TreeNode* find(const T& value) {
            TreeNode* node = _root;
            while (node && value != node->_value) {
                node = value > node->_value ? node->_right : node->_left;
            }
            return node;   
        }

        void LNR(TreeNode* node, std::vector<T>& ans) {
            if (!node)
                return;
            if (node->_left)
                LNR(node->_left, ans);
            ans.push_back(node->_value);
            if (node->_right)
                LNR(node->_right, ans);
        }

        void RNL(TreeNode* node, std::vector<T>& ans) {
            if (node == nullptr)
                return;
            if (node->_right)
                RNL(node->_right, ans);
            ans.push_back(node->_value);
            if (node->_left)
                RNL(node->_left, ans);
        }

        void insertFixup(TreeNode* node) {
            while (node != _root && node->_parent->_color == RED) {
                
                if (node->_parent == node->_parent->_parent->_left) {
                    TreeNode* uncle = node->_parent->_parent->_right;
                    if (uncle && uncle->_color == RED) {
                        node->_parent->_color = BLACK;
                        uncle->_color = BLACK;
                        node->_parent->_parent->_color = RED;
                        node = node->_parent->_parent;
                    } else {
                        if (node == node->_parent->_right) {
                            node = node->_parent;
                            rotate_left(node);
                        }
                        node->_parent->_color = BLACK;
                        node->_parent->_parent->_color = RED;
                        rotate_right(node->_parent->_parent);
                    }
                } else {
                    TreeNode* uncle = node->_parent->_parent->_left;
                    if (uncle && uncle->_color == RED) {
                        node->_parent->_color = BLACK;
                        uncle->_color = BLACK;
                        node->_parent->_parent->_color = RED;
                        node = node->_parent->_parent;
                    } else {
                        if (node == node->_parent->_left) {
                            node = node->_parent;
                            rotate_right(node);
                        }

                        node->_parent->_color = BLACK;

                        node->_parent->_parent->_color = RED;
                        rotate_left(node->_parent->_parent);
                    }
                }
            }

            _root->_color = BLACK;
        }

        void rotate_left(TreeNode* node) {
            TreeNode* rnode = node->_right;
            node->_right = rnode->_left;
            if (rnode && rnode->_left)
                rnode->_left->_parent = node;
            if (rnode)
                rnode->_parent = node->_parent;
            if (node->_parent) {
                if (node == node->_parent->_left)
                    node->_parent->_left = rnode;
                else
                    node->_parent->_right = rnode;
            } else _root = rnode;

            rnode->_left = node;
            if (node)
                node->_parent = rnode;
        }

        void rotate_right(TreeNode* node) {
            TreeNode* lnode = node->_left;
            node->_left = lnode->_right;
            if (lnode && lnode->_right)
                lnode->_right->_parent = node;
            if (lnode)
                lnode->_parent = node->_parent;
            if (node->_parent) {
                if (node == node->_parent->_right)
                    node->_parent->_right = lnode;
                else
                    node->_parent->_left = lnode;
            } else _root = lnode;

            lnode->_right = node;
            if (node)
                node->_parent = lnode;
        }

        void deleteFixup(TreeNode* node) {
            while (node != _root && node->_color == BLACK) {
                if (node == node->_parent->_left) {
                    TreeNode* brother = node->_parent->_right;
                    if (brother->_color == RED) {
                        brother->_color = BLACK;
                        node->_parent->_color = RED;
                        rotate_left(node->_parent);
                        brother = node->_parent->_right;
                    }
                    if (brother->_left->_color == BLACK && brother->_right->_color == BLACK) {
                        brother->_color = RED;
                        node = node->_parent;
                    } else {
                        if (brother->_right->_color == BLACK) {
                            brother->_left->_color = BLACK;
                            brother->_color = RED;
                            rotate_right(brother);
                            brother = node->_parent->_right;
                        }

                        brother->_color = node->_parent->_color;
                        node->_parent->_color = BLACK;
                        brother->_right->_color = BLACK;
                        rotate_left(node->_parent);
                        node = _root;
                    }
                } else {
                    TreeNode* brother = node->_parent->_left;
                    if (brother->_color == RED) {
                        brother->_color = BLACK;
                        node->_parent->_color = RED;
                        rotate_right(node->_parent);
                        brother = node->_parent->_left;
                    }
                    if (brother->_right->_color == BLACK && brother->_left->_color == BLACK) {
                        brother->_color = RED;
                        node = node->_parent;
                    } else {
                        if (brother->_left->_color == BLACK) {
                            brother->_right->_color = BLACK;
                            brother->_color = RED;
                            brother->_color = RED;
                            rotate_left(brother);
                            brother = node->_parent->_left;
                        }
                        brother->_color = node->_parent->_color;
                        node->_parent->_color = BLACK;
                        brother->_left->_color = BLACK;
                        rotate_right(node->_parent);
                        node = _root;
                    }
                }
            }
            node->_color = BLACK;
        }
    public:
    
        RBTree() {
            _root = nullptr;
        }
        RBTree(std::vector<T>& values) : RBTree() {
            for (auto i : values)
                insert(i);
        }
        ~RBTree() {
            std::stack<TreeNode*> st;
            if (_root)
                st.push(_root);
            while (!st.empty()) {
                TreeNode* node = st.top(); st.pop();
                if (node->_left)
                    st.push(node->_left);
                if (node->_right)
                    st.push(node->_right);
                delete node;
            }
        }
        RBTree(const RBTree& other) {
            _root = new TreeNode(*(other._root));
        }
        RBTree(RBTree&& other) {
            _root = other._root;
            other._root = nullptr;
        }
        RBTree& operator=(const RBTree&) = delete;
        RBTree& operator=(RBTree&&) = delete;
        bool empty() const {
            return !_root;
        }
    
        bool insert(const T& value) {
            TreeNode* curr = _root, 
                    *_parent = nullptr;
            
            while (curr) {
                if (value == curr->_value)
                    return false;
                _parent = curr;
                curr = value >= curr->_value ? curr->_right : curr->_left;
            }
            TreeNode* newNode = new TreeNode(value);
            if (_parent) {
                if (value >= _parent->_value)
                    _parent->_right = newNode;
                else
                    _parent->_left = newNode;
            } else
                _root = newNode;
            newNode->_parent = _parent;
            insertFixup(newNode);
            return true;
        }
    
        bool remove(const T& value) {
            TreeNode* x;
            TreeNode* y;
            TreeNode* target = find(value);
            if (!target)
                return false;
            if (!target->_left && !target->_right) {
                if (target == _root)
                {
                    delete _root;
                    _root = nullptr;
                    return true;
                }
                if (target == target->_parent->_left)
                    target->_parent->_left = nullptr;
                else
                    target->_parent->_right = nullptr;
                delete target;
                return true;
            }
            if (!target->_left || !target->_right)
                y = target;
            else {
                y = target->_right;
                while (y->_left)
                    y = y->_left;
            }
            if (y->_left)
                x = y->_left;
            else
                x = y->_right;

            x->_parent = y->_parent;
            if (y->_parent) {
                if (y == y->_parent->_left)
                    y->_parent->_left = x;
                else
                    y->_parent->_right = x;
            } else {
                _root = x;
                _root->_color = BLACK;
                delete y;
                return true;
            }
            if (y != target)
                target->_value = y->_value;

            if (y->_color == BLACK)
                deleteFixup(x);

            delete y;
            return true;
        }
    
        bool contains(const T& value) {
            return bool(find(value));
        }
    
        std::vector<T> RoundLrootR() {
            std::vector<T> ans;
            LNR(_root, ans);
            return ans;
        }
    
        std::vector<T> RoundRrootL() {
            std::vector<T> ans;
            RNL(_root, ans);
            return ans;
        }
    
        void MakeStringToGV(std::string& str, TreeNode* node)
        {
            if (!node)
                return;
            if (node->_color == RED) {
                str += std::to_string(node->_value) + "[style=filled, fillcolor=red]\n";
            } else {
                str += std::to_string(node->_value) + "[style=filled, fillcolor=black, fontcolor=white]\n";
            }
            if (node->_left) {
                std::string left = std::to_string(node->_left->_value);
                str += std::to_string(node->_value) + "->" + left + "[color=black]\n";
            } else
                str += std::to_string(node->_value) + "->" + "nullptr_" + std::to_string(node->_value) + "[fillcolor=black, stile=filled, fontcolor=white]\n";
            if (node->_right) {
                std::string right = std::to_string(node->_right->_value);
                str += std::to_string(node->_value) + "->" + right + "[color=black]\n";
            } else
                str += std::to_string(node->_value) + "->" + "nullptr_" + std::to_string(node->_value) + "[fillcolor=black, stile=filled, fontcolor=white]\n";
            MakeStringToGV(str, node->_left);
            MakeStringToGV(str, node->_right);
        }
        void MakeGVFile(const std::string filepath)
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
};
#endif