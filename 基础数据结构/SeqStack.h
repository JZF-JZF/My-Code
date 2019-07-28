#ifndef SEQSTACK_H
#define SEQSTACK_H
#define STACK_INIT_SIZE 10
#define STACK_INC_SIZE 2
typedef int ElemType;
typedef struct
{
	ElemType *data;
	int maxsize;
	int top;
}SeqStack;

bool InitStack(SeqStack &s);

void DestroyStack(SeqStack &s);

void ClearStack(SeqStack &s);

int GetSize(SeqStack &s);

bool EmptyStack(SeqStack &s);

bool FullStack(SeqStack &s);

bool Inc_Size(SeqStack &s);

bool Push(SeqStack &s, ElemType val);

bool GetTop(SeqStack &s, ElemType &e);

bool Pop(SeqStack &s, ElemType &e);


#endif
