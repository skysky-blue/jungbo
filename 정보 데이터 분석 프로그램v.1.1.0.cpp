	/* 
   =================================================================
   =                                                               =
   =  기업의 영업이익과 당기순이익에 따른 주가 변화 및 추세 파악   =
   =                        제작자: 정찬웅                         =
   =                                                               =
   =                                                     ver.1.1.0 =
   =================================================================
*/

//데이터 출처:https://www.deepsearch.com/ , https://kr.investing.com/equities/yahoo-inc-chart
//

#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<math.h>
#include<time.h>
#include<stdlib.h> // sleep 함수 가져오기 
#define stx 100 //주식 y축 x좌표 
#include<string.h> 




int restart = 0; //재시작했는지 처음 구동했는지 판단해주는 변수 
int position = 0; // start 함수에서 0이면 1번 질문을, 1이면 2번 질문을 택하는 것을 확인할 수 있음  
int company = 1; // 회사 선택을 설정해주는 변수. 1 : SAMSUNG, 2 : APPL, 3 : AMAZON, 4 : MICROSOFT, 5 : TSMC, 6: SK hynix
int range_company[100]={0,2010,2016,2016,2016,2016,2011}; //기업의 데이터 사용 가능 최소 범위에서 년도 표시 배열 
int range_company_1[100]={0,1,1,1,1,1,1};  //기업의 데이터 사용 가능 최소 범위에서 분기 표시 배열 
int lim_range_company[100]={0,2021,2020,2020,2020,2020,2021};  //기업의 데이터 사용 가능 최대 범위에서 년도 표시 배열
int lim_range_company_1[100]={0,4,4,4,4,4,4};  //기업의 데이터 사용 가능 최대 범위에서 년도 표시 배열 
int index_com[100]={0,48,44,44,44,44,48}; //기업의 데이터 분기 수 
const char* company_name[100]={0,"SAMSUNG","APPLE","AMAZON","MICROSOFT","TSMC","SK hynix"};
const char* unit[100]={0,"백억KRW","백만USD","백만USD","백만USD","백만USD","백억KRW"}; //당기순이익, 영엉이익 단위 배열 
const char* unit_st[100]={0,"KRW","USD","USD","USD","USD","KRW"}; //주식 단위 배열 
const char *filename[100]={0,"samsung.txt","apple.txt","amazon.txt","microsoft.txt","tsmc.txt","sk hynix.txt"}; //파일 불러올 때 이름 배열 선언 filename[company]하면 그 회사의 파일 이름이 나옴 
int draw_X(int start_company ,int start_company_Q,int finish_company,int finish_company_Q,int max_a_y, int min_a_y );//x축 그리기 
int draw_y ( int max_a_y, int min_a_y); //y축 그리기 unit  
void print_x(int k, int x, int y, int width,int sc ,int scq,int fc,int fcq); //x축 그리는 함수 
int draw_x_d(int t,int n); // x축 밑 부분 그리는 함수 
void gotoxy(int x, int y);
void print_com(int k,int x, int y,int sc ,int scq); //x축에 년도, 분기 적기 
int axis( int start_company ,int start_company_Q,int finish_company,int finish_company_Q, int max_a_y, int min_a_y,int max_st,int min_st, int max_b_y, int min_b_y ); // 좌표축 나타내기 
int dif_st(int max_st, int min_st); //주식의 최댓값의 1/3이 최솟값보다 크면 1을 작으면 0을 return해주는 함수 
void draw_st(int max_st,int min_st,int max_a_y, int min_a_y); //주식 축 그래프 그리는 함수 
int stc_gap(int max_st); // 주식 간격 계산해주는 함수  
void unit_y(); //y 축에 단위 입력해주는 함수 
void textc(int colorNum); //텍스트 색상 바꿔주는 함수 
int draw_y ( int max_a_y, int min_a_y, int max_b_y, int min_b_y) ;  //y축에 단위 색깔바꾸고 입력해주는 함수
void danwi(int a, int b,int k, int max_a_y, int min_a_y); //y축에 단위 색깔바꾸고 입력해주는 함수  max&min_a 는 당기 순이익, max,min_b는 영업이익을 입력 
int excel(); //데이터 불러와주는 함수  
int term = 0; // 데이터 범위를 설정한 후에 총 x축에 총 몇 분기가 있는지 저장해주는 변수 
int wi ,dangiwi,stockwi; //x축의 너비, 당기순이익 너비, 주가 너비를 저장해주는 변수 
 



struct stock{ //주식 정보 받아오는 구조체 구조 선언 
	double date; //년도_분기 정보 받음 
	double dangi; //당기순이익 정보 받음 
	double yeop; // 영업 이익 정보 받음
	double stck; //평균 주가 정보 얻음 
};
struct stock comp[100]; //주식 정보를 입력받는 구조체 변수 만들기 





HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE); //배경 설정할 때 선언해야 하는 명령어 
int text_data(int re,int i); //중간에 다시 시작시키겠습니까 혹은 시작시키겠습니까 문장을 출력해주는 함수 
int text_company(int company); //회사 나타내는 문장 출력해주는 함수 
int start();   // 처음 시작 창을 띄우는 함수 
int select();  // 회사를 선택하는 함수  
int menu_2(int company); // 회사를 선택한 후 데이터 범위를 선택해주는 함수 
int y_a_dif(int max_a_y, int min_a_y); // y의 max값의 1/3이 min값보다 큰지 작은지 알려주는 함수   
int y_a_gap(int max_a_y, int min_a_y); // y 당기 순이익 간격 계산 해주는 함수 
int draw_y (int n,int max_a_y, int min_a_y); //y축 그리기
int s_com,s_comQ,f_com,f_comQ; // menu_2에서 변수 받아오기 
int  coms; //x축에 데이터 입력할 때 범위 간격 나타내주는 변수 
int st_term; //주식축의 한 단위 당 몇 주를 할당하는지 확인해주는 변수 
int graph(int max_a_y, int min_a_y,int max_st, int min_st,int wid, int dangiwid, int stockwid,int start_company ,int start_company_Q,int finish_company,int finish_company_Q); //그래프에 데이터 값을 *로 표시해주는 함수 
double mami_data(int start_data, int index); //max값,min값 반환해주는 함수 
int dan_gr(int max_a_y, int min_a_y,int wid, int dangiwid,int start_company ,int start_company_Q,int finish_company,int finish_company_Q); //당기 순이익 그래프 그려주는 함수 
double max(double x, double y); //최댓갑 반환해주는 함수 
double min(double x, double y); //최솟값 반환해주는 함수 
double max_a_y_1, min_a_y_1 ,max_b_y_1, min_b_y_1, max_st_1, min_st_1; //max함수,min함수 만들고 나서 적기 
int maxd[20][20][20]; //max값 저장해주는 3차원 배열 1은 당기 순이익, 2은 영업이익, 3는 주가 
int mind[20][20][20]; //min값 저장해주는 3차원 배열 1은 당기 순이익, 2은 영업이익, 3는 주가 
int yeop_gr(int max_b_y, int min_b_y, int wid, int dangiwid, int start_company, int start_company_Q, int finish_company, int finish_company_Q); //영업이익 그래프 그리기 



int main(){
	int company_position=1;
	int excel_true=0; //excel 파일을 불러올 수 있는지 확인하고 -1이 리턴되면 프로그램을 다시 시작 하도록 한다. 
	int start_data = 0; //기업의 데이터 시작 년도가 몇 번째인지 확인해주는 변수 
	while(1){
		coms=0; 
		start();
		if (position == 1){
			break;
		}
		company_position=select();
		start_data=(range_company[company]-2010)*4+1; 
//		printf("%d",company); 
		excel_true = excel(); // 만약 파일이 정상적으로 읽어졌다면 index값이 반환된다. 
		gotoxy(10,10);
//		printf("%d",excel_true);
		mami_data(start_data,index_com[company]);
		gotoxy(20,20);
		
		maxd[company][1][1] = floor(max_a_y_1+0.5),maxd[company][2][1]=(max_b_y_1+0.5),maxd[company][3][1]=(max_st_1+0.5);
		mind[company][1][1] = floor(min_a_y_1+0.5),mind[company][2][1]=(min_b_y_1+0.5),mind[company][3][1]=(min_st_1+0.5);
//		printf("%lf %lf %lf %lf %lf %lf",max_a_y_1,min_a_y_1,max_b_y_1,min_b_y_1,max_st_1,min_st_1) ;
		
//		printf("%d",excel_true); 
//		printf("%s",filename[company]);
		if (excel_true !=-1){
			menu_2(company_position); //데이터 범위 물어보고 데이터 범위 시작 년도, 분기, 끝나는 년도, 분기 받기 
			
			
			
			axis(s_com,s_comQ,f_com,f_comQ,maxd[company][1][1],mind[company][1][1],maxd[company][3][1],mind[company][3][1],maxd[company][2][1],mind[company][2][1]); //나중에 여기 당기순이익, 주가, 영업이익 입력해주기 wid는 x축 상에서 데이터 값의 너비, 여기다 +9를 해주면 넣어야할 데이터의 x좌표가 나온다. 
			gotoxy(20,10);
//			printf("%d",wid);
			gotoxy(1,1);
			printf("※노란색은 당기순이익, 파란색은 영업이익, 초록색은 주가를 나타낸 것입니다.※");
			dan_gr(max_a_y_1,min_a_y_1,wi,dangiwi,s_com,s_comQ,f_com,f_comQ);
			yeop_gr(max_a_y_1,min_a_y_1,wi,dangiwi,s_com,s_comQ,f_com,f_comQ);
			while (true){
				int i=1;
			}
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

void textc(int colorNum) { //텍스트 색상 바꾸는 함수 https://dev-with-precious-dreams.tistory.com/m/entry/C%EC%96%B8%EC%96%B4-%EC%BD%98%EC%86%94%EC%B0%BD%EC%97%90-%EC%B6%9C%EB%A0%A5%EB%90%98%EB%8A%94-%EA%B8%80%EC%9E%90%EC%83%89-%EB%B0%94%EA%BE%B8%EB%8A%94-%EB%B0%A9%EB%B2%95 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

int y_a_dif(int max_a_y, int min_a_y){ // y의 max값의 1/3이 min값보다 큰지 작은지 알려주는 함수 크면 1을 작으면 0을 return한다.  
	return max_a_y/3 > min_a_y;
}

int y_a_gap(int max_a_y, int min_a_y){ // y간격 계산 해주는 함수 max_a_y, min_a_y 는 그 기업 주식의 최대 당기순이익과 최소 당기순이익을 입력해준다. 
	int y_a_gap = 0;
	y_a_gap = max_a_y / 36 ;
	return y_a_gap;
} 

//void delay(clock_t n)
//
//{
//
//  clock_t start = clock();
//
//  while(clock() - start < n);
//
//}

//void unityd(int a, int b, int t){ //y축에 단위 입력해주는 함수 중 반복되는 코드 
//	textc(a);
//	if (t==0)	printf("(%s)",unit[company]);
//	elif (t==1) printf("(%s)",unit_st[company])
//	elif(t==2) printf("(%s)",)
//	textc(b);
//}    지금 생각해보니 딱히 필요가 없음 단기 순이익 하고 영업 이익은 단위 같음 구별할 필요 x 

void unit_y(){ //y 축에 단위 입력해주는 함수
	int company_s = company; //전역변수 company에서 받아오기 
	gotoxy(1,3);
	printf("(%s)",unit[company]);
	gotoxy(95,3);
	printf("(%s)",unit_st[company]);
}

void danwi(int a, int b,int k, int max_a_y, int min_a_y){ //y축에 단위 색깔바꾸고 입력해주는 함수  
	textc(a); 
	printf("%d",((36-k)*y_a_gap(max_a_y,min_a_y)));
	textc(b);
}

int draw_y ( int max_a_y, int min_a_y, int max_b_y, int min_b_y){ //y축 그리기   
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
			gotoxy(1,i); // y축에 단위 표시를 한다. max_a_y이용 
			danwi(14,15,k,max_a_y,min_a_y);
			gotoxy(1,i+1); // y축에 당기순이익 밑에 영업이익을 표시한다 max_b_y이용 
			danwi (11,15,k,max_b_y,min_b_y);
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
				textc(10);
				printf("%d",((36-k)*stc_gap(max_st)));
				textc(15);
			}
			k++;
			
		}
	} 
	if ((y_a_dif(max_a_y,min_a_y))==0){ // max값의 1/3보다 min값이 크면 ~을 y축 중간에 넣어야 하므로 조건문 사용 
		gotoxy(stx,n);
		printf("~");
		gotoxy(stx,n+1);
		printf("~");
		for (int i =2; i<=4;i++){
			gotoxy(stx,n+i);
			printf("|");
		}
		
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
	term = 0;
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
	return width;
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
int axis( int start_company ,int start_company_Q,int finish_company,int finish_company_Q,int max_a_y, int min_a_y,int max_st,int min_st, int max_b_y, int min_b_y ) { // 좌표축 나타내기 
	int i;
	int dangiwid=y_a_gap(max_a_y,min_a_y);
	int stockwid = stc_gap(max_st); //당기 순이익 간격과 주식 값의 간격을 불러와주는 변수 
	int wid=0; // x축의 너비를 저장해주는 변수 
	draw_y(max_a_y,min_a_y, max_b_y, min_b_y);
	wid = draw_x(start_company,start_company_Q,finish_company,finish_company_Q,max_a_y,min_a_y);
	draw_st(max_st,min_st,max_a_y,min_a_y);
	dangiwi=dangiwid, stockwi=stockwid, wi=wid;
}

int excel(){ //데이터 불러와주는 함수 

	FILE *fp = fopen(filename[company],"r");
	int index = 1; //구조체의 배열에서 회사 번호마다 하나씩 넣기 
	if (!fp){ //파일이 찾아지지 않았을 때 빠져나오도록 한다. 
		system("cls");
		printf("%d",fp);
		printf("\n\n파일을 찾을 수 없습니다.\n3초 뒤 프로그램이 다시 시작됩니다.");
		Sleep(3000);
		return -1;		
	}
	
	while(!feof(fp)){ //파일의 끝까지만 true 
		fscanf(fp,"%lf,%lf,%lf,%lf",&comp[index].date,&comp[index].dangi,&comp[index].yeop,&comp[index].stck);
//		printf("%5.5lf:date %5d:dangi %5d:yeop %5.5lf:stck\n",comp[index].date,comp[index].dangi,comp[index].yeop,comp[index].stck);
//		char p[150]; 
//		fgets(line,1024,fp); //한 라인값을 받아온 후 p에 저장시킨다. 
//		char *ptr = strtok(p,",");
//		scanf("%s",comp[index].date);
//		ptr=strtok(NULL,",");
//		while(ptr != NULL){
//			scanf("%f",com)
//		}

//		sscanf(line, "%lf %d %lf %lf",&comp[index].date,&comp[index].dangi,&comp[index].yeop,&comp[index].stck); // 년도_분기, 당기순이익, 영업이익, 평균 주가 입력 받기 
		index++;
	}
	return (index-1);
//	for (int i = 1; i<(index); i++){  //파일 읽어서 입력해주기 (test용도) 
//		printf("%5.1lf:date, %5.3lf:dangi, %5.3lf:yeop, %5.0lf:stck\n",comp[i].date,comp[i].dangi,comp[i].yeop,comp[i].stck);
//	}
} 

double mami_data(int start_data, int index){ //max값,min값 반환해주는 함수 
	double max_data=0, min_data=100000;
	double max_data_ye=0, min_data_ye=100000;
	double max_data_st=0, min_data_st=100000;
	int start = start_data;
	
	for (int i =start_data; i <index; i++){
		max_data=max(comp[i].dangi,max_data);
		min_data=min(comp[i].dangi,min_data);
//		printf("%5.5lf , %5.5lf\n",max_data,min_data);
	}
	for (int i =start_data; i <=index; i++){
		max_data_ye=max(comp[i].yeop,max_data_ye);
		min_data_ye=min(comp[i].yeop,min_data_ye);
	}
	for (int i =start_data; i <=index; i++){
		max_data_st=max(comp[i].stck,max_data_st);
		min_data_st=min(comp[i].stck,min_data_st);
		
	}
//	printf("%lf %lf %lf %lf %lf %lf",max_data, min_data,max_data_ye,min_data_ye,max_data_st,min_data_st );
	 max_a_y_1 =max_data, min_a_y_1=min_data , max_b_y_1=max_data_ye, min_b_y_1=min_data_ye,max_st_1=max_data_st, min_st_1=min_data_st;
}

int dan_gr(int max_a_y, int min_a_y,int wid, int dangiwid,int start_company ,int start_company_Q,int finish_company,int finish_company_Q){ //당기 순이익 그래프 그려주는 함수 
	int po_ind=(start_company-2010)*4+start_company_Q; //시작하는 데이터 범위가 comp구조체의 몇번째 index에 위치해있는지 확인해주는 변수이다.
	float dangi_y=0; //당기순이익이 그래프에서 어느 위치에 있는지 저장해주는 변수 
	textc(14);
	for (int i=1; i<=term;i++){
		dangi_y= 6+(36-(comp[i+po_ind-1].dangi/dangiwid))*4;
//		gotoxy(50,i+20);
//		printf("%f",dangi_y);
		gotoxy((i*wid)+9,dangi_y);
		printf("*");
	} 
	textc(15);
//	gotoxy()
}

int yeop_gr(int max_b_y, int min_b_y, int wid, int dangiwid, int start_company, int start_company_Q, int finish_company, int finish_company_Q){ //영업이익 그래프 그리기 
	int po_ind=(start_company-2010)*4+start_company_Q; //시작하는 데이터 범위가 comp구조체의 몇번째 index에 위치해있는지 확인해주는 변수이다.
	float yeop_y=0; //영업이익이 그래프에서 어느 위치에 프린트 해야하는지 입력해주는 변수
	textc(11);
	for (int i=1; i<=term; i++){
		yeop_y=6+(36-(comp[i+po_ind-1].yeop/dangiwid))*4;
		gotoxy((i*wid)+9,yeop_y);
		printf("*");
	} 
	textc(15);
}

double min(double x, double y) {return x < y ? x : y ;}
double max(double x, double y) {return x > y ? x : y ;}



int graph(int max_a_y, int min_a_y,int max_st, int min_st,int wid, int dangiwid, int stockwid,int start_company ,int start_company_Q,int finish_company,int finish_company_Q ){ //그래프에 데이터 값을 *로 표시해주는 함수 
	
} 
