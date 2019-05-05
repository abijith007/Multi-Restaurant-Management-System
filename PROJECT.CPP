#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<fstream.h>
#include<dos.h>            //For delay func
#include<string.h>
#include<process.h>        //For exit function
#include<iomanip.h>        //Setwidth
#include<stdlib.h>         //For randomize function for bill and graphics
#include<time.h>           //retrieve current date and time
#include<graphics.h>       //Intro page


int list=0,food,Bill;
float total=0;
char name[50],add[100],phone[20],username[20],password[20],formal[50];
char d1=186,d2=201,d3=205,d4=187,d6=188,d7=200,d8=204,d9=185;         //Global variables

class Restaurant                   //MAIN CLASS 1
{
 int id,qty;
 char slno[20],RestName[50],cui[30],loc[50],item[50];
 float price;

 public:

 char* ret_rest()  //* returns a string
 {
  return(slno);
 }

 int ret_id()      //Returns the food id
 {
  return(id);
 }

 void input()
 {
   int opt,chk;            //Under admin->Add a restaurant(open)
   loop:
   Restaurant rest;
   cout<<"\nEnter The Details Of The Restaurant:\n";
   output();
   cout<<"\n\nEnter the serial number: ";
   gets(rest.slno);

   chk=check_rest(rest.slno);

   if(chk==0)
   {
    cout<<"\nThis serial number already exists.";
    getch();
    clrscr();
    title(1);
    rest.output();
    goto loop;
   }       //------------------------------------------------------

   cout<<"Enter the name of the restaurant: ";
   gets(rest.RestName);
   cout<<"Enter the option of the cuisine which the restaurant belongs to: \n1.Indian \t2.Italian \t3.Chinese \t4.Mexican\t5.Fastfoods \n";
   cout<<"Your Option: ";
   cin>>opt;

   cus:

   if(opt==1)                      //To select the type of cuisine(In admin->ADD)
   strcpy(rest.cui,"Indian");
   if(opt==2)
   strcpy(rest.cui,"Italian");
   if(opt==3)
   strcpy(rest.cui,"Chinese");
   if(opt==4)
   strcpy(rest.cui,"Mexican");
   if(opt==5)
   strcpy(rest.cui,"Fastfoods");

   if(opt>=6&&opt<=0)
   {
    cout<<"The option doesnt exist please enter one of the existing options.";
    goto cus;
   }


   cout<<"Enter the location at which the restaurant is present at: ";
   gets(rest.loc);
   list++;

   ofstream fout("List.txt",ios::app|ios::binary);
   fout.write((char*)&rest,sizeof(rest));
   fout.close();

					//Final close of "Add" in Admin
 }
 //--------------------------------------------------------------------------
 int enter_food()   //Adding of food in the restraunt(Admin->Manage)
 {
  int e=0;
  food=0;
  char ch;
  char s[10];

  cout<<"\nEnter the serial number of the restaurant which the food belongs to: \n";               //->Admin->Manage->add
  gets(s);

  ifstream chk("List.txt",ios::in|ios::binary);
  while(chk.read((char*)&rest,sizeof(rest)))
   {
    if(strcmp(rest.slno,s)==0)
    e++;
   }
  chk.close();

  if(e==0)
  {
   cout<<"\nThe serial number which you entered does not exist.";               //To check if the given restraunt ID is valid
   getch();
   return(0);
  }

  loop:

  clrscr();
  title(1);

  rest.show_food(s);

  id=0;
  cout<<endl<<endl;
  cout<<"Enter the ID of food item: ";                                      //->admin->manage->add food
  cin>>id;

  id=check_food(id,s);

  if(id==0)
  {
   cout<<endl<<"The ID number exist.";
   getch();
   goto loop;
  }

  cout<<"Enter the name of the food: ";
  gets(rest.item);
   cout<<"Enter the price: ";
  cin>>price;

  strcpy(rest.slno,s);

  ofstream fout("food.txt",ios::app|ios::binary);
  fout.write((char*)&rest,sizeof(rest));
  fout.close();

  clrscr();
  title(1);
  rest.show_food(s);
  cout<<endl<<"\nDo you want to enter more items? (Y(y)/N(n))\n";
  cin>>ch;

  if(ch=='Y'||ch=='y')             //under Admin->Add food(MAnage)(to add items)
  goto loop;

 }               //final close of Add food inside Admin

   //------------------------------------------------------
 void del_food(char* s)           //Delete food item(Admin->MAnage)
 {
  int e=0,id;
  food=0;
  char ch;

  loop:
  show_food(s);

  if (food>0)
  {
   cout<<endl<<endl<<"Enter the ID of the food which you want to delete: ";          //->Admin->Manage
   cin>>id;

   ifstream chk("food.txt",ios::in|ios::binary);
   while(chk.read((char*)&rest,sizeof(rest)))
   {
    if(rest.id==id)
    e++;
   }
   chk.close();

   if(e>0)
   {
    ofstream fout("temp.txt",ios::out|ios::binary);
    ifstream fin3("food.txt",ios::in|ios::binary);
    while(fin3.read((char*)&rest,sizeof(rest)))
    {
     if(rest.id!=id && strcmp(rest.slno,s)==0)
     fout.write((char*)&rest,sizeof(rest));

     if((strcmp(rest.slno,s)!=0))
     fout.write((char*)&rest,sizeof(rest));
    }
    fout.close();
    fin3.close();
    remove("food.txt");         //To delete specific food items from list
    rename("temp.txt","food.txt");
    food--;

    clrscr();
    title(1);
    rest.show_food(s);

    cout<<"Do you want to delete any more food items? (Y(y)/N(n))\n";
    cin>>ch;

    if(ch=='Y'||ch=='y')
    goto loop;
   }

   else
   {
    cout<<"The food ID which you want to delete does not exist."; //Verifying whether the food itme to be deleted exists or not
    getch();
    goto loop;
   }
  }

  else
  cout<<"The list is empty.";

 }                            //Close

  //---------------------------------------------------------------------
int show_food(char* s)                            //admin->manage->display
 {
  loop:            //to display the food items contained in  the restraunt
  clrscr();
  title(1);

  char ch,ch1=179,ch2=196;
  int chk=0;
  clrscr();
  title(1);
  cout<<endl<<endl;
  ifstream fin2("list.txt",ios::in|ios::binary);
  while(fin2.read((char*)&rest,sizeof(rest)))
  {
   if(strcmp(rest.slno,s)==0)
   { cout<<"Restaurant Name: ";
     cout<<rest.RestName;
     chk++;
     break;
   }
  }
  fin2.clear();
  fin2.close();

  if(chk==0)
  {
   cout<<"\nThe serial number doesnt exist.";
   getch();
   return(0);
  }

  cout<<endl;

  for(int i=0;i<80;i++)
  cout<<ch2;
  cout<<ch1;

  gotoxy(4,10);
  cout<<" ID"; //Creating a table using co-ordinates to display the items
  gotoxy(33,10);
  cout<<"Item Name";
  gotoxy(70,10);
  cout<<"Rate";

  gotoxy(80,10);
  cout<<ch1;
  for(i=0;i<80;i++)
  cout<<ch2;

  ifstream fin("food.txt",ios::in|ios::binary);
  fin.clear();

  i=12;
  while(fin.read((char*)&rest,sizeof(rest)))
  {
   if(strcmp(rest.slno,s)==0)
   {
     gotoxy(1,i);
     cout<<ch1;
     gotoxy(80,i);
     cout<<ch1;
     gotoxy(5,i);
     cout<<rest.id<<".";
     gotoxy(33,i);
     cout<<rest.item;
     gotoxy(70,i);
     cout<<rest.price;
     food++;
     i++;
     cout<<endl;
   }
  }

  if(food==0)
  cout<<"\n\t          The list of food items is empty.\n";

  for(i=0;i<80;i++)
  cout<<ch2;

  fin.close();
  getch();

 }                    //final close(of display<-admin)
 //___________________________________________________________________________

 int mod_food()                         //->admin->manage->modify
 {
  char s[20],chk;
  int m,opt=0;

  loop:
  rest.output();

  cout<<"Enter the serial number of the restaurant of which you want to modify its food\nitems: ";
  gets(s);

  ifstream fin("List.txt",ios::in|ios::binary);
  while(fin.read((char*)&rest,sizeof(rest)))
  {
   if(strcmp(s,rest.slno)==0)
   opt++;
  }

  if(opt==0)
  {
   cout<<"\nThe serial number which you entered does not exist. ";
   getch();
   clrscr();
   title(1);
   goto loop;
  }

  loop2:

  rest.show_food(s);
  cout<<endl<<endl;

  cout<<endl<<"Enter the id of the food item which you want to modify: \n";
  cin>>m;

  opt=0;

  ifstream fin2("food.txt",ios::in|ios::binary);
  while(fin2.read((char*)&rest,sizeof(rest)))
  {
   if(m==rest.id)
   opt++;
  }
  fin2.close();

  if(opt==0)
  {
   cout<<"The ID which you entered doesnt exist.";
   getch();
   clrscr();
   title(1);
   goto loop2;
  }

  clrscr();
  title(1);

  rest.show_food(s);

  fstream fout("food.txt",ios::out|ios::in|ios::binary);
  while(fout.read((char*)&rest,sizeof(rest)))
  {
   if(strcmp(s,rest.slno)==0 && m==rest.id)
   {
    cout<<endl;
    cout<<"Enter the ID of food item: ";
    cin>>rest.id;
    cout<<"Enter the name of the food: ";
    gets(rest.item);
    cout<<"Enter the price: ";
    cin>>rest.price;
    fout.seekp(fout.tellg()-sizeof(rest));
    fout.write((char*)&rest,sizeof(rest));
   }
  }

  clrscr();
  title(1);
  rest.show_food(s);
  cout<<endl;
  cout<<"\nDo you want to modify any more items: (Y(y)/N(n))\n";
  cout<<"Enter your choice: ";
  cin>>chk;

  if(chk=='Y'||chk=='y')
  {
   goto loop2;
   clrscr();
   title(1);
  }

  else if(chk=='N'||chk=='n')
  {
   clrscr();
   title(1);
   rest.output();
   cout<<"Do you want to modify any restaurants. (Y(y)/ N(n))\n";
   cout<<"Enter your choice: ";
   cin>>chk;
   if(chk=='Y'||chk=='y')
   return(1);
   else
   return(0);
  }
 }           //final close (modify<-manage<-admin)
//____________________________________________________________________________


 void output()  //Display the data(ADMIN->Display)
 {
  cout<<endl;
  char ch1=179,ch2=196;
  clrscr();
  title(1);
  cout<<endl;

  if(list==0)
  {
   cout<<setw(55)<<"The restaurant list is empty.";
   getch();
  }
  else
  {
   for(int i=0;i<80;i++)
   cout<<ch2;
   cout<<ch1<<" Sl.no \tRestaurant Name\t\tLocation\t     Cuisine\t       "<<ch1;
   for(i=0;i<80;i++)
   cout<<ch2;
   fstream fin("List.txt",ios::in|ios::binary);
   i=10;
   while(fin.read((char*)&rest,sizeof(rest)))
   {                               //Coordinates to make table to display
    gotoxy(1,i);
    cout<<ch1;
    gotoxy(80,i);
    cout<<ch1;
    gotoxy(4,i);
    cout<<rest.slno<<".";
    gotoxy(19,i);
    cout<<rest.RestName;
    gotoxy(41,i);
    cout<<rest.loc;
    gotoxy(62,i);
    cout<<rest.cui<<endl;
    i++;
   }
   for(i=0;i<80;i++)
   cout<<ch2;
   getch();
   fin.close();
  }
 }
       //____________________________________________________________________

 void output_cuisine(char str[])/*shows the no of restaurants with a
				specific cuisine i.e under one cuisine how
				 many restaurants are registered*/


 { //Login as existing cust->order your food->Choose cuisine

  int chk=0;
  char ch2=196,ch1=179;

  loop:
  clrscr();
  title(1);
  char opt[10];
  cout<<endl<<str<<" Restaurants in "<<str<<" cuisine:"<<endl<<endl;

  for(int i=0;i<80;i++)
   cout<<ch2;
   cout<<ch1<<" Sl.no \t\t    Restaurant Name\t\t      Location         "<<ch1;
   for(i=0;i<80;i++)
   cout<<ch2;

   i=12;

  ifstream fin("List.txt",ios::in|ios::binary);
  while(fin.read((char*)&rest,sizeof(rest)))
  {
   if(strcmp(str,rest.cui)==0)
   {
    gotoxy(1,i);
    cout<<ch1;    //table for displaying the restaurant name
    gotoxy(80,i);
    cout<<ch1;
    gotoxy(4,i);
    cout<<rest.slno<<".";
    gotoxy(30,i);
    cout<<rest.RestName;
    gotoxy(63,i);
    cout<<rest.loc;
    i++;
   }
  }
  cout<<endl;

  for(i=0;i<80;i++)
  cout<<ch2;

  fin.close();

  cout<<"\n0.Back\n\n";

 }        //close of (order your food)
 //__________________________________________________________________________

 int mod_rest()  //admin->modify the restaurant
 {
  int x=0,pos,opt,chk=0;
  char m[10],ch;

  loop:
  rest.output();
  cout<<endl<<endl;
  cout<<"Enter the serial number of the restaurant which you want to modify: ";
  gets(m);

  ifstream fin("List.txt",ios::in|ios::binary);
  while(fin.read((char*)&rest,sizeof(rest)))
  {
   if(strcmp(m,rest.slno)==0)
   chk++;
  }
  fin.close();

  if(chk==0)
  {
   cout<<endl<<"The serial number which you entered doesnt exist.";
   getch();
   clrscr();
   title(1);
   goto loop;
  }

  clrscr();
  title(1);
  rest.output();
  cout<<endl<<"Enter the details of the restaurant: ";
  fstream fout("List.txt",ios::out|ios::in|ios::binary);
  while(fout.read((char*)&rest,sizeof(rest)))
  {
   if(strcmp(m,rest.slno)==0)
   {
    x++;
    cout<<"\n\nEnter the serial number: ";
    gets(rest.slno);
    cout<<"Enter the name of the restaurant: ";
    gets(rest.RestName);

    cout<<"Enter the option of the cuisine which the restaurant belongs to: \n1.Indian \n2.Italian \n3.Chinese \n4.Mexican\n5.Fastfoods \n";
    cout<<"Your Option: ";
    cin>>opt;

    if(opt==1)
    strcpy(rest.cui,"Indian");
    if(opt==2)
    strcpy(rest.cui,"Italian");
    if(opt==3)
    strcpy(rest.cui,"Chinese");
    if(opt==4)
    strcpy(rest.cui,"Mexican");
    if(opt==5)
    strcpy(rest.cui,"Fastfoods");
    cout<<"Enter the location at which the restaurant is present at: ";
    gets(rest.loc);

    fout.seekp(fout.tellg()-sizeof(rest));
    fout.write((char*)&rest,sizeof(rest));

   }
  }

  if(x==0)
  {
   cout<<"The serial number does not exist. ";
   getch();
  }
  else
  {
   clrscr();
   title(1);
   rest.output();
   cout<<endl<<"Do you want to modify any more restaurants? (Y(y)/N(n))\n";
   cin>>ch;
   if(ch=='Y'||ch=='y')
   return(1);
  }

  fout.close();               //close of (modify  restaurant<-admin)
 }
//____________________________________________________________________________

 int del()               //Admin->Delete(To delete the restaurants)
 {
  int e=0;
  char rem[10];

  rest.output();
  cout<<"\nEnter the serial number of the restaurant you want to delete: \n";
  cout<<"\nYour choice: ";
  gets(rem);

  ifstream check("List.txt",ios::in|ios::binary);
  while(check.read((char*)&rest,sizeof(rest)))
  {
   if(strcmp(rem,rest.slno)==0)
   e++;
  }

  if(e>0)
  {
   ifstream dat("List.txt",ios::in|ios::binary);
   ofstream dat1("list_dub.txt",ios::out|ios::binary);
   ofstream dat3("food_dub.txt",ios::out|ios::binary);
   while(dat.read((char*)&rest,sizeof(rest)))
   {
    if(strcmp(rem,rest.slno)!=0)
    {
     dat1.write((char*)&rest,sizeof(rest));
     dat3.write((char*)&rest,sizeof(rest));
    }
   }

   dat.close();
   dat1.close();
   dat3.close();
   remove("List.txt");
   rename("list_dub.txt","List.txt");
   remove("food.txt");
   rename("food_dub.txt","food.txt");
   list--;
  }

  else
  {
   cout<<"The serial number does not exit.";
   getch();
   return(0);
  } //Final close of (delete<-Admin )
 }
//________________________________________________________________________

 int enter_cart(char sl[])
 {                         //Login as cust->order your food->Enter cuisine..
  int id,qty,chk=0;
  char ch[20];
  cout<<"\n0. Back"<<endl<<endl;
  cout<<"Enter the id of the food which you want to buy: ";
  cin>>id;

  if(id==0)
  return(0);

  ifstream fin2("food.txt",ios::in|ios::binary);
  while(fin2.read((char*)&rest,sizeof(rest)))
  {
   if(id==rest.id)
   chk++;
  }
  fin2.close();

  if(chk==0)
  {
   cout<<"\nThe ID which you entered does not exist.";
   getch();
   return(1);
  }

   ifstream fin4("list.txt",ios::in|ios::binary);
  while(fin4.read((char*)&rest,sizeof(rest)))
  {
   if(strcmp(sl,rest.slno)==0)
   strcpy(ch,rest.RestName);
  }
  fin4.close();

  cout<<"Enter the quantity: ";
  cin>>qty;

  ////////////////////////////

  chk=0;

  ifstream fin3("bill.txt",ios::in|ios::binary);
  while(fin3.read((char*)&rest,sizeof(rest)))
  {
   if(id==rest.id && strcmp(rest.slno,sl)==0)
   chk++;
  }
  fin3.close();

  if(chk==0)
  {ofstream fout("bill.txt",ios::app|ios::binary);
  ifstream fin("food.txt",ios::in|ios::binary);
  while(fin.read((char*)&rest,sizeof(rest)))
  {
   if(id==rest.id && strcmp(rest.slno,sl)==0)
   {
    rest.qty=qty;
    strcpy(rest.RestName,ch);
    fout.write((char*)&rest,sizeof(rest));
    chk++;
   }
  }
  fout.close();
  }

  else if(chk>0)
  {fstream update("Bill.txt",ios::in|ios::out|ios::binary);
  while(update.read((char*)&rest,sizeof(rest)))
  {
   if(id==rest.id && strcmp(rest.slno,sl)==0)
   {
     rest.qty=rest.qty+qty;
     cout<<endl<<rest.qty;
     getch();
     strcpy(rest.RestName,ch);
     update.seekg(update.tellg()-sizeof(rest));
     update.write((char*)&rest,sizeof(rest));
   }
  }
  update.close();
  }

 }  //close
 //_________________________________________________________________________

 void display_cart() //login as cust->display your cart(to display bill details)                                                        //Under order food-->Display the items
 {
  Restaurant temp;
  char ch2=196,ch1=179;

  ::total=0;
  char ch[10]="A",date[20],time[20]; //declared date and time  for use in _strdate/_strtime
  int i=0,k=17;

  for(i=0;i<80;i++)
  cout<<ch2;

  cout<<endl;

  gotoxy(4,9);
  cout<<"Bill Number: "<<Bill;
  _strdate(date);  //function to display date
  _strtime(time);  //function to display time
  gotoxy(24,9);
  cout<<"|";
  gotoxy(33,9);           //creates table to display Bill no,Time,DAte
  cout<<"Time: "<<time;
  gotoxy(53,9);
  cout<<"|";
  gotoxy(62,9);
  cout<<"Date: "<<date;

  cout<<endl;

  for(i=0;i<80;i++)
  cout<<ch2;

  cout<<endl;

  ifstream fin1("bill.txt",ios::in|ios::binary);
  ofstream fout("temp_bill.txt",ios::out|ios::binary);
  while(fin1.read((char*)&rest,sizeof(rest)))
  {
   fout.write((char*)&rest,sizeof(rest));
  }
  cout<<endl;
  fin1.close();
  fout.close();


  ifstream fin2("bill.txt",ios::in|ios::binary);
  Restaurant rest1,rest2;
  while(fin2.read((char*)&rest1,sizeof(rest1)))
  {

   if(strcmp(ch,rest1.slno)!=0)
   {
    cout<<rest1.slno<<". "<<rest1.RestName<<endl;
    strcpy(ch,rest1.slno);

     gotoxy(0,9);
     for(i=0;i<80;i++)     //creates table AND display the headings
     cout<<ch2;
     cout<<ch1<<" ID No."<<setw(25)<<"Item Name"<<setw(23)<<"Quantity"<<setw(19)<<"Rate"<<"    "<<ch1;
     for(i=0;i<80;i++)
     cout<<ch2;

     ifstream fin3("temp_bill.txt",ios::in|ios::binary);
     while(fin3.read((char*)&rest2,sizeof(rest2)))
     {
      if(strcmp(ch,rest2.slno)==0)
      {
       gotoxy(0,k);
       cout<<ch1;              //creates a table and displays the purchase details(item name and no)
       gotoxy(5,k);
       cout<<rest2.id;
       gotoxy(25,k);
       cout<<rest2.item;
       gotoxy(51,k);
       cout<<rest2.qty;
       gotoxy(73,k);
       cout<<rest2.price;
       gotoxy(80,k);
       cout<<ch1;

       k++;
       ::total=::total+(rest2.price*rest2.qty);
       delay(1000);
      }
     }
     for(i=0;i<80;i++)
     cout<<ch2;
     fin3.close();
   }
  }

  fin2.close();

  cout<<"\nTotal Price: "<<::total;

 }//close of  display cart
 //__________________________________________________________________________

 int del_cart()        //login as customer->display your cart->(do u want to delete any items)
 {                     //To delete the items from the cart
  char ch,sl[10];
  int id,qty;
  display_cart();
  cout<<endl;
  cout<<"Are you sure you want to delete one of the food item? (Y(y)/N(n))\n";
  cin>>ch;

  if(ch=='Y'||ch=='y')
  {
   clrscr();
   title(1);
   display_cart();
   cout<<endl<<"Enter the restaurant which the food belongs to: ";
   gets(sl);
   cout<<"Enter the Sl. No. of the food: ";
   cin>>id;

   ofstream fout("temp.txt",ios::out|ios::binary);
   ifstream fin("bill.txt",ios::in|ios::binary);
   while(fin.read((char*)&rest,sizeof(rest)))
   {
    if(strcmp(sl,rest.slno)!=0 && id!=rest.id)
    fout.write((char*)&rest,sizeof(rest));
   }
   fin.close();
   fout.close();
   remove("bill.txt");
   rename("temp.txt","bill.txt");
  }

  else
  return(0);
 }

}rest; //close  of class

//___________________________________________________________________________


int check_rest(char* a)//checks uniqueness for restaurant(sl no.)
{
 ifstream fin("List.txt",ios::in|ios::binary);
 while(fin.read((char*)&rest,sizeof(rest)))
 {
  if(strcmp(a,rest.ret_rest())==0)
  return(0);
 }
 fin.close();
 return(1);
}
//__________________________________________________________________________
int check_food(int a,char ch[])//checks uniqueness for food item
{
 ifstream fin("food.txt",ios::in|ios::binary);
 while(fin.read((char*)&rest,sizeof(rest)))
 {
  if(a==rest.ret_id()&&strcmp(ch,rest.ret_rest())==0)
  return(0);
 }
 fin.close();
 return(a);

}
//________________________________________________________________________
class Customer   //MAIN CLASS 2 (to get customer details)                                                                 //Opening of Class to manage customer details and accounts
{
 char name[50],add[100],phone[20],username[20],password[20];

 public:

 void insert()  //create an account for customer..(in home screen)
 {
  Customer cust;
									       //Table of contents
  gotoxy(21,8);
  cout<<d2;

  gotoxy(21,20);
  cout<<d7;
  gotoxy(60,8);
  cout<<d4;
  gotoxy(60,20);
  cout<<d6;

  for(int i=0,j=22;i<38;i++,j++)
  {
   gotoxy(j,8);
   cout<<d3;
  }

  for(i=0,j=9;i<11;i++,j++)
  {
   gotoxy(21,j);
   cout<<d1;
   gotoxy(60,j);
   cout<<d1;
  }
   //To accept the customer details(Contact details,Name,Address,Username,Password)
  gotoxy(25,9);
  cout<<"   Enter the Customer Details: ";
  gotoxy(21,10);
  cout<<d8;
  gotoxy(60,10);
  cout<<d9;
  for(i=0,j=22;i<38;i++,j++)
  {
   gotoxy(j,10);
   cout<<d3;
  }
  gotoxy(24,11);
  cout<<"Name: ";//to accept name of customer
  gotoxy(21,12);
  cout<<d8;
  gotoxy(60,12);
  cout<<d9;
  for(i=0,j=22;i<38;i++,j++)
  {
   gotoxy(j,12);
   cout<<d3;
  }
  gotoxy(24,13);
  cout<<"Phone number: ";
  gotoxy(21,14);
  cout<<d8;
  gotoxy(60,14);
  cout<<d9;
  for(i=0,j=22;i<38;i++,j++)
  {
   gotoxy(j,14);
   cout<<d3;
  }
  gotoxy(24,15);
  cout<<"Address: ";
  gotoxy(21,17);
  cout<<d8;
  gotoxy(60,17);
  cout<<d9;
  for(i=0,j=22;i<38;i++,j++)
  {
   gotoxy(j,17);
   cout<<d3;
  }
  gotoxy(24,18);
  cout<<"Username: ";
  gotoxy(21,19);
  cout<<d8;
  gotoxy(60,19);
  cout<<d9;
  for(i=0,j=22;i<38;i++,j++)
  {
   gotoxy(j,19);
   cout<<d3;
  }
  gotoxy(24,20);
  cout<<"Password: ";
  for(i=0,j=21;i<39;i++,j++)
  {
   gotoxy(j,21);
   cout<<d3;
  }
  gotoxy(21,20);
  cout<<d1;
  gotoxy(21,21);
  cout<<d7;
  gotoxy(60,20);
  cout<<d1;
  gotoxy(60,21);
  cout<<d6;


  gotoxy(30,11); // to enter all details in the corresponding fields
  gets(name);
  strcpy(formal,name);
  gotoxy(38,13);
  gets(phone);
  gotoxy(33,15);
  gets(add);
  gotoxy(34,18);
  gets(username);
  gotoxy(34,20);
  gets(password);

  strcpy(::name,name); //   copying all the details from local to global variable
  strcpy(formal,name);
  strcpy(::add,add);
  strcpy(::phone,phone);
  strcpy(::username,username);
  strcpy(::password,password);
 }
 //________________________________________________________________________
 int check()
 {                  //home page->login as an existing customer(to check if username exists)
  char u[30],p[50];
  int i=0,chk=0;

  gotoxy(37,9);
  cout<<"Login:";

  gotoxy(28,11);
  for(i=0;i<23;i++)
  cout<<::d3;
  gotoxy(28,13);
  for(i=0;i<23;i++)
  cout<<::d3;
  gotoxy(28,15);
  for(i=0;i<23;i++)
  cout<<::d3;
  gotoxy(28,12);
  cout<<::d1;
  gotoxy(50,12);
  cout<<::d1;
  gotoxy(28,14);
  cout<<::d1;
  gotoxy(50,14);
  cout<<::d1;
  gotoxy(28,11);
  cout<<d2;
  gotoxy(50,11);
  cout<<d4;
  gotoxy(28,15);
  cout<<d7;
  gotoxy(50,15);
  cout<<d6;
  gotoxy(28,13);
  cout<<d8;
  gotoxy(50,13);
  cout<<d9;

  gotoxy(30,12);
  cout<<"Username: ";   //accepts the user name and password from user
  gotoxy(30,14);
  cout<<"Password: ";
  gotoxy(40,12);
  gets(u);
  gotoxy(40,14);
  gets(p);

  ifstream fin("customer.txt",ios::in|ios::binary);//to check if the  username and pass exist in the file
  while(fin.read((char*)&cust,sizeof(cust)))
  {
   if(strcmp(u,cust.username)==0&&strcmp(p,cust.password)==0) //if exists then the cust details are stored in global varible
   {
    strcpy(::name,cust.name);
    strcpy(formal,cust.name);
    strcpy(::add,cust.add);
    strcpy(::phone,cust.phone);
    strcpy(::username,cust.username);
    strcpy(::password,cust.password);
    ++chk; //counter to check if username and pass is correct
   }
  }

  fin.close();
  return(chk);//if chk=0 then details entered are wrong
 }
//___________________________________________________________________________
 void del()  //To let the customer delete the account
 { char ch;
  cust.display(0);
  cout<<endl<<endl<<endl<<"Are you sure you want to delete the account(Y(y)/N(n))\n";
  cin>>ch;
  if(ch=='Y'||ch=='y')
  {
   ifstream dat("customer.txt",ios::in|ios::binary);     //to delete the record from file
   ofstream dat1("cust_dub.txt",ios::out|ios::binary);
   while(dat.read((char*)&cust,sizeof(cust)))
   {
    if(strcmp(::username,cust.username)!=0&&strcmp(::password,cust.password)!=0)
    dat1.write((char*)&cust,sizeof(cust));
   }
   dat.close();
   dat1.close();
   remove("customer.txt");
   rename("cust_dub.txt","customer.txt");
  }
 }
 //________________________________________________________________________

 int mod()  //To let the customer modify the account
 {
  char ch;
  cust.display(0);
  cout<<endl<<endl<<endl<<"Are you sure you want to modify the account(Y(y)/N(n))\n";
  cin>>ch;

  if(ch=='Y'||ch=='y')//To modify the record in a file
  {
   fstream fout("customer.txt",ios::out|ios::in|ios::binary);
   while(fout.read((char*)&cust,sizeof(cust)))
   {
    if(strcmp(cust.username,::username)==0 && strcmp(cust.password,::password)==0)
    {
     clrscr();
     title(1);
     cust.insert();
     fout.seekp(fout.tellg()-sizeof(cust));
     fout.write((char*)&cust,sizeof(cust));
     strcpy(::name,cust.name);    //saves new details in global variable
     strcpy(::add,cust.add);
     strcpy(::phone,cust.phone);
     strcpy(::username,cust.username);
     strcpy(::password,cust.password);
    }
   }
   return(1);
  }
 }
//__________________________________________________________________________
void display(int a) //Login as existing cust-->Manage your account-->Display your account
 {
  if(a==0)
  {
   gotoxy(26,7);
  for(int i=0,j=26;i<30;j++,i++)
  {
   gotoxy(j,8);
   cout<<d3;
   gotoxy(j,22);
   cout<<d3;
  }
  for(i=0,j=9;i<13;i++,j++)
  {
   gotoxy(26,j);
   cout<<d1;
   gotoxy(55,j);
   cout<<d1;
  }

  gotoxy(26,8);
  cout<<d2;
  gotoxy(55,8);
  cout<<d4;
  gotoxy(26,22);
  cout<<d7;
  gotoxy(55,22);
  cout<<d6;

  gotoxy(29,10);
  cout<<"Details Of Your Account:";//Manage your account->Display your account
  gotoxy(29,12);
  cout<<"Name: ";
  gotoxy(29,14);
  cout<<"Phone Number: ";
  gotoxy(29,16);
  cout<<"Address: ";
  gotoxy(29,18);
  cout<<"Username: ";
  gotoxy(29,20);
  cout<<"Password: ";
  gotoxy(36,12);
  cout<<::name;
  gotoxy(44,14);
  cout<<::phone;
  gotoxy(38,16);
  cout<<::add;
  gotoxy(39,18);
  cout<<::username ;
  gotoxy(39,20);
  cout<<::password;
  }

  if(a==1)
  {
   gotoxy(26,7);
   for(int i=0,j=26;i<30;j++,i++)
   {
    gotoxy(j,8);
    cout<<d3;
    gotoxy(j,18);
    cout<<d3;
   }
   for(i=0,j=9;i<10;i++,j++)
   {
    gotoxy(26,j);
    cout<<d1;
    gotoxy(55,j);
    cout<<d1;
   }

   gotoxy(26,8);
   cout<<d2;
   gotoxy(55,8);
   cout<<d4;
   gotoxy(26,18);
   cout<<d7;
   gotoxy(55,18);
   cout<<d6;

   gotoxy(29,10);
   cout<<"Details Of Your Account:"; //in CHECKOUT
   gotoxy(29,12);
   cout<<"Name: ";
   gotoxy(29,14);
   cout<<"Phone Number: ";
   gotoxy(29,16);
   cout<<"Address: ";
   gotoxy(35,12);
   cout<<::name;
   gotoxy(44,14);
   cout<<::phone;
   gotoxy(38,16);
   cout<<::add;
   gotoxy(39,18);

  }
 }

}cust;
//___________________________________________________________________________
void title(int n)     //Title(Front page)
{
 for(int i=0;i<80;i++)
 cout<<"*";
 cout<<endl;
 if(n==0)
 {
  for(i=0;i<=28;i++)
  cout<<" ";
  textcolor(10);
  cprintf("Welcome To Food Colony \n");
  textcolor(WHITE);
  cout<<endl;                         //Introduction
  }
 else
 {
  for(i=0;i<=33;i++)
  cout<<" ";
  textcolor(13);
  cprintf("Food Colony \n");//for color
  textcolor(WHITE);
  cout<<endl;
 }
 for(i=0;i<80;i++)
 cout<<"*";
}
//_________________________________________________________________________
void load()//This function is called whenever we displayed LOADING...
{
 cout<<"\n\t\t\t\t   Loading...\n\n";
 char a=177, b=219;
 cout<<"\t\t    ";
 for (int i=0;i<=40;i++)
 cout<<a;
 cout<<"\r";
 cout<<"\t\t    ";
 for (i=0;i<=40;i++)
 {cout<<b;
  delay(100);
 }}
//__________________________________________________________________________
void descrip()//Starting page
{
 int i,j;
 textcolor(WHITE);

 title(0);

 cout<<"\n\n   Hungry and wondering about What to eat? Then Dealer Food is just the right \n    place for you. Find freedom of choice from thousands of restaurants and \n    cuisines.From traditional meals to well-known fast food restaurants like \n    Dominos, Pizza Hut and Subway along with delicate cuisines as Japanese, \n    and Punjabi, you can find it all. \n\n";

 for(i=5;i<25;i++)
 {
  gotoxy(1,i);
  cout<<"*";
  gotoxy(80,i);
  cout<<"*";
 }

 for(i=1;i<=80;i++)
 {
  gotoxy(i,24);
  cout<<"*";
 }

 gotoxy(16,15);
 cout<<d2;
 gotoxy(17,15);
 for(i=0,j=0;i<45;i++)
 cout<<d3;

 cout<<endl;
 cout<<"                 For any queries about us please contact us:\n";
 cout<<endl<<"\t\t          Mobile Number: 9611304829";
 cout<<"\n\t\t       Email ID: food_colony@gmail.com";

 gotoxy(61,15);
 cout<<d4;

 for(i=0,j=16;i<5;i++,j++)
 {
  gotoxy(16,j);
  cout<<d1;
  gotoxy(61,j);
  cout<<d1;
 }

 gotoxy(17,21);
 for(i=0;i<45;i++)
 cout<<d3;

 gotoxy(61,21);
 cout<<d6;
 gotoxy(16,21);
 cout<<d7;
 gotoxy(1,17);
 cout<<"*";
 gotoxy(1,18);
 cout<<"*";
 gotoxy(1,16);
 cout<<"*";
 gotoxy(1,19);
 cout<<"*";

ifstream dat("list.txt",ios::in|ios::binary);//checks if the file containig restaurant is empty or not
 while(dat.read((char*)&rest,sizeof(rest)))
 list++;//increments the var if a restaurant is there in the list
 dat.close();

 getch();
 clrscr();
 title(0);
}//______________________________________________________________________
int admin_login() //In (login as admin)
{
 int i=0,j=0;
 char user[100];
 char pass[100];
 gotoxy(10,9);
 cout<<"Enter the username and password to access the admin account:";
 for(i=12;i<16;i++)
 {
  gotoxy(25,i);
  cout<<d1;
  gotoxy(52,i);
  cout<<d1;
 }

 gotoxy(27,13);
 cout<<d8;
 gotoxy(52,13);
 cout<<d9;

 for(i=26;i<52;i++)
 {
  gotoxy(i,11);
  cout<<d3;
  gotoxy(i,13);
  cout<<d3;
  gotoxy(i,15);
  cout<<d3;
 }

 gotoxy(25,11);
 cout<<d2;
 gotoxy(52,11);
 cout<<d4;
 gotoxy(25,13);
 cout<<d8;
 gotoxy(52,15);
 cout<<d6;
 gotoxy(25,15);
 cout<<d7;

 gotoxy(27,12);
 cout<<"Username: ";  //Accepts the username and pass..

 gotoxy(27,14);
 cout<<"Password: ";

 gotoxy(37,12);
 gets(user);
 gotoxy(37,14);
 i=0;
 pass[0]=getch();
 while(pass[i]!=13)
 {
  i++;
  cout<<"*"; //to show password in ****...form
  pass[i]=getch();
 }
 pass[i]='\0';

 if(strcmp(pass,"BGS")==0&&strcmp(user,"BGS")==0) //password='BGS'                               //Password for admin
  j=1;

 cout<<endl;
if(j==1)
 return(1);
 else
 return(0);
}//______________________________________________________________________
int choice() //In (Login as an existing customer)
{
 loop:
 int a;
cout<<endl<<endl<<"WELCOME "<<formal; //'formal' is a var storing the cust name
gotoxy(26,7);
 for(int i=0,j=26;i<30;j++,i++)
 {gotoxy(j,8);
  cout<<d3;
  gotoxy(j,23);
  cout<<d3;
 }
 for(i=0,j=9;i<14;i++,j++)
 {
  gotoxy(26,j);
  cout<<d1;
  gotoxy(55,j);
  cout<<d1;
 }

 gotoxy(26,8);
 cout<<d2;
 gotoxy(55,8);
 cout<<d4;
 gotoxy(26,23);
 cout<<d7;
 gotoxy(55,23);
 cout<<d6;

 gotoxy(36,9);   //Options under (Login as cust->Main menu)
 cout<<"Main Menu:";
 gotoxy(29,11);
 cout<<"1.Order your food\n";
 gotoxy(29,13);
 cout<<"2.Display your cart\n";
 gotoxy(29,15);
 cout<<"3.\Checkout\n";
 gotoxy(29,17);

 cout<<"4.Manage your account\n";
 gotoxy(29,19);
 cout<<"5.Logout\n";
 gotoxy(29,21);
 cout<<"Enter your choice: ";
 gotoxy(48,21);
 cin>>a;
 if(a<1||a>6)
 {
  cout<<"Invalid option.";
  getch();
  goto loop;
 }
 return(a);
}//_______________________________________________________________________
int order()//first option under Main menu(Order your food)
{
 char c[20],sl[30],ch;
 int opt,food,chk=0;
 loop1://Invoked if the cuisine no. is not correctly selected
 clrscr();
 title(1);

 gotoxy(26,7);
 for(int i=0,j=26;i<30;j++,i++)
 {
  gotoxy(j,8);
  cout<<d3;
  gotoxy(j,25);
  cout<<d3;
 }
 for(i=0,j=9;i<16;i++,j++)
 {
  gotoxy(26,j);
  cout<<d1;
  gotoxy(55,j);
  cout<<d1;
 }

 gotoxy(26,8);
 cout<<d2;
 gotoxy(55,8);
 cout<<d4;
 gotoxy(26,25);
 cout<<d7;
 gotoxy(55,25);
 cout<<d6;

 gotoxy(32,9);         //Inside (Order your food)
 cout<<"Enter the cuisine:";
 gotoxy(34,11);
 cout<<"1. Indian\n";
 gotoxy(34,13);
 cout<<"2. Italian\n";
 gotoxy(34,15);
 cout<<"3. Chinese\n";
 gotoxy(34,17);
 cout<<"4. Mexican";
 gotoxy(34,19);
 cout<<"5. Fastfoods";
 gotoxy(34,21);
 cout<<"6. Back";
 gotoxy(30,23);
 cout<<"Enter your choice: ";
 gotoxy(50,23);
 cin>>opt;

 if(opt==6)
 return(opt);

 if(opt==1)
 strcpy(c,"Indian");
 if(opt==2)
 strcpy(c,"Italian");
 if(opt==3)
 strcpy(c,"Chinese");
 if(opt==4)
 strcpy(c,"Mexican");
 if(opt==5)
 strcpy(c,"Fastfoods");

 if(opt>=7||opt<=0)
 {
  cout<<"Invalid Option.";
  getch();
  goto loop1;
 }

 loop2://Invoked if chk=0 i.e if user enters wrong sl no for the restaurant under a specific cuisine
 chk=0;

 rest.output_cuisine(c);

 cout<<endl<<"Enter the serial number of the restaurant: ";
 gets(sl);

 if(strcmp(sl,"0")==0)
 goto loop1;

 ifstream fin2("List.txt",ios::in|ios::binary);
 while(fin2.read((char*)&rest,sizeof(rest)))
 {
  if(strcmp(sl,rest.ret_rest())==0)
  chk++; //Incrementing chk if rest id entered by user is correct
 }
 fin2.close();

 if(chk==0)
 {
  cout<<"The serial number which you entered does not exist please try again.";
  getch();
  clrscr();
  title(1);
  goto loop2;
 }

 loop3:
 rest.show_food(sl);
 rest.enter_cart(sl);


 if(chk==0)
 goto loop2;

 cout<<"\n\nDo you want to buy more food from this restaurant? (Y(y)/N(n))\n";
 cin>>ch;

 if(ch=='y'||ch=='Y')
 goto loop3;//to purchase more items
 else
 goto loop2;
}//_______________________________________________________________________
int admin() //options Inside admin
{
 int opt1,opt2,opt3,chk;
 char ch,name[10],s[10];
 main:          //Invoked when wrong option is entered by the user
 clrscr();
 title(1);

 gotoxy(26,7);
 for(int i=0,j=26;i<30;j++,i++)
 {
  gotoxy(j,7);
  cout<<d3;
  gotoxy(j,24);
  cout<<d3;
 }
 for(i=0,j=8;i<16;i++,j++)
 {
  gotoxy(26,j);
  cout<<d1;
  gotoxy(55,j);
  cout<<d1;
 }

 gotoxy(26,7);
 cout<<d2;
 gotoxy(55,7);
 cout<<d4;
 gotoxy(26,24);
 cout<<d7;
 gotoxy(55,24);
 cout<<d6;

 gotoxy(38,8);        //Options inside ADMIN
 cout<<"ADMIN:";
 gotoxy(29,10);
 cout<<"1.Add a restaurant\n";
 gotoxy(29,12);
 cout<<"2.Delete a restaurant\n";
 gotoxy(29,14);
 cout<<"3.Display the restaurants\n";
 gotoxy(29,16);
 cout<<"4.Modify a restaurant\n";
 gotoxy(29,18);
 cout<<"5.Manage a restaurant\n";
 gotoxy(29,20);
 cout<<"6.Back to login screen\n\n";
 gotoxy(29,23);
 cout<<"Enter your choice: ";
 gotoxy(40,30);
 cin>>opt1;

 if(opt1<0&&opt1>6)
 {
  cout<<"\nInvalid option.";
  getch();
  goto main;
 }
 switch(opt1)
 {
  case 1:loop:  //(Admin-->Add a restaurant)
	 clrscr();
	 title(1);
	 rest.input();
	 clrscr();
	 title(1);
	 rest.output();
	 cout<<"\nDo you want to add more restaurants ? (Y(y) /N(n))\n";
	 cin>>ch;
	 if(ch=='Y'||ch=='y')
	 goto loop;
	 else
	 goto main;

  case 2:loop2://(Admin-->Delete a restaurant)
	 clrscr();
	 title(1);
	 cout<<endl;
	 if(list>0)
	 {
	  chk=rest.del();
	  if(chk!=0)
	  {
	   clrscr();
	   title(1);
	   cout<<endl;
	   rest.output();
	   cout<<"\nDo you want to delete any more restaurant? (Y / N)\n";
	   cin>>ch;
	   if(ch=='Y'||ch=='y')
	   goto loop2;
	   else
	   goto main;
	  }
	  else
	  goto loop2;
	 }
	 else
	 {
	  rest.output();
	  goto main;
	 }

  case 3:clrscr(); //Admin-->Display restaurants)
	 title(1);
	 rest.output();
	 goto main;

  case 4:loop4: //Admin-->Modify the restaurants)
	 clrscr();
	 title(1);
	 chk=rest.mod_rest();
	 if(chk==1)
	 goto loop4;
	 else
	 goto main;

  case 5:loopManage://Admin-->Manage the restaurant)
	 clrscr();
	 title(1);

	 if(list>0)
	 {
	  gotoxy(26,8);
	  for(int i=0,j=26;i<30;j++,i++)
	  {
	   gotoxy(j,8);
	   cout<<d3;
	   gotoxy(j,23);
	   cout<<d3;
	  }
	  for(i=0,j=9;i<14;i++,j++)
	  {
	   gotoxy(26,j);
	   cout<<d1;
	   gotoxy(55,j);
	   cout<<d1;
	  }

	  gotoxy(26,8);
	  cout<<d2;
	  gotoxy(55,8);
	  cout<<d4;
	  gotoxy(26,23);
	  cout<<d7;
	  gotoxy(55,23);
	  cout<<d6;

	  gotoxy(38,9);
	  cout<<"MANAGE";//options under manage restaurants in admin
	  gotoxy(29,11);
	  cout<<"1.Add a food item";
	  gotoxy(29,13);
	  cout<<"2.Delete a food item";
	  gotoxy(29,15);
	  cout<<"3.Display the food itmes:";
	  gotoxy(29,17);
	  cout<<"4.Modify the food items";
	  gotoxy(29,19);
	  cout<<"5.Back to admin\n";
	  gotoxy(29,21);
	  cout<<"Enter your choice: ";
	  gotoxy(49,21);
	  cin>>opt3;

	  if(opt3==1)//(Admin->Manage->add food)
	  {
	   enter_loop:
	   clrscr();
	   title(1);
	   rest.output();
	   chk=rest.enter_food();
	   if(chk==0)
	   goto enter_loop;
	   else
	   goto loopManage;
	  }
	  else if(opt3==2)//(Admin->manage->delete)
	  {
	   clrscr();
	   title(1);
	   rest.output();
	   cout<<"\nEnter the serial number of the restaurant whose food you want to delete: \n";
	   gets(s);
	   rest.del_food(s);
	   goto loopManage;
	  }
	  else if(opt3==3)//(Admin->manage->display food)
	  {
	   chk:
	   clrscr();
	   title(1);
	   rest.output();
	   cout<<"\nEnter the serial number of the restaurant whose food you want to display: \n";
	   gets(s);
	   opt3=rest.show_food(s);
	   if(opt3==0)
	   goto chk;
	   goto loopManage;
	  }

	  else if(opt3==4)//Admin->Manage->Modify)
	  {
	   loop5:
	   clrscr();
	   title(1);
	   chk=rest.mod_food();
	   if(chk==1)
	   goto loop5;
	   else
	   goto loopManage;

	  }

	  else if(opt3==5)  //to go back to main menu
	  goto main;

	  else
	  { cout<<"\nInvalid option.";
	    getch();
	    goto loopManage;
	  }
	 }

	 else
	 {
	  rest.output();
	  goto main;
	 }

  case 6: return(1);//to go back to login screen

  default:cout<<"Invalid option.";
	  getch();
	  goto main;
  }
 return(0);
}//__________________________________________________________________________
void main_login()          //Login for the customer
{
 Customer cust;               //Creation of an object for class Customer
 int opt,z,i,j,chk;
 char ch;
 main:
 clrscr();
 title(0);

 ofstream fout("bill.txt",ios::out|ios::binary);
 fout.close();

 textcolor(11);
cprintf("\n\n\n\n                         Please login to order from us:");//cprintf is used for color
 textcolor(WHITE);

 gotoxy(23,11);
 cout<<d2;

 gotoxy(24,11);
 for(i=0;i<34;i++)
 cout<<d3;

 gotoxy(57,18);
 cout<<d6;

 gotoxy(23,18);
 cout<<d7;

 gotoxy(57,11);
 cout<<d4;

 for(i=0,j=12;i<6;i++,j++)
 {
  gotoxy(23,j);
  cout<<d1;
  gotoxy(57,j);
  cout<<d1;
 }
 gotoxy(25,12);   //options given to a customer
 cout<<"1.Login as an existing customer";
 gotoxy(25,13);
 cout<<"2.Create a new account";
 gotoxy(25,14);
 cout<<"3.Login as an admin";
 gotoxy(25,15);
 cout<<"4.Exit";
 gotoxy(25,17);
 cout<<"Enter your option: ";

 gotoxy(24,18);
 for(i=0;i<33;i++)
 cout<<d3;

 //Pizza pic
 gotoxy(2,17);
 cout<<"// ''--.._\n||  (_)  _ '-._\n||    _ (_)    '-.\n||   (_)   __..-'\n \\__..--'''";

 gotoxy(44,17);
 cin>>opt;//options in login menu
 switch(opt)
 {
  case 1:loop:  //login as existing cust
	 clrscr();
	 title(1);

	 chk=cust.check();
	 cout<<endl;
	 load();
	 cout<<endl;

	 if(chk==0)
	 {
	  cout<<endl<<"\tThe username or password which you have entered is wrong.\n\t     Would you like to try again? (Y / N): ";
	  cin>>ch;
	  if(ch=='Y'||ch=='y')
	  goto loop;
	  else
	  goto main;
	 }
	 break;

  case 2:clrscr();//to create a new account on main page
	 title(1);
	 cust.insert();
	 fstream fout("customer.txt",ios::app|ios::binary);
	 fout.write((char*)&cust,sizeof(cust));
	 fout.close();
	 load();
	 cout<<"\n\t\t   Your account has been successfully created.";
	 getch();
	 break;

  case 3:loop2: //login as an admin
	 clrscr();
	 title(1);
	 z=admin_login();
	 cout<<endl;
	 load();
	 cout<<endl;
	 if(z==1)
	 {
	  clrscr();
	  i=admin();
	  if(i==1)
	  {
	   goto main;
	  }
	 }
	 else
	 {
	  cout<<endl<<"\nWrong Password";
	  cout<<endl<<"Do you want to go back or try again? (Y / N): ";
	  cin>>ch;
	  if(ch=='Y'||ch=='y')
	  {
	   goto loop2;
	  }
	  else
	  {
	   goto main;
	  }
	 }

  case 4:exit(1);//to go back to code window

  default:cout<<"\nInvalid option.";
	  getch();
	  goto main;
 }
}//__________________________________________________________________________
int payment() //Login as existing customer->checkout..
{
 int choice,cvv,opt,i,j;
 char name[30],number[30],expiry[20];

 loop:
 clrscr();
 title(1);

 gotoxy(26,7);
 for(i=0,j=26;i<30;j++,i++)
 {
  gotoxy(j,8);
  cout<<d3;
  gotoxy(j,21);
  cout<<d3;
 }
 for(i=0,j=9;i<12;i++,j++)
 {
  gotoxy(26,j);
  cout<<d1;
  gotoxy(55,j);
  cout<<d1;
 }

 gotoxy(26,8);
 cout<<d2;
 gotoxy(55,8);
 cout<<d4;
 gotoxy(26,21);
 cout<<d7;
 gotoxy(55,21);
 cout<<d6;

 gotoxy(33,9);     //inside checkout
 cout<<"Payment Method:";
 gotoxy(29,11);
 cout<<"1.Credit Card";
 gotoxy(29,13);
 cout<<"2.Debit Card";
 gotoxy(29,15);
 cout<<"3.Cash On Delivery";
 gotoxy(29,17);
 cout<<"4.Go Back To Main Menu";
 gotoxy(29,19);
 cout<<"Enter your choice: ";
 gotoxy(48,19);
 cin>>choice;

 if(choice>4||choice<1)
 {
  gotoxy(48,19);
  cout<<"Invalid Option";
  getch();
  goto loop;
 }

 switch(choice) //to execute the payment method
 {
  case 1:loop1://payment by credit card
	 clrscr();
	 title(1);

	 for(i=0,j=16;i<50;i++,j++)
	 {
	  gotoxy(j,7);
	  cout<<d3;
	  gotoxy(j,24);
	  cout<<d3;
	 }

	 for(i=0,j=8;i<17;i++,j++)
	 {
	  gotoxy(16,j);
	  cout<<d1;
	  gotoxy(65,j);
	  cout<<d1;
	 }
	 gotoxy(32,9);
	 cout<<"Credit Card Details:";
	 for(i=0,j=17;i<48;i++,j++)
	 {
	  gotoxy(j,11);
	  cout<<d3;
	 }
	 gotoxy(19,12);
	 cout<<" Choose the type of card which you possess:";
	 gotoxy(19,13);
	 cout<<"1.Visa    ";
	 cout<<"2.Master Card    ";
	 cout<<"3.American Express";
	 gotoxy(19,15);
	 cout<<"Your choice: ";
	 for(i=0,j=17;i<48;i++,j++)
	 {
	  gotoxy(j,16);
	  cout<<d3;
	 }
	 gotoxy(19,17);
	 cout<<"Enter the name on the card: ";
	 for(i=0,j=17;i<48;i++,j++)
	 {
	  gotoxy(j,18);
	  cout<<d3;
	 }
	 gotoxy(19,19);
	 cout<<"Enter the card number: ";
	 for(i=0,j=17;i<48;i++,j++)
	 {
	  gotoxy(j,20);
	  cout<<d3;
	 }
	 gotoxy(19,21);
	 cout<<"Enter the expiry date: ";
	 for(i=0,j=17;i<48;i++,j++)
	 {
	  gotoxy(j,22);
	  cout<<d3;
	 }
	 gotoxy(19,23);
	 cout<<"Enter the CVV number: ";

	 gotoxy(16,7);
	 cout<<d2;
	 gotoxy(16,11);
	 cout<<d8;
	 gotoxy(16,16);
	 cout<<d8;
	 gotoxy(16,18);
	 cout<<d8;
	 gotoxy(16,20);
	 cout<<d8;
	 gotoxy(16,22);
	 cout<<d8;
	 gotoxy(16,24);
	 cout<<d7;
	 gotoxy(65,7);
	 cout<<d4;
	 gotoxy(65,11);
	 cout<<d9;
	 gotoxy(65,16);
	 cout<<d9;
	 gotoxy(65,18);
	 cout<<d9;
	 gotoxy(65,20);
	 cout<<d9;
	 gotoxy(65,22);
	 cout<<d9;
	 gotoxy(65,24);
	 cout<<d6;


	 gotoxy(32,15);
	 cin>>opt;

	 if(opt<1||opt>3)
	 {
	  gotoxy(32,15);
	  cout<<"Invalid option. Try Again";
	  getch();
	  goto loop1;
	 }

	 gotoxy(47,17);
	 gets(name);
	 gotoxy(42,19);
	 gets(number);
	 gotoxy(42,21);
	 gets(expiry);
	 gotoxy(41,23);
	 cin>>cvv;

	 clrscr();
	 title(1);
	 cout<<endl;
	 load();
	 clrscr();
	 title(1);
	 cout<<"\n\n Your items will be delivered within the next 45 minutes.\n Thank you for ordering your mouth watering foods from us.\n We hope to see you again :D ";
	 getch();
	 return(0);

  case 2:loop2: //payment by debit card
	 clrscr();
	 title(1);

	 for(i=0,j=16;i<50;i++,j++)
	 {
	  gotoxy(j,7);
	  cout<<d3;
	  gotoxy(j,24);
	  cout<<d3;
	 }

	 for(i=0,j=8;i<17;i++,j++)
	 {
	  gotoxy(16,j);
	  cout<<d1;
	  gotoxy(65,j);
	  cout<<d1;
	 }
	 gotoxy(32,9);
	 cout<<"Debit Card Details:";
	 for(i=0,j=17;i<48;i++,j++)
	 {
	  gotoxy(j,11);
	  cout<<d3;
	 }
	 gotoxy(19,12);
	 cout<<" Choose the type of card which you possess:";
	 gotoxy(19,13);
	 cout<<"1.Visa    ";
	 cout<<"2.Master Card    ";
	 cout<<"3.American Express";
	 gotoxy(19,15);
	 cout<<"Your choice: ";
	 for(i=0,j=17;i<48;i++,j++)
	 {
	  gotoxy(j,16);
	  cout<<d3;
	 }
	 gotoxy(19,17);
	 cout<<"Enter the name on the card: ";
	 for(i=0,j=17;i<48;i++,j++)
	 {
	  gotoxy(j,18);
	  cout<<d3;
	 }
	 gotoxy(19,19);
	 cout<<"Enter the card number: ";
	 for(i=0,j=17;i<48;i++,j++)
	 {
	  gotoxy(j,20);
	  cout<<d3;
	 }
	 gotoxy(19,21);
	 cout<<"Enter the expiry date: ";
	 for(i=0,j=17;i<48;i++,j++)
	 {
	  gotoxy(j,22);
	  cout<<d3;
	 }
	 gotoxy(19,23);
	 cout<<"Enter the CVV number: ";

	 gotoxy(16,7);
	 cout<<d2;
	 gotoxy(16,11);
	 cout<<d8;
	 gotoxy(16,16);
	 cout<<d8;
	 gotoxy(16,18);
	 cout<<d8;
	 gotoxy(16,20);
	 cout<<d8;
	 gotoxy(16,22);
	 cout<<d8;
	 gotoxy(16,24);
	 cout<<d7;
	 gotoxy(65,7);
	 cout<<d4;
	 gotoxy(65,11);
	 cout<<d9;
	 gotoxy(65,16);
	 cout<<d9;
	 gotoxy(65,18);
	 cout<<d9;
	 gotoxy(65,20);
	 cout<<d9;
	 gotoxy(65,22);
	 cout<<d9;
	 gotoxy(65,24);
	 cout<<d6;


	 gotoxy(32,15);
	 cin>>opt;

	 if(opt<1||opt>3)
	 {
	  gotoxy(32,15);
	  cout<<"Invalid option. Try Again";
	  getch();
	  goto loop2;
	 }

	 gotoxy(47,17);
	 gets(name);
	 gotoxy(42,19);
	 gets(number);
	 gotoxy(42,21);
	 gets(expiry);
	 gotoxy(41,23);
	 cin>>cvv;

	 clrscr();
	 title(1);
	 cout<<endl;
	 load();
	 clrscr();
	 title(1);
	 cout<<"\n\n Your items will be delivered within the next 45 minutes.\n Thank you for ordering your mouth watering foods from us.\n We hope to see you again :D ";
	 getch();
	 return(0);

  case 3:clrscr(); //COD method
	 title(1);
	 cout<<"\n\n Your items will be delivered within the next 45 minutes.\n Thank you for ordering your mouth watering foods from us.\n We hope to see you again :D ";
	 getch();
	 return(0);

  case 4: return(4);

  default: cout<<endl<<"Invalid option.";
	   getch();
	   goto loop;
 }
}
//________________________________________________________________________
void stars()//first page design
{
 randomize();
 int j;
 for(int i=0;i<550;i=i+20)
 {
  setcolor(62);
  j=random(600);
  outtextxy(j,i,"*");//to dispaly the design
 }
}//_________________________________________________________________________
void graphics()
{
int gdriver = DETECT, gmode;
initgraph(&gdriver,&gmode,"\\TC\\BGI");

for(int i=0,j=-300;i<1000;i++,j++)
{
 settextstyle(2,HORIZ_DIR,8);
 stars();
 settextstyle(6,HORIZ_DIR,8);
 setcolor(5);
 outtextxy(160,j,"WELCOME");
 outtextxy(161,j+1,"WELCOME");
 outtextxy(162,j+2,"WELCOME");
 outtextxy(163,j+3,"WELCOME");
 outtextxy(165,j+4,"WELCOME");
 outtextxy(166,j+5,"WELCOME");
 outtextxy(167,j+6,"WELCOME");
 outtextxy(168,j+7,"WELCOME");
 outtextxy(169,j+8,"WELCOME");
 outtextxy(170,j+9,"WELCOME");

 cleardevice();
}

stars();
for( i=0,j=500;i<1450;i++,j--)
{
 settextstyle(2,HORIZ_DIR,8);
 stars();
 settextstyle(6,HORIZ_DIR,8);
 setcolor(3);
 outtextxy(j,150,"TO");
 outtextxy(j+1,150,"TO");
 outtextxy(j+2,150,"TO");
 outtextxy(j+3,150,"TO");
 outtextxy(j+4,150,"TO");
 outtextxy(j+5,150,"TO");
 outtextxy(j+6,150,"TO");
 outtextxy(j+7,150,"TO");
 outtextxy(j+8,150,"TO");
 outtextxy(j+9,150,"TO");
 outtextxy(j+10,150,"TO");
 outtextxy(j+11,150,"TO");
 outtextxy(j+12,150,"TO");
 outtextxy(j+13,150,"TO");

 cleardevice();
}

stars();
for( i=0,j=-450;i<1450;i++,j++)
{
 settextstyle(2,HORIZ_DIR,8);
 stars();
 settextstyle(6,HORIZ_DIR,8);
 setcolor(7);
 outtextxy(j,150,"FOOD COLONY");
 outtextxy(j+1,150,"FOOD COLONY");
 outtextxy(j+2,150,"FOOD COLONY");
 outtextxy(j+3,150,"FOOD COLONY");
 outtextxy(j+4,150,"FOOD COLONY");
 outtextxy(j+5,150,"FOOD COLONY");
 outtextxy(j+6,150,"FOOD COLONY");
 outtextxy(j+7,150,"FOOD COLONY");
 outtextxy(j+8,150,"FOOD COLONY");
 outtextxy(j+9,150,"FOOD COLONY");
 outtextxy(j+10,150,"FOOD COLONY");
 cleardevice();
}
closegraph();
}//_________________________________________________________________________
void main()
{
 remove("bill.txt");
 clrscr();
 //graphics();
 textcolor(WHITE);
 clrscr();
 int opt,i=0,z,chk;
 randomize();
 Bill=random(2001);//displays the bill number randomly
 char ch;
 descrip();

 start:
 main_login();
 MainMenu: //Bookmark
 clrscr();
 title(0);
 opt=choice();

 switch(opt) //Main menu(Login as existing)
 {
  case 1:opt=order();
	 if(opt==6)
	 {
	  goto MainMenu;
	 }
	 getch();
	 break;

  case 2:check:     //login as existing cust->Display your cart
	 clrscr();
	 title(1);
	 cout<<"\nYour cart\n";
	 rest.display_cart();
	 cout<<endl<<"\n1.Do you want to delete any items\n2.Back to main menu\n\nEnter your choice: ";
	 cin>>opt;

	 cout<<endl<<endl;
	 switch(opt)   //nested switch 1
	 {
	  case 1:clrscr();
		 title(1);
		 rest.del_cart();
		 cout<<endl;
		 load();
		 clrscr();
		 title(1);
		 rest.display_cart();
		 cout<<endl<<"The item was successfully removed.";
		 goto check;

	 case 2:goto MainMenu;

	 default:cout<<"\nInvalid option.";
		 getch();
		 goto check;
	 }

  case 3:clrscr();  //for checkout
	 title(1);
	 cout<<"\nCheckout:\n";
	 cout<<endl;
	 load();
	 clrscr();
	 title(1);
	 cout<<"\nCheckout:\n\n";
	 cust.display(1);
	 getch();
	 clrscr();
	 title(1);
	 cout<<endl;
	 cout<<setw(50)<<"Your cart: \n";
	 rest.display_cart();
	 getch();
	 chk=payment();

	 if(chk==4)
	 goto MainMenu;

	 else if(chk==0)
	 goto start;

	 goto MainMenu;


  case 4:loop: //login as cust->manage your account
	 clrscr();
	 title(1);

	 gotoxy(26,8);
	 for(int i=0,j=26;i<30;j++,i++)
	 {
	  gotoxy(j,8);
	  cout<<d3;
	  gotoxy(j,21);
	  cout<<d3;
	 }
	 for(i=0,j=9;i<12;i++,j++)
	 {
	  gotoxy(26,j);
	  cout<<d1;
	  gotoxy(55,j);
	  cout<<d1;
	 }
	 gotoxy(26,8);
	 cout<<d2;
	 gotoxy(55,8);
	 cout<<d4;
	 gotoxy(26,21);
	 cout<<d7;
	 gotoxy(55,21);
	 cout<<d6;

	 gotoxy(32,9);
	 cout<<"ACCOUNT MANAGEMENT:";
	 gotoxy(29,11);
	 cout<<"1.Modify your account";
	 gotoxy(29,13);
	 cout<<"2.Delete your account";
	 gotoxy(29,15);
	 cout<<"3.Display your account";
	 gotoxy(29,17);
	 cout<<"4.Back to main menu";
	 gotoxy(29,19);
	 cout<<"Enter your choice: ";
	 gotoxy(49,19);
	 cin>>opt;
    /* */switch(opt)  //nested switch 2
	 {
	  case 1:clrscr(); //login as existing customer->Manage->Modify
		 title(1);
		 opt=cust.mod();
		 if(opt==1)
		 {
		  cout<<endl;
		  load();
		  cout<<endl<<endl<<"Your account has been successfully modified.";
		  getch();
		 }
		 goto MainMenu;

	  case 2:clrscr(); //login as existing customer->Manage->Delete
		 title(1);
		 cust.del();
		 cout<<endl;
		 load();
		 cout<<endl<<"Your account has been successfully deleted.";
		 goto start;

	  case 3:clrscr();//login as existing cust->manage->display
		 title(1);
		 cout<<endl;
		 load();
		 clrscr();
		 title(1);
		 cout<<endl;
		 cust.display(0);
		 getch();
		 goto loop;
	  case 4:goto MainMenu;
	  default: cout<<"\nInvalid Option";
		   getch();
		   goto MainMenu;
	 }
  case 5:goto start;
 }                     /****************/
}//_________________________________________________________________________