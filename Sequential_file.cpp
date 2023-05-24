#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

struct Student
{
	int roll_no;
	char name[100];
	float marks;
	int status;
};

class Sequential
{
	public:
		fstream f;
		Sequential()
		{
			f.open("file.txt", ios::binary | ios::in);
			if(f.fail())
			{
				f.open("file.txt", ios::binary | ios::out);
			}
			f.close();
		}
		
		
		void insert(Student rec1);
		void read(); 
		void del(int rollno);
		void update();
};

void Sequential :: insert(Student rec1)
{
	Student crec;
	int n,i;
	f.open("file.txt" , ios::in | ios::out);
	rec1.status = 1;
	f.seekg(0 , ios::end);
	n = f.tellg()/sizeof(Student);
	cout<<n<<endl;
	if(n == 0)
	{
		rec1.status = 1;
		f.write((char*)&rec1 , sizeof(Student));
		f.close();
		return;
	}
	else
	{
		i = n-1;
	while(i>=0)
	{
		f.seekg(i*sizeof(Student) ,ios::beg);
		f.read((char*)&crec,sizeof(Student));
		if(crec.roll_no > rec1.roll_no)
		{
			f.seekp((i+1)*sizeof(Student) ,ios::beg);
			f.write((char*)&crec , sizeof(Student));
		}
		else
			break;
		i--;
	}
	i++;
	f.seekp(i*sizeof(Student) ,ios::beg);
	f.write((char*)&rec1 ,sizeof(Student));
	f.close();
	}
	cout<<"Status: "<<rec1.status<<endl;
	
}

void Sequential :: read()
{
	Student crec;
	int n;
	cout<<"******Data File******"<<endl;
	f.open("file.txt" , ios::binary | ios::in);
	f.seekg(0,ios::end);
	n = f.tellg()/sizeof(Student);
	f.seekg(0,ios::beg);
	
	for(int i=1;i<=n;i++)
	{
		f.read((char*)&crec , sizeof(Student));
		if(crec.status == 1)
		{
			cout<<"---Rec (1)---"<<endl;
			cout<<crec.roll_no<<endl;
			cout<<crec.name<<endl;
			cout<<crec.marks<<endl;
			cout<<"--------------"<<endl;
		}
		else
		{
			cout<<"*****Deleted*****"<<endl;
		}
	}
	f.close();
}

void Sequential :: del(int rollno)
{
	Student crec;
	int i,n;
	f.open(f.open("file.txt" , ios::in | ios::out);
	f.seekg(0 ,ios::end);
	n = f.tellg()/sizeof(Student);
	f.seekg(0,ios::beg);
	
	for(int i=0;i<n;i++)
	{
		if(crec.roll_no == rollno)
		{
			crec.status = 1;
			f.seekp(i*sizeof(Student) ,ios::beg);
			f.write((char*)&crec , sizeof(Student));
			f.close();
			return 1;
		}
	}
	return 0;
}

void Sequential :: update()
{
	int rollno;
	Student rec1;
	cout<<"Enter the roll_no of record to be updated: ";
	cin>>roll_no;
	cout<<"Enter New record(rollno , name , marks): ";
	cin>>rec1.roll_no>>rec1.name>>rec1.marks;
	if(Del(rec1))
		insert(rec1);
	else
		cout<<"Record not found"<<endl;
}

int main()
{
	Sequential s;
	Student rec;
	int ch;
	do
	{
		cout<<"1:Insert"<<endl;
		cout<<"2:Read"<<endl;
		cout<<"3:Delete"<<endl;
		cout<<"4:Update"<<endl;
		cout<<"Enter choice: ";
		cin>>ch;
		switch(ch)
		{
			case 1:
				cout<<"Enter records: (Roll_no,name,marks): ";
				cin>>rec.roll_no>>rec.name>>rec.marks;
				s.insert(rec);
				break;
			case 2:
				s.read();
				break;
				
			case 3:
				cout<<"Enter roll_no do you want to delete: ";
				cin>>rollno;
				s.del(rollno);
				break;
			
			case 4:
				s.update();
				break;
		}
	}while(ch != 5);
	return 0;
}
