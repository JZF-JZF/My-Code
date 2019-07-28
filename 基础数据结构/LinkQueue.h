

#ifndef LINKQUEUE_H
#define LINKQUEUE_H
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

QueueNode * Buynode();
void Freenode(QueueNode *p);
void InitQueue(LinkQueue &Q);
void DestroyQueue(LinkQueue &Q);
void ClearQueue(LinkQueue &Q);
bool QueueEmpty(LinkQueue &Q);
int QueueLength(LinkQueue &Q);
bool GetFront(LinkQueue &Q, QElemType &e);
bool GetRear(LinkQueue &Q, QElemType &e);
void EnQueue(LinkQueue &Q, QElemType x);
bool DeQueue(LinkQueue &Q, QElemType &e);

#endif