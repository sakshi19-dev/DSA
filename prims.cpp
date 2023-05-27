#include<iostream>
using namespace std;
class graph
{
	int n,m,u,v,c;
	int adj[100][100],final[100][100];
	int visited[100],dist[100],from[100];
	public:	
		
		void create()
		{
			cout<<"Enter no. of vertices: ";
			cin>>n;
			for(int i =0;i<n;i++)
			{
				visited[i] = 0;
				for(int j=0 ;j<n; j++)
				{
					adj[i][j] = 0;
				}
			}
			cout<<"Enter no. of edges: ";
			cin>>m;
			for(int i=0;i<m;i++)
			{
				cout<<"Enter Edge: "<<endl;
				cout<<"From :";
				cin>>u;
				cout<<"To : ";
				cin>>v;
				cout<<"Enter Cost: ";
				cin>>c;
				adj[u][v] = adj[v][u] = c;
			}
		}
		
		void display()
		{
			for(int i=0;i<n;i++)
			{
				for(int j =0;j<n;j++)
				{
					cout<<adj[i][j]<<" ";
				}
				cout<<endl;
			}
		}
		
		void prims()
		{
			int total =0;
			int cost[100][100];
			
			//1) converting input matrix to cost matrix:-
			for(int i=0;i<n;i++)
			{
				for(int j =0;j<n;j++)
				{
					if(adj[i][j] == 0)
					{
						cost[i][j] = 100;
					}
					else
					{
						cost[i][j] = adj[i][j];
					}
				}
			}
			
			//initial vertex is taken as zero:-
			visited[0] = 1;
			
			//2)initialized disatnce ,visited and from array:-
			for(int i=1;i<n;i++)
			{
				visited[i] = 0;
				dist[i] = cost [0][i];
				from [i] =0;
			}
			m = n-1;
			while(m>=0)
			{
				int min = 100;
				for(int i=1;i<n;i++)
				{
					if(visited[i] == 0 && min>dist[i])
					{
						min = dist[i];
						v = i;
					}
				}
					u = from[v];
					final[u][v] = cost[u][v];
					final[v][u] = cost[v][u];				
				m--;
				total = total+final[u][v];
				visited[v] = 1;
			}
			
			//3)update from and distance array:-			
			for(int i=1;i<n;i++)
			{
				if(dist[i] > cost[v][i] && visited[i] == 0)
				{
					dist[i] = cost[v][i];
					from[i] = v;
				}
			}
			cout<<"Total cost: "<<total<<endl;
		}
};

int main()
{
	graph g;
	int ch;
	do
	{
		cout<<"1: Create a graph: "<<endl;
		cout<<"2: Display Graph using adjancy matrix: "<<endl;
		cout<<"3: Find Minimum total cost(PRIM'S ALGORITHM'): "<<endl;
		cout<<"4: Exit: "<<endl;
		cout<<"Enter choice: ";
		cin>>ch;
		switch(ch)
		{
			case 1:
				g.create();
				break;
			case 2:
				g.display();
				break;
			case 3:
				g.prims();
				break;
		}
	}
	while(ch != 4);
	return 0;
}

