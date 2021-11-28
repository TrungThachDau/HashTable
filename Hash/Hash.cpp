#include <iostream>
using namespace std;
#define keysize 10
struct Node
{
	int Key;
	Node* Next;
};
Node* bucket[keysize];
int Hash(int Key)
{
	return Key % keysize;
}
void initBucket()
{
	for (int b = 0; b < keysize; b++)
		bucket[b] = NULL;
}
void Push(int b, int x)
{
	Node* p = new Node;
	p->Key = x;
	p->Next = bucket[b];
	bucket[b] = p;
}
//Phép toán thêm vào bucket 1 nút mới sau nút p
void InsertAfter(Node* p, int k)
{
	if (p)
	{
		Node* q = new Node;
		q->Key = k;
		q->Next = p->Next;
		p->Next = q;
	}
	else
		return;
}
void Place(int b, int k)
{
	Node* q = NULL;
	Node* p = bucket[b];
	while (p != NULL&&k>p->Key)
	{
		q = p;
		p = p->Next;
	}
	if (q == NULL)
		Push(b, k);
	else
		InsertAfter(q, k);

}
bool isEmpty(int i)
{

	if (bucket[i] == NULL)
		return true;
	return false;
}
void DeleteHead(Node*& l)
{
	if (l != NULL)
	{
		Node* p = l;
		l = l->Next;
		delete p;
	}
}

void DeleteAfter(Node*& q)
{
	Node* p = q->Next;
	if (p != NULL)
	{
		q->Next = p->Next;
		delete p;
	}
}

void Remove(int k)
{
	int i = Hash(k);
	Node* p = bucket[i];
	Node* q = p;
	while (p != NULL && p->Key != k)
	{
		q = p;
		p = p->Next;
	}
	if (p == NULL)
		cout << k << "Khong tim thay!" << endl;
	else if (p == bucket[i])
		DeleteHead(bucket[i]);
	else
		DeleteAfter(q);
}
void addNode(int k)
{
	int b = Hash(k);
	Place(b, k);
}
void createHashArray(int a[])
{
	for (int i = 0; i < 27; i++)
	{
		addNode(a[i]);
	}
}

void createBucket(int &n)
{
	n = 100;
	for (int i = 0; i < n; i++)
	{
		int k = rand() % 100;
		cout << "  " << k;
		addNode(k);
	}
	cout << endl;
}
void createBucketArray(int a[])
{
	for (int i = 0; i < 27;i++)
	{
		addNode(a[i]);
	}
}
void Traverse(Node* p)
{
	while (p != NULL)
	{
		cout << p-> Key << "-->";
		p = p->Next;
	}
	cout << endl;
}
void TraverseHashTable()
{
	for (int b = 0; b < keysize; b++)
	{
		cout << "Bucket " << b << ":  ";
		Traverse(bucket[b]);
	}
}
Node* SearchNode(int k)
{
	int i = Hash(k);
	Node* p = bucket[i];
	while (p != NULL && p->Key != k)
		p = p->Next;
	if (p == NULL)
		return NULL;
	return p;
}
void ClearBucket(int b)
{
	Node* q = NULL;
	Node* p = bucket[b];
	while (p != NULL)
	{
		q = p;
		p = p->Next;
		delete q;
	}
	bucket[b] = NULL;
}
void Clear()
{
	for (int i = 0; i < keysize; i++)
	{
		ClearBucket(i);
	}
}
void menu()
{
	cout << "\n1. Tao bang bam";
	cout << "\n2. Xuat bang bam";
	cout << "\n3. Tim";
	cout << "\n4. Xoa";
	cout << "\n5. Them";
	cout << "\n6. Xoa Bucket";
	cout << "\n7. Xoa bang bam";
	cout << "\n8. Duyet bucket";
	cout << "\nNhap 0 de thoat";
	cout << "\nChon chuc nang: ";
}
int main()
{
	int n = 0;
	int a[] = { 3,7,9,12,15,4,99,462,438,23,40,23,99,182,192,3184,12,474,12,18,58,43,39,85,83,42,53 };
	initBucket();
	int chucnang;
	do
	{
		menu();
		cin >> chucnang;
		switch (chucnang)
		{
		case 1:
		{
			createBucket(n); break;
			//createBucketArray(a);
		}
		case 2:
		{
			TraverseHashTable();
			break;
		}
		case 3:
		{
			int k;
			cout << "\nNhap nut can tim: ";
			cin >> k;
			Node* result = SearchNode(k);
			if (result == NULL)
				cout << "\nKhong tim thay!";
			else
				cout << "\nDa tim thay";
			break;
		}
		case 4:
		{
			int k;
			cout << "\nNhap nut can xoa: ";
			cin >> k;
			Remove(k);
			TraverseHashTable(); break;
		}
		case 5:
		{
			int k;
			cout << "\nNhap 1 nut: ";
			cin >> k;
			addNode(k);
			TraverseHashTable(); break;
		}
		case 6:
		{
			int b;
			cout << "\n Nhap bucket can xoa: ";
			cin >> b;
			ClearBucket(b);
			TraverseHashTable();
			break;
		}
		case 7:
		{
			Clear();
			break;
		}
		case 8:
		{
			int i;
			cout << "Nhap bucket de duyet: ";
			cin >> i;
			Traverse(bucket[i]); break;
		}
		default:
		{
			cout << "\n Chuc nang khong hop le!";
			break;
		}
		}
	} while (chucnang!=0);
	system("pause");
	return 0;
}