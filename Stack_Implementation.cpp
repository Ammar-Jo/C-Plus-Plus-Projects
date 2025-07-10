#include<iostream>
using namespace std;

struct node { int item; node* next; };
class Stack
{
public:
	Stack();
	~Stack();
	bool isEmpty();
	void push(int);
	void pop();
	void pop(int&);
	void getTop(int&);
	void display();

private:
	node* top;

};

Stack::Stack() :top(NULL) {}


Stack::~Stack()
{
	while (!isEmpty())
		pop();
}

bool Stack::isEmpty() { return top == NULL; }

void Stack::push(int value)
{
	node* slot = new node;
	slot->next = top;
	slot->item = value;
	top = slot;
}

void Stack::pop()
{
	node* cur = top;
	top = top->next;
	cur->next = NULL;
	delete cur;
}

void Stack::pop(int& TOP)
{
	TOP = top->item;

	node* cur = top;
	top = top->next;
	cur->next = NULL;
	delete cur;

}

void Stack::getTop(int& Top)
{
	if (isEmpty())
		cout << "Stack is empty...\n";
	else
		Top = top->item;
}

void Stack::display()
{
	node* cur = top;

	cout << "Items in stack: [";
	while (cur != NULL)
	{
		cout << " " << cur->item;
		cur = cur->next;
	}
	cout << " ]\n";
}
int main()
{
	Stack s;
	s.push(10);
	s.push(20);
	s.push(30);
	s.push(40);
	s.push(50);
	s.display();
	s.pop();
	int x;
	s.pop(x);
	int y;
	s.getTop(y);
	s.display();
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;


}