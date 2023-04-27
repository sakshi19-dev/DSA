
#include<iostream>
using namespace std;
class Set
{
	int setA[10];
	int setB[10];
	int setU[10];
	int setD[10];
	int n,m,ele;
	char c;
		
	public:
		Set()
		{
			for(int i=0;i<10;i++)
			{
				setA[i]=-1;
				setB[i]=-1;
				setU[i]=-1;
			}
		}
				//******CREATE FUNCTION****//
		void create()
		{
			cout<<"*********SET A*************"<<endl;
			cout<<"Enter how many element do you want to insert in set A : ";
			cin>>n;
			
			cout<<"Enter Numbers: "<<endl;
			cout<<"(Enter unique number always)"<<endl;
			for(int i=1;i<=n;i++)
			{
				cin>>setA[i];
			}
			
			cout<<"*********SET B*************"<<endl;
			cout<<"Enter how many element do you want to insert in set B: ";
			cin>>m;
			
			cout<<"Enter Numbers: "<<endl;
			cout<<"(Enter unique number always)"<<endl;
			for(int i=1;i<=m;i++)
			{
				cin>>setB[i];
			}
		}
				//******DISPLAY FUNCTION****//
		void display()
		{
			cout<<"***********************"<<endl;
			cout<<"SET A = {";
			for(int i=1;i<=n;i++)
			{
				cout<<setA[i]<<" ";
			}
			cout<<"}"<<endl;
			
			cout<<"SET B = {";
			for(int i=1;i<=m;i++)
			{
				cout<<setB[i]<<" ";
			}
			cout<<"}"<<endl;
			cout<<"*************************"<<endl;
		}
				//******CONTAIN FUNCTION****//
		bool containA()
		{
			cout<<"Enter element: ";
			cin>>ele;
			for(int i=0;i<n;i++)
			{
				if(setA[i]==ele)
				{
					return true;
				}
			}
			return false;
		}
		
		bool containB()
		{
			cout<<"Enter element: ";
			cin>>ele;
			for(int i=0;i<m;i++)
			{
				if(setB[i]==ele)
				{
					return true;
				}
			}
			return false;
		}
				//******ADD ELEMENT FUNCTION****//
		void Add()
		{
			cout<<"********************"<<endl;
			cout<<"Enter set: ";
			cin>>c;
			
			if(c=='a' || c=='A')
			{
				if(containA())
				{
					cout<<"Not inserted because "<<ele<<" is already present"<<endl;
				}
				else
				{
					int pos;
					cout<<"Enter position: ";
					cin>>pos;
					
					n = n+1;
					if(pos == n+1)
					{
						setA[pos]=ele;
					}
					else
					{
						for(int i=n;i>=pos;i--)
						{
							setA[i]=setA[i-1];
						}
						setA[pos]=ele;
					}
				}
			}
			
			if(c=='b' || c=='B')
			{
				if(containB())
				{
					cout<<"Not inserted because "<<ele<<" is already present"<<endl;
				}
				else
				{
					int pos;
					cout<<"Enter position: ";
					cin>>pos;
					
					m = m+1;
					if(pos == m+1)
					{
						setB[pos]=ele;
					}
					else
					{
						for(int i=m;i>=pos;i--)
						{
							setB[i]=setB[i-1];
						}
						setB[pos]=ele;
					}
				}
			}
			display();
		}
				//******REMOVE ELEMENT FUNCTION****//	
		void remove()
		{
			cout<<"***************"<<endl;
			cout<<"Enter Set: ";
			cin>>c;
			
			cout<<"Enter element: ";
			cin>>ele;
			
			if(c=='a' || c=='A')
			{
			int i;
			for( i=1;i<=n;i++)
			{
				if(setA[i]==ele)
				{
					break;
				}
			}
			
			if(i<=n)
			{
				for(int j=i;j<n;j++)
				{
					setA[j]=setA[j+1];
				}
				n = n-1;
			}
			else
			{
				cout<<ele<<" is not present"<<endl;
			}
		}
		
		if(c=='b' || c=='B')
		{
			int i;
			for(i=0;i<m;i++)
			{
				if(setB[i]==ele)
				{
					break;
				}
			}
			if(i<=m)
			{
				for(int j=i;j<m;j++)
				{
					setB[j]=setB[j+1];
				}
				m = m-1;
			}
			else
			{
				cout<<ele<<" is not present"<<endl;
			}
		}
		display();
	}
			//******SIZE FUNCTION****//
	void size()
	{
		cout<<"***************"<<endl;
		int count=0;
		cout<<"Enter set: ";
		cin>>c;
		if(c=='a' || c=='A')
		{
		for(int i=0;i<10;i++)
		{
			if(setA[i] != -1)
			{
				count = count+1;
			}
		}
		cout<<"Size of SET A = "<<count<<endl;
		}
		
		if(c=='b' || c=='B')
		{
		for(int i=0;i<10;i++)
		{
			if(setB[i] != -1)
			{
				count = count+1;
			}
		}
		cout<<"Size of SET B = "<<count<<endl;
		}
		cout<<"***************"<<endl;
	}
			//******UNION FUNCTION****//
	void Union()
	{
		cout<<"***************"<<endl;
		for(int i=1;i<=n;i++)
		{
			setU[i] = setA[i];
		}
		
		for(int j=1;j<=m;j++)
		{
			setU[n+j] = setB[j];
		}
		
		cout<<"Union: {";
		for(int i=1;i<=(n+m);i++)
		{
			int k=0;
			for(int j=i+1;j<=(n+m);j++)
			{
				if(setU[i] == setU[j])
				{
					k=1;
					break;
				}
			}
			if(k==0)
			{
				cout<<setU[i]<<" ";
			}
		}
		cout<<"}"<<endl;
		cout<<"***************"<<endl;
	}
			//******INTERSECTION FUNCTION****//
	void intersection()
	{
		cout<<"***************"<<endl;
		cout<<"Intersection: {";
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(setA[i] == setB[j])
				{
					cout<<setA[i]<<" ";
				}
			}
		}
		cout<<"}"<<endl;
		cout<<"***************"<<endl;
	}
			//******DIFFERNCE FUNCTION****//
	void Difference()
	{
		cout<<"***************"<<endl;
		int choice;
		do
		{
			cout<<"1: A-B"<<endl;
			cout<<"2: B-A"<<endl;
			cout<<"3: Exit"<<endl;
			
			cout<<"Enter choice :";
			cin>>choice;
			
			switch(choice)
			{
				case 1:
					for(int i=1;i<=n;i++)
					{
						setD[i] = setA[i];	
					}
		
					cout<<"Difference(A-B): {";
					for(int i =1;i<=n;i++)
					{
						int k=0;
						for(int j=1;j<=m;j++)
						{
							if(setD[i] == setB[j])
							{
								k=1;
								break;
							}
						}
					if(k==0)
					{
						cout<<setD[i]<<" ";
					}
					}
					cout<<"}"<<endl;
					break;
					
					case 2:
					for(int i=1;i<=m;i++)
					{
						setD[i] = setB[i];	
					}
		
					cout<<"Difference(B-A): {";
					for(int i =1;i<=m;i++)
					{
						int k=0;
						for(int j=1;j<=n;j++)
						{
							if(setD[i] == setA[j])
							{
								k=1;
								break;
							}
						}
			
					if(k==0)
					{
						cout<<setD[i]<<" ";
					}
					}
					cout<<"}"<<endl;
					break;
					
					case 3:
						break;	
			}	
		}	while(choice != 3);
		cout<<"***************"<<endl;
	}
			//******SUBSET FUNCTION****//
	bool Subset()
	{
		cout<<"***************"<<endl;
		int j;
		for(int i=0;i<m;i++)
		{
		for( j=0;j<n;j++)
		{
			if(setB[i] == setA[j])
				break;
		}
		if(j == n)
		{
			return 0;
		}
		}
		cout<<"***************"<<endl;
		return 1;	
	}
};

int main()
{
	Set s;
	int ch;
	do
	{
		cout<<"1: Create"<<endl;
		cout<<"2: Display"<<endl;
		cout<<"3: Add"<<endl;
		cout<<"4: Remove"<<endl;
		cout<<"5: Size"<<endl;
		cout<<"6: Intersection"<<endl;
		cout<<"7: Union"<<endl;
		cout<<"8: Difference"<<endl;
		cout<<"9: Subset"<<endl;
		cout<<"10: Exit"<<endl;
		
		cout<<"Enter choice: ";
		cin>>ch;
		
		switch(ch)
		{
			case 1:
				s.create();
				break;
				
			case 2:
				s.display();
				break;
				
			case 3:
				s.Add();
				break;
				
			case 4:
				s.remove();
				break;
				
			case 5:
				s.size();
				break;
				
			case 6:
				s.intersection();
				break;
				
			case 7:
				s.Union();
				break;
				
			case 8:
				s.Difference();
				break;
				
			case 9:
				if(s.Subset())
				{
					cout<<"Yes !!! B is not a subset of A"<<endl;
				}
				else
				{
					cout<<"No !!! B is not a subset of A"<<endl;
				}
				break;
				
			case 10:
				break;
		}
	}while(ch != 10);
	return 0;
}

