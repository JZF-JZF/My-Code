#ifndef SEQLIST_H
#define SEQLIST_H

#define LIST_INIT_SIZE 10
#define LIST_INC_SIZE  2

typedef int SElemType;



typedef enum {
	OK = 1,
	ERROR = -1,
	POSERROR = -2,
	INITFAULT = -3,
	INCFAULT = -4,
	FAULT = -5,
}Status;

typedef struct
{
	Status tag;
	SElemType item;
}RetType;


typedef struct
{
	SElemType *data;
	int  cursize; // 当前元素的个数
	int  maxsize; // CapacitySize;
}SeqList;


void SeqList_Swap(SElemType &a, SElemType &b);
Status InitList(SeqList &seq);

void DestroyList(SeqList &seq);

void ClearList(SeqList &seq);

int GetSize(SeqList &seq);

int GetCapacity(SeqList &seq);

bool Is_Empty(SeqList &seq);

bool Is_Full(SeqList &seq);

//bool Inc_Size(SeqList &seq);

Status InsertList(SeqList &seq, int pos, SElemType val);

Status Push_Back(SeqList &seq, SElemType val);

Status Push_Front(SeqList &seq, SElemType val);

Status EraseList(SeqList &seq, int pos);

Status Pop_Front(SeqList &seq);

Status Pop_Back(SeqList &seq);

Status Remove(SeqList &seq, SElemType val);

RetType GetFront(SeqList &seq);

RetType GetBack(SeqList &seq);

void PrintList(SeqList &seq);

void InsertSort(SeqList &seq);

void SelectSort(SeqList &seq);

void FilterDown(SeqList &seq, int start, int end);

void HeapSort(SeqList &seq);

int BinaryFindValue(SeqList &seq, SElemType val);

int Search(SeqList &seq, int left, int right, SElemType val);

int SearchValue(SeqList &seq, SElemType val);

#endif

