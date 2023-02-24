#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
//////////////////////////////////  Linear Single Linked List  ////////////////////////////////////
class Node {
public:
	int data;
	Node* next;
};

class linkedList {
public:
	Node* head;
	linkedList() {
		head = NULL;
	}
	bool isempty() {
		return (head == NULL);
	}

	void insertFirst(int newvalue) {
		Node* newnode = new Node();
		newnode->data = newvalue;
		if (isempty()) {
			newnode->next = NULL;
			head = newnode;
		}
		else
		{
			newnode->next = head;
			head = newnode;
		}
	}
	void display() {
		Node* temp = head;
		while (temp != NULL)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
	}
	int count() {
		Node* temp = head;
		int counter = 0;
		while (temp != NULL) {
			counter++;
			temp = temp->next;
		}
		return counter;
	}
	bool isfound(int value) {
		Node* temp = head;
		bool found = false;
		while (temp != NULL)
		{
			if (temp->data == value) {
				found = true;
				break;
			}
			temp = temp->next;

		}
		return found;
	}
	void insertBefore(int position, int item) {
		if (isempty()) {
			insertFirst(item);
			return;
		}
		if (isfound(position)) {
			Node* newnode = new Node();
			newnode->data = item;
			Node* temp = head;
			while (temp != NULL && temp->next->data != position) {
				temp = temp->next;
			}
			newnode->next = temp->next;
			temp->next = newnode;
		}
		else
			cout << "Sorry not found\n";
	}
	void append(int item) {
		if (isempty()) {
			insertFirst(item);
			return;
		}
		Node* temp = head;
		Node* newnode = new Node();
		newnode->data = item;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newnode;
		newnode->next = NULL;
	}

	void del(int item) {
		Node* delptr = head;
		if (isempty()) {
			cout << "List is empty\n";
			return;
		}
		if (isfound(item) == false) {
			cout << "Not found\n";
		}
		if (head->data == item) {
			head = head->next;
			delete delptr;
		}
		Node* temp = NULL;
		while (delptr->data != item) {
			temp = delptr;
			delptr = delptr->next;
		}
		temp->next = delptr->next;
		delete delptr;


	}

};
///////////////////////////// Circular Linked List /////////////////////////////////
struct CNode {
	int data;
	CNode* next;
}*Head;

void CCreate(int arr[], int n) {

	Head = new CNode;
	Head->data = arr[0];
	Head->next = Head;
	CNode* last = Head, * t;

	for (int i = 1; i < n; i++) {
		t = new CNode;
		t->data = arr[i];
		t->next = last->next;
		last->next = t;
		last = t;
	}
}
void CDisplay(CNode* h) {
	do {

		printf("%d", h->data);
		h = h->next;
	} while (h != Head);
}
void RCDisplay(CNode* h) {
	static int flag = 0;

	if (h != Head || flag == 0) {
		printf("%d\t", h->data);
		flag++;
		RCDisplay(h->next);
	}
	flag = 0;
}
int CLength(CNode* p) {
	int len = 0;
	do {
		len++;
		p = p->next;
	} while (p != Head);
	return len;
}
void CInsert(CNode* p, int pos, int x) {

	CNode* t = new CNode;
	t->data = x;

	if (pos >= 0 && CLength(Head) >= pos)
	{

		if (pos == 0) {
			if (Head == NULL) {
				Head = t;
				Head->next = Head;
			}
			else {
				while (p->next != Head)p = p->next;
				p->next = t;
				t->next = Head;
				Head = t;
			}
		}
		else {
			for (int i = 0; i < pos - 1; i++) {
				p = p->next;
			}
			t->next = p->next;
			p->next = t;
		}
	}
}
int CDelete(CNode* p, int pos) {
	int x = -1;
	if (pos <= CLength(Head) && pos > 0) {
		if (pos == 1) {
			if (CLength(Head) == 1) {
				x = p->data;
				delete Head;
			}
			else {
				while (p->next != Head)p = p->next;
				p->next = Head->next;
				x = Head->data;
				delete Head;
				Head = p->next;
			}
		}
		else {
			for (int i = 0; i < pos - 2; i++)p = p->next;
			CNode* q = p->next;
			p->next = q->next;
			x = q->data;
			delete q;
		}
	}
	return x;
}
void findMiddle(CNode* p) {
	CNode* q = p;

	do {
		p = p->next;
		p = p->next;
		if (p != Head && p != Head->next) q = q->next;
	} while (p != Head && p != Head->next);

	cout << "Middle = " << q->data << endl;
}


///////////////////////////////////// Doubly LinkedList ////////////////////////////////////

struct DNode {
	DNode* prev;
	int data;
	DNode* next;
}*first;

int DLength(DNode* p) {
	int len = 0;
	while (p) {
		len++;
		p = p->next;
	}
	return len;
}
void DCreate(int arr[], int n) {
	first = new DNode;
	DNode* last, * t;
	first->data = arr[0];
	first->next = first->prev = NULL;
	last = first;

	for (int i = 1; i < n; i++) {
		t = new DNode;
		t->data = arr[i];
		t->next = last->next;
		t->prev = last;
		last->next = t;
		last = t;
	}
}

void DInsert(DNode* p, int pos, int x) {
	DNode* t = new DNode;
	t->data = x;

	if (pos <= DLength(first) && pos >= 0) {
		if (pos == 0) {
			t->next = first;
			t->prev = NULL;
			first->prev = t;
			first = t;
		}
		else {
			for (int i = 0; i < pos - 1; i++)p = p->next;

			t->prev = p;
			t->next = p->next;
			if (p->next)
				p->next->prev = t;
			p->next = t;
		}
	}
}

int DDelete(DNode* p, int index) {
	int x = -1;
	if (index > 0 && index <= DLength(first)) {
		if (index == 1) {
			first = first->next;
			x = p->data;
			if (p->next)first->prev = NULL;
			delete p;
		}
		else {
			x = p->data;
			for (int i = 0; i < index - 1; i++)p = p->next;
			p->prev->next = p->next;
			if (p->next) p->next->prev = p->prev;
			delete p;
		}
	}
	return x;
}
void DDisplay(DNode* p) {
	while (p) {
		printf("%d\t", p->data);
		p = p->next;
	}
}
void DReverseDisplay(DNode* p) {
	while (p->next)
		p = p->next;

	while (p)
	{
		printf("%d\t", p->data);
		p = p->prev;
	}
}
void DReverse(DNode* p) {
	DNode* temp;
	while (p) {
		temp = p->next;
		p->next = p->prev;
		p->prev = temp;
		p = p->prev;
		if (p && !p->next)
			first = p;
	}
}

int main() {
	linkedList lst;
	
	cout << "Enter number of items\n";
	int num;
	cin >> num;
	for (int i = 0; i < num; i++) {
		int item;
		cin >> item;
		lst.insertFirst(item);

	}
	lst.display();
	cout << endl << "Number of items= " << lst.count() << endl;

	cout << "Enter item to search\n";
	int item;
	cin >> item;
	cout << lst.isfound(item) << endl;


	cout << "Enter the position and value of new item\n";
	int pos;
	cin >> pos;
	cin >> item;
	lst.insertBefore(pos, item);
	lst.display();

	cout << endl << "Enter item to append\n";
	cin >> item;
	lst.append(item);
	lst.display();

	cout << endl << "Enter item to delete\n";
	cin >> item;
	lst.display();

	return 0;
}