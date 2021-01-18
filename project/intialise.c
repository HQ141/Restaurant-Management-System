#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
typedef struct auth{
	char username[10];
	char password[10];
	int use;
}log;
typedef struct guest{
	char fname[10];
	char lname[10];
	int item;
}guest;
typedef struct sheet{
	int menuno;
	int noofsale;
}sheet;
typedef struct menu{
	int num;
	char name[20];
	int ingredient[10];
	int discount;
	int price;
}menu;
typedef struct invent{
	int ingredient;
	char name[20];
	int present;
}item;
void intialiseall(){
	FILE *iptr;
	FILE *fptr;
	int i,x;
	if((fptr=fopen("login.dat","wb"))==NULL){
		printf("error");
		return;
	}
	log admin={"killjoy56","helpme",1};
	log chef;
	fwrite(&admin,sizeof(log),1,fptr);
	printf("enter number of chefs\n");
	scanf("%d",&i);
	for(x=0;x<i;x++){
		chef.use=0;
		printf("enter user name\n");
		scanf("%s",&chef.username);
		printf("enter password\n");
		scanf("%s",&chef.password);
		fwrite(&chef,sizeof(log),1,fptr);
	}
	fclose(fptr);
	if((fptr=fopen("guest.dat","wb"))==NULL){
		printf("error");
		return;
	}
	guest gg={"","",0};
	fclose(fptr);

	if((iptr=fopen("spreedsheet.dat","wb"))==NULL){
		printf("error");
		return;
	}
/*	if((fptr=fopen("ingredient.dat","wb"))==NULL){
		printf("error");
		return ;
	}
	int j,k;
	menu aa;
	sheet ss;
	printf("Enter no of dishes\n");
	scanf("%d",&i);
	for(x=1;x<=i;x++){
		printf("Enter name");
		fflush(stdin);
		scanf(" %s",&aa.name);
		aa.num=x;
		aa.discount=0;
		printf("enter price");
		scanf("%d",&aa.price);
		printf("Enter number of ingredient");
		scanf("%d",&j);
		for(k=0;k<10;k++){
			if(k<j){
				printf("Enter ingredient number\n");
				scanf("%d",&aa.ingredient[k]);
			}
			else
			aa.ingredient[k]=0;
		}
		ss.menuno=aa.num;
		ss.noofsale=0;
		fwrite(&ss,sizeof(ss),1,iptr);
		fwrite(&aa,sizeof(menu),1,fptr);
	}
	fclose(fptr);
	fclose(iptr);
/*	if((fptr=fopen("inventory.dat","wb"))==NULL){
		printf("error");
		return ;
	}
	item record;
	int y=5,j;
	printf("number of item\n");
	scanf("%d",&i);
	j=x+i;
	for(x=1;x<=j;x++){
		printf("enter ingredient name\n");
		fflush(stdin);
		gets(record.name);
		record.ingredient=x;
		record.present=20;
		fwrite(&record,sizeof(item),1,fptr);
	}
	fclose(fptr);*/
}
void read(FILE *cp){
	menu rec;
	FILE *fptr;
	if((fptr=fopen("guest.dat","rb"))==NULL){
		printf("error");
		return ;
	}
	guest ss;
	while(1){
		if(feof(fptr))
		return ;
		fread(&ss,sizeof(guest),1,fptr);
		printf("%s %s %d\n",ss.fname,ss.lname,ss.lname);
	}
	fclose(fptr);
	
}
void initial (){
	FILE *fptr;
	FILE *iptr;
	int x;
	if((fptr=fopen("guest.dat","wb"))==NULL){
		printf("error");
		return;
	}
	fclose(fptr);
	if((iptr=fopen("spreedsheet.dat","wb"))==NULL){
		printf("error");
		return;
	}
	sheet ss;
	for(x=1;x<=5;x++){
		ss.menuno=x;
		ss.noofsale=0;
		fwrite(&ss,sizeof(ss),1,iptr);
	}
	fclose(iptr);
}
void main(){
//	intialiseall();
/*	FILE *c;
	if((c=fopen("ingredient.dat","rb"))==NULL){
		printf("error");
		return 0;
	}
	read(c);
	fclose(c);*/
	initial();
}
