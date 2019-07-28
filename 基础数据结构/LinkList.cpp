
#include"AfxStd.h"
#include"LinkList.h"

void LinkList_Swap(ElemType &a, ElemType &b)
{
	ElemType c = a;
	a = b;
	b = c;
}
ListNode * Buynode()
{
	ListNode *s = (ListNode*)malloc(sizeof(ListNode));
	if (NULL == s) exit(1);
	memset(s, 0, sizeof(ListNode));
	return s;
}
void Freenode(ListNode *p)
{
	free(p);
}
void InitList(List &Lt) // 
{
	Lt.size = 0;
	Lt.head = Buynode();
}

bool Insert_Item(List &Lt, ListNode *ptr, ElemType val)
{
	if (NULL == ptr) return false;
	ListNode *s = Buynode();
	s->next = ptr->next;
	ptr->next = s;
	s->data = val;
	Lt.size += 1;
	return true;
}

bool InsertList(List &Lt, int pos, ElemType val)
{
	if (pos < 1 || pos > Lt.size + 1) return false;
	ListNode *p = Lt.head;
	int i = 1;
	while (i<pos)
	{
		++i;
		p = p->next;
	}
	return Insert_Item(Lt, p, val);
}
void Push_Front(List &Lt, ElemType val)
{
	InsertList(Lt, 1, val);
}
void Push_Back(List &Lt, ElemType val)
{
	InsertList(Lt, Lt.size + 1, val);
}

ListNode * FindValue(List &Lt, ElemType val)
{
	ListNode *p = Lt.head->next;
	while (p != NULL && p->data != val)
	{
		p = p->next;
	}
	return p;
}

ListNode * FindValue_Prev(List &Lt, ElemType val)
{
	ListNode *p = Lt.head;
	while (p->next != NULL && p->next->data != val)
	{
		p = p->next;
	}
	if (p->next == NULL) { p = NULL; }
	return p;
}
void EraseNext(List &Lt, ListNode *ptr)
{
	if (NULL == ptr || NULL == ptr->next)
	{
		return;
	}
	ListNode *q = ptr->next;
	ptr->next = q->next;
	Freenode(q);
	Lt.size -= 1;
}
void EraseList(List &Lt, int pos)
{
	if (pos < 1 || pos > Lt.size) return;
	ListNode *p = Lt.head;
	int i = 1;
	while (i < pos)
	{
		p = p->next;
		++i;
	}
	EraseNext(Lt, p);
}
void Pop_front(List &Lt)
{
	EraseList(Lt, 1);
}
void Pop_back(List &Lt)
{
	EraseList(Lt, Lt.size);
}
void Remove(List &Lt, ElemType val)
{
	ListNode *p = Lt.head;
	while (p->next != NULL)
	{
		if (p->next->data == val)
		{
			ListNode *q = p->next;
			p->next = q->next;
			Freenode(q);
			Lt.size -= 1;
		}
		else
		{
			p = p->next;
		}
	}
}

int GetSize(List &Lt)
{
	return Lt.size;
}
bool Is_Empty(List &Lt)
{
	return GetSize(Lt) == 0;
}

void ClearList(List &Lt)
{
	Lt.size = 0;
	while (Lt.head->next != NULL)
	{
		ListNode *q = Lt.head->next;
		Lt.head->next = q->next;
		Freenode(q);
	}
}
void DestroyList(List &Lt)
{
	ClearList(Lt);
	Freenode(Lt.head);
	Lt.head = NULL;
}
//==============================按位置查找单链表的值并且用x返回==================
bool  GetItem(List &Lt, int pos, ElemType &x)
{
	if (pos < 0 || pos > Lt.size)
	{
		return false;
	}
	int i = 1;
	ListNode *p = Lt.head->next;
	while (i<pos) { p = p->next; ++i; }
	x = p->data;
	return true;

}
//=============================得到队头元素=================================
ElemType GetFront(List &Lt)
{
	ElemType x;
	GetItem(Lt, 1, x);
	return x;
}
//=============================得到队尾元素================================
ElemType GetBack(List &Lt)
{
	ElemType x;
	GetItem(Lt, Lt.size, x);
	return x;
}
//================================单链表的逆置===============================
void ReverseList(List &Lt)
{
	ListNode *p = Lt.head->next;
	Lt.head->next = NULL;
	while (p != NULL)
	{
		ListNode *s = p;
		p = p->next;
		s->next = Lt.head->next;
		Lt.head->next = s;
	}
}
//=================================堆排序======================================
void BubbleSort(List &Lt)
{
	int n = Lt.size;
	for (int i = 1; i<n; ++i)// 
	{
		ListNode *p = Lt.head->next;
		for (int j = 1; j<n - i; ++j)// 
		{
			if (p->data > p->next->data)
			{
				LinkList_Swap(p->data, p->next->data);
			}
			p = p->next;
		}
	}
}
//===================================单链表选择排序=================================
void SelectSort(List &Lt)
{
	ListNode *ptr = Lt.head->next;
	while (ptr->next != NULL)
	{
		ListNode *minp = ptr;
		ListNode *p = ptr;
		while (p != NULL)
		{
			if (p->data < minp->data)
			{
				minp = p;
			}
			p = p->next;
		}
		if (minp != ptr)
		{
			LinkList_Swap(minp->data, ptr->data);
		}
		ptr = ptr->next;
	}
}
//===========================两个链表的合并================================
void  MergeList(List &La, List &Lb, List &Lc)
{
	ListNode *pa = La.head->next; // 
	ListNode *pb = Lb.head->next;// 
	ListNode *pc = Lc.head;
	while (pa != NULL && pb != NULL)
	{
		if (pa->data < pb->data)
		{
			pc->next = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pb = pb->next;
		}
		pc = pc->next;
	}
	if (pa == NULL)
	{
		pc->next = pb;
	}
	if (pb == NULL)
	{
		pc->next = pa;
	}
	Lc.size = La.size + Lb.size;
	La.size = 0;
	Lb.size = 0;
	La.head->next = NULL;
	Lb.head->next = NULL;
}
