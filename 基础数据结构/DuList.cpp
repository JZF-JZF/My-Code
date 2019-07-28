#include"AfxStd.h"
#include"DuLinkList.h"

typedef int ElemType;
typedef struct DuLNode
{
	DuLNode *prev;
	DuLNode *next;
	ElemType data;
}DuLNode;

typedef struct
{
	DuLNode *head;
	int size;
}DuList;

DuLNode * Buynode(DuLNode *pr, DuLNode *nt)   //创建节点
{
	DuLNode *s = (DuLNode*)malloc(sizeof(DuLNode));
	if (NULL == s) exit(1);
	s->prev = (pr == NULL) ? s : pr;
	s->next = (nt == NULL) ? s : nt;
	return s;
}
void Freenode(DuLNode *p)     //释放节点
{
	free(p);
}

void InitDuList(DuList &Lt)   //初始化链表
{
	Lt.size = 0;
	Lt.head = Buynode(Lt.head->next,Lt.head->prev);
}
void DestroyDuList(DuList &Lt)
{
	Lt.head->next = Lt.head->prev;
	Lt.head->prev = Lt.head->next;
	Lt.size = 0;
}
void Insert_Item_Prev(DuList &Lt, DuLNode *ptr, ElemType x)  //向链表某个结点前插入某个值
{
	ptr->prev = Buynode(ptr->prev, ptr);
	ptr = ptr->prev;
	ptr->prev->next = ptr; // 4;
	ptr->data = x;
	Lt.size += 1;
}
void Push_Back(DuList &Lt, ElemType x)    //尾插入某个值
{
	Insert_Item_Prev(Lt, Lt.head, x);
}
void Push_Front(DuList &Lt, ElemType x)   //头插入某个值
{
	Insert_Item_Prev(Lt, Lt.head->next, x);
}
void Insert(DuList &Lt, int size, ElemType x)  //插入特定数量的的某个值
{
	for (int i = 0; i < size; i++)
	{
		Push_Front(Lt, x);
	}
}
void Insert_Array(DuList &Lt, ElemType *first, ElemType *last)   //插入数组
{
	if (NULL == first || NULL == last)
		return;
	for (; first != last; ++first)
	{
		Insert_Item_Prev(Lt, Lt.head, *first);
	}
}
DuLNode *FindValue(DuList &Lt, ElemType x)   //查找值为x的结点 并且返回
{
	if (Lt.head->next = Lt.head->prev)
		return;
	DuLNode *p = Lt.head->next;
	while (p->data != x &&p != Lt.head)
	{
		p = p->next;
	}
	if (p == Lt.head)
	{
		p = NULL;
	}
	return p;
}
DuLNode *FindPos(DuList &Lt, int pos)     //查找pos位置的结点 按位置删除
{
	if (pos<1 || pos>Lt.size) return NULL;
	DuLNode *p = Lt.head->next;
	int i = 1;
	while (i < pos)
	{
		++i;
		p = p->next;
	}
	return p;
}
void EarseDulist(DuList &Lt, DuLNode*ptr)  //按结点删除
{
	assert(NULL == ptr);
	ptr->next->prev = ptr->prev;
	ptr->prev->next = ptr->next;
	Freenode(ptr);
	Lt.size -= 1;
}
bool EmptyDulist(DuList&Lt)    //双链表判空
{
	return Lt.size == 0;
}
void Pop_Front(DuList &Lt)    //头删元素
{
	if (EmptyDulist(Lt)) return;
	EarseDulist(Lt, Lt.head->next);
}
void Pop_Back(DuList &Lt)     //尾删元素
{
	if (EmptyDulist(Lt)) return;
	EarseDulist(Lt, Lt.head->prev);
}
void EarsePos(DuList &Lt, int pos)  //按位置删除
{
	DuLNode *p = FindPos(Lt, pos);

}
void Remove(DuList&Lt, ElemType x) //删除双链表中值为x的所有值；
{
	while (NULL == Lt.head)
	{
		return;
	}
	DuLNode *p = Lt.head->next;
	while (Lt.head != p)
	{
		while (p->data = x)
		{
			DuLNode *q = p;
			EarseDulist(Lt, q);
		}
		p = p->next;
	}
}
void Swap(DuLNode *a, DuLNode *b)   //交换结点
{
	DuLNode*tmp= a;
	a = b;
	b = tmp;
}
void ReverseDulist(DuList &Lt)     //逆置双链表
{
	while (NULL == Lt.head)
	{
		return;
	}
	while (Lt.size > 2)
	{
		DuLNode *p = Lt.head->next;
		while (Lt.head != p)
		{
			DuLNode *s = p;
			p = p->next;
			Swap(p->next,p->prev);
		}
	}
	Swap(Lt.head->next,Lt.head->prev);
}
