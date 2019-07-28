

#ifndef SEQQUEUE_H
#define SEQQUEUE_H
#define QUEUE_INIT_SIZE 8
#define QUEUE_INC_SIZE 2

typedef int QElemType;
typedef struct
{
	QElemType *data;
	int front;
	int rear;
	int cursize;
	int maxsize;
}SeqQueue;

void InitQueue(SeqQueue &Q);
void DestroyQueue(SeqQueue &Q);
void ClearQueue(SeqQueue &Q);
bool QueueEmpty(SeqQueue &Q);
bool QueueFull(SeqQueue &Q);
int QueueLength(SeqQueue &Q);
bool GetFront(SeqQueue &Q, QElemType &e);
bool GetRear(SeqQueue &Q, QElemType &e);
bool EnQueue(SeqQueue &Q, QElemType x);
bool DeQueue(SeqQueue &Q, QElemType &e);


#endif

