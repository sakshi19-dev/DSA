#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

struct Employee
{
	int id;
	char name[100];
	char designation[100];
	int salary;
	int status;
};

struct Index
{
	int id;
	int recno;
};

class IndexSequential
{
	fstream mas;
	fstream ind;
	public:
		IndexSequential()
		{
			mas.open("master.txt" , ios::binary | ios::in);
			ind.open("indexfile.txt" , ios::binary | ios::in);
			if(mas.fail())
			{
				mas.open("master.txt" ,ios::binary | ios::out);
			}
			if(ind.fail())
			{
				ind.open("indexfile.txt" ,ios::binary | ios::out );
			}
			mas.close();
			ind.close();	
		}
		void insert(Employee rec1);
		void reindex() ;//Regenerate index file after adding record
		void read() ;// Read master file
		void readi(); //Read index file
};

void IndexSequential :: insert(Employee rec1)
{
	Employee crec;
	int n,i;
	mas.open("master.txt" , ios::in |ios::out | ios::binary);
	rec1.status = 0;
	mas.seekg(0 ,ios::end);
	n = mas.tellg()/sizeof(Employee);
	
	if(n == 0)
	{
		crec.status = 0;
		mas.write((char*)&rec1 , sizeof(Employee));
		mas.close();
		return ;
	}
	
	else
	{
		i = n-1;
		while(i>=0)
		{
			mas.seekg(i*sizeof(Employee) , ios::beg);
			mas.read((char*)&crec ,sizeof(Employee));
			if(crec.id > rec1.id)
			{
				mas.seekp((i+1)*sizeof(Employee) , ios::beg);
				mas.write((char*)&crec , sizeof(Employee));
			}
			else
				break;
			i = i-1;
		}
		i = i+1;
		mas.seekp(i*sizeof(Employee) , ios::beg);
		mas.write((char*)&rec1, sizeof(Employee));
	}
	mas.close();
	reindex();
}

void IndexSequential :: reindex()
{
	int id,n;
	Employee crec;
	Index rec1;
	
	ind.open("indexfile.txt" , ios::binary | ios::out | ios::trunc);
	mas.open("master.txt" , ios::binary | ios::in);
	
	mas.seekg(0,ios::end);
	n = mas.tellg() / sizeof(Employee);
	mas.seekg(0,ios::beg);
	for(int i=0;i<n;i+5) // Block is assumed to contain 5 records
	{
		mas.seekg(i*sizeof(Employee) ,ios::beg);
		mas.read((char*)&crec , sizeof(Employee));
		rec1.id = crec.id;
		rec1.recno = i;
		ind.write((char*)&rec1 , sizeof(Index));
	}
	mas.close();
	ind.close();
}

void IndexSequential :: read() 
{
	Employee crec;
	int n;
	cout<<"******DATA FILE*****"<<endl;
	mas.open("master.txt" ,ios::binary | ios::in);
	mas.seekg(0 , ios::end);
	n = mas.tellg() / sizeof(Employee);
	mas.seekg(0 ,ios::beg);
	
	for(int i=0;i<n;i++)
	{
		mas.read((char*)&crec , sizeof(Employee));
		if(crec.status == 0)
		{
			cout<<"---Record("<<i+1<<")---"<<endl;
			cout<<crec.id<<endl;
			cout<<crec.name<<endl;
			cout<<crec.designation<<endl;
			cout<<crec.salary<<endl;		
		}
		else
		{
			cout<<"*****Delteted*****"<<endl;
		}
	}
	mas.close();
}

void IndexSequential :: readi() 
{
	Index crec;
	int n ;
	cout<<"*****INDEX FILE****"<<endl;
	ind.open("indexfile.txt" , ios::binary | ios::in);
	ind.seekg(0,ios::end);
	n= ind.tellg()/sizeof(Index);
	ind.seekg(0,ios::beg);
	for(int i=0;i<n;i++)
	{
		ind.read((char*)&crec , sizeof(Index));
		cout<<i<<")"<<crec.id<<" "<<crec.recno<<endl;
	}
	ind.close();
}


int main()
{
	IndexSequential obj;
	int ch;
	Employee rec1;
	do
	{
		cout<<"1: Insert"<<endl;
		cout<<"2: Read"<<endl;
		cout<<"3: Exit"<<endl;
		cout<<"Enter choice: ";
		cin>>ch;
		switch(ch)
		{
			case 1:
				cout<<"Enter record to be inserted (id,name,desiganation,salary):";
				cin>>rec1.id>>rec1.name>>rec1.designation>>rec1.salary;
				obj.insert(rec1);
				break;
							
			case 2:
				obj.read();
				obj.readi();
				break;				
		}
	}while(ch != 3);
	return 0;
}

