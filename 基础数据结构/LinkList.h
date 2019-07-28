// SeqList List // DuList //
// SeqStack
// LinkStack
// SeqQueue
// LinkQueue
// PrQueue

#ifndef LINKLIST_H
#define LINKLIST_H

typedef int ElemType;
typedef struct ListNode
{
	ElemType data;
	ListNode *next;
}ListNode;
typedef struct
{
	ListNode *head;
	int size;
}List;

void LinkList_Swap(ElemType &a, ElemType &b);

ListNode * Buynode();

void Freenode(ListNode *p);

void InitList(List &Lt);

bool Insert_Item(List &Lt, ListNode *ptr, ElemType val);

bool InsertList(List &Lt, int pos, ElemType val);

void Push_Front(List &Lt, ElemType val);

void Push_Back(List &Lt, ElemType val);

ListNode * FindValue(List &Lt, ElemType val);

ListNode * FindValue_Prev(List &Lt, ElemType val);

void EraseNext(List &Lt, ListNode *ptr);

void EraseList(List &Lt, int pos);

void Remove(List &Lt, ElemType val);

void Pop_front(List &Lt);

void Pop_back(List &Lt);

int GetSize(List &Lt);

bool Is_Empty(List &Lt);

void ClearList(List &Lt);

void DestroyList(List &Lt);

bool  GetItem(List &Lt, int pos, ElemType &x);

ElemType GetFront(List &Lt);

ElemType GetBack(List &Lt);

void ReverseList(List &lt);


#endif
