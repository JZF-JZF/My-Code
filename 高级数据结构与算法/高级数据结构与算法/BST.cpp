// 高级数据结构与算法.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#if 0
// BST树的实现
template<typename T>
class BSTree
{
public:
	BSTree() :_root(nullptr) {}

	//非递归实现BST树的插入操作
	void noninsert(const T &val)
	{
		if (_root == nullptr)
		{
			_root = new BSTNode(val);
			return;
		}
		BSTNode *pre = nullptr;
		BSTNode *tmp = _root;
		while (tmp != nullptr)
		{
			pre = tmp;
			if (tmp->_data == val)
			{
				return;
			}
			else if (val < tmp->_data)
			{
				tmp = tmp->_left;
			}
			else 
			{
				tmp = tmp->_right;
			}
		}
		if (val < pre->_data)
		{
			pre->_left = new BSTNode(val);
		}
		else
		{
			pre->_right = new BSTNode(val);
		}
	}

	//递归实现BST树的插入操作
	void insert(const T&val)
	{
		_root = insert(_root, val);
	}

	//树的镜像翻转
	void mirror()
	{
		cout << "镜像翻转：";
		mirror(_root);
	}

	//非递归实现BST树的删除操作
	void nonmove(const T& val)
	{
		if (_root == nullptr)
		{
			return;
		}
		BSTNode*pre = nullptr;
		BSTNode*tmp = _root;
		while (tmp != nullptr)
		{
			if (val < tmp->_data)
			{
				pre = tmp;
				tmp = tmp->_left;
			}
			else if(val > tmp->_data)
			{
				pre = tmp;
				tmp = tmp->_right;
			}
			else
			{
				break;
			}
		}
		if (tmp == nullptr)
			return;
		//左右孩子都存在
		if (tmp->_left != nullptr&&tmp->_right != nullptr)
		{
			BSTNode*old = tmp;
			pre = tmp;
			while (tmp->_right != nullptr)
			{
				pre = tmp;
				tmp=tmp->_right;
			}
			old->_data = tmp->_data;
		}
		//只存在左孩子或者右孩子的情况
		//判断孩子是左孩子还是右孩子
		BSTNode*child = tmp->_left;
		if (child == nullptr)
		{
			child = tmp->_right;
		}
		//删除的是根结点
		if (pre == nullptr)	//父结点为空时则是删除根结点
		{
			_root = child;
		}
		else
		{
			//要把删除结点的孩子赋给tmp父结点相应的地址域里边
			if (tmp == pre->_left)	//如果要删除的结点是前驱结点的左孩子 则把要删除的结点的孩子置为前驱结点的左孩子
			{
				pre->_left = child;
			}
			else		//否则要删除的结点是前驱结点的右孩子
			{
				pre->_right = child;
			}
		}
		delete tmp;
	}

	//递归实现BST树的节点个数  返回树的节点的个数
	int numble()	
	{
		return numble(_root);
	}

	//递归实现BST树的高度  返回树的高度
	int leavl()		
	{
		return leavl(_root);
	}

	//实现BST树查找指定的元素值val是否存在
	bool nonquery(const T &val)	
	{
		if (_root == nullptr)
		{
			return false;
		}
		BSTNode*ptmp = _root;
		while (ptmp != nullptr&&ptmp->_data != val)
		{
			if (val < ptmp->_data)
			{
				ptmp = ptmp->_left;
			}
			if (val > ptmp->_data)
			{
				ptmp = ptmp->_right;
			}
		}
		if (ptmp == nullptr)
		{
			return false;
		}
		return true;
	}

	//递归实现树的前序遍历
	void Pre_out()
	{
		cout << "递归实现前序遍历:";
		Pre_out(_root);
		cout << endl;
	}

	//递归实现树的中序遍历
	void Mid_out()
	{
		cout << "递归实现中序遍历:";
		Mid_out(_root);
		cout << endl;
	}

	//递归实现树的后序遍历
	void Last_out()
	{
		cout << "递归实现后序遍历:";
		Last_out(_root);
		cout << endl;
	}

	//递归实现层序遍历
	void leavlOrder()
	{
		cout << "递归实现层序遍历:";
		int l = leavl(_root);
		for(int i = 0; i < l; ++i)
		{
			leavlOrder(_root, i);
		}
		cout << endl;
	}

	//非递归实现前序遍历
	void NonPre_Post()
	{
		cout << "非递归实现前序遍历:";
		if (_root == nullptr)
		{
			return;
		}
		stack<BSTNode*>s;
		s.push(_root);
		while(!s.empty())
		{
			BSTNode*top = s.top();
			s.pop();
			cout << top->_data << " ";
			if (top->_right != nullptr)
			{
				s.push(top->_right);
			}
			if (top->_left != nullptr)
			{
				s.push(top->_left);
			}
		}
		cout << endl;
	}

	//非递归实现中序遍历
	void NonMid_Post()
	{
		cout << "非递归实现中序遍历:";
		if (_root == nullptr)
		{
			return;
		}
		stack<BSTNode*>s;
		BSTNode*cur = _root;
		while (!s.empty() || cur != nullptr)
		{
			if (cur != nullptr)
			{
				s.push(cur);
				cur = cur->_left;
			}
			else
			{
				BSTNode*top = s.top();
				s.pop();
				cout << top->_data << " ";

				cur = top->_right;
			}
		}
		cout << endl;
	}

	//非递归实现后序遍历
	void NonLast_Post()
	{
		cout << "非递归实现后序遍历:";
		if (_root == nullptr)
		{
			return;
		}
		stack<BSTNode*>sa;
		stack<BSTNode*>sb;
		sa.push(_root);
		while (!sa.empty())
		{
			BSTNode* top = sa.top();
			sa.pop();
			sb.push(top);
			if (top->_left != nullptr)
			{
				sa.push(top->_left);
			}
			if (top->_right != nullptr)
			{
				sa.push(top->_right);
			}
		}
		while (!sb.empty())
		{
			cout << sb.top()->_data << " ";
			sb.pop();
		}
		cout << endl;
	}

	//非递归实现层序打印(从根节点开始，一层一层按从左向右的顺序打印BST树节点的值)
	void NonLevelOrder()
	{
		cout << "非递归实现层序遍历:";
		// 1.如果_root为空，直接返回
		if (_root == nullptr)
			return;
		// 2._root -> queue
		queue<BSTNode*> que;
		que.push(_root);

		// 3.循环判断队列是否为空， 不为空取出队头元素，分别判断左右孩子是否为nullptr，不为空
		// 就要依次入队，然后打印队头元素，继续判断下一个队头元素
		while (!que.empty())
		{
			BSTNode *front = que.front();
			cout << front->_data << " ";
			que.pop();
			if (front->_left != nullptr)
			{
				que.push(front->_left);
			}
			if (front->_right != nullptr)
			{
				que.push(front->_right);
			}
		}
		cout << endl;
	}

	//判断当前二叉树是不是BST树
	bool isBSTtree()
	{
		BSTNode *pre = nullptr;
		return isBSTree(_root, pre);
	}

	// 在当前BST树中，把满足区间[first, last]的所有元素找出来并打印
	void findAreaData(int first, int last)
	{
		vector<int>vec;
		findAreaData(_root, first, last, vec);
		for (int v : vec)
		{
			cout << v << " ";
		}
		cout << endl;
	}

	// 获取两个节点的最近公共祖先节点
	int getLCA(int val1, int val2)
	{
		return getLCA(_root, val1, val2);
	}

	// 获取中序遍历倒数第k个节点的值
	int getLastKValue(int k) // LVR    RVL
	{
		int i = 0;
		BSTNode *p = getLastKValue(_root, k, i);
		if (p != nullptr)
		{
			return p->_data;
		}
		else
		{
			throw "no last k value, k is invalid!";
		}
	}

	// 判断参数tree是否是当前BST树的一颗子树，是返回true，否则返回false
	bool isChildTree(const BSTree<T> &tree)
	{
		bool isChildTree(const BSTree<T> &tree)
		{
			if (_root == nullptr)
				return false;
			BSTNode *cur = _root;
			while (cur != nullptr)
			{
				if (tree._root->_data > cur->_data)
				{
					cur = cur->_right;
				}
				else if (tree._root->_data < cur->_data)
				{
					cur = cur->_left;
				}
				else
				{
					break;
				}
			}
			if (cur == nullptr)
				return false;

			return isChildTree(cur, tree._root);
		}
	}

	// 已知一颗BST树的前序遍历结果pre数组，和中序遍历结果in数组，重建二叉树
	void rebuildBSTree(int pre[], int len1, int in[], int len2)
	{
		this->_root = rebuildBSTree(pre, 0, len1 - 1, in, 0, len2 - 1);
	}

	//递归实现查找val的值，找到返回true，否则返回false。
	bool query(const T val)
	{
		return query(_root, val);
	}

	//删除一个值为value的结点
	void remove(const T val)
	{
		remove(_root, val);
	}
private:

	// 定义BST树节点的类型
	struct BSTNode
	{
		BSTNode(T data = T())
			:_data(data)
			, _left(nullptr)
			, _right(nullptr)
		{}
		T _data;
		BSTNode *_left;
		BSTNode *_right;
	};

	BSTNode *_root; // 指向树的根节点

	//返回以node为根节点的子树的节点的个数
	int numble(BSTNode *node)	
	{
		if (node == nullptr)
		{
			return 0;
		}
		return 1 + numble(node->_left) + numble(node->_right);
	}

	//返回以node为根节点的子树的高度
	int leavl(BSTNode *node)	
	{
		if (node == nullptr)
		{
			return 0;
		}
		int h = leavl(node->_left) >= leavl(node->_right) ? leavl(node->_left) : leavl(node->_right);
		return h + 1;
	}

	//递归前序遍历
	void Pre_out(BSTNode *node)	
	{
		if (node != nullptr)
		{
			cout << node->_data << " ";
			Pre_out(node->_left);
			Pre_out(node->_right);
		}
	}

	//递归中序遍历
	void Mid_out(BSTNode *node)	
	{
		if (node != nullptr)
		{
			Mid_out(node->_left);
			cout << node->_data << " ";
			Mid_out(node->_right);
		}
	}

	//递归后序遍历
	void Last_out(BSTNode *node)	
	{
		if (node != nullptr)
		{
			Last_out(node->_left);
			Last_out(node->_right);
			cout << node->_data << " ";
		}
	}

	//递归实现层序遍历
	void leavlOrder(BSTNode *node, int l)
	{
		if (node != nullptr)
		{
			if(l==0)
			{ 
				cout << node->_data << " ";
				return;
			}
			leavlOrder(node->_left, l - 1);
			leavlOrder(node->_right, l - 1);
		}
	}

	//树的镜像翻转
	void mirror(BSTNode *node)
	{
		if (node == nullptr)
			return;

		BSTNode *ptmp = node->_left;
		node->_left = node->_right;
		node->_right = ptmp;

		mirror(node->_left);
		mirror(node->_right);
	}

	//判断一个二叉树是不是BST树
	bool isBSTree(BSTNode *node,BSTNode *&pre)	//必须是引用 
	{
		if (node == nullptr)
		{
			return true;
		}

		if (!isBSTree(node->_left, pre))
		{
			return false;
		}

		if (pre != nullptr)
		{
			if (node->_data < pre->_data)
			{
				return false;
			}
		}
		pre = node;
		return isBSTree(node->_right, pre);
	}

	//以node为根节点寻找first到last区间的元素
	void findAreaData(BSTNode *node, int first, int last, vector<int>&vec)
	{
		if (node == nullptr)
		{
			return;
		}

		findAreaData(node->_left, first, last, vec);

		if (node->_data > last)
		{
			return;
		}
		if (node->_data <= last&&node->_data >= first)
		{
			vec.push_back(node->_data);
		}

		findAreaData(node->_right, first, last, vec);
	}

	// 获取两个节点的最近公共祖先节点
	int getLCA(BSTNode*node, int val1, int val2)
	{
		if (node == nullptr)
		{
			throw("error");
		}
		if (node->_data > val1 && node->_data > val2)
		{
			return getLCA(node->_left, val1, val2);
		}
		else if (node->_data < val1 && node->_data < val2)
		{
			return getLCA(node->_right, val1, val2);
		}
		else
		{
			return node->_data;
		}
	}

	// LVR RVL 以node为根节点，找反向中序遍历的第K个节点
	BSTNode* getLastKValue(BSTNode *node, int k, int &i)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		BSTNode *p1 = getLastKValue(node->_right, k, i); // R
		if (p1 != nullptr)
		{
			return p1;
		}

		i++;
		if (k == i)
		{
			return node; // V
		}

		return getLastKValue(node->_left, k, i); // L
	}

	// 判断是否是当前树的子树，从father节点开始判断，是否全包含child的节点
	bool isChildTree(BSTNode *father, BSTNode *child)
	{
		if (father == nullptr && child == nullptr)
		{
			return true;
		}

		if (father == nullptr)
		{
			return false;
		}

		if (child == nullptr)
		{
			return true;
		}

		if (father->_data != child->_data)
		{
			return false;
		}

		return isChildTree(father->_left, child->_left)
			&& isChildTree(father->_right, child->_right);
	}

	//重建整个树
	BSTNode* rebuildBSTree(int pre[], int i, int j, int in[], int m, int n)
	{
		if (i > j || m > n)
		{
			return nullptr;
		}

		BSTNode *root = new BSTNode(pre[i]);
		for (int k = m; k <= n; ++k)
		{
			if (pre[i] == in[k]) // 中序遍历种找到根节点了
			{
				root->_left = rebuildBSTree(pre, i + 1, i + (k - m), in, m, k - 1);
				root->_right = rebuildBSTree(pre, i + (k - m) + 1, j, in, k + 1, n);
				break;
			}
		}
		return root;
	}

	//递归实现查找一个数是否是BST树的结点
	bool query(BSTNode*node, const T &val)
	{
		if (node == nullptr)
		{
			return false;
		}
		if (node->_data > val)
		{
			return query(node->_left, val);
		}
		else if (val > node->_data)
		{
			return query(node->_right, val);
		}
		else return true;
	}

	//删除一个值为value的结点
	BSTNode* remove(BSTNode *node, const T &val)
	{
		if (node == nullptr)
			return nullptr;

		if (node->_data > val)
		{
			node->_left = remove(node->_left, val);
		}
		else if (node->_data < val)
		{
			node->_right = remove(node->_right, val);
		}
		else
		{
			if (node->_left != nullptr && node->_right != nullptr)
			{
				BSTNode *pre = node->_left;
				while (pre->_right != nullptr)
				{
					pre = pre->_right;
				}
				node->_data = pre->_data;
				// 直接删除前驱
				node->_left = remove(node->_left, pre->_data);
			}
			else
			{
				if (node->_left != nullptr)
				{
					BSTNode *left = node->_left;
					delete node;
					return left;
				}
				else if (node->_right != nullptr)
				{
					BSTNode *right = node->_right;
					delete node;
					return right;
				}
				else
				{
					delete node;
					return nullptr;
				}
			}
		}
		return node;
	}

};

int main()
{
	//				40

	//		20				65
	//	10		25		45		70

	BSTree<int>bst;
	bst.noninsert(40);
	bst.noninsert(20);
	bst.noninsert(65);
	bst.noninsert(25);
	bst.noninsert(45);
	bst.noninsert(70);
	bst.noninsert(10);
	bst.noninsert(99);

	cout << "删除前:";
	bst.NonLevelOrder();
	cout << endl;

	cout << "删除后:";
	bst.nonmove(99);
	bst.NonLevelOrder();


	cout << "结点数:" << bst.numble() << endl;
	cout << "是否存在70：" << bst.nonquery(70) << endl;
	cout << "高度:" << bst.leavl() << endl;

	bst.Pre_out();
	bst.NonPre_Post();
	cout << endl;

	bst.Mid_out();
	bst.NonMid_Post();
	cout << endl;

	bst.Last_out();
	bst.NonLast_Post();
	cout << endl;

	bst.leavlOrder();
	bst.NonLevelOrder();
	cout << endl;


	if (bst.isBSTtree())
	{
		cout << "是一个BST树" << endl;
	}
	else
	{
		cout << "不是一个BST树" << endl;
	}

	bst.findAreaData(25,66);
	bst.mirror();
	bst.NonLevelOrder();
	bst.mirror();
	bst.NonLevelOrder();

	int LCA = bst.getLCA(25, 45);
	cout << "LCA:" << LCA << endl;
	cout << "是否存在70：" << bst.query(70) << endl;
	
	cout << "倒数第N个数:" << bst.getLastKValue(2) << endl;

	cout << endl;
	cout << "重建二叉树" << endl;
	int pre[] = { 40,20,10,25,60,50,70 }; // VLR
	int in[] = { 10,20,25,40,50,60,70 }; // LVR
	BSTree<int> bst1;
	bst1.rebuildBSTree(pre, sizeof(pre) / sizeof(pre[0]),
		in, sizeof(in) / sizeof(in[0]));
	bst1.Pre_out();
	bst1.Mid_out();
	bst1.remove(40);
	bst1.Pre_out();
	bst1.Mid_out();
	return 0;
}

#endif
