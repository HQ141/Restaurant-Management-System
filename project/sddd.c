#include<stdio.h>
#include<stdlib.h>
struct auth{
	char username[10];
	char password[10];
	int use;
}log;
struct guest{
	char fname[10];
	char lname[10];
	int item;
}guest;
struct sheet{
	int menuno;
	int noofsale;
}sheet;
struct menu{
	int num;
	char name[20];
	int ingredient[10];
	int discount;
	int price;
}menu;
struct invent{
	int ingredient;
	char name[20];
	int present;
}item;
void main(){
	FILE *c;
	if((c=fopen("inventory.dat","rb"))==NULL){
		printf("error");
		return 0;
	}
	while(fread(&item,sizeof(item),1,c)){
		printf("%d %s %d\n",item.ingredient,item.name,item.present);
	}
	fclose(c);
	if((c=fopen("guest.dat","rb"))==NULL){
		printf("error");
		return 0;
	}
	while(fread(&guest,sizeof(guest),1,c)){
		printf("%s %s %d\n",guest.fname,guest.lname,guest.item);
	}
	fclose(c);
	if((c=fopen("ingredient.dat","rb"))==NULL){
		printf("error");
		return 0;
	}
	while(fread(&menu,sizeof(menu),1,c)){
		printf("%d %s %d %d\n",menu.num,menu.name,menu.price,menu.discount);
	}
	fclose(c);
	if((c=fopen("spreedsheet.dat","rb"))==NULL){
		printf("error");
		return 0;
	}
	while(fread(&sheet,sizeof(sheet),1,c)){
		printf("%d %d\n",sheet.menuno,sheet.noofsale);
	}
	fclose(c);
}
