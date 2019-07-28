3#include"AfxStd.h"
#include"SeqQueue.h"



void InitQueue(SeqQueue &Q)
{
	Q.data = (QElemType*)malloc(sizeof(QElemType)*QUEUE_INIT_SIZE);
	if (NULL == Q.data)
	{
		exit(1);
	}
	Q.cursize = 0;
	Q.front = 0;
	Q.rear = 0;
	Q.maxsize = QUEUE_INIT_SIZE;
}
void DestroyQueue(SeqQueue &Q)
{
	ClearQueue(Q);
	free(Q.data);
	Q.data = NULL;
	Q.maxsize = 0;
}
void ClearQueue(SeqQueue &Q)
{
	Q.cursize = 0;
	Q.front = 0;
	Q.rear = 0;
}
int QueueLength(SeqQueue &Q)
{
	return Q.cursize;
}
bool QueueEmpty(SeqQueue &Q)
{
	return QueueLength(Q) == 0;
}

bool QueueFull(SeqQueue &Q)
{
	return QueueLength(Q) == Q.maxsize;
}
bool GetRear(SeqQueue &Q, QElemType &e)
{
	if (QueueEmpty(Q))
	{
		return false;
	}
	e = Q.data[(Q.rear + Q.maxsize - 1) % Q.maxsize];
	return true;
}
bool GetFront(SeqQueue &Q, QElemType &e)
{
	if (QueueEmpty(Q))
	{
		return false;
	}
	e = Q.data[Q.front];
	return true;
}

bool Inc_Queue(SeqQueue &Q)
{
	QElemType *newdata = (QElemType *)malloc(sizeof(QElemType)*Q.maxsize * QUEUE_INC_SIZE);
	if (NULL == newdata)
	{
		return false;
	}
	int j = Q.front;
	for (int i = 0; i < Q.cursize; ++i)
	{
		newdata[i] = Q.data[j];
		j = (j + 1) % Q.maxsize;
	}
	free(Q.data);
	Q.data = newdata;//
	Q.front = 0;
	Q.rear = Q.maxsize;
	Q.maxsize = Q.maxsize * QUEUE_INC_SIZE;
	return true;
}
bool EnQueue(SeqQueue &Q, QElemType x)
{
	if (QueueFull(Q) && !Inc_Queue(Q))
	{
		return false;
	}
	Q.data[Q.rear] = x;
	Q.rear = (Q.rear + 1) % Q.maxsize;
	Q.cursize += 1;
	return true;
}
bool DeQueue(SeqQueue &Q, QElemType &e)
{
	if (QueueEmpty(Q))
	{
		return false;
	}
	e = Q.data[Q.front];
	Q.front = (Q.front + 1) % Q.maxsize;
	Q.cursize -= 1;
	return true;
}

bool Inc_Queue2(SeqQueue &Q)
{
	QElemType *newdata = (QElemType *)malloc(sizeof(QElemType)*Q.maxsize * QUEUE_INC_SIZE);
	if (NULL == newdata)
	{
		return false;
	}
	QElemType x;
	int i = 0;
	while (DeQueue(Q, x))
	{
		newdata[i++] = x;
	}
	free(Q.data);
	Q.data = newdata;     
	Q.front = 0;
	Q.rear = Q.maxsize;
	Q.cursize = Q.maxsize;
	Q.maxsize = Q.maxsize * QUEUE_INC_SIZE;
	return true;
}