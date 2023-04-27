#include<iostream>
using namespace std;
struct node
{	
int data;
	node *next;
};

class Hashing 
{
	node* TelBook[10];
	int TelBook1[10];
	public:
		Hashing()
		{
			for(int i = 0 ;i <10;i++)
			{
				TelBook[i] = NULL;
			}
			
			for(int i =0 ;i<10;i++)
			{
				TelBook1[i] = 0;
			}
		}
		
		node *CreateNode(int x)
		{
			node *temp = new node();
			temp->data = x;
			temp->next = NULL;
			return temp;
		}
		
		
		/********************INSERT FUNCTION FOR SEPERATE CHAINING***************************/
		void insert1(int num)
		{
			int loc = num % 10;
			node *temp = new node;
			node *head = new node;

			head = CreateNode(num);
			temp = TelBook[loc];
			
			if(temp == NULL)
			{
				TelBook[loc] = head;
			}
			else
			{
				while(temp->next != NULL)
				{
					temp = temp->next;
				}
				temp->next = head;
			}
		}
		
		
	/********************DISPLAY FUNCTION FOR SEPERATE CHAINING***************************/
		void display1()
		{
			node *temp;
			for(int i = 0;i<10;i++)
			{
				node *temp = new node;
				temp = TelBook[i];
				cout<<"TelBook["<<i<<"] = ";
				if(temp == NULL)
				{
					cout<<"-----"<<endl;
				}
				else
				{
					while(temp != NULL)
					{
						cout<<temp->data<< "  ";
						temp = temp->next;
					}
					cout<<endl;
				}
			}
		}
		
		/********************SERACH FUNCTION FOR SEPERATE CHAINING***************************/
		void search1(int key)
		{
			int loc = key % 10;
			node *temp = TelBook[loc];
			int count =0;
			if(temp == NULL)
			{
				cout<<"Not found"<<endl;
				count = 1;	
			}	
			else
			{
				while(temp != NULL)
				{
					if(temp->data == key)
					{
						cout<<key<<" is found at loc "<<loc<<endl;
					}
					temp = temp->next;
					count = count +1;
				}
			}
			cout<<"No of comparison required to search "<<key<<" is: "<<count<<endl;
		}
		
		/****************************INSERT FUNCTION FOR LINEAR PROBING***************/
		void insert2(int num)
		{
			int loc = num % 10;
			int count = 0;
			if(TelBook1[loc] == 0 )
			{
				TelBook1[loc] = num;
			}
			else
			{
				int i = 0;
				while(i < 10)
				{
					loc = (loc+1) % 10;
					if(TelBook[loc] == 0)
					{
						TelBook1[loc] = num;
						break;
					}
					i =i+1;
					count = count+1;
				}
				
				if(count == 10)
				{
					cout<<"Telephone book list get full"<<endl;
				}
			}
		}
	
	/****************************SEARCH FUNCTION FOR LINEAR PROBING***************/	
		void search2(int key)
		{
			int loc = key % 10;
			int count = 0;
			if(TelBook1[loc] == key)
			{
				cout<<key<<" is found at loc "<<loc<<endl;
				count = count+1;
			}
			else
			{
				int i =0;
				while(i < 10)
				{
					loc = (loc+1)%10;
					if(TelBook1[loc] == key)
					{
						cout<<key<<" is found at loc "<<loc<<endl;
						break;
					}
				
					i = i+1;
					count += 1;
					
				}
			}
		}
		
		
		/****************************DISPLAY FUNCTION FOR LINEAR PROBING***************/
		void display2()
		{
			for(int i =0 ;i<10;i++)
			{
				cout<<"TelBook["<<i<<"] = "<<TelBook1[i]<<endl;
			}
		}
};

int main()
{
	Hashing h;
	int ch1,ch2,ch3;
	do
	{
		cout<<"1: Collision handled by using Sepaerate chainning:"<<endl;
		cout<<"2: Collision handled by using linerar probing without chaining:"<<endl;
		cout<<"3: Exit"<<endl;
		
		cout<<"*****************************************************"<<endl;
		
		cout<<"Enter choice :";
		cin>>ch1;
		
		switch(ch1)
		{
		case 1:
		do
		{
		cout<<"1: Insert :"<<endl;
		cout<<"2: Search :"<<endl;
		cout<<"3: Display : "<<endl;
		cout<<"4: Exit"<<endl;
		
		cout<<"*****************************************************"<<endl;
		
		cout<<"Enter choice : ";
		cin>>ch2;
		
		switch(ch2)
		{
			case 1: 
			int TelNo;
			cout<<"Enter Telephone Number which is to be insreted: ";
			cin>>TelNo;
			h.insert1(TelNo);
			break;
			
			case 2:
			int key;
			cout<<"Enter Telephone nuumber which is to be searched: ";
			cin>>key;
			h.search1(key);
			break;
			
			case 3:
			cout<<"*****************************************************"<<endl;
			h.display1();
			cout<<"*****************************************************"<<endl;
			break;
			
			case 4:
			exit;
			break;
		}
		}
		while(ch2 != 4);
		break;
		
		case 2:
		do
		{
			cout<<"1: Insert"<<endl;
			cout<<"2: display"<<endl;
			cout<<"3: Search"<<endl;
			cout<<"4: Exit"<<endl;
			
			cout<<"*****************************************************"<<endl;
			
			cout<<"Enter choice: ";
			cin>>ch3;
			
			cout<<"*****************************************************"<<endl;
			
			switch(ch3)
			{
				case 1:
				int TelNo;
				cout<<"Enter Telephone number which is to be inserted: ";
				cin>>TelNo;
				h.insert2(TelNo);
				break;
				
				case 2:
				cout<<"*****************************************************"<<endl;
				h.display2();
				cout<<"*****************************************************"<<endl;
				break;
				
				case 3:
				int key;
				cout<<"Enter TelNo which is to be searched: ";
				cin>>key;
				cout<<"*****************************************************"<<endl;
				h.search2(key);
				break;
				
				case 4:
				break;
			}
		}
		while(ch3 != 4);
		}
	}while(ch1 != 3);
return 0;
}

