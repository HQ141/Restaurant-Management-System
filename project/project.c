#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
float bill;
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
void end();
void who();
void sales();
void inventorych();
void discount();
void admin();
void adminmenu();
void chef();
void customer();
void firstscreen();
void additem();
void delitem();
void addmenu();
void delmenu();
void recipe();
void chrecipe();
int oldcus(guest id);
void secscreen(char a[10]);
int newcus(guest id);
void (*aduse[4])()={inventorych,sales,discount,end};
void (*user[4])()={admin,chef,customer,end};
void(*chuse[7])()={additem,delitem,addmenu,delmenu,recipe,chrecipe,end};
void end(){
		exit(0);
}
void who(){
	int c=6;
	system("cls");
	printf("For Admin press 1\nFor Chef press 2\nFor Guest press 3\nTo exit press 4\n");
	while(c<1||c>4){
		printf("?");
		scanf("%d",&c);
	}
	system("cls");
	(*user[c-1])();
}
void sales(){
	FILE *fptr;
	FILE *ptr;
	int a;
	if((fptr=fopen("spreedsheet.dat","rb"))==NULL){
		printf("error");
		return;
	}
	if((ptr=fopen("ingredient.dat","rb"))==NULL){
		printf("error");
		return;
	}	
	sheet rec;
	menu check;
	system("cls");
	printf("#\tItem Name\tSales\n");
	while(fread(&rec,sizeof(sheet),1,fptr)){
		fread(&check,sizeof(menu),1,ptr);
		printf("%d\t%s\t\t%d\n",rec.menuno,check.name,rec.noofsale);
	}
	getch();
	system("cls");
	adminmenu();
}
void inventorych(){
	item aa;
	int i=0,j;
	printf("To view all items press 1\nTo view items which are low press 2\nTo restock press 3\nTo exit press 4");
	while(i>4||i<1){
		printf("\n?");
		scanf("%d",&i);
	}
	if(i==1){
		FILE *fptr;
		if((fptr=fopen("inventory.dat","rb"))==NULL){
			printf("error");
			return;
		}
		printf("\n#\tName\t\t\tAmount(per portion)\n");
		while(fread(&aa,sizeof(item),1,fptr)){
			printf("%d\t%s\t\t\t%d\n",aa.ingredient,aa.name,aa.present);
		}
	}
	if(i==2){
		FILE *fptr;
		if((fptr=fopen("inventory.dat","rb"))==NULL){
			printf("error");
			return;
		}
		printf("\nItems which are low are :\n");
		printf("#\tName\t Amount(per portion)");
		while(fread(&aa,sizeof(item),1,fptr)){
			if(aa.present<=10){
				printf("%d\t%s\t %d\n",aa.ingredient,aa.name,aa.present);
			}
		}
	}
	if(i==3){
		FILE *fptr;
		FILE *temp;
		if((fptr=fopen("inventory.dat","rb"))==NULL){
			printf("error 1");
			return;
		}
		if((temp=fopen("temp.dat","wb"))==NULL){
			printf("error 2");
			return;
		}
		int var=0;
		while(fread(&aa,sizeof(item),1,fptr)){
			if(aa.ingredient!=0&&aa.ingredient!=var){
				aa.present=20;
				fwrite(&aa,sizeof(item),1,temp);
				var=aa.ingredient;
			}
		}
		fclose(fptr);
		fclose(temp);
		if((fptr=fopen("inventory.dat","wb"))==NULL){
			printf("error 3");
			return;
		}
		if((temp=fopen("temp.dat","rb"))==NULL){
			printf("error 4");
			return;
		}
		var=0;
		while(fread(&aa,sizeof(item),1,temp)){
			if(aa.ingredient!=0&&aa.ingredient!=var){
				aa.present=20;
				fwrite(&aa,sizeof(item),1,fptr);
				var=aa.ingredient;
			}
		}
		printf("items have been restocked\n");
	}
	getch();
	system("cls");
	adminmenu();
}
void discount(){
	FILE *fptr;
	FILE *ptr;
	int x,i,j,k;
	if((fptr=fopen("ingredient.dat","rb"))==NULL){
		printf("error");
		return;
	}
	if((ptr=fopen("temp.dat","wb"))==NULL){
		printf("error");
		return;
	}
	menu rec;
	menu check;
	printf("Item Name\t\tDiscount on item\n");
	while(fread(&rec,sizeof(menu),1,fptr)){
		
		printf("%s\t\t\t%d\n",rec.name,rec.discount);
	}
	fclose(fptr);
	if((fptr=fopen("ingredient.dat","rb"))==NULL){
		printf("error");
		return;
	}
		printf("To change discounts press 1\nTo end press 0\n");
		i=9;
		while(i<0||i>1){
			printf("?");
			scanf("%d",&i);
		}
		if(i==0)
		return;
		printf("Enter item no and percent of discount\n?");
		scanf("%d%d",&j,&k);
		while(fread(&check,sizeof(menu),1,fptr)){
			if(check.num==j){
				check.discount=k;
			}
			fwrite(&check,sizeof(menu),1,ptr);
		}
		fclose(ptr);
		fclose(fptr);
	if((fptr=fopen("ingredient.dat","wb"))==NULL){
		printf("error");
		return;
	}
	if((ptr=fopen("temp.dat","rb"))==NULL){
		printf("error");
		return;
	}
	while(fread(&check,sizeof(menu),1,ptr)){
			fwrite(&check,sizeof(menu),1,fptr);
		}
		fclose(ptr);
		fclose(fptr);
	
	getch();
	system("cls");
	adminmenu();
}
void admin(){
	FILE *fptr;
	if((fptr=fopen("login.dat","rb"))==NULL){
		printf("error");
		return;
	}
	log ad={"","",1};
	log check;
	printf("Enter your username\n?");
	scanf("%s",&ad.username);
	printf("Enter your password\n?");
	scanf("%s",&ad.password);
	fread(&check,sizeof(log),1,fptr);
	fclose(fptr);
	if(strcmp(check.username,ad.username)==0&&strcmp(check.password,ad.password)==0)	
	secscreen("Admin");
	else{
		printf("wrong creds");
		return;
	}
	adminmenu();
}
void adminmenu(){
	int var;
	printf("For inventory check press 1\nFor Sales check press 2\nFor Discount check press 3\nTo Exit press 4\n?");
	scanf("%d",&var);
	(aduse[var-1])();
}
void chefmenu(){
	int i;
	printf("Press 1 to Add Items to the inventory\nPress 2 to Delete Items from Inventory\nPress 3 to Add Items to the menu\nPress 4 to Delete Items from the Menu\nPress 5 to check ingredients\nPress 6 to change Ingredients in Dish\nPress 7 to End\n");
	scanf("%d",&i);
	(chuse[i-1])();
}
void chrecipe(){
	system("cls");
	FILE *fptr;
	FILE *iptr;
	FILE *ptr;
	int i,x,y,z,j,k;
	menu aa;
	item rec;
	printf("Enter dish no");
	scanf(" %d",&i);
	if((fptr=fopen("ingredient.dat","rb"))==NULL){
		printf("error");
		end();
	}
	if((ptr=fopen("ingredient.dat","rb+"))==NULL){
		printf("error");
		end();
	}
	fseek(fptr,(i-1)*sizeof(menu),SEEK_SET);
	fread(&aa,sizeof(menu),1,fptr);
	fclose(fptr);
	printf("The ingredients for %s are\n",aa.name);
	if((iptr=fopen("inventory.dat","rb"))==NULL){
		printf("error");
		end();
	}
	for(x=0;x<10;x++){
		if(aa.ingredient[x]!=0){
			y=aa.ingredient[x];
			printf("%d ",y);
			fseek(iptr,(y-1)*sizeof(item),SEEK_SET);
			fread(&rec,sizeof(item),1,iptr);
			printf("%s\n",rec.name);
		}
	}
	printf("Enter number of ingredient\n");
	scanf("%d",&j);
	for(k=0;k<10;k++){
		if(k<j){
			printf("Enter ingredient number\n");
			scanf("%d",&aa.ingredient[k]);
		}
		else
			aa.ingredient[k]=0;
		}
	fseek(ptr,(i-1)*sizeof(menu),SEEK_SET);	
	fwrite(&aa,sizeof(menu),1,ptr);
	getch();
	system("cls");
	chefmenu();
}
void delmenu(){
	system("cls");
	FILE *fptr;
	FILE *ptr;
	int x,i,j,k;
	if((fptr=fopen("ingredient.dat","rb"))==NULL){
		printf("error");
		end();
	}
	if((ptr=fopen("temp.dat","wb"))==NULL){
		printf("error");
		end();
	}
	menu aa;
	printf("#\tName\tPrice\n");
	while(fread(&aa,sizeof(menu),1,fptr)){
		printf("%d\t%s\t%d\n",aa.num,aa.name,aa.price);
	}
	fclose(fptr);
	if((fptr=fopen("ingredient.dat","rb"))==NULL){
		printf("error");
		end();
	}
	printf("Enter number\n?");
	scanf("%d",&j);
	while(fread(&aa,sizeof(menu),1,fptr)){
		if(aa.num==j){
			aa.discount=0;
			strcpy(aa.name,"");
			aa.price=0;
		}
		fwrite(&aa,sizeof(menu),1,ptr);
	}
	fclose(fptr);
	fclose(ptr);
	if((fptr=fopen("ingredient.dat","wb"))==NULL){
		printf("error");
		end();
	}
	if((ptr=fopen("temp.dat","rb"))==NULL){
		printf("error");
		end();
	}
	while(fread(&aa,sizeof(menu),1,ptr)){
		if(aa.num==j){
			aa.discount=0;
			strcpy(aa.name,"");
			aa.price=0;
		}
		fwrite(&aa,sizeof(menu),1,fptr);
	}
	fclose(fptr);
	fclose(ptr);
	getch();
	system("cls");
	chefmenu();
}
void recipe(){
	system("cls");
	FILE *fptr;
	FILE *iptr;
	int i,x,y,z;
	menu aa;
	item rec;
	printf("Enter dish no");
	scanf(" %d",&i);
	if((fptr=fopen("ingredient.dat","rb"))==NULL){
		printf("error");
		end();
	}
	fseek(fptr,(i-1)*sizeof(menu),SEEK_SET);
	fread(&aa,sizeof(menu),1,fptr);
	fclose(fptr);
	printf("The ingredients for %s are\n",aa.name);
	if((iptr=fopen("inventory.dat","rb"))==NULL){
		printf("error");
		end();
	}
	for(x=0;x<10;x++){
		if(aa.ingredient[x]!=0){
			y=aa.ingredient[x];
			printf("%d ",y);
			fseek(iptr,(y-1)*sizeof(item),SEEK_SET);
			fread(&rec,sizeof(item),1,iptr);
			printf("%s\n",rec.name);
		}
	}
	fclose(fptr);
	fclose(iptr);
	getch();
	system("cls");
	chefmenu();
}
void addmenu(){
	system("cls");
	int x,i;
	FILE *fptr;
	FILE *iptr;
	if((fptr=fopen("ingredient.dat","ab+"))==NULL){
		printf("error");
		return ;
	}
	if((iptr=fopen("spreedsheet.dat","ab+"))==NULL){
		printf("error");
		return ;
	}
	int j,k;
	sheet ss;
	menu aa;
	while(fread(&aa,sizeof(menu),1,fptr)){
		x=1+aa.num;
	}
		printf("Enter name");
		fflush(stdin);
		scanf(" %s",&aa.name);
		aa.num=x;
		aa.discount=0;
		printf("Enter Price");
		scanf("%d",&aa.price);
		printf("Enter number of ingredient\n");
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
		fwrite(&ss,sizeof(sheet),1,iptr);
		fwrite(&aa,sizeof(menu),1,fptr);
	fclose(fptr);
	fclose(iptr);
	getch();
	system("cls");
	chefmenu();
}
void delitem(){
	FILE *fptr;
	FILE *ptr;
	int x,i,j,k;
	if((fptr=fopen("inventory.dat","rb"))==NULL){
		printf("error");
		end();
	}
	if((ptr=fopen("temp.dat","wb"))==NULL){
		printf("error");
		end();
	}
	item rec;
	printf("#\tName\tPresent\n");
	while(fread(&rec,sizeof(item),1,fptr)){
		printf("%d %s %d\n",rec.ingredient,rec.name,rec.present);
	}
	fclose(fptr);
	printf("Enter value");
	scanf("%d",&j);
	
	if((fptr=fopen("inventory.dat","rb"))==NULL){
		printf("error");
		end();
	}
	while(fread(&rec,sizeof(item),1,fptr)){
		if(rec.ingredient==j){
			strcpy(rec.name,"");
			rec.present=0;
		}
		fwrite(&rec,sizeof(item),1,ptr);
	}
	fclose(fptr);
	fclose(ptr);
	if((fptr=fopen("inventory.dat","wb"))==NULL){
		printf("error");
		end();
	}
	if((ptr=fopen("temp.dat","rb"))==NULL){
		printf("error");
		end();
	}
		while(fread(&rec,sizeof(item),1,ptr)){
		if(rec.ingredient==j){
			strcpy(rec.name,"");
			rec.present=0;
		}
		fwrite(&rec,sizeof(item),1,fptr);
	}
	fclose(fptr);
	fclose(ptr);
	getch();
	system("cls");
	chefmenu();
}
void additem(){
	FILE *fptr;
	int x,i,j,k;
	if((fptr=fopen("inventory.dat","ab+"))==NULL){
		printf("error");
		end();
	}
	item aa;
	while(fread(&aa,sizeof(item),1,fptr)){
		if(aa.ingredient!=0)
		x=1+aa.ingredient;
	}
		aa.ingredient=x;
		printf("Enter name\n");
		scanf(" %s",&aa.name);
		aa.present=20;
		fwrite(&aa,sizeof(item),1,fptr);
	fclose(fptr);
	getch();
	system("cls");
	chefmenu();
}
void chef(){
	FILE *fptr;
	if((fptr=fopen("login.dat","rb"))==NULL){
		printf("error");
		return;
	}
	log ch={"","",0};
	log check;
	printf("Enter your username\n?");
	scanf("%s",&ch.username);
	printf("Enter your password\n?");
	scanf("%s",&ch.password);
	while(fread(&check,sizeof(log),1,fptr)){
		if(strcmp(check.username,ch.username)==0&&strcmp(check.password,ch.password)==0&&check.use==0){
			printf("check");
			goto line1;
		}	
	}
	printf("wrong cred");
	fclose(fptr);
	return;
	line1:secscreen("Chef");
	fclose(fptr);
	chefmenu();
}
void customer(){
	guest id;
	char ff[10],ll[10];
	guest check;
	int x,y,z;
	FILE *fptr;
	FILE *ptr;
	if((fptr=fopen("guest.dat","ab"))==NULL){
		printf("error");
		end();
	}
	printf("Are you a new Customer enter 1 for yes and 2 for no\n?");
	scanf("%d",&x);
	printf("Please enter your first name and last name\n");
	scanf("%s%s",&ff,&ll);
	strcpy(id.fname,ff);
	strcpy(id.lname,ll);
	if(x==1){
		do{
			id.item=newcus(id);
			strcpy(id.fname,ff);
			strcpy(id.lname,ll);
			fwrite(&id,sizeof(guest),1,fptr);
			printf("Would you like to continue Enter 1 for yes and 2 for no\n");
			y=5;
			while(y>2||y<1){
				printf("?");
				scanf("%d",&y);
			}
		}while(y==1);
	}
	if(x==2){
		do{
			id.item=oldcus(id);
			strcpy(id.fname,ff);
			strcpy(id.lname,ll);
			fwrite(&id,sizeof(guest),1,fptr);
			printf("Would you like to continue Enter 1 for yes and 2 for no\n");
			y=5;
			while(y>2||y<1){
				printf("?");
				scanf("%d",&y);
			}
		}while(y==1);	
	}
	printf("Your Total Bill will be Rs.%.2f",bill);
		fclose(fptr);
		getch();
		return;
	
}
void order(int i){
	int j,k,x,y,z,l;
	int var;
	FILE *fptr;
	FILE *iptr;
	FILE *wiptr;
	FILE *wsale;
	FILE *sale;
	FILE *temp;
	menu list;
	item iii;
	sheet record;
	if((fptr=fopen("ingredient.dat","rb"))==NULL){
		printf("errror");
		end();
	}
	fseek(fptr,(i-1)*sizeof(menu),SEEK_SET);
		fread(&list,sizeof(menu),1,fptr);
		fclose(fptr);
		if(list.discount!=0)
		bill=bill+(list.price*(100-list.discount))/100;
		else
		bill+=(list.price);
		for(x=0;x<10;x++){
			y=list.ingredient[x];
			if((iptr=fopen("inventory.dat","rb"))==NULL){
			printf("errror");
			end();
			}
			if((temp=fopen("temp.dat","wb"))==NULL){
			printf("errror");
			end();
			}
			while(fread(&iii,sizeof(item),1,iptr)){
				if(iii.ingredient==y)
				iii.present--;
				fwrite(&iii,sizeof(item),1,temp);
			}
			fclose(iptr);
			fclose(temp);
			if((iptr=fopen("inventory.dat","wb"))==NULL){
			printf("errror");
			end();
			}
			if((temp=fopen("temp.dat","rb"))==NULL){
			printf("errror");
			end();
			}
			while(fread(&iii,sizeof(item),1,temp)){
				fwrite(&iii,sizeof(item),1,iptr);
			}
			fclose(temp);
			fclose(iptr);
		}
	if((sale=fopen("spreedsheet.dat","rb"))==NULL){
		printf("errror");
		end();
	}
	if((temp=fopen("temp.dat","wb"))==NULL){
		printf("errror");
		end();
	}
	while(fread(&record,sizeof(sheet),1,sale)){
		if(record.menuno==i)
		record.noofsale++;
		fwrite(&record,sizeof(sheet),1,temp);
	}
	fclose(temp);
	fclose(sale);
	if((sale=fopen("spreedsheet.dat","wb"))==NULL){
		printf("errror");
		end();
	}
	if((temp=fopen("temp.dat","rb"))==NULL){
		printf("errror");
		end();
	}
	while(fread(&record,sizeof(sheet),1,temp)){
		fwrite(&record,sizeof(sheet),1,sale);
	}
	fclose(sale);
	fclose(temp);
}
int oldcus(guest id){
	menu list;
	item iii;
	sheet record;
	FILE *gptr;
	FILE *fptr;
	FILE *iptr;
	FILE *wiptr;
	FILE *sale;
	FILE *wsale;
	int i=0,jk,x,var,y,z,j,k,l;
	int *a;
	int *b;
	int pre;
	int max=-1000000;
	guest check;
	system("cls");
	printf("\t\t\t Welcome %s\n",id.fname);	
	if((gptr=fopen("guest.dat","rb"))==NULL){
			printf("error");
			return;
		}
	if((fptr=fopen("ingredient.dat","rb"))==NULL){
		printf("errror");
		end();
	}
	if((sale=fopen("spreedsheet.dat","rb"))==NULL){
		printf("errror");
		end();
	}
	
	if((iptr=fopen("inventory.dat","rb"))==NULL){
		printf("errror");
		end();
	}
	a=malloc(sizeof(int));
	b=malloc(sizeof(int));
	i=1;
	while(fread(&check,sizeof(guest),1,gptr)){
		if(strcmp(check.fname,id.fname)==0&&strcmp(check.lname,id.lname)==0){
			jk=check.item;	
			for(x=0;x<i;x++){
				if(a[x]==jk){
					b[x]+=1;
					goto line3;
				}
			}
			i++;
			a=realloc(a,i*sizeof(int));
			b=realloc(b,i*sizeof(int));
			*(a+i-1)=jk;
			*(b+i-1)=1;			
		}
		line3:var=0;
		if(feof(gptr))
		break;
	}
	for(x=1;x<i;x++){
		if(max<b[x]){
			pre=a[x];
			max=b[x];
		}
	}
	fseek(fptr,(pre-1)*sizeof(menu),SEEK_SET);
	fread(&list,sizeof(menu),1,fptr);
	printf("Your Preferred Meal is %s\nTo order this press 1\nPress 0 to see menu\n",list.name);
	scanf("%d",&j);
	if(j==0){
		return newcus(id);
	}
	if(j==1){
		id.item=pre;
		order(pre);
		fclose(fptr);
		fclose(iptr);
		return pre;
	
	}
}
int newcus(guest id){
	int i,j,k,x,y,z,l;
	system("cls");
	int var;
	printf("\t\t\t Welcome %s\n",id.fname);
	printf("\t\t\t\tMenu\n");
	FILE *fptr;
	FILE *iptr;
	FILE *wiptr;
	FILE *wsale;
	FILE *sale;
	menu list;
	item iii;
	sheet record;
	if((fptr=fopen("ingredient.dat","rb"))==NULL){
		printf("errror");
		end();
	}
	if((iptr=fopen("inventory.dat","rb"))==NULL){
		printf("errror");
		end();
	}
	printf("#\tDish\t\tPrice\n");
	while(fread(&list,sizeof(menu),1,fptr)){
		z=list.num;
		for(x=0;x<10;x++){
			y=list.ingredient[x];
			fseek(iptr,(y-1)*sizeof(item),SEEK_SET);
			fread(&iii,sizeof(item),1,iptr);
			if(iii.present<2){
				goto line2;
			}
		}
		printf("%d\t%s\t\tRs.%d\n",list.num,list.name,list.price);
		line2:var=0; 
	}
	printf("Please Enter the dish You would like\nTo exit press 0\n");
	do{
		printf("?");
		scanf("%d",&i);
	}while(i<0||i>z);
	if(i!=0){
		id.item=i;
		order(i);
		fclose(fptr);
		fclose(iptr);
		return i;
	}
	fclose(fptr);
	fclose(iptr);
	printf("Your Total Bill will be Rs.%.2f",bill);
	end();
}
void firstscreen(){
	int delay;
	printf("\t\t\t%s","Welcome to the Restaurant");
	for(delay=0;delay<1000000000;delay++);
	system("cls");
}
void secscreen(char a[10]){
	int delay;
	system("cls");
	printf("\t\t\t%s %s\n\n","Welcome",a);
	for(delay=0;delay<1000000000;delay++);
}
void main(){
	firstscreen();
	who();
	end();
}

