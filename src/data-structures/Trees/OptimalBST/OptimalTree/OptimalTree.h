#include "pch.h"
using namespace std;
template <typename T>
class OptimalBinaryTree
{
private:
    struct TreeNode
    {
        T _key;
        TreeNode *_left;
        TreeNode *_right;
        TreeNode *_parent;
        TreeNode(T key = T(), TreeNode *left = nullptr, TreeNode *right = nullptr, TreeNode *parent = nullptr)
            : _key(key), _right(right), _left(left), _parent(parent) {}
    };

    TreeNode *_root = nullptr;
    void CreateEmptyMatrix(vector<vector<tuple<int, double, double>>> &matrix, const int size);
    void MainDiagonal(vector<vector<tuple<int, double, double>>> &matrix, const vector<double> &qValues, const int size);
    void FillMatrix(vector<vector<tuple<int, double, double>>> &matrix, const vector<double> pValues, const vector<double> qValues, const int size);
    void diagonal(vector<vector<tuple<int, double, double>>> &matrix, const vector<double> pValues, const vector<double> qValues, int i, int j, int minKey);
    TreeNode *MatrixToTree(vector<vector<tuple<int, double, double>>> matrix, vector<T> keys, TreeNode *tree, set<T> &set, int y, int x);
    TreeNode *Find(const T &value);
    T MaxElem() const;
    T MinElem() const;
    void PrintBinaryTree(TreeNode *container, int level);
    void DeleteTree(TreeNode *tree);

public:
    OptimalBinaryTree() = default;
    OptimalBinaryTree(vector<T> keys, vector<double> pValues, vector<double> qValues);
    T Search(const T &key);
    vector<T> RoundLrootR();
    vector<T> RoundRrootL();
    void Output();
    ~OptimalBinaryTree();
};

template <typename T>
void OptimalBinaryTree<T>::CreateEmptyMatrix(vector<vector<tuple<int, double, double>>> &matrix, const int size)
{
    for (int i = 0; i <= size; ++i)
    {
        matrix.push_back(vector<tuple<T, double, double>>());
        for (int j = 0; j <= size; ++j)
        {
            matrix[i].push_back(make_tuple(0, 0.0, 0.0));
        }
    }
}

template <typename T>
void OptimalBinaryTree<T>::MainDiagonal(vector<vector<tuple<int, double, double>>> &matrix, const vector<double> &qValues, const int size)
{
    int x = 0, y = 0;
    for (int i = 0; i <= size; ++i)
    {
        matrix[y][x] = make_tuple(i, qValues[i], 0.0);
        x++;
        y++;
    }
}

template <typename T>
void OptimalBinaryTree<T>::FillMatrix(vector<vector<tuple<int, double, double>>> &matrix, const vector<double> pValues, const vector<double> qValues, const int size)
{
    int j, minKey;
    for (int len = 1; len <= size; ++len)
    {
        for (int i = 0; i <= size - len; ++i)
        {
            j = i + len;
            diagonal(matrix, pValues, qValues, i, j, minKey);
        }
    }
}
template <typename T>
void OptimalBinaryTree<T>::diagonal(vector<vector<tuple<int, double, double>>> &matrix, const vector<double> pValues, const vector<double> qValues, int i, int j, int minKey)
{
    double minLengthWay = -1;
    for (int k = i + 1; k <= j; ++k)
    {
        double lengthWay = get<2>(matrix[i][k - 1]) + get<2>(matrix[k][j]) + get<1>(matrix[i][k - 1]) + get<1>(matrix[k][j]);
        if (minLengthWay == -1 || minLengthWay >= lengthWay)
        {
            minLengthWay = lengthWay;
            minKey = k;
        }
    }
    matrix[i][j] = make_tuple(minKey, get<1>(matrix[i][j - 1]) + qValues[j] + pValues[j - 1], minLengthWay);
}
template <typename T>
auto OptimalBinaryTree<T>::Find(const T &value) -> TreeNode *
{
    TreeNode *container = _root;
    if (container == nullptr)
        return container;
    while (container->_key != value)
    {
        if (value < container->_key)
        {
            container = container->_left;
        }
        else if (value > container->_key)
        {
            container = container->_right;
        }
        if (container == nullptr)
            return container;
    }
    return container;
}

template <typename T>
T OptimalBinaryTree<T>::Search(const T &key)
{
    TreeNode *node = Find(key);
    if (node == nullptr)
        return T();
    return node->_key;
}

template <typename T>
auto OptimalBinaryTree<T>::MatrixToTree(vector<vector<tuple<int, double, double>>> matrix, vector<T> keys, TreeNode *tree, set<T> &set, int y, int x) -> TreeNode *
{
    if (y > x)
        return tree;
    if (y + 1 > x)
        tree->_right = MatrixToTree(matrix, keys, tree->_right, set, y + 1, x);
    else if (get<0>(matrix[y + 1][x]) == get<0>(matrix[y][x]))
        tree = MatrixToTree(matrix, keys, tree, set, y + 1, x);
    else if (set.find(get<0>(matrix[y + 1][x])) == set.end() && get<0>(matrix[y + 1][x]) != get<0>(matrix[y][x]))
    {
        TreeNode *node = new TreeNode(keys[get<0>(matrix[y + 1][x]) - 1]);
        set.insert(get<0>(matrix[y + 1][x]));
        tree->_right = MatrixToTree(matrix, keys, node, set, y + 1, x);
        tree->_right->_parent = tree;
    }
    if (y > x - 1)
        tree->_left = MatrixToTree(matrix, keys, tree->_left, set, y, x - 1);
    else if (get<0>(matrix[y][x - 1]) == get<0>(matrix[y][x]))
        tree = MatrixToTree(matrix, keys, tree, set, y, x - 1);
    else if (set.find(get<0>(matrix[y][x - 1])) == set.end() && get<0>(matrix[y][x - 1]) != get<0>(matrix[y][x]))
    {
        TreeNode *node = new TreeNode(keys[get<0>(matrix[y][x - 1]) - 1]);
        set.insert(get<0>(matrix[y][x - 1]));
        tree->_left = MatrixToTree(matrix, keys, node, set, y, x - 1);
        tree->_left->_parent = tree;
    }
    return tree;
}

template <typename T>
OptimalBinaryTree<T>::OptimalBinaryTree(vector<T> keys, vector<double> pValues, vector<double> qValues)
{
    vector<vector<tuple<int, double, double>>> matrix;
    CreateEmptyMatrix(matrix, keys.size());
    MainDiagonal(matrix, qValues, keys.size());
    FillMatrix(matrix, pValues, qValues, keys.size());

    set<T> set = {get<0>(matrix[0][matrix.size() - 1])};
    _root = new TreeNode(keys[get<0>(matrix[0][matrix.size() - 1]) - 1]);
    _root = MatrixToTree(matrix, keys, _root, set, 0, matrix.size() - 1);
}

template <typename T>
T OptimalBinaryTree<T>::MaxElem() const
{
    TreeNode *maxContainer = _root;
    while (maxContainer->_right != nullptr)
    {
        maxContainer = maxContainer->_right;
    }
    return maxContainer->_key;
}

template <typename T>
T OptimalBinaryTree<T>::MinElem() const
{
    TreeNode *minContainer = _root;
    while (minContainer->_left != nullptr)
    {
        minContainer = minContainer->_left;
    }
    return minContainer->_key;
}

template <typename T>
vector<T> OptimalBinaryTree<T>::RoundLrootR()
{
    T maxValue = MaxElem();
    T minValue = MinElem();
    vector<T> LRR = {minValue};
    TreeNode *leftRoot = Find(minValue);
    T value = *(--LRR.end());
    while (value != maxValue)
    {
        if (leftRoot->_left != nullptr && value < leftRoot->_left->_key)
        {
            leftRoot = leftRoot->_left;
            if (leftRoot->_left != nullptr)
                continue;
            LRR.push_back(leftRoot->_key);
        }
        else if (leftRoot->_right != nullptr && value < leftRoot->_right->_key)
        {
            leftRoot = leftRoot->_right;
            if (leftRoot->_left != nullptr)
                continue;
            LRR.push_back(leftRoot->_key);
        }
        else
        {
            leftRoot = leftRoot->_parent;
            if (leftRoot->_key > value)
                LRR.push_back(leftRoot->_key);
        }
        value = *(--LRR.end());
    }
    return LRR;
}

template <typename T>
vector<T> OptimalBinaryTree<T>::RoundRrootL()
{
    T maxValue = MaxElem();
    T minValue = MinElem();
    vector<T> RRL = {maxValue};
    TreeNode *rightRoot = Find(maxValue);
    T value = *(--RRL.end());
    while (value != minValue)
    {
        if (rightRoot->_right != nullptr && value > rightRoot->_right->_key)
        {
            rightRoot = rightRoot->_right;
            if (rightRoot->_right != nullptr)
                continue;
            RRL.push_back(rightRoot->_key);
        }
        else if (rightRoot->_left != nullptr && value > rightRoot->_left->_key)
        {
            rightRoot = rightRoot->_left;
            if (rightRoot->_right != nullptr)
                continue;
            RRL.push_back(rightRoot->_key);
        }
        else
        {
            rightRoot = rightRoot->_parent;
            if (rightRoot->_key < value)
                RRL.push_back(rightRoot->_key);
        }
        value = *(--RRL.end());
    }
    return RRL;
}

template <typename T>
void OptimalBinaryTree<T>::PrintBinaryTree(TreeNode *container, int level)
{
    if (container)
    {
        PrintBinaryTree(container->_left, level + 1);
        for (int i = 0; i < level; ++i)
        {
            cout << "   ";
        }
        cout << container->_key << endl;
        PrintBinaryTree(container->_right, level + 1);
    }
}

template <typename T>
void OptimalBinaryTree<T>::Output()
{
    PrintBinaryTree(_root, 0);
}

template <typename T>
void OptimalBinaryTree<T>::DeleteTree(TreeNode *tree)
{
    if (tree != nullptr)
    {
        DeleteTree(tree->_right);
        DeleteTree(tree->_left);
        tree->_left = nullptr;
        tree->_right = nullptr;
        tree->_parent = nullptr;
        delete tree;
    }
}

template <typename T>
OptimalBinaryTree<T>::~OptimalBinaryTree<T>()
{
    DeleteTree(_root);
    _root = nullptr;
}
