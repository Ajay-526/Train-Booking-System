#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<time.h>
#include<iomanip>
#include<fstream>
char user_name[20]="admin";
char password[10]="1234";
static int ps_id=0;
using namespace std;
class admin{
public:	
	int pnr;
	int tno;
	int class_no;
	char tname[100];
	char bp[10];
	char dest[100];
	int distance;
	char approx_time[10];
	int no_of_seats;
public:	
	void main_menu();
	int check_trains(int,int,int);
	void add_trains();
	void display_trains();
	void total_trains();
	void edit_trains();
	void modify_train();
	void delete_train();
};
class passenger: public admin{
public:	
	int pass_id;
	int pass_pnr_no;
	int pass_tr_no;
	int pass_cls_no;
	char pname[100];
	int age;
	char date[10];
	char con[20];
	int amt;
public:
	void pass_menu();
	void book_train();
	void cancel_train();
	void edit_details();
	void see_your_booking();
	void all_bookings();
	int billing(int,char*);
};

void passenger::pass_menu()
{
	int ch;
	do
	{
		cout<<"\nWelcome to the Passenger:)";
		cout<<"\n1.To Book a train";
		cout<<"\n2.To Cancel the train";
		cout<<"\n3.See Your Booking";
		cout<<"\n4.Go Back to the menu";
		cout<<"\n5.Exit Out";
		cout<<"\nEnter the Choice:";
		cin>>ch;
		switch(ch)
		{
			case 1: book_train();
					break;
			case 2: cancel_train();
					break;
			case 3: see_your_booking();
					break;
			case 4: return;
					break;
			case 5: exit(0);
					break;
			default: cout<<"\nChoose a right one:";
					break;
		}
	}while(1);
}
void admin::edit_trains()
{
	int ch;
	cout<<"\n1.Modify Train details:";
	cout<<"\n2.Delete train details:";
	cout<<"\n3.Go Back";
	cout<<"\nEnter choice:";
	cin>>ch;
	switch(ch)
	{
		case 1: modify_train();
				break;
		case 2: delete_train();
				break;
		case 3: return;
				break;
	}
}
void admin::modify_train()
{
	int pnr_no,t_no,cls_no,i,flag=0;
	long pos,p;
	fstream ct("trains.dat",ios::in|ios::out|ios::binary);
	cout<<"Enter PNR no:";
	cin>>pnr_no;
	cout<<"Enter Train No:";
	cin>>t_no;
	cout<<"Enter class no:";
	cin>>cls_no;
	flag=check_trains(pnr_no,t_no,cls_no);
	if(flag)
	{
		while(!ct.eof())
		{
			pos=ct.tellg();
			ct.read((char*)this,sizeof(*this));
			if(pnr_no==pnr && t_no==tno && cls_no==class_no)
			{
				cout<<"\n------Enter New Details:";
				cout<<"Enter PNR no:";
				cin>>pnr;
				cout<<"Enter Train No:";
				cin>>tno;
				cout<<"Enter class no:";
				cin>>class_no;
				cout<<"Enter train name:";
				cin>>tname;
				cout<<"\nEnter Boarding point location";
				cin>>bp;
				cout<<"\nEnter Destination location";
				cin>>dest;
				cout<<"\nEnter Distance in kms:";
				cin>>distance;
				cout<<"\nEnter approximate time for the journey:";		
				cin>>approx_time;
				cout<<"\nEnter no. of seats:";
				cin>>no_of_seats;
				
				ct.seekg(pos);
				ct.write((char*)this,sizeof(admin));
				cout<<"\nTrain Record Modified:";
			}
		}
	}
	else
	{
		cout<<"Sorryy!!! No trains records found:";
	}
}
void admin::delete_train()
{
	ifstream ct("trains.dat",ios::in);
	ofstream t("t.dat",ios::app|ios::binary);
	int pnr_no,t_no,cls_no,i,flag=0;
	char ch;
	cout<<"Enter PNR no:";
	cin>>pnr_no;
	cout<<"Enter Train No:";
	cin>>t_no;
	cout<<"Enter class no:";
	cin>>cls_no;
		while(!ct.eof())
		{
			ct.read((char*)this,sizeof(admin));
			if(pnr_no==pnr && t_no==tno && cls_no==class_no)
			{
				cout<<"Trian's PNR number: "<<pnr;
				cout<<"\nTrian's number: "<<tno;
				cout<<"\nTrian's class number: "<<class_no;
				cout<<"\nTrain's Name: "<<tname;
				cout<<"\nTrain's Boarding point location:"<<bp;
				cout<<"\nTrain's Destination location:"<<dest;
				cout<<"\nTrain Travell overall "<<distance<<" kms.";
				cout<<"\nTrains take approximate time to reach the destination is "<<approx_time;
				cout<<"\nTrain consists of "<<no_of_seats<<"no of seats.";
				
				cout<<"\n\n Do you want to delete this record(y/n): ";
			    cin>>ch;
			    if(ch=='n')
			    	t.write((char*)this,sizeof(admin));
			    flag=1;
			}
			else
				t.write((char*)this,sizeof(admin));
				if(flag==1)
				break;
		}
		ct.close();
		t.close();
	if(flag==0)
	{
		cout<<"Sorry!! no details found";
	}
	remove("trains.dat");
	rename("t.dat","trains.dat");
}
void passenger::book_train()
{
	ofstream pass("passengers.dat",ios::app);
	int pnr_no,t_no,cls_no,i,flag=0,n;
	char ch;
	total_trains();
	cout<<"Enter PNR no:";
	cin>>pnr_no;
	cout<<"Enter Train No:";
	cin>>t_no;
	cout<<"Enter class no:";
	cin>>cls_no;
	flag=check_trains(pnr_no,t_no,cls_no);
	if(flag)
	{
		cout<<"\n****"<<pnr_no<<"***"<<t_no<<"****"<<cls_no;
		pass_id=ps_id+1;
		++ps_id;
		pass_pnr_no=pnr_no;
		pass_tr_no=t_no;
		pass_cls_no=cls_no;
		cout<<"\nEnter the passenger's details:";
		cout<<"\nEnter the passenger's name:";
		cin>>pname;
		cout<<"\nEnter the passenger's age:";
		cin>>age;
		cout<<"\nenter todays date:";
		cin.sync();
		scanf("%[^\n]s",date);
		cout<<"\nEnter the concession category in words:";
		cout<<"\n1.Military\n2.Senior citizen";
		cout<<"\n3.Children below 5 yrs\n4.None";
		cin.sync();
		scanf("\n");
		scanf("%[^\n]s",con);
		cout<<"\Do you want to the billing:(y/n)";
		cin>>ch;
		if(ch=='y')
			amt=billing(pass_id,con);
		else
		{
			cout<<"\nSorryy!! Exit time out";
			exit(0);
		}
		cout<<"\nYour's Passenger ID: "<<pass_id;
		cout<<"\n-------------------------------------";
		pass.write((char*)this,sizeof(passenger));
		pass.close();
	}
	else
	cout<<"\nSorry!! no such train details found:";
}
int passenger::billing(int p,char *c)
{
	int tot=0;
	char ch;
	cout<<"\nFor the Id "<<p<<" and for the concession category of "<<c;
	if(strcmp(c,"military")==0)
	{
		cout<<"\nThe Fee For this category is rs:250 per head";
		cout<<"\nDo you want to continue:(y/n)";
		cin>>ch;
		if(ch=='y')
		{
			tot=250;
			cout<<"\nyour billing done: "<<tot;
			return tot;
		}
		else
		{
			cout<<"\nCancelled";
			exit(0);
		}
	}
	else if(strcmp(c,"children")==0)
	{
		cout<<"\nThe Fee For this category is rs:150 per head";
		cout<<"\nDo you want to continue:(y/n)";
		cin>>ch;
		if(ch=='y')
		{
			tot=150;
			cout<<"\nyour billing done: "<<tot;
			return tot;
		}
		else
		{
			cout<<"\nCancelled";
			exit(0);
		}
	}
	else
	{
		cout<<"\nThe Fee For this category is rs:550 per head";
		cout<<"\nDo you want to continue:(y/n)";
		cin>>ch;
		if(ch=='y')
		{
			tot=550;
			cout<<"\nyour billing done: "<<tot;
			return tot;
		}
		else
		{
			cout<<"\nCancelled";
			exit(0);
		}
	}
}

void passenger::see_your_booking()
{
	ifstream passin("passengers.dat",ios::in);
	
	int p_id,i,flag=0,n;
	cout<<"Enter Passenger Id";
	cin>>p_id;
	while(!passin.eof())
	{
		passin.read((char*)this,sizeof(passenger));
		if(p_id==pass_id)
		{
			cout<<"\nPassenger's ID: "<<pass_id;
			cout<<"\nPassenger's train PNR number: "<<pass_pnr_no;
			cout<<"\nPassenger's train number: "<<pass_tr_no;
			cout<<"\nPassenger's train class number: "<<pass_cls_no;
			cout<<"\n---------------------------------------------";
			cout<<"\nPassenger's name: "<<pname;
			cout<<"\npassenger's age:"<<age;
			cout<<"\nDate of booking :"<<date;
			cout<<"\nThe concession category of the passengers are:"<<con;
			cout<<"\nAmount paid: "<<amt;
			flag=1;
		}
		if(flag=1)
		break;
	}
	if(flag==0)
	{
		cout<<"\nSoryy!! Details not found";
	}
}
void passenger::cancel_train()
{
	ifstream passin("passengers.dat",ios::in);
	int p_id,i,flag=0;
	char ch;
	cout<<"Enter passenger id:";
	cin>>p_id;
	ofstream temp("temp.dat",ios::app);
	while(!passin.eof())
	{
		passin.read((char*)this,sizeof(passenger));
		if(p_id==pass_id)
		{
			cout<<"\nPassenger's ID: "<<pass_id;
			cout<<"Passenger's train PNR number: "<<pass_pnr_no;
			cout<<"\nPassenger's train number: "<<pass_tr_no;
			cout<<"\nPassenger's train class number: "<<pass_cls_no;
			cout<<"\n---------------------------------------------";
			cout<<"\nPassenger's name: "<<pname;
			cout<<"\npassenger's age:"<<age;
			cout<<"\nDate of booking :"<<date;
			cout<<"\nThe concession category of the passengers are:"<<con;
			cout<<"\nAmount paid : "<<amt;
			cout<<"\n\n Do you want to delete this record(y/n): ";
		    cin>>ch;
		    if(ch=='n')
		  		temp.write((char*)this,sizeof(passenger));
		  	flag=1;
		}
		else
			temp.write((char*)this,sizeof(passenger));
			if(flag==1)
			break;
	}
	passin.close();
	temp.close();
	if(flag==0)
		cout<<"Soryy!! no details found";
	else
	{
		remove("passengers.dat");
		rename("temp.dat","passengers.dat");
	}
}
void passenger::all_bookings()
{
	ifstream passin("passengers.dat",ios::in);
	while(!passin.eof())
	{
		passin.read((char*)this,sizeof(passenger));
		cout<<"\nPassenger's ID: "<<pass_id;
		cout<<"\nPassenger's train PNR number: "<<pass_pnr_no;
		cout<<"\nPassenger's train number: "<<pass_tr_no;
		cout<<"\nPassenger's train class number: "<<pass_cls_no;
		cout<<"\n---------------------------------------------";
		cout<<"\nPassenger's name: "<<pname;
		cout<<"\npassenger's age:"<<age;
		cout<<"\nDate of booking :"<<date;
		cout<<"\nThe concession category of the passengers are:"<<con;
		cout<<"\nAmount paid"<<amt;
	}
	passin.close();
}
class regis: public admin{	
public:
	int id;
	int pass;
public:	
	void menu();
	void reg();
	void login();
	int check_reg(int,int);
	void all_registrations();
};
void regis::menu()
{
	int ch;
	do
	{
		cout<<"\nHello!!";
		cout<<"\n1.Adim Login:";
		cout<<"\n2.User Registration";
		cout<<"\n3.User Login";
		cout<<"\n4.All Registrations";
		cout<<"\n5.Exit";
		cout<<"\nEnter choice";
		cin>>ch;
		switch(ch)
		{
			case 1: main_menu();
					break;
			case 2: reg();
					break;
			case 3: login();
					break;
			case 4: all_registrations();
					break;
			case 5: exit(0);
					break;
			default: cout<<"Sorry! Choose a right one";
						break;
		}
	}while(1);
}
void regis::reg()
{
	int i,ps,flag=0;
	ofstream reg("registrations.dat",ios::app);
	cout<<"Enter id: in numbers:";
	cin>>i;
	cout<<"Choose Password in numbers:";
	cin>>ps;
	flag=check_reg(i,ps);
	if(flag)
	{
		cout<<"Sorry!! Registration details are already taken";
	}
	else
	{
		id=i;
		pass=ps;
		reg.write((char*)this,sizeof(*this));
		cout<<"-------------------Registration Successfull--------------------------";
	}
	reg.close();
}
int regis::check_reg(int i,int ps)
{
	int flag=0;
	ifstream check("registrations.dat",ios::in);
	check.seekg(0);
	while(!check.eof() && check.read((char*)this,sizeof(*this)))
	{
		//check.read((char*)this,sizeof(*this));
		if(i==id || ps==pass)
		{
			flag=1;
			break;
		}
	}
	check.close();
	return flag;
}
void regis::all_registrations()
{
	ifstream check("registrations.dat",ios::in);
	while(!check.eof() && check.read((char*)this,sizeof(*this)))
	{
		//check.read((char*)this,sizeof(*this));
		cout<<"\nId: "<<id;
		cout<<"\nPassword:"<<pass;
	}
	check.close();
}
void regis::login()
{
	int i,ps,flag=0;
	passenger pp;
	cout<<"Enter id: in numbers:";
	cin>>i;
	cout<<"Choose Password in numbers:";
	cin>>ps;
	flag=check_reg(i,ps);
	ifstream check("registrations.dat",ios::in);
	check.seekg(0);
	while(!check.eof() && check.read((char*)this,sizeof(*this)))
	{
		//check.read((char*)this,sizeof(*this));
		if(i==id && ps==pass)
		{
			cout<<"\n--------------Login Successfull-----------------";
			pp.pass_menu();
			break;
		}
		else
		{
			cout<<"Invalid Entries:";
		}
	}
	check.close();
}
void admin::main_menu()
{
	passenger p;
	regis r;
	char user[20];
	char ps[10];
	int ch;
	cout<<"Enter Login Credentials:";
	cout<<"\nEnter User_Name:";
	cin>>user;
	cin.sync();
	cout<<"\nEnter Password:";
	cin>>ps;
	if(strcmp(user,user_name)==0 && strcmp(password,ps)==0)
	{
		do{
			cout<<"\nWELCOME TO THE ADMIN:)";
			cout<<"\n1.Add Trains:";
			cout<<"\n2.Display Trains:";
			cout<<"\n3.Total Trains:";
			cout<<"\n4.Edit Train Details:";
			cout<<"\n5.see overall bookings";
			cout<<"\n6.see overall user registrations";
			cout<<"\n7.Go Back to the Menu:";
			cout<<"\n8.Exit(_)Out:";
			cout<<"\nEnter Admin Choice:";
			cin>>ch;
			switch(ch)
			{
				case 1: add_trains();
						break;
				case 2: display_trains();
						break;
				case 3: total_trains();
						break;
				case 4: edit_trains();
						break;
				case 5: p.all_bookings();
						break;
				case 6: r.all_registrations();
						break;
				case 7: return;
						break;
				case 8: exit(0);
						break;
				default: cout<<"\nSorry Admin for your choice:";
						break;
			}
		}while(1);
	}
	else
	{
		cout<<"\nSorry!! Admin Invalid Login Details.";
	}
}
void admin::add_trains()
{
	int pnr_no,t_no,cls_no,i,flag=0;
	ofstream tr("trains.dat",ios::app);
	cout<<"Enter PNR no:";
	cin>>pnr_no;
	cout<<"Enter Train No:";
	cin>>t_no;
	cout<<"Enter class no:";
	cin>>cls_no;
	flag=check_trains(pnr_no,t_no,cls_no);
	if(flag)
	{
		cout<<"Sorry!! already trains has entered";
	}
	else
	{
		pnr=pnr_no;
		tno=t_no;
		class_no=cls_no;
		cout<<"Enter train name:";
		cin>>tname;
		cout<<"\nEnter Boarding point location";
		cin>>bp;
		cout<<"\nEnter Destination location";
		cin>>dest;
		cout<<"\nEnter Distance in kms:";
		cin>>distance;
		cout<<"\nEnter approximate time for the journey:";		
		cin>>approx_time;
		cout<<"\nEnter no. of seats:";
		cin>>no_of_seats;
		tr.write((char*)this,sizeof(admin));
	}
	tr.close();
}
void admin::display_trains()
{
	int pnr_no,t_no,cls_no,i,flag=0;
	ifstream ct("trains.dat",ios::in);
	ct.seekg(0);
	cout<<"Enter PNR no:";
	cin>>pnr_no;
	cout<<"Enter Train No:";
	cin>>t_no;
	cout<<"Enter class no:";
	cin>>cls_no;
	cout<<"\n-------------------------------------------------";
	while(!ct.eof() && ct.read((char*)this,sizeof(admin)))
	{
		//ct.read((char*)this,sizeof(admin));
		if(pnr_no==pnr && t_no==tno && cls_no==class_no)
		{
			cout<<"Trian's PNR number: "<<pnr;
			cout<<"\nTrian's number: "<<tno;
			cout<<"\nTrian's class number: "<<class_no;
			cout<<"\nTrain's Name: "<<tname;
			cout<<"\nTrain's Boarding point location:"<<bp;
			cout<<"\nTrain's Destination location:"<<dest;
			cout<<"\nTrain Travell overall "<<distance<<" kms.";
			cout<<"\nTrains take approximate time to reach the destination is "<<approx_time;
			cout<<"\nTrain consists of "<<no_of_seats<<"no of seats.";
			flag=1;
		}
	}
	if(flag==0)
	{
		cout<<"Sorry!! no train details found!";
	}
	ct.close();
}
void admin::total_trains()
{
	ifstream ct("trains.dat",ios::in);
	std::cout << "\n|PNO No." << "\t" << "|Train Num" << "\t" << "|Class No." << "\t" << "|Train Name" <<"\t";
	std::cout << "|Boarding Point " << "\t"<< "|Destination " << "\t" << "|Distance Travelling" << "\t" << "|Approximate Time" <<"\t" <<"|No. Of Seats"<<"\t" << "\n";
	ct.seekg(0);
	while(!ct.eof() && ct.read((char*)this,sizeof(admin)))
	{
		//ct.read((char*)this,sizeof(admin));
		std::cout << "|" << pnr << "\t\t" << "|" << tno << "\t\t" << "|" << class_no << "\t\t" << "|" << tname <<"\t";
		std::cout << "|" << bp << "\t\t" << "|"<< dest << "\t\t" << "|" << distance << "\t\t" << "|" << approx_time <<"\t\t" << "|" << no_of_seats <<"\t\t\n";
	}
	ct.close();
}
int admin::check_trains(int pnr_no,int t_no,int cls_no)
{
	int flag=0;
	ifstream ct("trains.dat",ios::in);
	while(!ct.eof())
	{
		ct.read((char*)this,sizeof(admin));
		if(pnr_no==pnr && t_no==tno && cls_no==class_no)
		{
			flag=1;
			break;
		}
	}
	ct.close();
	return flag;
}
main()
{
	cout<<"*****WELCOME This Ajay Kumar*****";
	regis r;
	while(1)
	r.menu();
}
