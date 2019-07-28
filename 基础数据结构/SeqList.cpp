
#include"AfxStd.h"
#include"SeqList.h"

void SeqList_Swap(SElemType &a, SElemType &b)
{
	SElemType c = a;
	a = b;
	b = c;
}
Status InitList(SeqList &seq)
{
	seq.data = (SElemType*)malloc(sizeof(SElemType)*LIST_INIT_SIZE);
	if (NULL == seq.data)
	{
		//exit(1); 
		return INITFAULT;
	}
	memset(seq.data, 0, sizeof(SElemType)*LIST_INIT_SIZE);
	//memmove; memcpy; memcmp;//strcpy;strcmp
	seq.cursize = 0;
	seq.maxsize = LIST_INIT_SIZE;
	return OK;
}
void DestroyList(SeqList &seq)
{
	free(seq.data);
	seq.data = NULL;
	seq.cursize = 0;
	seq.maxsize = 0;
}

void ClearList(SeqList &seq)
{
	seq.cursize = 0;
}
int GetSize(SeqList &seq)
{
	return seq.cursize;
}
int GetCapacity(SeqList &seq)
{
	return seq.maxsize;
}
bool Is_Empty(SeqList &seq)
{
	return GetSize(seq) == 0;
}
bool Is_Full(SeqList &seq)
{
	return GetSize(seq) == GetCapacity(seq);
}
static bool Inc_Size(SeqList &seq)
{
	SElemType *newdata = (SElemType*)realloc(seq.data, sizeof(SElemType)*GetCapacity(seq)*LIST_INC_SIZE);
	if (NULL == newdata)
	{
		return false;
	}
	seq.data = newdata;
	seq.maxsize = seq.maxsize * LIST_INC_SIZE;
	return true;
}
Status InsertList(SeqList &seq, int pos, SElemType val)
{
	if (pos < 0 || pos > seq.cursize)
	{
		return POSERROR;
	}
	if (Is_Full(seq) && !Inc_Size(seq))
	{
		return INCFAULT;
	}
	for (int i = seq.cursize; i > pos; --i)
	{
		seq.data[i] = seq.data[i - 1];
	}
	seq.data[pos] = val;
	seq.cursize += 1;
	return OK;
}
Status Push_Back(SeqList &seq, SElemType val)
{
	return InsertList(seq, seq.cursize, val);
}
Status Push_Front(SeqList &seq, SElemType val)
{
	return InsertList(seq, 0, val);
}
Status EraseList(SeqList &seq, int pos)
{
	if (pos < 0 || pos > seq.cursize - 1)
	{
		return POSERROR;
	}
	for (int i = pos; i < seq.cursize - 1; ++i)
	{
		seq.data[i] = seq.data[i + 1];
	}
	seq.cursize -= 1;
	return OK;
}
Status Pop_Front(SeqList &seq)
{
	return EraseList(seq, 0);
}
Status Pop_Back(SeqList &seq)
{
	return EraseList(seq, seq.cursize - 1);
}
Status Remove(SeqList &seq, SElemType val)
{
	int i = 0, j = 0;
	while (i < seq.cursize)
	{
		if (seq.data[i] != val)
		{
			seq.data[j] = seq.data[i];
			++j;
		}
		++i;
	}
	seq.cursize = j;
	return OK;
}
RetType GetFront(SeqList &seq)
{
	RetType res = { FAULT };
	if (!Is_Empty(seq))
	{
		res.item = seq.data[0];
		res.tag = OK;
	}
	return res;// id name sex age addr 
}
RetType GetBack(SeqList &seq)
{
	RetType res = { FAULT };
	if (!Is_Empty(seq))
	{
		res.item = seq.data[seq.cursize - 1];
		res.tag = OK;
	}
	return res;// id name sex age addr 
}
void PrintList(SeqList &seq)
{
	int n = GetSize(seq);
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", seq.data[i]);
	}
	printf("\n");
}

void InsertSort(SeqList &seq)
{
	int n = GetSize(seq);
	for (int i = 1; i<n; ++i)
	{
		if (seq.data[i] < seq.data[i - 1])
		{
			SElemType tmp = seq.data[i];
			int j = i - 1;
			do
			{
				seq.data[j + 1] = seq.data[j];
				--j;
			} while (j >= 0 && tmp < seq.data[j]);
			seq.data[j + 1] = tmp;
		}
	}
}

void SelectSort(SeqList &seq)
{
	int n = GetSize(seq);
	for (int i = 0; i<n - 1; ++i)
	{
		int minpos = i;
		for (int j = i + 1; j<n; ++j)
		{
			if (seq.data[minpos] > seq.data[j])
			{
				minpos = j;
			}
		}
		if (i != minpos)
		{
			SeqList_Swap(seq.data[minpos], seq.data[i]);
		}
	}
}
void FilterDown(SeqList &seq, int start, int end)
{
	int i = start, j = 2 * i + 1;
	SElemType tmp = seq.data[i];
	while (j <= end) //
	{
		if (j < end && seq.data[j] < seq.data[j + 1]) ++j; // Max
		if (tmp >= seq.data[j]) break;
		seq.data[i] = seq.data[j];
		i = j;
		j = i * 2 + 1;
	}
	seq.data[i] = tmp;
}
void HeapSort(SeqList &seq)
{
	int end = seq.cursize - 1;
	int pos = (end - 1) / 2;
	// makeheap
	while (pos >= 0)
	{
		FilterDown(seq, pos, end);
		--pos;
	}
	for (int i = seq.cursize - 1; i>0; --i)
	{
		SeqList_Swap(seq.data[0], seq.data[i]);
		FilterDown(seq, 0, i - 1);
	}
}

int BinaryFindValue(SeqList &seq, SElemType val)
{
	int pos = -1;
	int left = 0, right = seq.cursize - 1;
	while (left <= right)
	{
		int mid = (right - left + 1) / 2 + left;
		if (val < seq.data[mid]) { right = mid - 1; }
		else if (val > seq.data[mid]) { left = mid + 1; }
		else
		{
			while (mid > left && val == seq.data[mid - 1]) --mid;
			pos = mid;
			break;
		}
	}
	return pos;
}

int Search(SeqList &seq, int left, int right, SElemType val)
{
	int pos = -1;
	if (left <= right)
	{
		int mid = (right - left + 1) / 2 + left;
		if (val < seq.data[mid])
		{
			pos = Search(seq, left, mid - 1, val);
		}
		else if (val > seq.data[mid])
		{
			pos = Search(seq, mid + 1, right, val);
		}
		else
		{
			while (mid > left && val == seq.data[mid - 1]) --mid;
			pos = mid;
		}
	}
	return pos;
}
int SearchValue(SeqList &seq, SElemType val)
{
	return Search(seq, 0, seq.cursize - 1, val);
}