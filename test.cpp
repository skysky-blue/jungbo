#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<math.h>




const char* unit[100]={0,"1593","백만USD","백만USD","백만USD","백만USD","조"}; //당기순이익, 영엉이익 단위 배열 

void gotoxy(int x, int y){
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);
}

int main(){
//	printf("%s",unit[2]);
//	gotoxy(10,2);
//	printf("1");
//	for (int i =1; i <=10;i++){
//		gotoxy(i,3);
//		if (i==10){
//			printf("2");
//		}
//		else{
//			printf("|");
//
//		}
//		
//	}
	int a= 0;
	scanf("%d",&a);
	printf("%d",a);
}
