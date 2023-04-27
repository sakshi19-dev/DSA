#include<iostream>
#include<string.h>												
using namespace std;
struct node
{
	char k[100];
	char m[100];
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
//**************CREATE FUNCTION**************
		void create()
		{
			node *temp;
			char reply;
			do
			{
				temp = new node;
				cout<<"Enter keyword: ";
				cin>>temp->k;
				cout<<"Enter Meaning: ";
				cin>>temp->m;
				temp->left = NULL;
				temp->right = NULL;
				if(root == NULL)
				{
					root = temp;
				}
				else
				{
					insert(root,temp);
				}
				cout<<"Do you want add new keyword:(y/n) ";
				cin>>reply;
			}while(reply == 'y');
		}
	//**************INSERT FUNCTION**************
		void insert(node *root,node *temp)
		{
			if(strcmp(temp->k,root->k)<0)
			{
				if(root->left == NULL)
				{
					root->left = temp;
				}
				else
				{
					insert(root->left,temp);
				}
			}
			else
			{
				if(root->right== NULL)
				{
					root->right = temp;
				}
				else
				{
					insert(root->right,temp);
				}
			}
		}
		//*************DISPLAY FUNCTION**************
		void inorder(node *root)
		{
			if(root != NULL)
			{
				inorder(root->left);
				cout<<root->k<<" == "<<root->m<<endl;
				inorder(root->right);
			}
		}
		//**************SEARCH FUNCTION**************
		node *search(node *root,char k[100])
		{
			int count = 1;
			while(root != NULL)
			{
			count = count+1;			
			if(strcmp(k,root->k) == 0)
			{
				cout<<"No of comparison: "<<count<<endl;
				return (root);
			}
			if(strcmp(k,root->k)<0)
				return (search(root->left,k));
			if(strcmp(k,root->k)>0)
				return (search(root->right,k));
			}
		}
		//**************UPDATE FUNCTION**************
		node *update(node *root,char k[100])
		{
			while(root != NULL)
			{
				if(strcmp(root->k,k) == 0)
				{
					cout<<"Enter New meaning of "<<root->k<<" : ";
					cin>>root->m;
					return(root);
				}
				if(strcmp(k,root->k)<0)
					return (update(root->left,k));
				if(strcmp(k,root->k)>0)
					return (update(root->right,k));
			}
		}
	//**************DELETE FUNCTION**************
		node *del(node *root ,char k[100])
		{
			node *temp;
			if(root == NULL)
			{
				cout<<"Element not found"<<endl;
				return(root);
			}
			if(strcmp(k,root->k)<0)
			{
				root->left = del(root->left,k);
				return(root);
			}
			if(strcmp(k,root->k)>0)
			{
				root->right = del(root->right,k);
				return(root);
			}
			if(root->left == NULL && root->right == NULL)
			{
				temp = root;
				delete(temp);
				return(NULL);
			}
			if(root->left == NULL)
			{
				temp =root;
				root= root->right;
				delete(temp);
			}
			if(root->right == NULL)
			{
				temp =root;
				root= root->left;
				delete(temp);
			}
			temp = min(root->right);
			strcpy(root->k,temp->k);
			root->right = del(root->right,temp->k);
			return(root);
		}
		node *min(node *q)
		{
			while(q->left != NULL)
			{
				q = q->left;
			}
			return(q);
		}
};

int main()
{
	int ch;
	dict d;
	d.create();
	do
	{
		cout<<"1: Adding new keyword"<<endl;
		cout<<"2: Display"<<endl;
		cout<<"3: Search"<<endl;
		cout<<"4: Update"<<endl;
		cout<<"5: Delete"<<endl;
		cout<<"6: Exit"<<endl;
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
				char k[100];
				cout<<"Enter keyword: ";
				cin>>k;
				node *temp;
				temp = d.search(d.root,k);
				if(temp == NULL )
				{
					cout<<"Not found"<<endl;
				}	
				else
				{
					cout<<"Found"<<endl;
				}
				break;
				
			case 4:
				char ku[100];
				cout<<"Enter keyword: ";
				cin>>ku;
				node *tempu;
				tempu = d.update(d.root,ku);
				if(tempu == NULL)
				{
					cout<<"Not update"<<endl;
				}
				else
				{
					cout<<"Meaning updated"<<endl;
					cout<<"Dictionay after updating meaning"<<endl;
					d.inorder(d.root);
				}
				break;
				
			case 5:
				char kd[100];
				cout<<"Enter keyword which u want to delete: ";
				cin>>kd;
				d.root = d.del(d.root,kd);
				cout<<"Deleted"<<endl;
				cout<<"Dictionary after deleting "<<kd<<endl;
				d.inorder(d.root);
				break;
		}
	}while(ch != 6);
	return 0;
}

