#include<iostream>
using namespace std;

struct node
{
	int data;
	node *next;
};

//CLASS STACK (FOR DFS TRAVERSAL)
class Stack
{
	int top,a[100];
	public:
		Stack()
		{
			top = -1 ;
		}
		void push(int x)
		{
			top++;
			a[top] = x;
		}
		int pop()
		{
			int x = a[top];
			top--;
			return(x);
		}
		int empty()
		{
			if(top == -1)
				return 1;
			else
				return 0;
		}
		int Top()
		{
			int x;
			x = a[top];
			return x;
		}
};

//CLASS QUEUE (FOR BFS TRAVERSAL)
class queue
{
	int r,f,b[100];
	public:
		queue()
		{
			r = f =-1;
		}
		
		void insert(int x)
		{
			if(r ==-1 && f == -1)
			{
				r=f=0;
				b[r] = x;
			}
			else
			{
				r++;
				b[r] = x;
			}
		}
		
		int del()
		{
			int x = b[f];
			if(r == f)
			{
				r = f =-1;
			}
			else
			{
				f++;
			}
		}
		int empty()		
		{
			if(r==-1 && f==-1)
				return 1;
			else
				return 0;
		}
		int front()
		{
			int x;
			x = b[f];
			return x;
		}
		
};

class Graph
{
	int n,e;
	int adj_matrix[100][100],visited[10];
	node *G[20];
	int n1,e1,src,des;
	public:
		
		Graph()
		{
			for(int i=1;i<=n;i++)
			{
				for(int j=1;j<=n;j++)
				{
					adj_matrix[i][j] = 0;
				}
			}
		}
		
	void create_mat()
	{
		cout<<"Enter no of vertices: ";
		cin>>n;
		
		cout<<"Enter no of edges: ";
		cin>>e;
		
		for(int i=0;i<e;i++)
		{
			int u,v;
			cout<<"Enter the vertices for edge "<<i+1<<" : ";
			cin>>u>>v;
			adj_matrix[u][v] = 1;
			adj_matrix[v][u] = 1;
		}
	}
	
	void display_mat()
	{
		for(int i=1;i<=n;i++)
			{
				for(int j=1;j<=n;j++)
				{
					cout<<adj_matrix[i][j]<<" ";
				}
				cout<<endl;
			}
	}
	
	void BFS_matrix(int start)
	{
		queue q;
		for(int i=1;i<=n;i++)
		{
			visited[i] = 0;
		}
		int i;
		q.insert(start);
		visited[start] = 1;
		while(!q.empty())
		{
			int a;
			a = q.front();
			cout<<a<<" ";
			q.del();
			for(int i=1;i<=n;i++)
			{
				if(adj_matrix[a][i] == 1 && visited[i] == 0 )
				{
					visited[i] = 1;
					q.insert(i);
				}
			}
		}
	}
	
	void DFS_matrix(int start)
	{
		Stack s;
		for(int i=1;i<=n;i++)
		{
			visited[i] = 0;
		}
		s.push(start);
		visited[start] = 1;
		
		while(!s.empty())
		{
			int a;
			a = s.Top();
			cout<<a<<" ";
			s.pop();
			for(int i=1;i<=n;i++)
			{
				if(adj_matrix[a][i] == 1 && visited[i] == 0)
				{
					s.push(i);
					visited[i] = 1;
				}
			}
		}
	}
	
	void create_list()
		{
			cout<<"Enter number of vertices: ";
			cin>>n1;
			
			for(int i=1;i<=n1;i++)
			{
				G[i] = NULL;
			}
			cout<<"Enter number of edge: ";
			cin>>e1;
			for(int i=1;i<=e1;i++)
			{
				cout<<"Enter vertices for edge "<<i<<" : ";
				cin>>src>>des;
				add_edge(src,des);
				add_edge(des,src);
			}
		}
		
		void add_edge(int src,int des)
		{
			node *p,*q;
			q = new node;
			q->data = des;
			q->next = NULL;
			
			if(G[src] == NULL)
			{
				G[src] = q;
			}
			else
			{
				p = G[src];
				while(p->next != NULL)
				{
					p = p->next;
				}
				p->next = q;
			}
		}
		
		void print_list()
		{
			for(int i=1;i<=n1;i++)
			{
				cout<<"Adjancy list of vertex "<<i<<" : ";
				node *cur = G[i];
				while(cur != NULL)
				{
					cout<<cur->data<<"  ";
					cur = cur->next;
				}
				cout<<endl;
			}
		}
		
		void BFS_list(int start)
		{
			queue q1;
			for(int i=1;i<=n1;i++)
			{
				visited[i] = 0;
			}
			
			q1.insert(start);
			visited[start] = 1;
			
			while(!q1.empty())
			{
				int a = q1.front();
				cout<<a<<" ";
				q1.del();
				node *p = G[a];
				while(p != NULL)
				{
					int w = p->data;
					if(visited[w] == 0)
					{
						visited[w] = 1;
						q1.insert(w);
					}
					p = p->next;
				}
			}
		}
		
		void DFS_list(int start)
		{
			Stack s1;
			for(int i=1;i<=n1;i++)
			{
				visited[i] = 0;
			}
			s1.push(start);
			visited[start] = 1;
			while(!s1.empty())
			{
				int a = s1.Top();
				cout<<a<<" ";
				s1.pop();
				node *p = G[a];
				while(p != NULL)
				{
					int w = p->data;
					if(visited[w] == 0)
					{
						s1.push(w);
						visited[w] = 1;
					}
					p = p->next;
				}
			}
		}
};

int main()
{
	Graph g;
	int ch,ch1,ch2;
	int start;
	
	do
	{
		cout<<"1: Using adjancy matrix"<<endl;
		cout<<"2: Using adjancy list"<<endl;
		cout<<"3: Exit"<<endl;
		cout<<"Enter choice: ";
		cin>>ch;
		switch(ch)
		{
			case 1:
				cout<<"**********Using adjancy matrix**********"<<endl;
				g.create_mat();
				g.display_mat();
				do
				{
					cout<<"1: BFS traversal"<<endl;
					cout<<"2: DFS traversal"<<endl;
					cout<<"3: Exit"<<endl;
					cout<<"Enter choice: ";
					cin>>ch1;
					switch(ch1)
					{
						case 1:
							cout<<"BFS traversal: ";
							cout<<"Enter starting vertex: ";
							cin>>start;
							g.BFS_matrix(start);
							cout<<endl;
							break;
						
						case 2:
							cout<<"DFS traversal: ";
							cout<<"Enter starting vertex: ";
							cin>>start;
							g.DFS_matrix(start);
							cout<<endl;
							break;
					}
				}while(ch1 != 3);
				break;
				
			case 2:
				cout<<"**********Using adjancy list**********"<<endl;
				g.create_list();
				g.print_list();
				do
				{
					cout<<"1: BFS traversal"<<endl;
					cout<<"2: DFS traversal"<<endl;
					cout<<"3: Exit"<<endl;
					cout<<"Enter choice: ";
					cin>>ch2;
					switch(ch2)
					{
						case 1:
							cout<<"BFS traversal: ";
							cout<<"Enter starting vertex: ";
							cin>>start;
							g.BFS_list(start);
							cout<<endl;
							break;
							
						case 2:
							cout<<"DFS traversal: ";
							cout<<"Enter starting vertex: ";
							cin>>start;
							g.DFS_list(start);
							cout<<endl;
							break;
					}
				}while(ch2 != 3);
				break;
		}
	}
	while(ch != 3);
	return 0;
}
