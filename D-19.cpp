/* AVL TREE */
#include<iostream>
#include<string.h>
using namespace std;

struct node
{
	char k[100];
	char m[100];
	int height;
	node *left;
	node *right;
};

class dict
{
	public:
	    node *root;
		dict()
		{
			root = NULL;
		}
		
		void create()
		{
			node *temp;
			char reply;
			do
			{
				temp = new node;
				cout<<"Enter Keyword: ";
				cin>>temp->k;
				cout<<"Enter Meaning: ";
				cin>>temp->m;
				temp->left = NULL;
				temp->right = NULL;				
				root = insert(root,temp);
				cout<<"Do you want to add new keyword(y/n): ";
				cin>>reply;
			}
			while(reply == 'y' || reply == 'Y');
		}

		node *insert(node *cur , node *temp)
		{
			if(cur == NULL)
			{
				return temp;
			}
			if(strcmp(temp->k,cur->k) < 0)
			{
				cur->left = insert(cur->left,temp);
			
			if(BF(cur) == 2)
			{
				if(strcmp(temp->k,(cur->left)->k) < 0)
				{
					cur = LL(cur);
				}
				else
				{
					cur = LR(cur);
				}
			}
			return cur;	
			}
						
			
			if(strcmp(temp->k,cur->k) > 0)
			{
				cur->right = insert(cur->right,temp);	
				if(BF(cur) == -2)
				{
					if(strcmp(temp->k,(cur->right)->k) > 0)
					{
						cur = RR(cur);
					}
					else
					{
						cur = RL(cur);
					}
				}
				return cur;
			}
		}
		
		node *RR(node *t)
		{
			t = rotateleft(t);
			return(t);
		}
		
		node *LL(node *t)
		{
			t = rotateright(t);
			return(t);
		}
		
		node *LR(node *t)
		{
			t->left = rotateleft(t->left);
			t = rotateright(t);
			return(t);
		}
		
		node *RL(node *t)
		{
			t->right = rotateright(t->right);
			t = rotateleft(t);
			return(t);
		}
		
		node *rotateleft(node *t)
		{
			node *y;
			y = t->right;
			t->right = y->left;
			y->left = t;
			y->height = height(y);
			t->height = height(t);
			return(y);
		}
		
		node *rotateright(node *t)
		{
			node *y;
			y = t->left;
			t->left = y->right;
			y->right = t;
			y->height = height(y);
			t->height = height(t);
			return(y);
		}
		
		int height(node *t)
		{
			if(t == NULL)
			{
				return 0;
			}
			if(t->left == NULL && t->right == NULL)
			{
				return 0;
			}
			int hl = 1+height(t->left);
			int hr = 1+height(t->right);
			if(hl > hr)
			{
				return hl;
			}
			else
			{
				return hr;
			}
		}
		
		int BF(node *t)
		{
			if(t == NULL)
			{
				return 0;
			}
			if(t->left == NULL && t->right == NULL)
			{
				return 0;
			}
			int hl = 1+height(t->left);
			int hr = 1+height(t->right);
			return (hl-hr);
		}
		
		void inorder(node *t)
		{
			if(t != NULL)
			{
				inorder(t->left);
				cout<<t->k<<" : "<<t->m<<endl;
				inorder(t->right);
			}
		}
		
		//SEARCH FUNCTION:-
		node *search(node *root,char k[100])
		{
			int count = 0;
			while (root != NULL)
			{
				count = count +1;
				if(strcmp(k,root->k) == 0)
				{
					cout<<"No of comparison: "<<count<<endl;
					return(root);
				}
				
				if(strcmp(k,root->k) < 0)
				{
					return(search(root->left,k));
				}
				
				if(strcmp(k,root->k) > 0)
				{
					return(search(root->right,k));
				}
			}
		}
		
		//UPADATE FUNCTION
		node *update(node *root,char k[100])
		{
			while(root != NULL)
			{
				if(strcmp(k,root->k) == 0)
				{
					cout<<"Enter New meaning of "<<root->k<<" : ";
					cin>>root->m;
					return(root);
				}
				
				if(strcmp(k,root->k) < 0)
				{
					return(update(root->left,k));
				}
				
				if(strcmp(k,root->k) > 0)
				{
					return(update(root->right,k));
				}				
			}
		}
		
		//DELETE FUNCTION:-
		node *del(node *root,char key[100])
		{
			node *temp;
			if(root == NULL)
			{
				cout<<"Element not found "<<endl;
				return(NULL);
			}
			
			else if (strcmp(key,root->k) < 0)
				{
					root ->left = del(root->left,key);
					if(BF(root) == -2)
					{
						if(BF(root->right) <= 0)
						{
							root = RR(root);
						}
						else
						{
							root = RL(root);
						}
					}
				}
			
			else if(strcmp(key,root->k) > 0)
			{
				root->right = del(root->right,key);
				if(BF(root) == -2)
				{
					if(BF(root->left)>=0)
					{
						root = LL(root);
					}
					else
					{
						root = LR(root);
					}
				}
			}
			
			else
			{
				if(root->left == NULL && root->right == NULL)
				{
					temp = root;
					delete(temp);
					return (NULL);
				}
				
				if(root->right == NULL)
				{
					temp = root;
					root = temp->left;
					delete(temp);
				}
				
				if(root->left == NULL)
				{
					temp = root;
					root = temp->right;
					delete(temp);
				}
				
				temp = min(root->right);
				strcpy(root->k,temp->k);
				root->right = del(root->right,temp->k);
				return(root);
				
			}
			root->height = height(root);
			return(root);
	}
	
	node *min(node *q)
	{
		while(q->left != NULL)
		{
			q = q->left;
		}
		return (q);
	}
};

int main()
{
	dict d;
	d.create();
	int ch;
	do
	{
		cout<<"1:Adding new keyword"<<endl;
		cout<<"2:Display"<<endl;
		cout<<"3:Search"<<endl;
		cout<<"4:Update"<<endl;
		cout<<"5:Delete"<<endl;
		cout<<"6:Exit"<<endl;
		cout<<"Enter choice: ";
		cin>>ch;
		
		switch(ch)
		{
			case 1:
				d.create();
				break;
				
			case 2:
				d.inorder(d.root);
				break;
				
			case 3:
				char key[100];
				cout<<"Enter keyword: ";
				cin>>key;
				node *temp;
				temp = d.search(d.root,key);
				if(temp == NULL)
				{
					cout<<"Not found"<<endl;
				}
				else
				{
					cout<<"Found"<<endl;
				}
				break;
				
			case 4:
				char k[100];
				cout<<"Enter Keyword: ";
				cin>>k;
				node *t;
				t = d.update(d.root,k);
				if(t == NULL)
				{
					cout<<"Not update"<<endl;
				}
				else
				{
					cout<<"Meaning Updated"<<endl;
					cout<<"Dictionary after updating meaning"<<endl;
					d.inorder(d.root);
				}
				break;
				
			case 5:
				char kd[100];
				cout<<"Enter keyword: ";
				cin>>kd;
				d.root = d.del(d.root,kd);
				cout<<"Deleted"<<endl;
				cout<<"Dictionary after deleting "<<kd<<endl;
				d.inorder(d.root);
				break;
		}
	}while (ch != 6);
	return 0;
}

