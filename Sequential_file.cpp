#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
struct Student	
{
	int roll_no;
	char name[100];	
	char division;
	char address[100];
	int status;
};
class Sequential
{
	public:
	    // constructor to create a file
	    Sequential()
		{
			f.open("file.txt", ios::binary | ios::in);
			if(f.fail())
			{
				f.open("file.txt", ios::binary | ios::out);
			}
			f.close();
		}
		fstream f;
		void insert(Student rec1);
		void read(); 
		int del(int rollno);//logical deletion
		void update();
		int search(int rollno);
		void display(int rollno);
};

void Sequential :: insert(Student rec1)
{
	Student crec;
	int n,i;
	
	//1)Open file
	f.open("file.txt" , ios::in | ios::out);
	
	//2)Assign status to record(zero means record is active)
	rec1.status = 0;
	
	//3)Go to end of file
	f.seekg(0 , ios::end);
	
	//4)Calculate number of record
	n = f.tellg()/sizeof(Student);
	
	//5)Insert first record
	if(n == 0)
	{
		rec1.status = 0;
		f.write((char*)&rec1 , sizeof(Student));
		f.close();
		return;
	}
	
	//6)Insert record
	else
	{
	    //Go to last record
		i = n-1;
	    while(i>=0)
	    {
		    f.seekg(i*sizeof(Student) ,ios::beg);//points last record
		    f.read((char*)&crec,sizeof(Student));//read last record
		    if(crec.roll_no > rec1.roll_no)
		    {
			    f.seekp((i+1)*sizeof(Student) ,ios::beg);//shift current record to 1 position down
			    f.write((char*)&crec , sizeof(Student));
		    }
		    else
			    break;
		i--;
	    }
	    i++;
	    f.seekp(i*sizeof(Student) ,ios::beg);
	    f.write((char*)&rec1 ,sizeof(Student));//write record to apppropriate position:-
	    f.close();
	}
}

void Sequential :: read()
{
	Student crec;
	int n;
	cout<<"******Data File******"<<endl;
	//1)open file
	f.open("file.txt" , ios::binary | ios::in);
	
	//2)Go to end of file
	f.seekg(0,ios::end);
	
	//3)calculate no of records
	n = f.tellg()/sizeof(Student);
	f.seekg(0,ios::beg);
	
	for(int i=1;i<=n;i++)
	{
	    //read record
		f.read((char*)&crec , sizeof(Student));
		//if record is active then only read this record
		if(crec.status == 0)
		{
			cout<<"---Rec ("<<i<<")---"<<endl;
			cout<<crec.roll_no<<endl;
			cout<<crec.name<<endl;
			cout<<crec.division<<endl;
			cout<<crec.address<<endl;
			cout<<"--------------"<<endl;
		}
		else
		{
			cout<<"*****Deleted*****"<<endl;
		}
	}
	f.close();
}

int Sequential :: del(int rollno)
{
	Student crec;
	int i,n;
	//1)Open file
	f.open("file.txt" , ios::in | ios::out);
	
	//2)Go to end of file
	f.seekg(0 ,ios::end);
	
	//3)calculate no of records
	n = f.tellg()/sizeof(Student);
	f.seekg(0,ios::beg);
	
	for(int i=0;i<n;i++)
	{
	    //read record
		f.read((char*)&crec ,sizeof(Student));
		if(crec.roll_no == rollno)
		{
		    //Make record inactive
			crec.status = 1;
			f.seekp(i*sizeof(Student) ,ios::beg);
			f.write((char*)&crec , sizeof(Student));
			f.close();
			return (1);
		}
	}
	return (0);
}

void Sequential :: update()
{
	int rollno;
	Student rec1;
	cout<<"Enter the roll_no of record to be updated: ";
	cin>>rollno;
	cout<<"Enter New record(rollno , name , division , address): ";
	cin>>rec1.roll_no>>rec1.name>>rec1.division>>rec1.address;
	
	//delete current record and replace it by new record
	if(del(rollno))
		insert(rec1);
	else
		cout<<"Record not found"<<endl;
}

int Sequential :: search(int rollno)
{
	Student crec;
	int n;
	//1)Open file
	f.open("file.txt" , ios::in | ios::out);
	
	//2)Go to end of file
	f.seekg(0 , ios::end);
	
	//3)Claculate number of records
	n = f.tellg()/sizeof(Student);
	f.seekg(0,ios::beg);
	for(int i=0;i<n;i++)
	{
	    //read record
		f.read((char*)&crec , sizeof(Student));
		//if record is active then only search
		if(crec.status == 0)
		{
		    //if record is absent
		    if(crec.roll_no > rollno)
		    {
		        f.close();
		        return(-1);
		    }
		    //if record matched
		    if(crec.roll_no == rollno);
		    {
			    f.close();
			    return (i);
		    }
		}
	}
	return(-1);
}

void Sequential :: display(int rollno)
{
    Student crec;
    int n;
    
    //1)Open file
    f.open("file.txt" , ios::binary | ios::in);
    
    //2)Go to end of file
    f.seekg(0,ios::end);
    
    //3)calculate number of records
    n = f.tellg() / sizeof(Student);
    f.seekg(0,ios::beg);
    for(int i=0;i<n;i++)
    {
        f.read((char*)&crec , sizeof(Student));
        if(crec.status == 0)
        {
            if(crec.roll_no == rollno)
            {
                cout<<"---Record---"<<endl;
                cout<<crec.roll_no<<endl;
                cout<<crec.name<<endl;
                cout<<crec.division<<endl;
                cout<<crec.address<<endl;
                break;
            }
        }
    }
}

int main()
{
	Sequential s;
	Student rec;
	int ch,rollno;
	do
	{
		cout<<"1:Insert"<<endl;
		cout<<"2:Read"<<endl;
		cout<<"3:Delete"<<endl;
		cout<<"4:Update"<<endl;
		cout<<"5:Search"<<endl;
		cout<<"6:Display particular record"<<endl;
		cout<<"7:Exit"<<endl;
		cout<<"Enter choice: ";
		cin>>ch;
		switch(ch)
		{
			case 1:
				cout<<"Enter records: (Roll_no,name,division,address): ";
				cin>>rec.roll_no>>rec.name>>rec.division>>rec.address;
				s.insert(rec);
				break;
				
			case 2:
				s.read();
				break;
				
			case 3:
			    cout<<"****DELETE FUNCTION****"<<endl;
				cout<<"Enter roll_no do you want to delete: ";
				cin>>rollno;
				s.del(rollno);
				s.read();
				break;
			
			case 4:
			    cout<<"****UPDATE FUNCTION****"<<endl;
				s.update();
				s.read();
				break;

			case 5:
			{
				cout<<"Enter roll_no do you want to serach: ";
				cin>>rollno;
				int r = s.search(rollno);
				if(r>=0)
				{
				    cout<<"Record is found "<<endl;
				}
				else
					cout<<"Record not found"<<endl;					
				break;
			}
            
            case 6:
                cout<<"Enter roll_no do you want to display: ";
                cin>>rollno;
                s.display(rollno);
                break;
		}
	}while(ch != 7);
	return 0;
}

