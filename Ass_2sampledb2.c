//sampledb2.c




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct edata
{
	int id;	
	char name[40];
	int bs;
	float allowance;
	float tax;
	float gs;
};

int pk;	
int flg;

struct edata getdata(int);
void dispheader();
void dispall(FILE *);
int getID(FILE *);



int main(int argc, char *argv[])
{	
	if(argc!=2)
	{
		printf("\nInsufficient number of arguments");
		exit(0);
	}


	FILE *fp,*fdel;
	fp=fopen(argv[1],"rb+");
	if(fp==NULL)
	{
		fp=fopen(argv[1],"wb+");
		if(fp==NULL)
		{
			puts("Cannot open the file");
			exit(0);
		}
	}
	
	pk=0;
	long int pos=ftell(fp);
	printf("%ld\n",pos);
	char another='Y';
do{

	system("clear");
	printf("\n\t1. \t\tAdd Record\n");
	printf("\n\t2. \t\tList Records\n");
	printf("\n\t3. \t\tDelete Record\n");
	printf("\n\t4. \t\tEdit Record\n");
	printf("\n\t5. \t\tExit\n");
	//long int pos=ftell(fp);
	//printf("%ld\n",pos);
	printf("\nEnter your option: [1...5]: ");
	int opt;
	scanf("%d",&opt);
	
//======================================================================	

struct edata ed;
if(opt==1)
{
		
	int ret;
	//++pk;
	int jj=getID(fp);
	
	ed=getdata(jj);
	//if(ret<0)
		//printf("Invalid data\n");
	fseek(fp,0,SEEK_END);

	fwrite(&ed,sizeof(ed),1,fp);
		
	
	printf("\nData written on the disk");
	
	
}

else if(opt==2)
{
	dispheader();
	
	dispall(fp);

}

else if (opt==3)
{

	printf("Enter record ID to delete: ");
	int i,flag=0;
	scanf("%d",&i);	
	fdel=fopen("tempdb","wb");
	rewind(fp);
	while(fread(&ed,sizeof(ed),1,fp)==1)
	{
		if(ed.id!=i)
			fwrite(&ed,sizeof(ed),1,fdel);
		else
			flag=1;
	}
	fclose(fp);
	fclose(fdel);
	remove(argv[1]);
	rename("tempdb",argv[1]);
	fp = fopen(argv[1],"rb+");
	if(flag==1)
		printf("\nRecord # %d deleted successfully.\n",i);
	else
		printf("Record # %d does not exists.\n",i);
}

else if(opt == 4)
{
	int i,flag=0;	
	printf("Enter record ID to update it: ");
	scanf("%d",&i);
	rewind(fp);
	
	while(fread(&ed,sizeof(ed),1,fp)==1)
	{
		if(ed.id == i)
		{
			flag=1;
			struct edata e;
			//dd = getdata(i);
			printf("Enter Name: ");
			char nam[30];
			scanf("%s",&nam);
			strcpy(e.name,nam);
			printf("Enter Basic Salary: ");
			scanf("%d",&e.bs); 
			//compute allowance
			if (e.bs<=50000 && e.bs>=10000)
		
				e.allowance = e.bs*0.25;
			else if(e.bs<=80000 && e.bs>=51000)
				e.allowance = e.bs*0.3;
			else
			{
			//printf("\nInvalid data entry");
			//*retval=-1;
			}

			//compute income tax
			if(e.bs<20000)
				e.tax = e.bs*0.04;
			else if(e.bs>20000 && e.bs <=40000)
				e.tax = e.bs*0.08;
			else
				e.tax = e.bs*0.12;
		
			//compute gross salary
			e.gs = e.bs + e.allowance - e.tax;
			e.id=i;
			long int recsize=sizeof(e);
			fseek(fp,-recsize,SEEK_CUR);
			fwrite(&e,sizeof(e),1,fp);
			
		}
	}
	if(flag==0)
	{
		printf("Cant find the specified record...\n");
	}

}			

else if(opt==5)
{
	close(fp);
	exit(0);
}




printf("\nDo you want to continue...");
scanf("%s",&another);

}while(another=='Y' || another=='y');

return 0;
}



//==============GETDATA()==================================

struct edata getdata(int pp)
{
		struct edata e;
		printf("Enter data to write on disk: \n");
		
		printf("Enter Name: ");
		char nam[30];
		scanf("%s",&nam);
		strcpy(e.name,nam);
		printf("Enter Basic Salary: ");
		scanf("%d",&e.bs); 
		//compute allowance
		if (e.bs<=50000 && e.bs>=10000)
		
			e.allowance = e.bs*0.25;
		else if(e.bs<=80000 && e.bs>=51000)
			e.allowance = e.bs*0.3;
		else
		{
			//printf("\nInvalid data entry");
			//*retval=-1;
		}

		//compute income tax
		if(e.bs<20000)
			e.tax = e.bs*0.04;
		else if(e.bs>20000 && e.bs <=40000)
			e.tax = e.bs*0.08;
		else
			e.tax = e.bs*0.12;
		
		//compute gross salary
		e.gs = e.bs + e.allowance - e.tax;

		e.id=pp;	

		return e;		


}

//==================dispheader()==================
void dispheader()
{
	printf("\tID\tName\tGross Salary\n");
	printf("\t==\t=====\t===========\n");
}

//================dispall()==========================
void dispall(FILE *fp)
{
	struct edata ed;	
	rewind(fp);	
	while(fread(&ed,sizeof(ed),1,fp)==1)
		printf("\t%d\t%s\t%f\n",ed.id,ed.name,ed.gs);

}
//===============generateID===========================
int getID(FILE *fp)
{
	int key=0;
	int long pos = ftell(fp);
	if(pos==0)
	{
		key=1;
		return key;
	}	
	struct edata ed;
	rewind(fp);
	while(fread(&ed,sizeof(ed),1,fp)==1)
	{
		if(ed.id>key)
			key=ed.id;
	}
	return key+1;
}
		
//================disptitle()======================
void disptitle()
{
	printf("\n\n");
	


}
