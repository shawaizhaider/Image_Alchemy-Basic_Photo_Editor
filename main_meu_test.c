#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <time.h>

int i,j,main_exit;
void menu();
void new_entry();
void edit();
void view_list();
void erase();
void see();
void sorter();
void closer();

struct date{
int month,day,year;
};
struct {
char name[120];
int age;
char city[120];
char mail_id[60];
char room_no[8];
char father_name[60];
int father_phone_no[11];
int phone_no[11];
char hostel_name[6];
char hostel_id[10];
struct date dob;
int rent_paid;
}add,upd,check,rem,sort;

int main(){
system("color 0b");
pass();
menu();
return 0;
}

void menu(){
system("CLS");
int choice;
system("color 07");
printf("\n\n\t\t\t\tHOSTEL MANAGEMENT SYSTEM");
printf("\n\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
printf("\n\n");
printf("\t\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
printf("\t\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  Enter new Student[1] \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  Update student information[2] \xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  Check student details [3]     \xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  View all Students[4]          \xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  Remove existing Student[5]    \xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  View all students list[6]  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
printf("\t\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
printf("\t\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
    printf("\n \t\t Today is: ");
    tm();//time call
    printf("\n\t\t Please Enter Your Choice(7 to exit): ");
scanf("%d",&choice);
switch(choice)
{
case 1:
    system("cls");
    system("color 0a");
    new_entry();
break;
case 2:
    system("cls");
    system("color 0f");
    edit();
break;
case 3:see();
break;
case 4:sorter();
break;
case 5:erase();
break;
case 6:view_list();
break;
case 7:closer();
break;
default:
printf("Wrong Choice! \a");
delay(100);
menu();
}
}
int delay(unsigned int mseconds)
{
clock_t goal=mseconds+clock();
while(goal>clock());
}
int tm ()
{
		time_t mytime;
		mytime = time(NULL);
		printf(ctime(&mytime));
	return 0;
}
void sorter()
{
system("CLS");
int choice,test=0;
printf("Enter year choice:\n\n\t\t1. BH-1 \n\t\t2. BH-2 \n\t\t3. BH-3 \n\t\t4. GH-1 \n\n");
scanf("%d",&choice);
FILE *fp, *hostel;
switch(choice){
case 1: hostel=fopen("BH-1.dat","a+");break;
case 2: hostel=fopen("BH-2.dat","a+");break;
case 3: hostel=fopen("BH-3.dat","a+");break;
case 4: hostel=fopen("GH-1.dat","a+");break;
default: sorter();
}
while(fscanf(hostel,"%s\n",check.hostel_id)!=EOF){
fp=fopen("record.dat","r");
while(fscanf(fp,"%s %s %d/%d/%d %d %s %s %s %s %s %s %s %d\n",sort.hostel_id, sort.name, &sort.dob.month, &sort.dob.day, &sort.dob.year, &sort.age, sort.city, &sort.phone_no, sort.mail_id, sort.father_name, &sort.father_phone_no, sort.room_no, sort.hostel_name, &sort.rent_paid)!=EOF)
{
if(strcmp(check.hostel_id,sort.hostel_id)==0)
{
if(test==0)
{
printf("\t\tFollowing is the list of requested students:");
printf("\n\tHOSTEL ID.\tNAME\tROOM NO.\n");
}
printf("\n\t%8s\t %8s\t %s", sort.hostel_id, sort.room_no, sort.name);
test++;
}
}
}
fclose(fp);
if (test==0)
printf("\nNO RECORDS!!\n");
sort_list_invalid:
printf("\n\nEnter 1 to go to the main menu and 0 to exit:");
scanf("%d",&main_exit);
if (main_exit==1)
menu();
else if(main_exit==0)
closer();
else{
printf("\nInvalid!\a");
goto sort_list_invalid;
}
}
void new_entry()
{
system("CLS");
int choice;
FILE *ptr,*hostel;
ptr=fopen("record.dat","a+");
hostel_id:
printf("\t\t\t\xB2\xB2\xB2 ADD STUDENTS DATA  \xB2\xB2\xB2\xB2");
printf("\nEnter your hostel_id:");
scanf("%s",check.hostel_id);
while(fscanf(ptr,"%s %s %d/%d/%d %d %s %s %s %s %s %s %s %d\n",add.hostel_id, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.city, &add.phone_no, add.mail_id, add.father_name, &add.father_phone_no, add.room_no, add.hostel_name, &add.rent_paid)!=EOF)
{
if (strcmp(check.hostel_id,add.hostel_id)==0)
{printf("Students hostel_id already in use!");
goto hostel_id;
}
}
strcpy(add.hostel_id,check.hostel_id);
printf("\nEnter the name:");
scanf("%s",add.name);
printf("\nEnter the date of birth(mm/dd/yyyy):");
scanf("%d/%d/%d",&add.dob.month,&add.dob.day,&add.dob.year);
printf("\nEnter the age:");
scanf("%d",&add.age);
printf("\nEnter the city:");
scanf("%s",add.city);
printf("\nEnter the phone number:");
scanf("%s",&add.phone_no);
printf("\n Enter your email id :");
scanf("%s",add.mail_id);
printf("\n Enter your Father's name:");
scanf("%s",add.father_name);
printf("\n Enter your Father's phone no.:");
scanf("%s",&add.father_phone_no);
printf("\n --------------------------Each Hostel has 10 rooms------------------------!!!!");
printf("\n Enter your room no.:");
scanf("%s",add.room_no);
printf("\n Enter your hostel name from BH-1, BH-2, BH-3, GH-1 :");
scanf("%s",add.hostel_name);
printf("\n Total rent is:5000");
printf("\n Amount of rent paid: ");
scanf("%d" , &add.rent_paid);
fprintf(ptr,"%s %s %d/%d/%d %d %s %s %s %s %s %s %s %d\n",add.hostel_id, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.city, add.phone_no, add.mail_id, add.father_name, add.father_phone_no, add.room_no, add.hostel_name, add.rent_paid);
if(strcmp(add.hostel_name,"BH-1")==0){
hostel=fopen("BH-1.dat","a[11]");
fprintf(hostel, "%s\n", add.hostel_id);
fclose(hostel);
}
else if(strcmp(add.hostel_name,"BH-2")==0){
hostel=fopen("BH-2.dat","[11]");
fprintf(hostel, "%s\n", add.hostel_id);
fclose(hostel);
}
else if(strcmp(add.hostel_name,"BH-3")==0){
hostel=fopen("BH-3.dat","a[11]");
fprintf(hostel, "%s\n", add.hostel_id);
fclose(hostel);
}
else if(strcmp(add.hostel_name,"GH-1")==0){
hostel=fopen("GH-1.dat","[11]");
fprintf(hostel, "%s\n",add.hostel_id);
fclose(hostel);
}
fclose(ptr);
printf("\nStudent added successfully!");
add_invalid:
printf("\n\n\n\t\tEnter 1 to go to the main menu and 0 to exit:");
scanf("%d",&main_exit);
if (main_exit==1)
menu();
else if(main_exit==0)
closer();
else{
printf("\nInvalid!\a");
goto add_invalid;
}
}
void view_list()
{
system("CLS");
FILE *view;
view=fopen("record.dat","r");
int test=0;
printf("\nHOSTEL_ID\tNAME\t\t\tCity\t\t\tRENT PAID\t\t\tROOM ALLOTED\n");
while(fscanf(view,"%s %s %d/%d/%d %d %s %s %s %s %s %s %s %d\n",add.hostel_id, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.city, &add.phone_no, add.mail_id, add.father_name, &add.father_phone_no, add.room_no, add.hostel_name, &add.rent_paid)!=EOF)
{
printf("\n%8s\t %10s\t\t\t %10s\t\t %d\t\t\t %s",add.hostel_id,add.name,add.city,add.rent_paid,add.room_no);
test++;
}
fclose(view);
if (test==0){
printf("\nNO RECORDS!!\n");}
view_list_invalid:
printf("\n\nEnter 1 to go to the main menu and 0 to exit:");
scanf("%d",&main_exit);
if (main_exit==1)
menu();
else if(main_exit==0)
closer();
else{
printf("\nInvalid!\a");
goto view_list_invalid;
}
}
void see()
{
system("CLS");
FILE *ptr;
int test=0;
int choice;
ptr=fopen("record.dat","r");
printf("Do you want to check by\n1.Hostel id.\nEnter your choice:");
scanf("%d",&choice);
if (choice==1)
{   printf("\n\nEnter the hostel id:");
scanf("%s",check.hostel_id);
while (fscanf(ptr,"%s %s %d/%d/%d %d %s %s %s %s %s %s %s %d\n",add.hostel_id, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.city, &add.phone_no, add.mail_id, add.father_name, &add.father_phone_no, add.room_no, add.hostel_name, &add.rent_paid)!=EOF)
{
if(strcmp(add.hostel_id,check.hostel_id)==0)
{
test=1;
printf("\nhostel_id:%s\nName:%s \nDOB:%d/%d/%d \nAge:%d \ncity:%s \nPhone number:%s \nE-Mail id:%s \nFather's name:%s \n Father's Phone No.:%s \nRoom No:%s \nHostel:%s \nAdd.rent_paid :%d\n",add.hostel_id, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.city, add.phone_no, add.mail_id, add.father_name, add.father_phone_no, add.room_no, add.hostel_name, add.rent_paid);
}
}
}
fclose(ptr);
if(test!=1)
printf("\nRecord not found!!\a\a\a");
see_invalid:
printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
scanf("%d",&main_exit);
if (main_exit==1)
menu();
else if (main_exit==2)
closer();
else if(main_exit==0)
erase();
else{
printf("\nInvalid!\a");
goto see_invalid;
}
}
void edit()
{
system("CLS");
int choice,test=0;
FILE *old,*newrec;
old=fopen("record.dat","r");
newrec=fopen("new.dat","w");
printf("\nEnter the hostel id of the student whose info you want to change:");
scanf("%s",upd.hostel_id);
while(fscanf(old,"%s %s %d/%d/%d %d %s %s %s %s %s %s %s %d\n",add.hostel_id, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.city, &add.phone_no, add.mail_id, add.father_name, &add.father_phone_no, add.room_no, add.hostel_name, &add.rent_paid)!=EOF)
{
if (strcmp(add.hostel_id,upd.hostel_id)==0)
{   test=1;
printf("\nWhich information do you want to change?\n1.Room no.\n2.Phone\n\nEnter your choice(1 for room no. and 2 for phone ):");
scanf("%d",&choice);
if(choice==1)
{printf("Enter the new room no.:");
scanf("%s",upd.room_no);
fprintf(newrec,"%s %s %d/%d/%d %d %s %s %s %s %s %s %s %d\n",add.hostel_id, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.city, add.phone_no, add.mail_id, add.father_name, add.father_phone_no, upd.room_no, add.hostel_name, add.rent_paid);
printf("Changes saved!");
}else if(choice==2)
{
printf("Enter the new phone number:");
scanf("%d",&upd.phone_no);
fprintf(newrec,"%s %s %d/%d/%d %d %s %s %s %s %s %s %s %d\n",add.hostel_id, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.city, upd.phone_no, add.mail_id, add.father_name, add.father_phone_no, add.room_no, add.hostel_name, add.rent_paid);
printf("Changes saved!");
}
}else
fprintf(newrec,"%s %s %d/%d/%d %d %s %s %s %s %s %s %s %d\n",add.hostel_id, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.city, add.phone_no, add.mail_id, add.father_name, add.father_phone_no, add.room_no, add.hostel_name, add.rent_paid);
}
fclose(old);
fclose(newrec);
remove("record.dat");
rename("new.dat","record.dat");
if(test!=1)
printf("\nRecord not found!!\a\a\a");
edit_invalid:
printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
scanf("%d",&main_exit);
if (main_exit==1)
menu();
else if (main_exit==2)
closer();
else if(main_exit==0)
edit();
else{
printf("\nInvalid!\a");
goto edit_invalid;
}
}
void erase(){
system("CLS");
FILE *old,*newrec;
int test=0;
old=fopen("record.dat","r");
newrec=fopen("new.dat","w");
printf("Enter the Hostel_id of student whose data you want to delete:");
scanf("%s",rem.hostel_id);
while (fscanf(old,"%s %s %d/%d/%d %d %s %s %s %s %s %s %s %d\n",add.hostel_id, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.city, &add.phone_no, add.mail_id, add.father_name, &add.father_phone_no, add.room_no, add.hostel_name, &add.rent_paid)!=EOF)
{
if(strcmp(add.hostel_id,rem.hostel_id)!=0)
fprintf(newrec,"%s %s %d/%d/%d %d %s %s %s %s %s %s %s %d\n",add.hostel_id, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.city, add.phone_no, add.mail_id, add.father_name, add.father_phone_no, add.room_no, add.hostel_name, add.rent_paid);
else{test++;
printf("\nRecord deleted successfully!\n");
}
}
fclose(old);
fclose(newrec);
remove("record.dat");
rename("new.dat","record.dat");
if(test==0)
printf("\nRecord not found!!\a\a\a");
erase_invalid:
printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
scanf("%d",&main_exit);
if (main_exit==1)
menu();
else if (main_exit==2)
closer();
else if(main_exit==0)
erase();
else{
printf("\nInvalid!\a");
goto erase_invalid;
}
}
void closer()
{
system("CLS");
printf("\n\n\n*THANK YOU FOR USING THE SYSTEM*\n\n");
printf("\n\n visit www.programmingboss.com for more projects\n\n\n");
}
int pass(void)
{
int a=0,i=0;
char uname[10],c=' ';
char pword[10],code[10];
char user[10]="user";
char pass[10]="pass";
system("cls");
system("color e0");
int i1,j,l,l1;
char name[50]="\n\n\n\n\t\t\t  WELCOME TO OUR PROJECT\n\n";
printf("\t\n");
for(i1=0;i1<50;i1++){
printf("%c",name[i1]);
delay(20);
}
printf("\n\t   ");
for(j=0;j<59;j++){
printf("%c",2);
delay(30);
}
printf("\n\n\n\n");
system("cls");
system("color 0f");
printf("\n\n\n");
printf("\t\tName Of The Group is.........\n\n\n");
printf("\n\n\t");
for(j=0;j<6;j++){
printf("%c ",1678);
delay(50);
}
printf(" ARTIFICIAL  INTELLIGENCE  GROUP ");
for(j=0;j<6;j++){
printf("%c ",1678);
delay(50);
}
delay(1000);
printf("\n\n");
system("CLS");
system("color 1f");
printf("\n\n\n");
printf("\tName Of The Group Members Of \n\t\t");
char ame[10]="\tA I G :\n\n";
printf("\t\n");
for(l1=0;l1<10;l1++){
printf("%c",ame[l1]);
delay(150);
}
printf(" \n\t * ID:  - Group Member Name 01\n\n");
printf(" \t * ID:  - Group Member Name 02\n\n");
printf(" \t * ID:  - Group Member Name 03\n\n");
printf(" \t * ID:  - Group Member Name 04\n\n");
printf(" \t * ID:  - Group Member Name 05\n\n");
printf(" \t * ID:  - Group Member Name 06\n");
printf("\n");
system("pause");
system("CLS");
system("color 5e");
printf("\n\n\n\n\n\n");
printf("\t\t\tOur project on:\n\n");
printf("\n");
char nam[]="\n\n\t\t\tHostel Management System Project \n\n";
printf("\t\n");
for(l=0;l<40;l++){
printf("%c",nam[l]);
delay(40);
}
printf("\n\n\n");
delay(600);
do{
    system("cls");
    printf("\n  ***  LOGIN FORM  ***  ");
    printf(" \n                       ENTER USERNAME:-");
    scanf("%s", &uname);
    printf(" \n                       ENTER PASSWORD:-");
    while(i<10){
    pword[i]=getch();
    c=pword[i];
    if(c==13) break;
    else printf("*");
    i++;
    }
    pword[i]='\0';
    i=0;
    if(strcmp(uname,user)==0 && strcmp(pword,pass)==0){
    printf("  \n\n\n       WELCOME !!!! LOGIN IS SUCCESSFUL\n");
    system("cls");
    system("color 1a");
    printf("\n\n\n\n\n\n");
    printf("                                                           \n");
    printf("                                                           \n");
    printf("                      \t  Please Wait...\n\n\n\n\n");
    printf("                     ______________ _____________               \n");
    printf("                    /                             \\          \n");
    printf("                   |     Loading.............      |           \n");
    printf("\t\t   |\t");
    for(j=0;j<24;j++){
    printf("%c",219);
    delay(50);
    }
    printf("   |\n                    \\______________ ______________/           \n");
    printf("                                                           \n");
    printf("\n\n\n");
    //system("pause");
    delay(1000);
    break;
    }else{
    printf("\n        SORRY !!!!  LOGIN IS UNSUCESSFUL\n");
    system("PAUSE");
    a++;
    getch();
    }
    }
    while(a<=2);
    if (a>2)
    {
    printf("\nSorry you have entered the wrong user name and password for four times!!!");
    getch();
    }
    system("cls");
}