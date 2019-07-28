

#ifndef DULINKLIST_H
#define DULINKLIST_H

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

DuLNode * Buynode(DuLNode *pr = NULL, DuLNode *nt = NULL);

void Freenode(DuLNode *p);

void InitDuList(DuList &Lt);

void DestroyDuList(DuList &Lt);

void Insert_Item_Prev(DuList &Lt, DuLNode *ptr, ElemType x);

void Insert(DuList &Lt, int size, ElemType x);

void Insert_Array(DuList &Lt, ElemType *first, ElemType *last);

DuLNode *FindPos(DuList &Lt, int pos);

DuLNode *FindValue(DuList &Lt, ElemType x);

void EarseDulist(DuList &Lt, DuLNode*ptr);

bool EmptyDulist(DuList&Lt);

void ReverseDulist(DuList &Lt);

#endif
