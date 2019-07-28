#include"stdafx.h"


//AVL的缺点： 旋转次数多 最差的时候要旋转hight次  log n  适合查询 不适合插入删除

template<typename T>
class AVL
{
public:
	AVL() { _root = nullptr; }

	// 递归实现AVL树的插入操作  BST + 平衡
	void insert(const T &val)
	{
		_root = insert(_root, val);
	}

	// 递归实现AVL树的删除操作  BST + 平衡
	void remove(const T &val)
	{
		_root = remove(_root, val);
	}

	// 判断一棵 二叉树 是否是 平衡二叉搜索树，是返回true，否则返回false
	bool isAVLTree()
	{
		return isAVLTree(_root);
	}

	//判断一棵 二叉搜索树 是否是 平衡树
	bool isAVL()
	{
		return isAVL(_root);
	}

	//树的高度
	int level()
	{
		return level(_root);
	}

private:
	struct AVLNode
	{
		AVLNode(T data = T())
			:_data(data)
			, _left(nullptr)
			, _right(nullptr)
			, _height(1)
		{}
		T _data;
		AVLNode *_left;
		AVLNode *_right;
		int _height; // 存储的就是节点的高度
	};
	// 以node为起始节点，插入值为val的节点
	AVLNode* insert(AVLNode *node, const T& val)
	{
		if (node == nullptr)
		{
			return new AVLNode(val);
		}

		if (node->_data > val)
		{
			node->_left = insert(node->_left, val);
			// AVL添加的节点失衡判断
			if (height(node->_left) - height(node->_right) > 1)
			{
				if (height(node->_left->_left) >= height(node->_left->_right))
				{
					// 左孩子的左子树太高
					node = rightRotate(node);
				}
				else
				{
					// 左孩子的右子树太高
					node = leftBalance(node);
				}
			}
		}
		else if (node->_data < val)
		{
			node->_right = insert(node->_right, val);
			// AVL添加的节点失衡判断
			if (height(node->_right) - height(node->_left) > 1)
			{
				if (height(node->_right->_right) >= height(node->_right->_left))
				{
					// 右孩子的右子树太高
					node = leftRotate(node);
				}
				else
				{
					// 右孩子的左子树太高
					node = rightBalance(node);
				}
			}
		}
		else
		{
			;
		}

		// 在递归回溯过程中，更新节点的高度值
		node->_height = maxHeight(node->_left, node->_right) + 1;
		return node;
	}

	// 以node为起始节点，删除值为val的节点
	AVLNode* remove(AVLNode *node, const T &val)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		if (node->_data > val)
		{
			node->_left = remove(node->_left, val);
			if (height(node->_right) - height(node->_left) > 1)
			{
				if (height(node->_right->_right) >= height(node->_right->_left))
				{
					// 右孩子的右子树太高
					node = leftRotate(node);
				}
				else
				{
					// 右孩子的左子树太高
					node = rightBalance(node);
				}
			}
		}
		else if (node->_data < val)
		{
			node->_right = remove(node->_right, val);
			if (height(node->_left) - height(node->_right) > 1)
			{
				if (height(node->_left->_left) >= height(node->_left->_right))
				{
					// 左孩子的左子树太高
					node = rightRotate(node);
				}
				else
				{
					// 左孩子的右子树太高
					node = leftBalance(node);
				}
			}
		}
		else
		{
			if (node->_left != nullptr && node->_right != nullptr)
			{
				if (height(node->_left) >= height(node->_right))
				{
					// 前驱替换
					AVLNode *pre = node->_left;
					while (pre->_right != nullptr)
					{
						pre = pre->_right;
					}
					node->_data = pre->_data;
					node->_left = remove(node->_left, pre->_data);
				}
				else
				{
					// 后继替换
					AVLNode *post = node->_right;
					while (post->_left != nullptr)
					{
						post = post->_left;
					}
					node->_data = post->_data;
					node->_right = remove(node->_right, post->_data);
				}
			}
			else
			{
				if (node->_left != nullptr)
				{
					AVLNode *left = node->_left;
					delete node;
					return left;
				}
				else if (node->_right != nullptr)
				{
					AVLNode *right = node->_right;
					delete node;
					return right;
				}
				else
				{
					return nullptr;
				}
			}
		}

		// 在递归回溯过程中，更新节点的高度值
		node->_height = maxHeight(node->_left, node->_right) + 1;
		return node;
	}

	// 返回节点的高度
	int height(AVLNode *node)const
	{
		return node == nullptr ? 0 : node->_height;
	}

	// 返回结点左右子树最高的层数
	int maxHeight(AVLNode *node1, AVLNode *node2)
	{
		return height(node1) > height(node2) ? height(node1) : height(node2);
	}

	// 左旋转操作 以node为根节点进行左旋转，返回旋转后的根节点
	AVLNode* leftRotate(AVLNode* node)
	{
		AVLNode* child = node->_right;// 得到旋转后的根节点
		node->_right = child->_left;// 该根节点的左子树则变成其原父节点的右子树
		child->_left = node;// 该根节点的原父节点变成该节点的左子树
		node->_height = maxHeight(node->_left, node->_right) + 1; // 更新节点高度
		child->_height = maxHeight(child->_left, child->_right) + 1; // 更新节点高度
		return child; //返回旋转后的根节点
	}

	// 右旋转操作  以node为根节点进行右旋转，返回旋转后的根节点
	AVLNode* rightRotate(AVLNode* node)
	{
		AVLNode* child = node->_left; // 拿到中间节点
		node->_left = child->_right; //该中间节点的右子树则变成其原父节点的左子树
		child->_right = node;// 该中间节点的原父节点变成该节点的右子节点
		node->_height = maxHeight(node->_left, node->_right) + 1; // 更新节点高度
		child->_height = maxHeight(child->_left, child->_right) + 1;// 更新节点高度
		return child;//返回旋转后的根节点
	}

	//  左-右旋转
	AVLNode* leftBalance(AVLNode *node)
	{
		node->_left = leftRotate(node->_left);
		return rightRotate(node);
	}

	//  右-左旋转
	AVLNode* rightBalance(AVLNode *node)
	{
		node->_right = rightRotate(node->_right);
		return leftRotate(node);
	}

	//判断一颗  二叉树  是否是  平衡二叉搜索树
	bool isAVLTree(AVLNode* node)
	{
	/*
	* 判断一颗  二叉树  是否是  平衡二叉搜索树  ，我们之前有写过判断一颗二叉树是否是
	* 二叉搜索树(BST)的代码，我们在递归函数前进行很多的条件判断，那么我们
	* 只需要在这部分继续添加条件，判断是否是平衡树即可。判断方式和上题是
	* 相同的。
	*/
		static AVLNode* prev = nullptr;
		if (node == nullptr)
		{
			return true;
		}

		if (!isAVLTree(node->_left))
		{
			return false;
		}

		if (prev != nullptr && node->_data < prev->_data)
		{
			return false;
		}

		if (abs(level(node->_left) - level(node->_right)) > 1)
		{
			return false;
		}

		prev = node;
		return isAVLTree(node->_right);
	}

	//判断一棵  二叉搜索树  是否是  平衡树
	bool isAVL(AVLNode *node)
	{
	/*
	* 判断一棵  二叉搜索树  是否是  平衡树  ，因为题目条件已经说明了该树是一棵二叉搜索树
	* 了，因此我们直接从二叉搜索树与平衡二叉搜索树在性质上的重要区别入手，即一颗
	* 平衡二叉搜索树任一结点的左右子树高度差不超过1，因此我们借助了求层数的函数
	* level(),在函数递归前判断是否满足该条件即可，若不满足，我们直接结束，若满足
	* 继续递归遍历其他结点即可。
	*/
		if (node == nullptr)
		{
			return true;
		}

		if (abs(level(node->_left) - level(node->_right)) > 1)
		{
			return false;
		}
		return isAVL(node->_left) && isAVL(node->_right);
	}

	//树的高度
	int level(AVLNode* node)
	{
		if (node == nullptr)
		{
			return 0;
		}

		int left = level(node->_left);
		int right = level(node->_right);

		return (left > right ? left : right) + 1;
	}

	AVLNode *_root;
};

int main()
{
	AVL<int>avl;
	for (int i = 0; i < 10; ++i)
	{
		avl.insert(i);
	}
	cout << avl.isAVL() << endl;
	cout << avl.isAVLTree() << endl;
	cout << avl.level() << endl;
	avl.remove(8);
	return 0;
}

