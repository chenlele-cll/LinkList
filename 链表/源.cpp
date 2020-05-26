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
	LinkList();//不带参数的构造函数
	LinkList(datatype x,int n);//初始化有n个val为x的链表
	datatype GetElem(int n);//取链表中第n个元素的值
	int FindElem(datatype value);//找链表中是否存在value的元素，存在返回pos，反之返回-1表示未找到
	void topinsert(datatype value);//头插法插入元素
	void backinsert(datatype value);//尾插法插入元素
	datatype getNthFromEnd(int n);//获取倒数第n个元素的值
	void removeNthFromEnd(int n);//删除链表倒数第n个元素
	void removeNthFromStart(int n);//删除链表第n个元素
	void sortLink1();//排序链表1;
	void sortLink2();//排序链表2;
	node<datatype> * mergesort(node<datatype> *node1);
	node<datatype> * merge(node<datatype>* l1, node<datatype>* l2);
	void reverseList();//反转链表
	bool judgeequal(LinkList &a);//判断两个链表是否相等
	int getlen() //返回链表长度
	{
		return len;
	};
	friend ostream &operator<<(ostream &output, const LinkList &D)//重载输出流
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
	~LinkList();//析构函数
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

//不带参数的构造函数
template<class datatype>
LinkList<datatype>::LinkList()
{
	head = new node<datatype>;
	len = 0;
	head->next = NULL;
}

//初始化有n个val为x的链表
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

//析构函数
template<class datatype>
LinkList<datatype>::~LinkList()
{
	node<datatype> *p1 = head, *p2;
	while (p1 != NULL)//排着释放
	{
		p2 = p1->next;
		delete p1;
		p1 = p2;
	}
}

//取链表中第n个元素的值
template<class datatype>
datatype LinkList<datatype>::GetElem(int n)
{
	if (n > len || n < 1)
	{
		cerr << "取值有误";
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

//找链表中是否存在value的元素，存在返回pos，反之返回-1表示未找到
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

//头插法插入元素
template<class datatype>
void  LinkList<datatype>::topinsert(datatype value)
{
	node<datatype> *p = new node<datatype>(value);
	node<datatype> *k = head->next;
	head->next = p;
	p->next = k;
	len++;
}

//尾插法插入元素
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

//获取倒数第n个元素的值
template<class datatype>
datatype LinkList<datatype>::getNthFromEnd(int n)
{
	if (n > len || n < 0)
	{
		cerr << "取值有误";
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

//删除倒数第n个元素的值
template<class datatype>
void LinkList<datatype>::removeNthFromEnd(int n)
{
	if (n > len || n < 0)
	{
		cerr << "取值有误" << endl;
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

//删除第n个元素的值
template<class datatype>
void LinkList<datatype>::removeNthFromStart(int n)
{
	if (n<0 || n>len)
		cerr << "取值有误" << endl;
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

//反转链表
template<class datatype>
void LinkList<datatype>::reverseList()
{
	if (!(head == NULL || head->next == NULL))
	{
		node<datatype> *p = head->next;//遍历节点的上一个节点
		node<datatype> *k = p->next;//当前遍历节点
		head->next->next = NULL;
		head->next = NULL;//更改头
		while (k)
		{
			node<datatype> *temp = k->next;//临时节点保存下一个遍历节点
			k->next = p;
			p = k;
			k = temp;
		}
		head->next = p;
	}
}

//排序1
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

//排序2
template<class datatype>
void LinkList<datatype>::sortLink2()
{
	head->next=mergesort(head->next);
}

template<class datatype>
node<datatype> * LinkList<datatype>::mergesort(node<datatype>*node1)
{
	if (!node1 || !node1->next) return node1;
	node<datatype> *fast = node1;//快指针走两步
	node<datatype> *slow = node1;//慢指针走一步
	node<datatype> *brek = node1;//断点
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

//判断两个链表是否相等
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
	cout << "此时链表A元素有：" << A;
	cout << "此时的链表A长度为" << A.getlen() << endl;
	cout << "此时链表A的倒数第二个元素为" << A.getNthFromEnd(2) << endl;
	cout << "此时链表B元素有：" << B;
	//A.removeNthFromEnd(3);
	//A.removeNthFromStart(4);
	//A.reverseList();
	//A.sortLink1();
	//A.sortLink2();
	cout << A;

	if (A.judgeequal(B))
		cout << "两个链表相等" << endl;
	else cout << "两个链表不相等" << endl;
	if (A.FindElem(3) != -1)
	{
		cout << "找到该元素,在第"<< A.FindElem(3)<<"个位置" << endl;
	}
	else cout << "未找到该元素" << endl;
	if (A.FindElem(1) != -1)
	{
		cout << "找到该元素,在第" << A.FindElem(1) << "个位置" << endl;
	}
	else cout << "未找到该元素" << endl;
	//cout << A.GetElem(1) << " " << A.GetElem(2) << endl;
	//cout << A.GetElem(3) << endl;
	//A.~LinkList();
	system("pause");
	return 0;
}