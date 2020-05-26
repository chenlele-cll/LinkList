#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
template<class datatype>
class node;

template<class datatype>
class LinkList
{
private:
	int len;
	node<datatype> *head;
public:
	LinkList();//���������Ĺ��캯��
	LinkList(datatype x,int n);//��ʼ����n��valΪx������
	datatype GetElem(int n);//ȡ�����е�n��Ԫ�ص�ֵ
	int FindElem(datatype value);//���������Ƿ����value��Ԫ�أ����ڷ���pos����֮����-1��ʾδ�ҵ�
	void topinsert(datatype value);//ͷ�巨����Ԫ��
	void backinsert(datatype value);//β�巨����Ԫ��
	datatype getNthFromEnd(int n);//��ȡ������n��Ԫ�ص�ֵ
	void removeNthFromEnd(int n);//ɾ����������n��Ԫ��
	void removeNthFromStart(int n);//ɾ�������n��Ԫ��
	void sortLink1();//��������1;
	void sortLink2();//��������2;
	node<datatype> * mergesort(node<datatype> *node1);
	node<datatype> * merge(node<datatype>* l1, node<datatype>* l2);
	void reverseList();//��ת����
	bool judgeequal(LinkList &a);//�ж����������Ƿ����
	int getlen() //����������
	{
		return len;
	};
	friend ostream &operator<<(ostream &output, const LinkList &D)//���������
	{
		if (D.len == 0)
		{
			cout << "LinkList is empty" << endl;
			exit(1);
		}
		node<datatype> *p = D.head->next;
		for (int i = 1; i <= D.len; i++)
		{
			output << p->val << ' ';
			p = p->next;
		}
		cout << endl;
		return output;
	}
	~LinkList();//��������
};

template<class datatype>
class node
{
	node() {};
	friend class LinkList<datatype>;
public:
	datatype val;
	node<datatype> * next;
	node(datatype x) : val(x), next(NULL) {};
};

//���������Ĺ��캯��
template<class datatype>
LinkList<datatype>::LinkList()
{
	head = new node<datatype>;
	len = 0;
	head->next = NULL;
}

//��ʼ����n��valΪx������
template<class datatype>
LinkList<datatype>::LinkList(datatype x, int n)
{
	head = new node<datatype>;
	len = n;
	head->next = NULL;
	node<datatype> *p = head;
	for (int i = 0; i < n; i++)
	{
		p->next = new node<datatype>(x);
		p = p->next;
	}
}

//��������
template<class datatype>
LinkList<datatype>::~LinkList()
{
	node<datatype> *p1 = head, *p2;
	while (p1 != NULL)//�����ͷ�
	{
		p2 = p1->next;
		delete p1;
		p1 = p2;
	}
}

//ȡ�����е�n��Ԫ�ص�ֵ
template<class datatype>
datatype LinkList<datatype>::GetElem(int n)
{
	if (n > len || n < 1)
	{
		cerr << "ȡֵ����";
		return -1;
	}
	else
	{
		node<datatype> *p = head;
		for (int i = 0; i < n; i++)
		{
			p = p->next;
		}
		datatype value = p->val;
		return value;
	}
}

//���������Ƿ����value��Ԫ�أ����ڷ���pos����֮����-1��ʾδ�ҵ�
template<class datatype>
int LinkList<datatype>::FindElem(datatype value)
{
	node<datatype> *p = head->next;
	int pos = 1;
	while (p)
	{
		if (p->val == value)
			return pos;
		else
		{
			p = p->next;
			pos++;
		}
	}
	return -1;
}

//ͷ�巨����Ԫ��
template<class datatype>
void  LinkList<datatype>::topinsert(datatype value)
{
	node<datatype> *p = new node<datatype>(value);
	node<datatype> *k = head->next;
	head->next = p;
	p->next = k;
	len++;
}

//β�巨����Ԫ��
template<class datatype>
void LinkList<datatype>::backinsert(datatype value)
{
	node<datatype> *p = head;
	for (int i = 0; i < len; i++)
	{
		p = p->next;
	}
	p->next = new node<datatype>(value);
	len++;
}

//��ȡ������n��Ԫ�ص�ֵ
template<class datatype>
datatype LinkList<datatype>::getNthFromEnd(int n)
{
	if (n > len || n < 0)
	{
		cerr << "ȡֵ����";
		return -1;
	}
	else if (n == len)
		return head->next->val;
	else
	{
		node<datatype> *p = head->next;
		for (int i = 0; i < len - n; i++)
		{
			p = p->next;
		}
		return p->val;
	}
}

//ɾ��������n��Ԫ�ص�ֵ
template<class datatype>
void LinkList<datatype>::removeNthFromEnd(int n)
{
	if (n > len || n < 0)
	{
		cerr << "ȡֵ����" << endl;
	}
	else
	{
		if (n == len)
		{
			node<datatype> *p = head->next;
			head->next = head->next->next;
			delete p;
		}
		else if (n == 1)
		{
			node<datatype> *p = head->next;
			for (int i = 1; i < len - 1; i++)
			{
				p = p->next;
			}
			node<datatype> *k = p->next;
			p->next = NULL;
			delete k;
		}
		else
		{
			node<datatype> *p = head;
			for (int i = 0; i < len - n; i++)
			{
				p = p->next;
			}
			node<datatype> *k = p->next;
			p->next = p->next->next;
			delete k;
		}
		len--;
	}
}

//ɾ����n��Ԫ�ص�ֵ
template<class datatype>
void LinkList<datatype>::removeNthFromStart(int n)
{
	if (n<0 || n>len)
		cerr << "ȡֵ����" << endl;
	else
	{
		if (n == 1)
		{
			node<datatype> *p = head->next;
			head->next = head->next->next;
			delete p;
		}
		else if (n == len)
		{
			node<datatype> *p = head->next;
			for (int i = 1; i < len - 1; i++)
			{
				p = p->next;
			}
			node<datatype> *k = p->next;
			p->next = NULL;
			delete k;
		}
		else
		{
			node<datatype> *p = head;
			for (int i = 0; i < n-1; i++)
			{
				p = p->next;
			}
			node<datatype> *k = p->next;
			p->next = p->next->next;
			delete k;
		}
		len--;
	}
}

//��ת����
template<class datatype>
void LinkList<datatype>::reverseList()
{
	if (!(head == NULL || head->next == NULL))
	{
		node<datatype> *p = head->next;//�����ڵ����һ���ڵ�
		node<datatype> *k = p->next;//��ǰ�����ڵ�
		head->next->next = NULL;
		head->next = NULL;//����ͷ
		while (k)
		{
			node<datatype> *temp = k->next;//��ʱ�ڵ㱣����һ�������ڵ�
			k->next = p;
			p = k;
			k = temp;
		}
		head->next = p;
	}
}

//����1
template<class datatype>
void LinkList<datatype>::sortLink1()
{
	vector<datatype> temp;
	node<datatype> *p = head->next;
	for (int i = 0; i < len; i++)
	{
		temp.push_back(p->val);
		p = p->next;
	}
	sort(temp.begin(), temp.end());
	p = head->next;
	for (int i = 0; i < len; i++)
	{
		p->val = temp[i];
		p = p->next;
	}
}

//����2
template<class datatype>
void LinkList<datatype>::sortLink2()
{
	head->next=mergesort(head->next);
}

template<class datatype>
node<datatype> * LinkList<datatype>::mergesort(node<datatype>*node1)
{
	if (!node1 || !node1->next) return node1;
	node<datatype> *fast = node1;//��ָ��������
	node<datatype> *slow = node1;//��ָ����һ��
	node<datatype> *brek = node1;//�ϵ�
	while (fast && fast->next)
	{
		fast = fast->next->next;
		brek = slow;
		slow = slow->next;
	}
	brek->next = nullptr;
	node<datatype> *l1 = mergesort(node1);
	node<datatype> *l2 = mergesort(slow);
	return merge(l1, l2);
}

template<class datatype>
node<datatype> * LinkList<datatype>::merge(node<datatype>* l1, node<datatype>* l2)
{
	if (l1 == NULL)
	{
		return l2;
	}
	if (l2 == NULL)
	{
		return l1;
	}
	if (l1->val < l2->val)
	{
		l1->next = merge(l1->next, l2);
		return l1;
	}
	else
	{
		l2->next = merge(l2->next, l1);
		return l2;
	}
}

//�ж����������Ƿ����
template<class datatype>
bool LinkList<datatype>::judgeequal(LinkList &a)
{
	if (a.getlen() != len)
		return false;
	else
	{
		node<datatype> *q = a.head->next;
		node<datatype> *k = head->next;
		for (int i = 0; i < len; i++)
		{
			if (q->val != k->val)
				return false;
			q = q->next;
			k = k->next;
		}
		return true;
	}
}
int main()
{
	LinkList<int> A;
	//LinkList<int> B(1,3);
	LinkList<int> B;
	//A.topinsert(2);
	//A.topinsert(1);
	//A.topinsert(3); 
	//A.topinsert(0);
	A.backinsert(2);
	A.backinsert(3);
	A.backinsert(1);
	A.backinsert(1);
	B.backinsert(2);
	B.backinsert(3);
	B.backinsert(1);
	B.backinsert(1);
	cout << "��ʱ����AԪ���У�" << A;
	cout << "��ʱ������A����Ϊ" << A.getlen() << endl;
	cout << "��ʱ����A�ĵ����ڶ���Ԫ��Ϊ" << A.getNthFromEnd(2) << endl;
	cout << "��ʱ����BԪ���У�" << B;
	//A.removeNthFromEnd(3);
	//A.removeNthFromStart(4);
	//A.reverseList();
	//A.sortLink1();
	//A.sortLink2();
	cout << A;

	if (A.judgeequal(B))
		cout << "�����������" << endl;
	else cout << "�����������" << endl;
	if (A.FindElem(3) != -1)
	{
		cout << "�ҵ���Ԫ��,�ڵ�"<< A.FindElem(3)<<"��λ��" << endl;
	}
	else cout << "δ�ҵ���Ԫ��" << endl;
	if (A.FindElem(1) != -1)
	{
		cout << "�ҵ���Ԫ��,�ڵ�" << A.FindElem(1) << "��λ��" << endl;
	}
	else cout << "δ�ҵ���Ԫ��" << endl;
	//cout << A.GetElem(1) << " " << A.GetElem(2) << endl;
	//cout << A.GetElem(3) << endl;
	//A.~LinkList();
	system("pause");
	return 0;
}