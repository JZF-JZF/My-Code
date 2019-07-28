#ifndef LISTSTACK_H
#define LISTSTACK_H

typedef int ElemType;
typedef struct StackNode
{
	ElemType data;
	StackNode *next;
}StackNode;

typedef struct
{
	StackNode *top;
	int size;
}LinkStack;

StackNode * Buynode();

void Freenode(StackNode *p);

void InitStack(LinkStack &s);

void DestroyStack(LinkStack &s);

void ClearStack(LinkStack &s);

int GetSize(LinkStack &s);

bool EmptyStack(LinkStack &s);

void Push(LinkStack &s, ElemType val);

bool GetTop(LinkStack &s, ElemType &e);

bool Pop(LinkStack &s, ElemType &e);

#endif

