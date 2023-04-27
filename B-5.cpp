#include<iostream>
using namespace std;

struct node
{
	string data;
	node *left;
	node *right;	
	node(string d)
	{
		data = d;
		left = NULL;
		right = NULL;
	}	
};
/***************CLASS QUEUE(FOR BFS)**********/
class Queue
{
	node *arr[20];
	int r,f;
	public:
		
	Queue()
	{
		r=f=-1;
	}

	int Empty()
	{
		if(r==-1 && f==-1)
		{
			return 1;
		}
	return 0;
	}

	void insert(node *p)
	{
		if(r==-1 && f==-1)
		{
			r=f=0;
			arr[r] = p;
		}
		else
		{
			r = r+1;
			arr[r] = p;
		}
	}
	
	void init()
	{
		r=f=-1;
	}

	node *remove()
	{
		node *p = arr[f];
		if(r==f)
		{
			r=f=-1;
		}
		else
		{
		f = f+1;
		}
		return p;
	}
};

/***********CLASS STACK (FOR NON-RECURSIVR TRAVERSAL)************/
class Stack
{
	node *a[10];
	int top;
	public:
		
	Stack()
	{
		top = -1;
	}
	
	void Push(node *p)
	{
		top = top+1;
		a[top] = p;	
	}
	
	node *Pop()
	{
		node *p = a[top];
		top = top-1;
		return p;
	}
	
	int empty()
	{
		if(top == -1)
			return 1;
		return 0;
	}	
};
/***********CLASS TREE*********/
class Tree
{
	public:
/*********CREATE FUNCTION***********/
node* create()
{
	string x;
	cout<<"Enter : ";
	cin>>x;
	if(x == "NA")
	{
		return NULL;
	}
	else
	{
		node *temp = new node(x);
		cout<<"left part of "<<x<<endl;
		temp->left = create();

		cout<<" right part of "<<x<<endl;
		temp->right = create();
		return temp;
	}
}

/**********BFS FUNCTION**********/
void BFS(node *t)
{
	Queue q1,q2;
	q1.insert(t);
	cout<<"BOOK NAME:\t    "<<t->data;
	int count = 1;
	int count1 = 1;
				
	while(!q1.Empty())
	{
		q2.init();
		cout<<"\n";
		while(!q1.Empty())
		{
			node *r = q1.remove();
			
			if(r->left != NULL)
			{
					
					if(count == 1)
							cout<<"\t\t";
						if(count == 2)
							cout<<"\t     ";
						if(count == 3)
							cout<<"\t";	
				cout<<(r->left)->data<<" ";
				q2.insert(r->left);
			}
			
			if(r->right != NULL)
			{
				if(count == 1)
					cout<<"\t";
				if(count == 2)
					cout<<"   ";
				if(count == 3)
					cout<<"";
				cout<<(r->right)->data<<" ";
				q2.insert(r->right);
			}
			cout<<"\t";
		}
	count = count +1;
	q1 = q2;
	}
	cout<<endl;
}
/**********RECURSIVE TRAVERSAL **********/
void inorder_r(node *t)
{
	if(t != NULL)
	{
		inorder_r(t->left);
		cout<<t->data<< " ";
		inorder_r(t->right);
	}
}

void preorder_r(node *t)
{
	if(t != NULL)
	{
		cout<<t->data<< " ";
		preorder_r(t->left);
		preorder_r(t->right);
	}
}

void postorder_r(node *t)
{
	if(t != NULL)
	{
		postorder_r(t->left);
		postorder_r(t->right);
		cout<<t->data<< " ";
	}
}
/**********NON-RECURSIVE TRAVERSAL **********/
void inorder_nr(node *t)
{
	Stack s;
	while(t != NULL)
	{
		s.Push(t);
		t = t->left;	
	}
	
	while(!s.empty())
	{
		t = s.Pop();
		cout<<t->data<<" ";
		t = t->right;
		
		while(t != NULL)
		{
			s.Push(t);
			t = t->left;
		}
	}
}

void preorder_nr(node *t)
		{
			Stack s;
			while(t != NULL)
			{
				cout<<t->data<<" ";
				s.Push(t);
				t = t->left;
			}
			while(!s.empty())
			{
				t = s.Pop();
				t = t->right;
				while(t != NULL)
				{
					cout<<t->data<<" ";
					s.Push(t);
					t = t->left;
				}
			}
		}
		
void postorder_nr(node* t)
{
		    Stack s1,s2;
		    node* temp;
		    
		    if(t==NULL)
			{
		        return;
		    }
		    
		    s1.Push(t);
		    while(s1.empty()!=1)
			{
		        temp=s1.Pop();
		        s2.Push(temp);
		        if(temp->left!=NULL)
		            s1.Push(temp->left);
		        if(temp->right)
		            s1.Push(temp->right);
		    }
		    while(s2.empty()!=1)
			{
		        temp=s2.Pop();
		        cout<<temp->data<<" ";
		    }
}

};
int main()
{
Tree t;
node *root =t.create();
int ch,choice,cho;
do
{
	cout<<"1:BSF"<<endl;
	cout<<"2:recursive:"<<endl;
	cout<<"3:Non-recursive"<<endl;
	cout<<"4:Exit"<<endl;
	cout<<"Enter choice: ";
	cin>>ch;
	switch(ch)
	{
		case 1:
			t.BFS(root);
			break;
		case 2:
			do
			{
				cout<<"1:Inorder"<<endl;
				cout<<"2:Preorder"<<endl;
				cout<<"3:Postorder"<<endl;
				cout<<"4: Exit"<<endl;
				cout<<"enter choice: ";
				cin>>choice;
				
				switch(choice)
				{
					case 1:
						cout<<"Inorder: ";
						t.inorder_r(root);
						cout<<endl;
						break;
					case 2:
						cout<<"Preorder: ";
						t.preorder_r(root);
						cout<<endl;
						break;
					case 3:
						cout<<"Postorder: ";
						t.postorder_r(root);
						cout<<endl;
						break;
				}
			}while(choice != 4);
			break;
			
		case 3:
			
				do
				{
				cout<<"1:Inorder"<<endl;
				cout<<"2:Preorder"<<endl;
				cout<<"3:Postorder"<<endl;
				cout<<"4: Exit"<<endl;
				cout<<"enter choice: ";
				cin>>cho;
				
				switch(cho)
				{
					case 1:
						cout<<"Inorder: ";
						t.inorder_nr(root);
						cout<<endl;
						break;
						
					case 2:
						cout<<"Preorder: ";
						t.preorder_nr(root);
						cout<<endl;
						break;
						
					case 3:
						cout<<"Postorder: ";
						t.postorder_nr(root);
						cout<<endl;
						break;
				}
				}while(cho != 4 );
				break;
			
	}
}while(ch != 3);
return 0;
}

