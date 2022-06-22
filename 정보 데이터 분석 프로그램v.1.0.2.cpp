	/* 
   =================================================================
   =                                                               =
   =  기업의 영업이익과 단기순이익에 따른 주가 변화 및 추세 파악   =
   =                        제작자: 정찬웅                         =
   =                                                               =
   =                                                     ver.1.0.2 =
   =================================================================
*/

//데이터 출처:https://www.deepsearch.com/ , https://kr.investing.com/equities/yahoo-inc-chart
//

#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<math.h>
#define stx 100 //주식 y축 x좌표  

int restart = 0; //재시작했는지 처음 구동했는지 판단해주는 변수 
int position = 0; // start 함수에서 0이면 1번 질문을, 1이면 2번 질문을 택하는 것을 확인할 수 있음  
int company = 1; // 회사 선택을 설정해주는 변수. 1 : SAMSUNG, 2 : APPL, 3 : AMAZON, 4 : MICROSOFT, 5 : TSMC, 6: SK hynix
int range_company[100]={0,2010,2016,2016,2016,2016,2010}; //기업의 데이터 사용 가능 최소 범위에서 년도 표시 배열 
int range_company_1[100]={0,1,1,1,1,1,1};  //기업의 데이터 사용 가능 최소 범위에서 분기 표시 배열 
int lim_range_company[100]={0,2021,2020,2020,2020,2020,2021};  //기업의 데이터 사용 가능 최대 범위에서 년도 표시 배열
int lim_range_company_1[100]={0,4,4,4,4,4,4};  //기업의 데이터 사용 가능 최대 범위에서 년도 표시 배열 
const char* company_name[100]={0,"SAMSUNG","APPLE","AMAZON","MICROSOFT","TSMC","SK hynix"};
const char* unit[100]={0,"조","백만USD","백만USD","백만USD","백만USD","조"}; //당기순이익, 영엉이익 단위 배열 
const char* unit_st[100]={0,"KRW","USD","USD","USD","USD","KRW"}; //주식 단위 배열  
int draw_X(int start_company ,int start_company_Q,int finish_company,int finish_company_Q,int max_a_y, int min_a_y );//x축 그리기 
void draw_y ( int max_a_y, int min_a_y); //y축 그리기 unit  
void print_x(int k, int x, int y, int width,int sc ,int scq,int fc,int fcq); //x축 그리는 함수 
int draw_x_d(int t,int n); // x축 밑 부분 그리는 함수 
void gotoxy(int x, int y);
void print_com(int k,int x, int y,int sc ,int scq); //x축에 년도, 분기 적기 
void axis( int start_company ,int start_company_Q,int finish_company,int finish_company_Q,int max_a_y, int min_a_y,int max_st,int min_st ); // 좌표축 나타내기 
int dif_st(int max_st, int min_st); //주식의 최댓값의 1/3이 최솟값보다 크면 1을 작으면 0을 return해주는 함수 
void draw_st(int max_st,int min_st,int max_a_y, int min_a_y); //주식 축 그래프 그리는 함수 
int stc_gap(int max_st); // 주식 간격 계산해주는 함수  
void unit_y(); //y 축에 단위 입력해주는 함수 



HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE); //배경 설정할 때 선언해야 하는 명령어 
int text_data(int re,int i); //중간에 다시 시작시키겠습니까 혹은 시작시키겠습니까 문장을 출력해주는 함수 
int text_company(int company); //회사 나타내는 문장 출력해주는 함수 
int start();   // 처음 시작 창을 띄우는 함수 
int select();  // 회사를 선택하는 함수  
int menu_2(int company); // 회사를 선택한 후 데이터 범위를 선택해주는 함수 
int y_a_dif(int max_a_y, int min_a_y); // y의 max값의 1/3이 min값보다 큰지 작은지 알려주는 함수   
int y_a_gap(int max_a_y, int min_a_y); // y 당기 순이익 간격 계산 해주는 함수 
void draw_y (int n,int max_a_y, int min_a_y); //y축 그리기
int s_com=0,s_comQ=0,f_com=0,f_comQ =0; // menu_2에서 변수 받아오기 
int  coms=0; //x축에 데이터 입력할 때 범위 간격 나타내주는 변수 
int st_term=0; //주식축의 한 단위 당 몇 주를 할당하는지 확인해주는 변수 



int main(){
	int company_position=1;
	while(1){
		coms=0; 
//		start();
//		if (position == 1){
//			break;
//		}
//		company_position=select();
		menu_2(company_position); //데이터 범위 물어보고 데이터 범위 시작 년도, 분기, 끝나는 년도, 분기 받기 
		
		axis(s_com,s_comQ,f_com,f_comQ,720,300,500,250);
		
		while (true){
			int i=1;
		}
		restart=1;
	}
	
	

}

int start(){   // 처음 시작 창을 띄우는 함수 
	position = 0;
	text_data(restart,position); 
	int keyboard_input = 0; //키보드에서 방향키 입력 받는 변수
//	if (restart == 0) printf("프로그램을 실행시키시겠습니까?");
//    else printf("프로그램을 다시 실행시키시겠습니까?");
	
	while(true){

		keyboard_input = getch();
		
		if (keyboard_input==224){
			keyboard_input = getch();
			
			switch(keyboard_input){
				case 72: // ↑방향키 눌렀을 때 
					position = 0;
					text_data(restart,position);
					break;
				case 80: //↓방향키 눌렀을 때 
				    position = 1;
					text_data(restart,position);
					break; 
				default:
					break;
			}
		}
		 
    	if (keyboard_input==13) break; // 엔터키를 눌렀을 때 빠져나오는 명령어 
	}
	
}
	
int select(){   // 회사를 선택하는 창을 띄우는 함수 
	company = 1; // 회사 선택 변수 초기화 
	int keyboard_input = 0; //키보드에서 방향키 입력 받는 변수
	text_company(company);
	while(true){

		keyboard_input = getch();
		
		if (keyboard_input==224){
			keyboard_input = getch();
			
			switch(keyboard_input){
				case 72: // ↑방향키 눌렀을 때 
					if (company == 1) company++; //company가 1이면 최소이므로 1더한 다음 1빼서 똑같은 상태 유지하기 
					company--;
					text_company(company);
					break;
				case 80: //↓방향키 눌렀을 때 
				    if (company == 6) company--; //company가 6이면 최대이므로 1 뺀다음 다시 올려서 똑같은 상태 유지하기 
				    company ++;
					text_company(company);
					break; 
				default:
					break;
			}
		}
		 
    	if (keyboard_input==13) return company; // 엔터키를 눌렀을 때 빠져나오는 명령어 
	}
	
}	

int text_company(int company){
	system("cls");
	printf("\n 어느 회사의 데이터를 분석할 것입니까?");
	for (int i=1;i<=6;i++){
		printf("\n");
		if(i==company) SetConsoleTextAttribute(hC,240); 
		printf(" %d.%s",i,company_name[i]);
		if(i==company) SetConsoleTextAttribute(hC,7);
	}
	printf("\n");
} 

int text_data(int re,int i){
	system("cls"); // 프로그램 창에 출력된 문자들을 삭제 시켜주는 명령어 
	printf("\n\n\n\n\t==========================================\n");
	printf("\t=                                        =\n");
	printf("\t=    ");
	if (i==0){ // position이 1이면 2번 질문에 위치하므로 배경색이 바뀌면 안되고 position이 0이면 1번 질문의 색을 바꿔야해서 if 조건문을 넣었다. 
		SetConsoleTextAttribute(hC,240); //배경색 흰색으로 바꾸기 
		if (restart == 0){ // 프로그램을 한바퀴 돌았다면 '다시'라는 단어를 붙여서 print 하도록 해주는 조건문 
			printf("1.프로그램을 실행시키시겠습니까?");
		    SetConsoleTextAttribute(hC,7); 	//배경색 검은색으로 바꾸기 
			printf("   ");
		}
	
		else{
			printf("\b\b1.프로그램을 다시 실행시키시겠습니까?");
   		}
    	SetConsoleTextAttribute(hC,7); 
		printf(" =\n");	
	}
	else{

		if (restart == 0){// 프로그램을 한바퀴 돌았다면 '다시'라는 단어를 붙여서 print 하도록 해주는 조건문 
			printf("1.프로그램을 실행시키시겠습니까?   ");
		}
		else{
			printf("\b\b1.프로그램을 다시 실행시키시겠습니까?");
  		}
		printf(" =\n");
	}
	printf("\t=     ");
	if (i==0){
		printf("2.프로그램을 종료하시겠습니까?");
	}
	else{
		SetConsoleTextAttribute(hC,240);
		printf("2.프로그램을 종료하시겠습니까?");
		SetConsoleTextAttribute(hC,7);
	}
	printf("     =\n");
	printf("\t=                                        =\n");
	printf("\t==========================================\n");
	
}

int menu_2(int company){
	int start_company = 0, start_company_Q=0, finish_company=0, finish_company_Q=0; //회사 데이터 분석 시작 범위, 끝나는 범위 입력 받는 변수 
	int start_input = 0, finish_input = 0; // 시작&끝나는 범위 선언했는지 확인하는 변수 
	int re=0; //잘못 입력하였는지 확인하는 변수 
	while (start_input!=1){
		if(re == 0){
			system("cls"); // 프로그램 창에 출력된 문자들을 삭제 시켜주는 명령어 
			printf("\n몇 년도 몇 분기 부터 확인할지 입력하십시오.(%d_%d<=입력할 수<=%d_%d)\n 입력 방식: (시작되는 년도)_(시작되는 분기) ",range_company[company],range_company_1[company],lim_range_company[company],lim_range_company_1[company]); 
		}
		else{
			system("cls"); // 프로그램 창에 출력된 문자들을 삭제 시켜주는 명령어 
			printf("\n잘못 입력하셨습니다. 몇 년도 몇 분기 부터 확인할지 입력하십시오.(%d_%d<=입력할 수<=%d_%d)\n 입력 방식: (시작되는 년도)_(시작되는 분기) ",range_company[company],range_company_1[company],lim_range_company[company],lim_range_company_1[company]); 
		} 
		scanf("%d_%d",&start_company,&start_company_Q); //시작 년도, 분기 받아오기 
		printf("%d",start_company_Q);
		fflush(stdin); // 입력 버퍼 초기화 
		printf("%d",start_company_Q);
		if (range_company[company]<=start_company && start_company<=lim_range_company[company]&&1<=start_company_Q&&start_company_Q<=4){ //회사의 데이터 시작 년도 부터 2021년 까지만 받기 단, 분기는 상관이 없다 
			re = 0;
			start_input = 0; 
			while(finish_input !=1){
				if(re == 0){
					system("cls"); // 프로그램 창에 출력된 문자들을 삭제 시켜주는 명령어 
					printf("\n %d년도 %d분기 부터 데이터 분석을 시작합니다. \n몇 년도 몇 분기 까지 확인할지 입력하십시오.(%d_%d<입력할 수<=%d_%d)\n 입력 방식: (끝나는 년도)_(끝나는 분기) ",start_company,start_company_Q,start_company,start_company_Q,lim_range_company[company],lim_range_company_1[company]); 
				}
				else{
					system("cls"); // 프로그램 창에 출력된 문자들을 삭제 시켜주는 명령어 
					printf("\n잘못 입력하셨습니다. 몇 년도 몇 분기 까지 확인할지 입력하십시오.(%d_%d<입력할 수<=%d_%d)\n 입력 방식: (끝나는 년도)_(끝나는 분기) ",start_company,start_company_Q,lim_range_company[company],lim_range_company_1[company]); 
				} 
				scanf("%d_%d",&finish_company,&finish_company_Q); 
				fflush(stdin); // 입력 버퍼 초기화 
				if (start_company<=finish_company&&finish_company<=2021&&1<=finish_company_Q&&finish_company_Q<=4){ // 끝나는 년도가 시작 년도보다 크거나 같고, 2021년 이하여야함 그리고 분기가 1~4사이에 있어야함을 분류하는 조건문 
					finish_input = 1; //finish 범위 입력 되었음을 확인 
					if (start_company == finish_company){ //만약 시작 년도와 끝나는 년도가 같다면 
						if (start_company_Q < finish_company_Q){ //끝나는 분기가 시작 분기보다 커야한다. 
							re=0;
							system("cls");
//							printf("%d",start_company_Q);

							s_com=start_company,s_comQ=start_company_Q,f_com=finish_company,f_comQ =finish_company_Q;
							return 0;
//							gotoxy(25,15); 
//							printf("%d, %d, %d, %d",start_company, start_company_Q, finish_company, finish_company_Q);
 
						}
						else{
							finish_input = 0; //분기가 잘못 입력되어서 다시 finish_input 0으로 바꿔주기 
						}
					}
					else{
						re=0;
						system("cls");
						s_com=start_company,s_comQ=start_company_Q,f_com=finish_company,f_comQ =finish_company_Q;
//						printf("%d",start_company_Q);

						return 0;
					}
				}
				re=1; 
			}
		}
		else{
			fflush(stdin); 
			re=1;
		}
		
	}

}
	
void gotoxy(int x, int y){
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);
	}

int y_a_dif(int max_a_y, int min_a_y){ // y의 max값의 1/3이 min값보다 큰지 작은지 알려주는 함수 크면 1을 작으면 0을 return한다.  
	return max_a_y/3 > min_a_y;
}

int y_a_gap(int max_a_y, int min_a_y){ // y간격 계산 해주는 함수 max_a_y, min_a_y 는 그 기업 주식의 최대 당기순이익과 최소 당기순이익을 입력해준다. 
	int y_a_gap = 0;
	y_a_gap = max_a_y / 36 ;
	return y_a_gap;
} 

void unit_y(){ //y 축에 단위 입력해주는 함수
	gotoxy(1,3);
	printf("(%s)",unit[company]);
	gotoxy(95,3);
	printf("(%s)",unit_st[company]);	
}

void draw_y ( int max_a_y, int min_a_y){ //y축 그리기   
	int k = 0; // 단위 표시가 몇 번 반복 되었는지 확인하는 변수 
	int n=0; //n은 y_a_dif = 1이라면 96 정도를 0이라면 144정도를 입력해주면 된다.
	if (y_a_dif(max_a_y,min_a_y)) n=144;
	else n=96; 
	for (int i = 3; i <= (n+3); i++){
		gotoxy(9,i);
		printf("|");
		if (((i+2)%4)==0){
			gotoxy(9,i);
			printf("-");
			gotoxy(1,i);
			printf("%d",((36-k)*y_a_gap(max_a_y,min_a_y)));
			k++;
			
		}
	} 
	if ((y_a_dif(max_a_y,min_a_y))==0){ // max값의 1/3보다 min값이 크면 ~을 y축 중간에 넣어야 하므로 조건문 사용 
		gotoxy(9,n+4);
		printf("~");
		gotoxy(9,n+5);
		printf("~");
		draw_x_d(y_a_dif(max_a_y,min_a_y),n);
	}
	else{
		draw_x_d(y_a_dif(max_a_y,min_a_y),n); //y_a_dif 가 1인 상황 
	}
	unit_y();
}

int dif_st(int max_st, int min_st){ //주식의 최댓값의 1/3이 최솟값보다 크면 1을 작으면 0을 return해주는 함수 
	return (max_st/3)>min_st;	
}

void draw_st (int max_st, int min_st,int max_a_y, int min_a_y){ //y축 그리기   
	int k = 0; // 단위 표시가 몇 번 반복 되었는지 확인하는 변수 
	int n=0; //n은 y_a_dif = 1이라면 96 정도를 0이라면 144정도를 입력해주면 된다.
	if (y_a_dif(max_a_y,min_a_y)) n=150;
	else n=100; 
	for (int i = 3; i <= (n); i++){
		gotoxy(stx,i);
		printf("|");
		if (((i+2)%4)==0){
			if (k!=36){
				gotoxy(stx,i);
				printf("-");
				gotoxy(stx-5,i);
				printf("%d",((36-k)*stc_gap(max_st)));
			}
			k++;
			
		}
	} 
	if ((y_a_dif(max_a_y,min_a_y))==0){ // max값의 1/3보다 min값이 크면 ~을 y축 중간에 넣어야 하므로 조건문 사용 
		gotoxy(stx,n+1);
		printf("~");
		gotoxy(stx,n+2);
		printf("~");
//		draw_x_d(y_a_dif(max_a_y,min_a_y),n);
	}
//	else{
//		draw_x_d(y_a_dif(max_a_y,min_a_y),n); //y_a_dif 가 1인 상황 
//	}
	
}

int stc_gap(int max_st){ // y간격 계산 해주는 함수 max_a_y, min_a_y 는 그 기업 주식의 최대 당기순이익과 최소 당기순이익을 입력해준다. 
	int stcgap = 0;
	stcgap = max_st / 36 ;
	return stcgap;
} 

void draw_st_d(int t,int n){ // 주식 축 밑 부분 그리는 함수 
	if(!t){
		for (int i = n+6; i<=(n+8);i++){
			gotoxy(99,i);
			printf("|");
		}
	}
	else{
		for (int i = n+4; i<=(n+6);i++){
			gotoxy(99,i);
			printf("|");
		}
	}
}

int draw_x_d(int t,int n){ // x축 밑 부분 그리는 함수 
	if(!t){
		for (int i = n+6; i<=(n+10);i++){
			gotoxy(9,i);
			printf("|");
			if(i==n+8){
				gotoxy(9,n+8);
				printf("+"); //원점 그래프를 +로 입력하기 
			}
		}
	}
	else{
		for (int i = n+4; i<=(n+8);i++){
			gotoxy(9,i);
			printf("|");
			if(i==n+8){
				gotoxy(9,n+6);
				printf("+"); //원점 그래프를 +로 입력하기 
			}
		}
	}
}

void write_x(int com, int comQ){
//	printf// 
} 

// p는 x축을 그래프에서 무슨 y좌표에 입력해야 하는지 입력해주는 변수  draw_y의 n+8이 p로 입력되면 된다. 
int draw_x(int start_company ,int start_company_Q,int finish_company,int finish_company_Q,int max_a_y, int min_a_y ){ //x축 그리기 데이터 범위를 받은 뒤 단위 표시 하기 
	int p=0;
	if (y_a_dif(max_a_y,min_a_y)) p=150;
	else p=104;
	int term = 0;
	int width = 0; // x축에 년도, 분기 입력할 때 서로 간의 너비 저장해주는 변수 
	term = (finish_company-start_company)*4+(finish_company_Q-start_company_Q)+1; //이런 식을 사용하면 데이터 범위 사이에 총 몇 분기가 있는지 확인 가능하다. 
	width = 90/term;
//	if (width * term >90){
//		width --; //width가 나누어
//	}
	gotoxy(50,200); 
	printf("%d",width);
	
	for (int i = 0; i<=(term); i++){
		if (i<=(term-1)){
			print_x(1,(i*width)+10,p,width,start_company,start_company_Q,finish_company,finish_company_Q);
			coms++;
		} 
		else{
			print_x(0,(i*width)+10,p,2,start_company,start_company_Q,finish_company,finish_company_Q);
			gotoxy((i*width)+9+width,p);
			printf("-");
		}
	}
//	gotoxy(9+2*width,150);
//	printf("%d",(9+width));
	return width+9;
}

void print_x(int k, int x, int y, int width,int sc ,int scq,int fc,int fcq){ //x축 ---| 한 번 그리는 함수 
	int com = sc, comq = scq;
	for (int i =0; i <=(width-2); i++){  // -을 너비만큼 출력해주도록 한다 
		gotoxy(x+i,y); 
		printf("-");
	gotoxy(x+width-1,y); // -을 입력한 후 마지막에 | 를 출력한다. 
	printf("|");
	print_com(k,x+width-1,y+1,sc+((scq+coms-1)/4),(scq+coms)%4); // | 밑에 년도, 분기를 한 글자씩 출력해준다. 
	}
}
void print_com(int k, int x, int y,int sc ,int scq){ //x축에 년도, 분기 적기
	if (k==1){
		for (int i = 0;i<4;i++){
			gotoxy(x,y+3-i); // y+3 부터 y까지 숫자를 입력해준다. 
			printf("%d",sc%10); // y+3부터 위로 숫자를 출력하므로 10으로 나눈 나머지를 출력한뒤 다시 10으로 나눈 값을 저장햐여 끝자리 숫자부터 하나하나 출력시켜준다. 
			sc=sc/10;
			}
		gotoxy(x,y+4);
		printf("|");
		gotoxy(x,y+5);
		if (scq == 0) printf("4");	// scq는 분기로 입력한 값을 4로 나눈 나머지를 나타내므로 4일때는 0이 출력된다 따라서 0일때는 4를 출력시켜줘야 한다. 
		else printf("%d",scq); 
	}
	else{
		gotoxy(x,y);
		printf("(년도)");
		gotoxy(x,y+1);
		
		printf("  |");
		gotoxy(x,y+2);
		printf("(분기)");
		
	}
}
void axis( int start_company ,int start_company_Q,int finish_company,int finish_company_Q,int max_a_y, int min_a_y,int max_st,int min_st ) { // 좌표축 나타내기 
	int i;
	draw_y(max_a_y,min_a_y);
	draw_x(start_company,start_company_Q,finish_company,finish_company_Q,max_a_y,min_a_y);
	draw_st(max_st,min_st,max_a_y,min_a_y);
}

