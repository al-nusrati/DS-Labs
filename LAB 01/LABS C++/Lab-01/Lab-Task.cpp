#include<iostream>

using namespace std;

struct node {
	int d;
	node* next;

	node() : d(0), next(NULL) {}
};

class linkedList
{
	node* head;

public:
	linkedList() : head(NULL)
	{

	}

	void insertAtStart(int d)
	{
		node* n = new node;
		(*n).d = d;
		n->next = head;
		head = n;
		
	}

	void deleteFromStart()
	{
		if (head != NULL)
		{
			node* temp = head;
			head = head->next;
			delete  temp;
		}
		else
		{
			cout << "list is empty" << endl;
		}

	}

	void deleteFromEnd()
	{
		if (head == NULL)
		{
			cout << "list is empty" << endl;
			return;
		}
		
		if (head->next == NULL)
		{
			delete head;
			head = NULL;
			return;
		}
		
		node* temp = head;
		while (temp->next->next != NULL)
		{
			temp = temp->next;
		}
		
		delete temp->next;
		temp->next = NULL;
	}

	void display()
	{
		node* temp = head;
		while (temp!=NULL)
		{
			cout << temp->d << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	void insertAtEnd(int d)
	{
		node* n = new node;
		n->d = d;
		
		if (head == NULL)
		{
			head = n;
			return;
		}
		
		node* temp = head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = n;
	}

	int getLength()
	{
		int count = 0;
		node* temp = head;
		
		while (temp != NULL)
		{
			count++;
			temp = temp->next;
		}
		
		return count;
	}

	bool isEmpty()
	{
		return (head == NULL);
	}

	bool searchData(int d)
	{
		node* temp = head;
		
		while (temp != NULL)
		{
			if (temp->d == d)
			{
				return true;
			}
			temp = temp->next;
		}
		
		return false;
	}
};
void main()
{
	linkedList list;

    list.deleteFromEnd();
    list.insertAtEnd(500);

	list.deleteFromEnd();

	list.insertAtStart(5);
	list.insertAtStart(10);
	list.insertAtStart(20);
	list.insertAtStart(100);
	list.deleteFromStart();
	list.display();

	list.insertAtStart(35);
	list.deleteFromEnd();
	list.display();
}