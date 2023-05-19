#include<iostream>
using namespace std;

float p[10],q[10];   //p for successful and q for failure
float c[10][10],w[10][10];
int r[10][10];
int n;
string key[10];

void OBST()
{	
	//1)Initialize c,r and w matrix
	for(int i = 0;i<n;i++)
	{
		c[i][i] = 0;
		r[i][i] = 0;
		w[i][i] = q[i];
		
		//if j-i=1 means j=i+1
		c[i][i+1] = q[i]+q[i+1]+p[i+1];
		r[i][i+1] = i+1;
		w[i][i+1] = q[i]+q[i+1]+p[i+1];
	}
	
	//2)Initialize last value of matrix(at [n][n]):-
	c[n][n] = 0;
	r[n][n] = 0;
	w[n][n] = q[n];
	
	//3)//for j-i = 2,3,4,....
	for(int i=2;i<=n;i++)
	{
		for(int j=0;j<=n;j++)
		{
			w[j][j+i] = p[j+i]+q[j+i]+w[j][j+i-1];
			c[j][j+i] = 1000;
			
			for(int l=j+1; l<=j+i ;l++)
			{
				if(c[j][j+i] >(c[j][l-1]+c[l][j+1]))
				{
					c[j][j+i] = c[j][l-1]+c[l][j+1];
					r[j][j+i] = l;
				}
			}
			c[j][j+i] = c[j][j+1] + w[j][j+i];
		}
		cout<<endl;
	}
	int root=r[0][n];
	cout<<"Optimal binary search tree: ";
	cout<<"Root :"<<key[root]<<endl;
	cout<<"Cost: "<<c[0][n]<<endl;
	
}

//Print function:-
void print(int i,int j)
{
	if(i<j)
	cout<<key[r[i][j]]<<endl;
	else
	return;
	print(i,r[i][j]-1);
	print(r[i][j],j);
}

int main()
{
	//1)Enter Keys:-
	cout<<"Enter number of keys: ";
	cin>>n;
	cout<<"Enter keys: "<<endl;
	for(int i=1;i<=n;i++)
	{
		cout<<"Key No: "<<i<<endl;
		cin>>key[i];
	}
	
	//2)Enter the probabilility of successful search:-
	cout<<"Enter the probabilility of successful search: "<<endl;
	for(int i=1;i<=n;i++)
	{
		cout<<"p["<<i<<"] : ";
		cin>>p[i];
	}
	
	//3)Enter the probabilility of failure search:-
	cout<<"Enter the probabilility of failure search: "<<endl;
	for(int i=0;i<=n;i++)     //1 more than number of nodes hence,for loop starts from "0"
	{
		cout<<"q["<<i<<"] : ";
		cin>>q[i];
	}
	
	//4) Call OBST function:-
	OBST();
	
	//5)call Print function:-
	cout<<"Preorder: "<<endl;
	print(0,n);
	return 0;
}
