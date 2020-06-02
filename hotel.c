/*
	developed by- 
		master Suraj Kumar gupta
*/

#include<stdio.h>
#include<string.h>
struct room
{
    char name[100];
    int num;
    int fd,fm,fy,td,tm,ty;
    char status[20];
}a,a2;

struct details
{
    char name[100];
    char password[100];
}user;

struct date
{
	int d,m,y;
}b,r;




// ******************************************************************************************


int days (int fd, int fm, int fy, int td, int tm, int ty)
{
    if (fm==tm && fy==ty)
    {
        return td-fd;
    } 
    else if (fm!=tm || fy!=ty)
    {
        int day=0;
        while(fd!=td || fm!=tm || fy!=ty)
        {   
		    if (fd==31 && (fm==1 || fm==3 || fm==5 || fm==7 || fm==8 || fm==10 ))
		    {
		        fm++;
		        fd=1;
		    }
		    else if (fd==30 && (fm==4 || fm==6 || fm==9 || fm==11 ))
		    {
	        	fm++;
	    	    fd=1;
		    }
		    else if (fd==29 && fm==2 && ((fy%4==0 && fy%100!=0) || (fy%400==0)))
		    {
		        fm++;
		        fd=1;
		    }
		    else if (fd==28 && fm==2 && !((fy%4==0 && fy%100!=0) || (fy%400==0)))
		    {
		        fd=1;
		        fm=3;   
		    }
		    else if (fd==31 && fm==12)
		    {
		        fd=1;
		        fm=1;
		        fy++;
		    }   
		    else 
		    {
		        fd++;
		    }
		    day++;
        }
       	return day;
    }
}
// compare function for two dates(from and to of database and from and t from the user)
int compare(int fd1,int fm1,int fy1, int td1,int tm1,int ty1,int fd2,int fm2,int fy2,int td2,int tm2,int ty2 )
{
	int flag=0;
	if((fd1==fd2) && (fm1==fm2) && (fy1==fy2) && (td1==td2) && (tm1==tm2) && (ty1==ty2))
	{
		return 0;
	}

	if(fy2>ty1)
	{
		flag=1;
		return 1;
	}
	else if(fm2>tm1 && fy2>=ty1)
	{
		flag=1;
		return 1;
	}
	else if(fd2>=td1 && fm2>=tm1 && fy2>=ty1)
	{
		flag=1;
		return 1;
	}
	else if(ty2<fy1 && flag==0)
	{
		return 1;
	}
	else if(tm2<fm1 && flag==0 && ty2<=fy1)
	{
		return 1;
	}
	else if(td2<=fd1 && flag==0 && ty2<=fy1 && tm2<=fm1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//checking if the date entered is correct or not
int checkdate(int fd, int fm, int fy, int td, int tm, int ty)
{
	if(tm>12 || tm<=0 || td <= 0 || td>31 || fm>12 || fm<=0 || fd <= 0 || fd>31)
	{
		return 1;
	}
	else if((( tm == 4 || tm == 6 || tm == 9 || tm == 11) && td>30) || ((fm == 4 || fm == 6 || fm == 9 || fm == 11) && fd>30))
	{
		return 1;
	}
	else if((tm == 2 && td > 29 && ((ty%4 == 0 && ty%100 != 0) || ty%400 == 0)) || (tm == 2 && td > 28 && !((ty%4 == 0 && ty%100 != 0) || ty%400 == 0)))
	{
		return 1;
	}
	else if(fy > ty)
	{
		return 1;
	}
	else if(fy == ty)
	{
		if(fm>tm)
		{
			return 1;
		}
		else if(fm == tm)
		{
			if(fd>=td)
			{
				return 1;
			}
		}
	}
	return 0;
}

//checking if there is a room available in the user entered to and from date
int available(char name2[],int room,int fd,int fm,int fy,int td,int tm,int ty,char status2[])
{
		FILE *q;
		int f=0,flag1=0,d1,m1,y1,d2,m2,y2,i=0,j,g=0;
		q=fopen("database","r");
		do
		{
			fscanf(q,"%s : Room no. %d from %d %d %d to %d %d %d : %s",a2.name,&a2.num,&a2.fd,&a2.fm,&a2.fy,&a2.td,&a2.tm,&a2.ty,a2.status);
			if(a2.num==room)
			{
				if(compare(a2.fd,a2.fm,a2.fy,a2.td,a2.tm,a2.ty,fd,fm,fy,td,tm,ty)==0)
				{
					if(strcmp(a2.status,"Booked") == 0)
					{
						return 0;
					}
				}
				flag1=1;
			}
		}while(!feof(q));

		if(flag1==1)
		{
			fclose(q);
			return 1;
		}
}

//if the room is available then the user is alloted that room
int allot(char name1[],int type,int fd,int fm,int fy,int td,int tm,int ty,char status1[])
{
		int i;
		for(i=(type*100)+1;i<(type*100)+10;i++)
		{
			if(available(name1,i,fd,fm,fy,td,tm,ty,status1)==1)
			{
				return i;
			}
		}
		return 0;
}

int printroom(int choice)
{
	int choice1,num=0;
	num=allot(a.name,choice,a.fd,a.fm,a.fy,a.td,a.tm,a.ty,a.status);
	if(num==0)
	{  
		printf("\nSorry No room available of this type!\nTry another type:");
		scanf("%d",&choice1);
		printroom(choice1);
	}
	else
	{
		return num;
	}
}
int getchoice()
{
	int choice=0;
	printf("\nEnter Type of Room(Type 1 to 6):");
	scanf("%d",&choice);
	if(choice>6 || choice<1)
	{
		printf("\nChoice you entered is invalid.Enter a valid choice.\n\n");
		getchoice();
	}
	else
	{
		return choice;
	}
}

struct date check() 
{
	printf("Enter date in format dd mm yyyy: ");
	scanf("%d %d %d",&b.d,&b.m,&b.y);
	if(b.m>12 || b.m<=0 || b.d <= 0 || b.d>31) 
	{
		printf("Sorry the Date you entered is invalid please enter again\n\n");
		check();
	}
	else if((( b.m == 4 || b.m == 6 || b.m == 9 || b.m == 11) && b.d>30))
	{
		printf("Sorry the Date you entered is invalid please enter again\n\n");
		check();
	}
	else if((b.m == 2 && b.d > 29 && ((b.y%4 == 0 && b.y%100 != 0) || b.y%400 == 0)) || (b.m == 2 && b.d > 28 && !((b.y%4 == 0 && b.y%100 != 0) || b.y%400 == 0)))
	{
		printf("Sorry the Date you entered is invalid please enter again\n\n");
		check();
	}
	return b;
}

//booking mechanism
void book()
{
	FILE *p,*q;
	int b,n,i,count=0,flag1;
	long long int fare = 0;
	int price[6]={2500,2000,3500,3000,4500,5000};
	FILE *pass;
	do
	{
		flag1 = 0;
		printf("\nEnter Name: ");
    	scanf("%s",a.name);
		pass = fopen("user credentials","r");
		do
		{
			fscanf(pass,"%s : %s",user.name,user.password);
			if( strcmp(user.name,a.name) == 0 )
			{
				printf("\nYou are already an existing user\n\nEnter your password: ");
				char ipassword[100];
				scanf("%s",ipassword);
				if(strcmp(user.password,ipassword) == 0)
				{
					flag1 = 1;
				}
				else
				{
					flag1 = -1;
					printf("\nInvalid password, You will have to make a new account with a different name\n\n");
				}
				break;
			}
		}
		while( !feof(pass) );
		fclose(pass);
	}
	while(flag1 == -1);
	if(flag1 == 0)
	{		
		printf("You are a new user, please enter a password for your account: ");
		char ipassword[100];
		scanf("%s",ipassword);
		pass = fopen("user credentials","a");
		fprintf(pass,"%s : %s\n",a.name,ipassword);
		fclose(pass);
		flag1 = 1;
	}
	if (flag1 == 1)
	{
		printf("\nFROM date\n");
		r=check();
		a.fd=r.d;
		a.fm=r.m;
		a.fy=r.y;
		printf("\nTO date\n");
		r=check();
		a.td=r.d;
		a.tm=r.m;
		a.ty=r.y;
		b=checkdate(a.fd,a.fm,a.fy,a.td,a.tm,a.ty);
		while(b==1)
		{
			printf("\nThe dates you entered are not in proper order.Try again\n\n");
			printf("\nFROM date\n");
			r=check();
			a.fd=r.d;
			a.fm=r.m;
			a.fy=r.y;
			printf("\nTO date\n");
			r=check();
			a.td=r.d;
			a.tm=r.m;
			a.ty=r.y;
			b=checkdate(a.fd,a.fm,a.fy,a.td,a.tm,a.ty);
		}
		printf("\n\nHere are the type of rooms and their maximum occupancy with tariffs:\n  Type         Max Occupancy    Tariff(/Night)\n");
		printf("1.Single AC          1             Rs.2500\n2.Non AC Single      1             Rs.2000\n3.Double AC          2             Rs.3500\n4.Double Non AC      2             Rs.3000\n5.Duplex             4             Rs.4500\n6.Suite              5             Rs.5000\n");
		printf("\nEnter Number of Rooms you want:");
		scanf("%d",&n);
		int choice;
		while(1)
		{
			choice=getchoice();
			a.num=printroom(choice);
		    count++;
			printf("\nHey %s, your booking is successful and your room number is %d!!\n\n",a.name,a.num);
			fare+=days(a.fd,a.fm,a.fy,a.td,a.tm,a.ty)*price[choice-1];
			strncpy(a.status,"Booked",sizeof(a.status));
			p=fopen("database","a");
			fprintf(p,"%s : Room no. %d from %d %d %d to %d %d %d : %s Fare:%d\n",a.name,a.num,a.fd,a.fm,a.fy,a.td,a.tm,a.ty,a.status,days(a.fd,a.fm,a.fy,a.td,a.tm,a.ty)*price[choice-1]);
			fclose(p);
			if(count==n)
			{
				break;
			}
		}
		printf("Total fare is Rs.%lld\n\n",fare);
	}
}
// *********************************************************************************************
void view()
{
    char f1[11][36];

    for(int i=0;i<36;i++)
    {
        f1[0][i]='_';
        f1[10][i]='-';
    }
    for(int i=1;i<10;i++)
    {
        f1[i][0]='|';
        f1[i][35]='|';
    }
    for(int i=1;i<10;i++)
    {
        f1[i][1]=' ';
        f1[i][2]=' ';
        for(int j=10;j<15;j++)
        {
            f1[i][j]=' ';
        }
        for(int j=21;j<26;j++)
        {
            f1[i][j]=' ';
        }       
        f1[i][32]=' ';
        f1[i][33]=' ';
        f1[i][34]=' ';
    }
    for(int i=0;i<2;i++)
    {
        for(int j=3;j<10;j++)
        {
            f1[2*i+1][j]='-';
        }
        for(int j=14;j<21;j++)
        {
            f1[2*i+1][j]='-';
        }
        for(int j=25;j<32;j++)
        {
            f1[2*i+1][j]='-';
        }   
    }
    for(int i=2;i<4;i++)
    {
        for(int j=3;j<10;j++)
        {
            f1[2*i][j]='-';
        }
        for(int j=14;j<21;j++)
        {
            f1[2*i][j]='-';
        }
        for(int j=25;j<32;j++)
        {
            f1[2*i][j]='-';
        }   
    }
    for(int i=3;i<5;i++)
    {
        for(int j=3;j<10;j++)
        {
            f1[2*i+1][j]='-';
        }
        for(int j=14;j<21;j++)
        {
            f1[2*i+1][j]='-';
        }
        for(int j=25;j<32;j++)
        {
            f1[2*i+1][j]='-';
        }   
    }
    for(int i=0;i<3;i++)
    {
        f1[3*i+2][3]='|';
        f1[3*i+2][9]='|';
        f1[3*i+2][14]='|';
        f1[3*i+2][20]='|';
        f1[3*i+2][25]='|';
        f1[3*i+2][31]='|';
    }
    for(int i=0;i<3;i++)
    {
        f1[3*i+2][4]=' ';
        f1[3*i+2][5]=' ';
        f1[3*i+2][7]=' ';
        f1[3*i+2][8]=' ';
        f1[3*i+2][15]=' ';
        f1[3*i+2][16]=' ';
        f1[3*i+2][18]=' ';
        f1[3*i+2][19]=' ';
        f1[3*i+2][26]=' ';
        f1[3*i+2][27]=' ';
        f1[3*i+2][29]=' ';
        f1[3*i+2][30]=' ';
    }
    for(int i=0;i<3;i++)
    {
        
        f1[3*i+2][6]=(char)(3*i+1+48);
        f1[3*i+2][17]=(char)(3*i+2+48);
        f1[3*i+2][28]=(char)(3*i+3+48);
    }

    while(1)
    {
        int choice;
        printf("Enter your choice:\n 1.General floor\n 2.Exit\n");
        scanf("%d",&choice);
        if(choice==1)
        {
            printf("             sea facing\n");
            for(int i=0;i<11;i++)
            {
                for(int j=0;j<36;j++)
                {
                    printf("%c",f1[i][j] );
                }
                printf("\n");
            }
        }
        else
        {
            break;
        }
    }
}


//*************************************************************************************************

void cancel()
{
	int fare;
    struct details
    {
        char name[100];
        char password[100];
    }user;
    int flag = 0,flag1,control = 0;
    FILE *database,*q,*newdata,*pass;
    char nam[100];
    char ipassword[100];
    printf("\nPlease enter your name: ");
        scanf("%s",nam);
    printf("Enter your password: ");
    scanf("%s",ipassword);
    pass = fopen("user credentials","r");
    do
    {
        fscanf(pass,"%s : %s",user.name,user.password);
        if(strcmp(user.name,nam) == 0 && strcmp(user.password,ipassword) == 0)
        {
        flag1 = 1; 
        }
    }
    while( !feof(pass) );

    fclose(pass);
    if(flag1 == 1)
    {
    	int cntrl = 0;
        q = fopen("database","r");
        do
        {
           fscanf(q,"%s : Room no. %d from %d %d %d to %d %d %d : %s Fare:%d",a.name,&a.num,&a.fd,&a.fm,&a.fy,&a.td,&a.tm,&a.ty,a.status,&fare);
           if(feof(q))
            {
               break;
            }
            if(strcmp(a.name,nam) == 0)
            {
            	if(strcmp(a.status,"Booked") == 0)
            	{
            		cntrl++;
            	}
            	control++;
                flag = 1;
                printf("%d.) %s : Room no. %d from %d %d %d to %d %d %d : %s Fare:%d\n\n",control,a.name,a.num,a.fd,a.fm,a.fy,a.td,a.tm,a.ty,a.status,fare);
            }    
        }
        while( !feof(q) );

        if (flag == 0)
        {
           printf("Booking Not Found\n\n");
           return;
        }
        fclose(q);
        int flag2 = 0;
        int loop;
        do
        {
        	flag2 = 0;
        	printf("How many bookings do you want to cancel: ");
        	scanf("%d",&loop);
        	if(loop>cntrl)
        	{
        		printf("Invalid number of cancellatons\n\n");
        		flag2 = 1;
        		int choice;
        		printf("Do you want to continue with cancellation? Enter 1 to continue, 0 to return to main menu: ");
        		scanf("%d",&choice);
        		if (choice == 0)
        		{
        			return;
        		}
       		}
       	}
       	while(flag2 == 1);
        for(int i = 0; i<loop; i++)
        {
        	int ctr,ctr1 = 0;
        	flag2 = 0;
        	do
        	{
        		flag2 = 0;
            	printf("\nWhich number booking do you want to cancel: ");
            	database = fopen("database","a");
            	q = fopen("database","r");
            	newdata = fopen("newdatabase","w");
            	scanf("%d",&ctr);
            	if(ctr > control)
            	{
            		flag2 = 1;
            		printf("Booking does not exist\n\n");
            	}
            }
            while(flag2 == 1);
            do
            {
               fscanf(q,"%s : Room no. %d from %d %d %d to %d %d %d : %s Fare:%d" ,a.name,&a.num,&a.fd,&a.fm,&a.fy,&a.td,&a.tm,&a.ty,a.status,&fare);
               if(strcmp(a.name,nam) == 0)
               {
                    if( feof(q) )
                    {
                        break;
                    }
                    ctr1++;
                    if (ctr == ctr1)
                    {
                    	flag2 = 1;
                        if (strcmp(a.status,"Booked") == 0)
                        {
                            fprintf(newdata,"%s : Room no. %d from %d %d %d to %d %d %d : Cancelled Fare:%d\n",a.name,a.num,a.fd,a.fm,a.fy,a.td,a.tm,a.ty,fare);
                            printf("Your booking has been cancelled\n");
                        }
                        else
                        {
                        	printf("This booking has already been cancelled\n\n");
                        	int choice;
                        	printf("Do you want to continue with the cancellation? Enter 1 to continue, 0 to return to main menu: ");
                        	scanf("%d",&choice);
                        	if (choice == 0)
                        	{
                        		return;
                        	}
                        	fprintf(newdata,"%s : Room no. %d from %d %d %d to %d %d %d : Cancelled Fare:%d\n",a.name,a.num,a.fd,a.fm,a.fy,a.td,a.tm,a.ty,fare);
                        	loop++;
                        }
                    } 
                    else
                    {
                        fprintf(newdata,"%s : Room no. %d from %d %d %d to %d %d %d : %s Fare:%d\n",a.name,a.num,a.fd,a.fm,a.fy,a.td,a.tm,a.ty,a.status,fare);
                    }
                }
                else
                {
                    fprintf(newdata,"%s : Room no. %d from %d %d %d to %d %d %d : %s Fare:%d\n",a.name,a.num,a.fd,a.fm,a.fy,a.td,a.tm,a.ty,a.status,fare);
                }
            }
            while( !feof(q) );

            fclose(database);
            fclose(q);
            fclose(newdata);
            newdata = fopen("newdatabase","r");
            database = fopen("database","w");
            do
            {
                fscanf(newdata,"%s : Room no. %d from %d %d %d to %d %d %d : %s Fare:%d" ,a.name,&a.num,&a.fd,&a.fm,&a.fy,&a.td,&a.tm,&a.ty,a.status,&fare);
                if( feof(newdata) )
                {
                    break;
                }
                fprintf(database,"%s : Room no. %d from %d %d %d to %d %d %d : %s Fare:%d\n",a.name,a.num,a.fd,a.fm,a.fy,a.td,a.tm,a.ty,a.status,fare);
            }
            while( !feof(newdata) );

            fclose(newdata);
            fclose(database);
        }
    }
    else
    {
        printf("Invalid username or password\n");
    }
}

//******************************************************************************************

void review()
{
	int fare;
    struct details
    {
        char name[100];
        char password[100];
    }user;
    printf("Review\n");
    int flag = 0,flag1 = 0;
    FILE *data,*pass;
    data = fopen("database","r");
    printf("Enter Name: ");
    char nam[100];
    char ipassword[100];
    scanf("%s",nam);
    printf("Enter your password: ");
    scanf("%s",ipassword);
    pass = fopen("user credentials","r");
    do
    {
        fscanf(pass,"%s : %s",user.name,user.password);
        if(strcmp(user.name,nam) == 0 && strcmp(user.password,ipassword) == 0)
        {
            flag1 = 1; 
        }
    }
    while( !feof(pass) );

    fclose(pass);
    if(flag1 == 1)
    {
        printf("Booking History:\n");
        do
        {
            fscanf(data,"%s : Room no. %d from %d %d %d to %d %d %d : %s Fare:%d" ,a.name,&a.num,&a.fd,&a.fm,&a.fy,&a.td,&a.tm,&a.ty,a.status,&fare);
            if( feof(data) )
            {
                break;
            }
            if(strcmp(a.name,nam) == 0)
            {
                flag = 1;
                printf("%s : Room no. %d from %d %d %d to %d %d %d : %s Fare:%d\n\n",a.name,a.num,a.fd,a.fm,a.fy,a.td,a.tm,a.ty,a.status,fare);
            }
        }
        while( !feof(data) );

    }
    else
    {
        printf("Invalid username or password\n");
    }
}








//********************************************************************************************************
int main()
{
    int choice1;
    char string[10],s1[2]={'y'},s2[2]={'n'};
    void (*f1[4])()={book,cancel,review,view};

	printf("**************************************************************************************\n");
	printf("**************************************************************************************\n");
	printf("**                                                                                  **\n");
	printf("**                                                                                  **\n");
	printf("**                                                                                  **\n");
	printf("**      *      *  *****  *******  *******  *          ****  *     *  ****           **\n");
	printf("**      *      *  *   *     *     *        *          *      *   *   *              **\n");
	printf("**      *      *  *   *     *     *        *          *       * *    *              **\n");
	printf("**      ********  *   *     *     *******  *          ****     *     ****           **\n");
	printf("**      *      *  *   *     *     *        *             *     *        *           **\n");
	printf("**      *      *  *   *     *     *        *             *     *        *           **\n");
	printf("**      *      *  *****     *     *******  *******    ****     *     ****           **\n");
	printf("**    ---------------------------------------------------------------------         **\n");
	printf("**    ---------------------------------------------------------------------         **\n");
	printf("**                                                                                  **\n");
	printf("**      	      **********************************************                **\n");
	printf("**       	      * CO-FOUNDERS ARE:                           *                **\n");
	printf("**      	      *                                            *                **\n");
	printf("**      	      *       MASTER SURAJ                          *                **\n");
	printf("**      	      **********************************************                **\n");
	printf("**                                                                                  **\n");
	printf("**                                                                                  **\n");
	printf("**************************************************************************************\n");
	printf("**************************************************************************************\n");
	
//----------------------------Designing part----------------------------------------------------		

    while(1)
        {
        		printf("\n");
                printf("Enter:\n \n1.  Book\n \n2.  Cancel\n \n3.  Review booking\n \n4.  View\n \n5.  Exit\n");
                printf("\nEnter your choice: ");
                scanf("%d",&choice1);
                if(choice1 > 5)
                {
                	printf("Invalid choice\n\n");
                	continue;
                }
                if(choice1==5)
                {
                    break;
                }
                else
                {
                    (*f1[choice1-1])();
                }
        printf("\nDo you wish to continue?(y/n):");
        scanf("%s",string);
        if (strcmp(string,s2) == 0)
        {
        	break;
        }
        }
    return 0;
} 
