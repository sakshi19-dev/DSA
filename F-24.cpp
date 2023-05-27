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
		int search(int id);
		int del(int id);
		void update();
		void display(int recno);
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
	for(int i=0;i<n;i++) // Block is assumed to contain 5 records
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
	
	for(int i=1;i<=n;i++)
	{
		mas.read((char*)&crec , sizeof(Employee));
		if(crec.status == 0)
		{
			cout<<"---Record("<<i<<")---"<<endl;
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
	for(int i=1;i<=n;i++)
	{
		ind.read((char*)&crec , sizeof(Index));
		cout<<i<<")"<<crec.id<<" "<<crec.recno<<endl;
	}
	ind.close();
}

int IndexSequential :: search(int id)
{
	Index indices[50];
	Employee rec1;
	Index crec;
	int n,recno;
	ind.open("indexfile.txt", ios::binary | ios::in);
	ind.seekg(0 ,ios::end);
	n = ind.tellg()/sizeof(Index);
	ind.seekg(0 , ios::beg);
	ind.read((char*)&indices , n*sizeof(Index));
	ind.close();
	
	if(n == 0 || id<indices[0].id)
	{
		return(-1);
	}
	
	for(int i=1 ;i<n && id>=indices[i].id ; i++)
	
	int recno = indices[i-1].recno;
	mas.open("master.txt" ,ios::binary | ios::in);
	mas.seekg(recno*sizeof(Employee) , ios::beg);
	for(int i=0;i<=1&&!mas.eof();i++,recno++)
	{
		mas.read((char*)&rec1 , sizeof(Employee));
		if(rec1.id == id && rec1.status == 0)
		{
			mas.close();
			return(recno);
		}
	}
}

int IndexSequential :: del(int id)
{
    Employee crec;
    int n,recno;
    recno = search(id);
    if(recno >=0)
    {
        cout<<"Record is found = "<<recno<<endl;
        mas.open("master.txt" , ios::binary | ios:: in | ios::out);
        mas.seekg(recno*sizeof(Employee) , ios::beg);
        mas.read((char*)&crec , sizeof(Employee));
        crec.status = 1;
        mas.seekp(recno*sizeof(Employee) , ios::beg);
        mas.write((char*)&crec , sizeof(Employee));
        mas.close();
    }
    else
    {
        cout<<"Record not found...."<<endl;
        return(0);
    }
    reindex();
    read();
    return(1);
}

void IndexSequential :: update()
{
    int id;
    Employee crec;
    cout<<"Enter the id of record to be updated: ";
    cin>>id;
    cout<<"Enter a new record(id,name,designation,salary) : ";
    cin>>crec.id>>crec.name>>crec.designation>>crec.salary;
    if(del(id))
        insert(crec);
    else
    {
        cout<<"Record is not found"<<endl;
    }
}

void IndexSequential :: display(int recno)
{
    Employee rec1;
    mas.open("master.txt" , ios::binary | ios::in);
    mas.seekg(recno*sizeof(Employee) , ios::beg);
    mas.read((char*)&rec1 , sizeof(Employee));;
    cout<<"----Record----"<<endl;
    cout<<rec1.id<<endl;
    cout<<rec1.name<<endl;
    cout<<rec1.designation<<endl;
    cout<<rec1.salary<<endl;
    mas.close();
}

int main()
{
	IndexSequential obj;
	int ch,id,recno;
	Employee rec1;
	do
	{
		cout<<"1: Insert"<<endl;
		cout<<"2: Read"<<endl;
		cout<<"3: Search"<<endl;
		cout<<"4: Delete"<<endl;
		cout<<"5: Update"<<endl;
		cout<<"6: Display"<<endl;
		cout<<"7: Exit"<<endl;
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
				
			case 3:
				cout<<"Enter id: ";
				cin>>id;
				recno = obj.search(id);
				if(recno >= 0)
				{
					cout<<"Found (record no: ) "<<recno<<endl;
				}
				else
					cout<<"Not found"<<endl;
				break;	
			
			case 4:
			    cout<<"Enter id: ";
			    cin>>id;
			    obj.del(id);
			    break;
			    
			case 5:
			    obj.update();
			    cout<<"****After updating a record****"<<endl;
			    obj.read();
			    break;
			    
			case 6:
			    cout<<"Enter record no: ";
			    cin>>recno;
			    obj.display(recno);
			    break;
		}
	}while(ch != 7);
	return 0;
}

