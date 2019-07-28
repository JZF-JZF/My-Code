
#include"AfxStd.h"
#include"LinkQueue.h"


typedef int QElemType;
typedef struct QueueNode
{
	QElemType data;
	QueueNode *next;
}QueueNode;
typedef struct
{
	QueueNode *front;
	QueueNode *rear;
	int cursize;
}LinkQueue;

QueueNode * Buynode()
{
	QueueNode * s = (QueueNode*)malloc(sizeof(QueueNode));
	if (NULL == s) exit(1);
	memset(s, 0, sizeof(QueueNode));
	return s;
}
void Freenode(QueueNode *p)
{
	free(p);
}
void InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = Buynode();                      
	Q.cursize = 0;
}
void DestroyQueue(LinkQueue &Q)
{
	ClearQueue(Q);
	Freenode(Q.front);
	Q.front = Q.rear = NULL;
}
void ClearQueue(LinkQueue &Q)
{
	if (Q.front->next != NULL)
	{
		QueueNode *q = Q.front->next;
		Q.front->next = q->next;
		Freenode(q);
	}
	Q.rear = Q.front;
	Q.cursize = 0;
}
int QueueLength(LinkQueue &Q)
{
	return Q.cursize;
}
bool QueueEmpty(LinkQueue &Q)
{
	return QueueLength(Q) == 0;
}

bool GetFront(LinkQueue &Q, QElemType &e)
{
	if (QueueEmpty(Q))
	{
		return false;
	}
	e = Q.front->next->data;
	return true;
}
bool GetRear(LinkQueue &Q, QElemType &e)
{
	if (QueueEmpty(Q))
	{
		return false;
	}
	e = Q.rear->data;
	return true;
}

void EnQueue(LinkQueue &Q, QElemType x)
{
	QueueNode *s = Buynode();
	s->data = x;
	s->next = Q.rear->next;
	Q.rear->next = s;
	Q.rear = s;
	Q.cursize += 1;
}
bool DeQueue(LinkQueue &Q, QElemType &e)
{
	if (QueueEmpty(Q))
	{
		return false;
	}
	QueueNode *q = Q.front->next; // 
	e = q->data;
	Q.front->next = q->next;
	Freenode(q);
	Q.cursize -= 1;
	if (Q.front->next == NULL) // if(Q.cursize == 0)
	{
		Q.rear = Q.front;
	}
	return true;
}
