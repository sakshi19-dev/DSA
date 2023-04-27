#include<iostream>										
using namespace std;
struct node
{
	int data;
	node *left;
	node *right;
};

class BST
{
	node *root;
	public:
		BST()
		{
			root = NULL;
		}
		//****************INSERT A NEW ELEMENT********************
		node *insert(node *t,int x)
		{
			if(t == NULL)
			{
				node *t = new node;
				t->data = x;
				t->left = NULL;
				t->right = NULL;
				return (t);
			}
			
			else if(x<t->data)
			{
				t->left = insert(t->left,x);
				return (t);
			}
			
			else if(x>t->data)
			{
				t->right = insert(t->right,x);
				return (t);
			}
		}
		
		node *create()
		{
			int n,x;
			cout<<"Enter number of nodes: ";
			cin>>n;
			for(int i=0;i<n;i++)
			{
				cout<<"Enter x: ";
				cin>>x;
				root = insert(root,x);
			}
			return (root);
		}
		
		void inorder(node *root)
		{
			if(root != NULL)
			{
				inorder(root->left);
				cout<<root->data<<" ";
				inorder(root->right);
			}
		}
	//*****************NUMBER OF NODES IN LONGEST PATH**************
		int no_of_nodes(node *root)
		{
		    int hl,hr;
			if(root == NULL)
			{
				return 0;
			}
			
			else if(root->left == NULL &&  root->right==NULL)
			{
				return 0;
			}
			else
			{
				 hl = 1+no_of_nodes(root->left);
				 hr = 1+no_of_nodes(root->right);
			}
			
			if(hl>hr)
			{
				return (hl);
			}
			else
			{
				return (hr);
			}
		}
		//************MINIMUM DATA VALUE FOUND  IN TREE************
		node *minimum(node *t)
		{
			while(t->left != NULL)
			{
				t = t->left;
			}
			return(t);
		}
		//***********SEARCH**********
		node *search(node *t,int x)
		{
			if(t == NULL)
			{
				return NULL;
			}
			
			if(x == t->data)
			{
				return (t);
			}
			
			if(x < t->data)
			{
				return(search(t->left,x));
			}
			
			if(x > t->data)
			{
				return(search(t->right,x));
			}
		}
		//************SWAP************
		node *swap(node *t)
		{
			node *p;
			if(t != NULL)
			{
				p = t->left;
				t->left = swap(t->right);
				t->right = swap(p);
			}
			return t;
		}
};

int main()
{
	BST T;
	node *root = T.create();
	T.inorder(root);
	cout<<endl;
	cout<<"********************************"<<endl;
	int ch;
	
	do
	{
		cout<<"1: Insert new node"<<endl;
		cout<<"2: Find number of nodes in longest path"<<endl;
		cout<<"3: Minimum data value found in a tree"<<endl;
		cout<<"4: Swap a tree"<<endl;
		cout<<"5: Search a value"<<endl;
		cout<<"6: Exit"<<endl;
		cout<<"Enter choice: ";
		cin>>ch;
		
		switch(ch)
		{
			case 1:
				int num;
				cout<<"Enter number: ";
				cin>>num;
				T.insert(root,num);
				T.inorder(root);
				cout<<endl;
				cout<<"********************************"<<endl;
				break;
				
			case 2:
				{
					int number = T.no_of_nodes(root)+1;
					cout<<"Number of nodes in longest path: "<<number;
					cout<<endl;
					cout<<"********************************"<<endl;
					break;
				}
			
			case 3:
				{
					node *p = T.minimum(root);
					cout<<"Minimum data: "<<p->data;
					cout<<endl;
					cout<<"********************************"<<endl;
					break;
				}
						
			case 4:
				{
					node *b = T.swap(root);
					T.inorder(b);
					cout<<endl;
					cout<<"********************************"<<endl;
					break;
				}
				
			case 5:
				{
					int x;
					cout<<"Enter number which is to searched:  ";
					cin>>x;
					node *a = T.search(root,x);
					if( a == NULL)
					{
						cout<<"Number is not found"<<endl;
					}
					else
					{
						cout<<a->data<<" is found"<<endl;
					}
					cout<<"********************************"<<endl;
					break;
				}
				
			case 6:
				break;				
			}
	}while(ch != 6); 
	return 0;
}

