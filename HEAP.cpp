#include<iostream>
using namespace std;

class heap
{
	int a[100],b[100];
	int n,x,m1;
	public:
		void create();
		void insert_max(int a[],int);		
		void downadjust_max(int a[],int);
		
		void insert_min(int b[],int);
		void downadjust_min(int b[],int);
		void display();
};

void heap :: create()
{
	cout<<"Enter the number of students: ";
	cin>>n;
	a[0] = 0;
	b[0] = 0;
	cout<<"Enter the marks: ";
	for(int i=0;i<n;i++)
	{
		cin>>x;
		insert_max(a,x);
		insert_min(b,x);
	}
}

void heap :: insert_max (int a[],int x)
{
	int m;
	m = a[0];
	a[m+1] = x;
	a[0] = m+1;
	for(int i=m/2;i>=1;i--)
	{
		downadjust_max(a,i);
	}
}

void heap :: downadjust_max(int a[], int i)
{
	int flag = 1;
	int n = a[0];
	while(2*i <= n && flag == 1)
	{
		int j = 2*i;
		if(j+1 <= n && a[j+1]>a[j])
			j = j+1;
		if(a[i] > a[j])
			flag = 0;
		else
		{
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			i = j;
		}
	}
}

void heap :: insert_min(int b[],int x)
{
	m1= b[0];
	b[m1+1] = x;
	b[0] = m1+1;
	for(int i=m1/2; i>=1;i--)
	{
		downadjust_min(b,i);
	}
}

void heap :: downadjust_min(int b[], int i)
{
	int flag = 1;
	int n = b[0];
	while(2*i <= n && flag == 1)
	{
		int j = 2*i;
		if(j+1 <= n && b[j+1]<b[j])
			j = j+1;
		if(b[i] < b[j])
			flag = 0;
		else
		{
			int temp = b[i];
			b[i] = b[j];
			b[j] = temp;
			i = j;
		}
	}
}

void heap :: display ()
{
	cout<<"Maximum marks: "<<a[1]<<endl;
	cout<<"Minimum marks: "<<b[1]<<endl;
}

int main()
{
	heap h;
	h.create();
	h.display();
	return 0;
}
