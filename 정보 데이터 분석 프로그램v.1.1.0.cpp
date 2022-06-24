	/* 
   =================================================================
   =                                                               =
   =  ����� �������Ͱ� �������Ϳ� ���� �ְ� ��ȭ �� �߼� �ľ�   =
   =                        ������: ������                         =
   =                                                               =
   =                                                     ver.1.1.0 =
   =================================================================
*/

//������ ��ó:https://www.deepsearch.com/ , https://kr.investing.com/equities/yahoo-inc-chart
//

#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<math.h>
#include<time.h>
#include<stdlib.h> // sleep �Լ� �������� 
#define stx 100 //�ֽ� y�� x��ǥ 
#include<string.h> 




int restart = 0; //������ߴ��� ó�� �����ߴ��� �Ǵ����ִ� ���� 
int position = 0; // start �Լ����� 0�̸� 1�� ������, 1�̸� 2�� ������ ���ϴ� ���� Ȯ���� �� ����  
int company = 1; // ȸ�� ������ �������ִ� ����. 1 : SAMSUNG, 2 : APPL, 3 : AMAZON, 4 : MICROSOFT, 5 : TSMC, 6: SK hynix
int range_company[100]={0,2010,2016,2016,2016,2016,2011}; //����� ������ ��� ���� �ּ� �������� �⵵ ǥ�� �迭 
int range_company_1[100]={0,1,1,1,1,1,1};  //����� ������ ��� ���� �ּ� �������� �б� ǥ�� �迭 
int lim_range_company[100]={0,2021,2020,2020,2020,2020,2021};  //����� ������ ��� ���� �ִ� �������� �⵵ ǥ�� �迭
int lim_range_company_1[100]={0,4,4,4,4,4,4};  //����� ������ ��� ���� �ִ� �������� �⵵ ǥ�� �迭 
int index_com[100]={0,48,44,44,44,44,48}; //����� ������ �б� �� 
const char* company_name[100]={0,"SAMSUNG","APPLE","AMAZON","MICROSOFT","TSMC","SK hynix"};
const char* unit[100]={0,"���KRW","�鸸USD","�鸸USD","�鸸USD","�鸸USD","���KRW"}; //��������, �������� ���� �迭 
const char* unit_st[100]={0,"KRW","USD","USD","USD","USD","KRW"}; //�ֽ� ���� �迭 
const char *filename[100]={0,"samsung.txt","apple.txt","amazon.txt","microsoft.txt","tsmc.txt","sk hynix.txt"}; //���� �ҷ��� �� �̸� �迭 ���� filename[company]�ϸ� �� ȸ���� ���� �̸��� ���� 
int draw_X(int start_company ,int start_company_Q,int finish_company,int finish_company_Q,int max_a_y, int min_a_y );//x�� �׸��� 
int draw_y ( int max_a_y, int min_a_y); //y�� �׸��� unit  
void print_x(int k, int x, int y, int width,int sc ,int scq,int fc,int fcq); //x�� �׸��� �Լ� 
int draw_x_d(int t,int n); // x�� �� �κ� �׸��� �Լ� 
void gotoxy(int x, int y);
void print_com(int k,int x, int y,int sc ,int scq); //x�࿡ �⵵, �б� ���� 
int axis( int start_company ,int start_company_Q,int finish_company,int finish_company_Q, int max_a_y, int min_a_y,int max_st,int min_st, int max_b_y, int min_b_y ); // ��ǥ�� ��Ÿ���� 
int dif_st(int max_st, int min_st); //�ֽ��� �ִ��� 1/3�� �ּڰ����� ũ�� 1�� ������ 0�� return���ִ� �Լ� 
void draw_st(int max_st,int min_st,int max_a_y, int min_a_y); //�ֽ� �� �׷��� �׸��� �Լ� 
int stc_gap(int max_st); // �ֽ� ���� ������ִ� �Լ�  
void unit_y(); //y �࿡ ���� �Է����ִ� �Լ� 
void textc(int colorNum); //�ؽ�Ʈ ���� �ٲ��ִ� �Լ� 
int draw_y ( int max_a_y, int min_a_y, int max_b_y, int min_b_y) ;  //y�࿡ ���� ����ٲٰ� �Է����ִ� �Լ�
void danwi(int a, int b,int k, int max_a_y, int min_a_y); //y�࿡ ���� ����ٲٰ� �Է����ִ� �Լ�  max&min_a �� ��� ������, max,min_b�� ���������� �Է� 
int excel(); //������ �ҷ����ִ� �Լ�  
int term = 0; // ������ ������ ������ �Ŀ� �� x�࿡ �� �� �бⰡ �ִ��� �������ִ� ���� 
int wi ,dangiwi,stockwi; //x���� �ʺ�, �������� �ʺ�, �ְ� �ʺ� �������ִ� ���� 
 



struct stock{ //�ֽ� ���� �޾ƿ��� ����ü ���� ���� 
	double date; //�⵵_�б� ���� ���� 
	double dangi; //�������� ���� ���� 
	double yeop; // ���� ���� ���� ����
	double stck; //��� �ְ� ���� ���� 
};
struct stock comp[100]; //�ֽ� ������ �Է¹޴� ����ü ���� ����� 





HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE); //��� ������ �� �����ؾ� �ϴ� ��ɾ� 
int text_data(int re,int i); //�߰��� �ٽ� ���۽�Ű�ڽ��ϱ� Ȥ�� ���۽�Ű�ڽ��ϱ� ������ ������ִ� �Լ� 
int text_company(int company); //ȸ�� ��Ÿ���� ���� ������ִ� �Լ� 
int start();   // ó�� ���� â�� ���� �Լ� 
int select();  // ȸ�縦 �����ϴ� �Լ�  
int menu_2(int company); // ȸ�縦 ������ �� ������ ������ �������ִ� �Լ� 
int y_a_dif(int max_a_y, int min_a_y); // y�� max���� 1/3�� min������ ū�� ������ �˷��ִ� �Լ�   
int y_a_gap(int max_a_y, int min_a_y); // y ��� ������ ���� ��� ���ִ� �Լ� 
int draw_y (int n,int max_a_y, int min_a_y); //y�� �׸���
int s_com,s_comQ,f_com,f_comQ; // menu_2���� ���� �޾ƿ��� 
int  coms; //x�࿡ ������ �Է��� �� ���� ���� ��Ÿ���ִ� ���� 
int st_term; //�ֽ����� �� ���� �� �� �ָ� �Ҵ��ϴ��� Ȯ�����ִ� ���� 
int graph(int max_a_y, int min_a_y,int max_st, int min_st,int wid, int dangiwid, int stockwid,int start_company ,int start_company_Q,int finish_company,int finish_company_Q); //�׷����� ������ ���� *�� ǥ�����ִ� �Լ� 
double mami_data(int start_data, int index); //max��,min�� ��ȯ���ִ� �Լ� 
int dan_gr(int max_a_y, int min_a_y,int wid, int dangiwid,int start_company ,int start_company_Q,int finish_company,int finish_company_Q); //��� ������ �׷��� �׷��ִ� �Լ� 
double max(double x, double y); //�ִ� ��ȯ���ִ� �Լ� 
double min(double x, double y); //�ּڰ� ��ȯ���ִ� �Լ� 
double max_a_y_1, min_a_y_1 ,max_b_y_1, min_b_y_1, max_st_1, min_st_1; //max�Լ�,min�Լ� ����� ���� ���� 
int maxd[20][20][20]; //max�� �������ִ� 3���� �迭 1�� ��� ������, 2�� ��������, 3�� �ְ� 
int mind[20][20][20]; //min�� �������ִ� 3���� �迭 1�� ��� ������, 2�� ��������, 3�� �ְ� 
int yeop_gr(int max_b_y, int min_b_y, int wid, int dangiwid, int start_company, int start_company_Q, int finish_company, int finish_company_Q); //�������� �׷��� �׸��� 



int main(){
	int company_position=1;
	int excel_true=0; //excel ������ �ҷ��� �� �ִ��� Ȯ���ϰ� -1�� ���ϵǸ� ���α׷��� �ٽ� ���� �ϵ��� �Ѵ�. 
	int start_data = 0; //����� ������ ���� �⵵�� �� ��°���� Ȯ�����ִ� ���� 
	while(1){
		coms=0; 
		start();
		if (position == 1){
			break;
		}
		company_position=select();
		start_data=(range_company[company]-2010)*4+1; 
//		printf("%d",company); 
		excel_true = excel(); // ���� ������ ���������� �о����ٸ� index���� ��ȯ�ȴ�. 
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
			menu_2(company_position); //������ ���� ����� ������ ���� ���� �⵵, �б�, ������ �⵵, �б� �ޱ� 
			
			
			
			axis(s_com,s_comQ,f_com,f_comQ,maxd[company][1][1],mind[company][1][1],maxd[company][3][1],mind[company][3][1],maxd[company][2][1],mind[company][2][1]); //���߿� ���� ��������, �ְ�, �������� �Է����ֱ� wid�� x�� �󿡼� ������ ���� �ʺ�, ����� +9�� ���ָ� �־���� �������� x��ǥ�� ���´�. 
			gotoxy(20,10);
//			printf("%d",wid);
			gotoxy(1,1);
			printf("�س������ ��������, �Ķ����� ��������, �ʷϻ��� �ְ��� ��Ÿ�� ���Դϴ�.��");
			dan_gr(max_a_y_1,min_a_y_1,wi,dangiwi,s_com,s_comQ,f_com,f_comQ);
			yeop_gr(max_a_y_1,min_a_y_1,wi,dangiwi,s_com,s_comQ,f_com,f_comQ);
			while (true){
				int i=1;
			}
		}
	restart=1;
}

   
    
}

int start(){   // ó�� ���� â�� ���� �Լ� 
	position = 0;
	text_data(restart,position); 
	int keyboard_input = 0; //Ű���忡�� ����Ű �Է� �޴� ����
//	if (restart == 0) printf("���α׷��� �����Ű�ðڽ��ϱ�?");
//    else printf("���α׷��� �ٽ� �����Ű�ðڽ��ϱ�?");
	
	while(true){

		keyboard_input = getch();
		
		if (keyboard_input==224){
			keyboard_input = getch();
			
			switch(keyboard_input){
				case 72: // �����Ű ������ �� 
					position = 0;
					text_data(restart,position);
					break;
				case 80: //�����Ű ������ �� 
				    position = 1;
					text_data(restart,position);
					break; 
				default:
					break;
			}
		}
		 
    	if (keyboard_input==13) break; // ����Ű�� ������ �� ���������� ��ɾ� 
	}
	
}
	
int select(){   // ȸ�縦 �����ϴ� â�� ���� �Լ� 
	company = 1; // ȸ�� ���� ���� �ʱ�ȭ 
	int keyboard_input = 0; //Ű���忡�� ����Ű �Է� �޴� ����
	text_company(company);
	while(true){

		keyboard_input = getch();
		
		if (keyboard_input==224){
			keyboard_input = getch();
			
			switch(keyboard_input){
				case 72: // �����Ű ������ �� 
					if (company == 1) company++; //company�� 1�̸� �ּ��̹Ƿ� 1���� ���� 1���� �Ȱ��� ���� �����ϱ� 
					company--;
					text_company(company);
					break;
				case 80: //�����Ű ������ �� 
				    if (company == 6) company--; //company�� 6�̸� �ִ��̹Ƿ� 1 ������ �ٽ� �÷��� �Ȱ��� ���� �����ϱ� 
				    company ++;
					text_company(company);
					break; 
				default:
					break;
			}
		}
		 
    	if (keyboard_input==13) return company; // ����Ű�� ������ �� ���������� ��ɾ� 
	}
	
}	

int text_company(int company){
	system("cls");
	printf("\n ��� ȸ���� �����͸� �м��� ���Դϱ�?");
	for (int i=1;i<=6;i++){
		printf("\n");
		if(i==company) SetConsoleTextAttribute(hC,240); 
		printf(" %d.%s",i,company_name[i]);
		if(i==company) SetConsoleTextAttribute(hC,7);
	}
	printf("\n");
} 

int text_data(int re,int i){
	system("cls"); // ���α׷� â�� ��µ� ���ڵ��� ���� �����ִ� ��ɾ� 
	printf("\n\n\n\n\t==========================================\n");
	printf("\t=                                        =\n");
	printf("\t=    ");
	if (i==0){ // position�� 1�̸� 2�� ������ ��ġ�ϹǷ� ������ �ٲ�� �ȵǰ� position�� 0�̸� 1�� ������ ���� �ٲ���ؼ� if ���ǹ��� �־���. 
		SetConsoleTextAttribute(hC,240); //���� ������� �ٲٱ� 
		if (restart == 0){ // ���α׷��� �ѹ��� ���Ҵٸ� '�ٽ�'��� �ܾ �ٿ��� print �ϵ��� ���ִ� ���ǹ� 
			printf("1.���α׷��� �����Ű�ðڽ��ϱ�?");
		    SetConsoleTextAttribute(hC,7); 	//���� ���������� �ٲٱ� 
			printf("   ");
		}
	
		else{
			printf("\b\b1.���α׷��� �ٽ� �����Ű�ðڽ��ϱ�?");
   		}
    	SetConsoleTextAttribute(hC,7); 
		printf(" =\n");	
	}
	else{

		if (restart == 0){// ���α׷��� �ѹ��� ���Ҵٸ� '�ٽ�'��� �ܾ �ٿ��� print �ϵ��� ���ִ� ���ǹ� 
			printf("1.���α׷��� �����Ű�ðڽ��ϱ�?   ");
		}
		else{
			printf("\b\b1.���α׷��� �ٽ� �����Ű�ðڽ��ϱ�?");
  		}
		printf(" =\n");
	}
	printf("\t=     ");
	if (i==0){
		printf("2.���α׷��� �����Ͻðڽ��ϱ�?");
	}
	else{
		SetConsoleTextAttribute(hC,240);
		printf("2.���α׷��� �����Ͻðڽ��ϱ�?");
		SetConsoleTextAttribute(hC,7);
	}
	printf("     =\n");
	printf("\t=                                        =\n");
	printf("\t==========================================\n");
	
}

int menu_2(int company){
	int start_company = 0, start_company_Q=0, finish_company=0, finish_company_Q=0; //ȸ�� ������ �м� ���� ����, ������ ���� �Է� �޴� ���� 
	int start_input = 0, finish_input = 0; // ����&������ ���� �����ߴ��� Ȯ���ϴ� ���� 
	int re=0; //�߸� �Է��Ͽ����� Ȯ���ϴ� ���� 
	while (start_input!=1){
		if(re == 0){
			system("cls"); // ���α׷� â�� ��µ� ���ڵ��� ���� �����ִ� ��ɾ� 
			printf("\n�� �⵵ �� �б� ���� Ȯ������ �Է��Ͻʽÿ�.(%d_%d<=�Է��� ��<=%d_%d)\n �Է� ���: (���۵Ǵ� �⵵)_(���۵Ǵ� �б�) ",range_company[company],range_company_1[company],lim_range_company[company],lim_range_company_1[company]); 
		}
		else{
			system("cls"); // ���α׷� â�� ��µ� ���ڵ��� ���� �����ִ� ��ɾ� 
			printf("\n�߸� �Է��ϼ̽��ϴ�. �� �⵵ �� �б� ���� Ȯ������ �Է��Ͻʽÿ�.(%d_%d<=�Է��� ��<=%d_%d)\n �Է� ���: (���۵Ǵ� �⵵)_(���۵Ǵ� �б�) ",range_company[company],range_company_1[company],lim_range_company[company],lim_range_company_1[company]); 
		} 
		scanf("%d_%d",&start_company,&start_company_Q); //���� �⵵, �б� �޾ƿ��� 
		printf("%d",start_company_Q);
		fflush(stdin); // �Է� ���� �ʱ�ȭ 
		printf("%d",start_company_Q);
		if (range_company[company]<=start_company && start_company<=lim_range_company[company]&&1<=start_company_Q&&start_company_Q<=4){ //ȸ���� ������ ���� �⵵ ���� 2021�� ������ �ޱ� ��, �б�� ����� ���� 
			re = 0;
			start_input = 0; 
			while(finish_input !=1){
				if(re == 0){
					system("cls"); // ���α׷� â�� ��µ� ���ڵ��� ���� �����ִ� ��ɾ� 
					printf("\n %d�⵵ %d�б� ���� ������ �м��� �����մϴ�. \n�� �⵵ �� �б� ���� Ȯ������ �Է��Ͻʽÿ�.(%d_%d<�Է��� ��<=%d_%d)\n �Է� ���: (������ �⵵)_(������ �б�) ",start_company,start_company_Q,start_company,start_company_Q,lim_range_company[company],lim_range_company_1[company]); 
				}
				else{
					system("cls"); // ���α׷� â�� ��µ� ���ڵ��� ���� �����ִ� ��ɾ� 
					printf("\n�߸� �Է��ϼ̽��ϴ�. �� �⵵ �� �б� ���� Ȯ������ �Է��Ͻʽÿ�.(%d_%d<�Է��� ��<=%d_%d)\n �Է� ���: (������ �⵵)_(������ �б�) ",start_company,start_company_Q,lim_range_company[company],lim_range_company_1[company]); 
				} 
				scanf("%d_%d",&finish_company,&finish_company_Q); 
				fflush(stdin); // �Է� ���� �ʱ�ȭ 
				if (start_company<=finish_company&&finish_company<=2021&&1<=finish_company_Q&&finish_company_Q<=4){ // ������ �⵵�� ���� �⵵���� ũ�ų� ����, 2021�� ���Ͽ����� �׸��� �бⰡ 1~4���̿� �־������ �з��ϴ� ���ǹ� 
					finish_input = 1; //finish ���� �Է� �Ǿ����� Ȯ�� 
					if (start_company == finish_company){ //���� ���� �⵵�� ������ �⵵�� ���ٸ� 
						if (start_company_Q < finish_company_Q){ //������ �бⰡ ���� �б⺸�� Ŀ���Ѵ�. 
							re=0;
							system("cls");
//							printf("%d",start_company_Q);

							s_com=start_company,s_comQ=start_company_Q,f_com=finish_company,f_comQ =finish_company_Q;
							return 0;
//							gotoxy(25,15); 
//							printf("%d, %d, %d, %d",start_company, start_company_Q, finish_company, finish_company_Q);
 
						}
						else{
							finish_input = 0; //�бⰡ �߸� �ԷµǾ �ٽ� finish_input 0���� �ٲ��ֱ� 
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

void textc(int colorNum) { //�ؽ�Ʈ ���� �ٲٴ� �Լ� https://dev-with-precious-dreams.tistory.com/m/entry/C%EC%96%B8%EC%96%B4-%EC%BD%98%EC%86%94%EC%B0%BD%EC%97%90-%EC%B6%9C%EB%A0%A5%EB%90%98%EB%8A%94-%EA%B8%80%EC%9E%90%EC%83%89-%EB%B0%94%EA%BE%B8%EB%8A%94-%EB%B0%A9%EB%B2%95 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

int y_a_dif(int max_a_y, int min_a_y){ // y�� max���� 1/3�� min������ ū�� ������ �˷��ִ� �Լ� ũ�� 1�� ������ 0�� return�Ѵ�.  
	return max_a_y/3 > min_a_y;
}

int y_a_gap(int max_a_y, int min_a_y){ // y���� ��� ���ִ� �Լ� max_a_y, min_a_y �� �� ��� �ֽ��� �ִ� �������Ͱ� �ּ� ���������� �Է����ش�. 
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

//void unityd(int a, int b, int t){ //y�࿡ ���� �Է����ִ� �Լ� �� �ݺ��Ǵ� �ڵ� 
//	textc(a);
//	if (t==0)	printf("(%s)",unit[company]);
//	elif (t==1) printf("(%s)",unit_st[company])
//	elif(t==2) printf("(%s)",)
//	textc(b);
//}    ���� �����غ��� ���� �ʿ䰡 ���� �ܱ� ������ �ϰ� ���� ������ ���� ���� ������ �ʿ� x 

void unit_y(){ //y �࿡ ���� �Է����ִ� �Լ�
	int company_s = company; //�������� company���� �޾ƿ��� 
	gotoxy(1,3);
	printf("(%s)",unit[company]);
	gotoxy(95,3);
	printf("(%s)",unit_st[company]);
}

void danwi(int a, int b,int k, int max_a_y, int min_a_y){ //y�࿡ ���� ����ٲٰ� �Է����ִ� �Լ�  
	textc(a); 
	printf("%d",((36-k)*y_a_gap(max_a_y,min_a_y)));
	textc(b);
}

int draw_y ( int max_a_y, int min_a_y, int max_b_y, int min_b_y){ //y�� �׸���   
	int k = 0; // ���� ǥ�ð� �� �� �ݺ� �Ǿ����� Ȯ���ϴ� ���� 
	int n=0; //n�� y_a_dif = 1�̶�� 96 ������ 0�̶�� 144������ �Է����ָ� �ȴ�.
	if (y_a_dif(max_a_y,min_a_y)) n=144;
	else n=96; 
	for (int i = 3; i <= (n+3); i++){
		gotoxy(9,i);
		printf("|");
		if (((i+2)%4)==0){
			gotoxy(9,i);
			printf("-");
			gotoxy(1,i); // y�࿡ ���� ǥ�ø� �Ѵ�. max_a_y�̿� 
			danwi(14,15,k,max_a_y,min_a_y);
			gotoxy(1,i+1); // y�࿡ �������� �ؿ� ���������� ǥ���Ѵ� max_b_y�̿� 
			danwi (11,15,k,max_b_y,min_b_y);
			k++;
			
		}
	} 
	if ((y_a_dif(max_a_y,min_a_y))==0){ // max���� 1/3���� min���� ũ�� ~�� y�� �߰��� �־�� �ϹǷ� ���ǹ� ��� 
		gotoxy(9,n+4);
		printf("~");
		gotoxy(9,n+5);
		printf("~");
		draw_x_d(y_a_dif(max_a_y,min_a_y),n);
	}
	else{
		draw_x_d(y_a_dif(max_a_y,min_a_y),n); //y_a_dif �� 1�� ��Ȳ 
	}
	unit_y();
}

int dif_st(int max_st, int min_st){ //�ֽ��� �ִ��� 1/3�� �ּڰ����� ũ�� 1�� ������ 0�� return���ִ� �Լ� 
	return (max_st/3)>min_st;	
}

void draw_st (int max_st, int min_st,int max_a_y, int min_a_y){ //y�� �׸���   
	int k = 0; // ���� ǥ�ð� �� �� �ݺ� �Ǿ����� Ȯ���ϴ� ���� 
	int n=0; //n�� y_a_dif = 1�̶�� 96 ������ 0�̶�� 144������ �Է����ָ� �ȴ�.
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
	if ((y_a_dif(max_a_y,min_a_y))==0){ // max���� 1/3���� min���� ũ�� ~�� y�� �߰��� �־�� �ϹǷ� ���ǹ� ��� 
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
//		draw_x_d(y_a_dif(max_a_y,min_a_y),n); //y_a_dif �� 1�� ��Ȳ 
//	}
	
}

int stc_gap(int max_st){ // y���� ��� ���ִ� �Լ� max_a_y, min_a_y �� �� ��� �ֽ��� �ִ� �������Ͱ� �ּ� ���������� �Է����ش�. 
	int stcgap = 0;
	stcgap = max_st / 36 ;
	return stcgap;
} 

void draw_st_d(int t,int n){ // �ֽ� �� �� �κ� �׸��� �Լ� 
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

int draw_x_d(int t,int n){ // x�� �� �κ� �׸��� �Լ� 
	if(!t){
		for (int i = n+6; i<=(n+10);i++){
			gotoxy(9,i);
			printf("|");
			if(i==n+8){
				gotoxy(9,n+8);
				printf("+"); //���� �׷����� +�� �Է��ϱ� 
			}
		}
	}
	else{
		for (int i = n+4; i<=(n+8);i++){
			gotoxy(9,i);
			printf("|");
			if(i==n+8){
				gotoxy(9,n+6);
				printf("+"); //���� �׷����� +�� �Է��ϱ� 
			}
		}
	}
}

void write_x(int com, int comQ){
//	printf// 
} 

// p�� x���� �׷������� ���� y��ǥ�� �Է��ؾ� �ϴ��� �Է����ִ� ����  draw_y�� n+8�� p�� �ԷµǸ� �ȴ�. 
int draw_x(int start_company ,int start_company_Q,int finish_company,int finish_company_Q,int max_a_y, int min_a_y ){ //x�� �׸��� ������ ������ ���� �� ���� ǥ�� �ϱ� 
	int p=0;
	if (y_a_dif(max_a_y,min_a_y)) p=150;
	else p=104;
	term = 0;
	int width = 0; // x�࿡ �⵵, �б� �Է��� �� ���� ���� �ʺ� �������ִ� ���� 
	term = (finish_company-start_company)*4+(finish_company_Q-start_company_Q)+1; //�̷� ���� ����ϸ� ������ ���� ���̿� �� �� �бⰡ �ִ��� Ȯ�� �����ϴ�. 
	width = 90/term;
//	if (width * term >90){
//		width --; //width�� ������
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

void print_x(int k, int x, int y, int width,int sc ,int scq,int fc,int fcq){ //x�� ---| �� �� �׸��� �Լ� 
	int com = sc, comq = scq;
	for (int i =0; i <=(width-2); i++){  // -�� �ʺ�ŭ ������ֵ��� �Ѵ� 
		gotoxy(x+i,y); 
		printf("-");
	gotoxy(x+width-1,y); // -�� �Է��� �� �������� | �� ����Ѵ�. 
	printf("|");
	print_com(k,x+width-1,y+1,sc+((scq+coms-1)/4),(scq+coms)%4); // | �ؿ� �⵵, �б⸦ �� ���ھ� ������ش�. 
	}
}
void print_com(int k, int x, int y,int sc ,int scq){ //x�࿡ �⵵, �б� ����
	if (k==1){
		for (int i = 0;i<4;i++){
			gotoxy(x,y+3-i); // y+3 ���� y���� ���ڸ� �Է����ش�. 
			printf("%d",sc%10); // y+3���� ���� ���ڸ� ����ϹǷ� 10���� ���� �������� ����ѵ� �ٽ� 10���� ���� ���� �����Ῡ ���ڸ� ���ں��� �ϳ��ϳ� ��½����ش�. 
			sc=sc/10;
			}
		gotoxy(x,y+4);
		printf("|");
		gotoxy(x,y+5);
		if (scq == 0) printf("4");	// scq�� �б�� �Է��� ���� 4�� ���� �������� ��Ÿ���Ƿ� 4�϶��� 0�� ��µȴ� ���� 0�϶��� 4�� ��½������ �Ѵ�. 
		else printf("%d",scq); 
	}
	else{
		gotoxy(x,y);
		printf("(�⵵)");
		gotoxy(x,y+1);
		
		printf("  |");
		gotoxy(x,y+2);
		printf("(�б�)");
		
	}
}
int axis( int start_company ,int start_company_Q,int finish_company,int finish_company_Q,int max_a_y, int min_a_y,int max_st,int min_st, int max_b_y, int min_b_y ) { // ��ǥ�� ��Ÿ���� 
	int i;
	int dangiwid=y_a_gap(max_a_y,min_a_y);
	int stockwid = stc_gap(max_st); //��� ������ ���ݰ� �ֽ� ���� ������ �ҷ����ִ� ���� 
	int wid=0; // x���� �ʺ� �������ִ� ���� 
	draw_y(max_a_y,min_a_y, max_b_y, min_b_y);
	wid = draw_x(start_company,start_company_Q,finish_company,finish_company_Q,max_a_y,min_a_y);
	draw_st(max_st,min_st,max_a_y,min_a_y);
	dangiwi=dangiwid, stockwi=stockwid, wi=wid;
}

int excel(){ //������ �ҷ����ִ� �Լ� 

	FILE *fp = fopen(filename[company],"r");
	int index = 1; //����ü�� �迭���� ȸ�� ��ȣ���� �ϳ��� �ֱ� 
	if (!fp){ //������ ã������ �ʾ��� �� ������������ �Ѵ�. 
		system("cls");
		printf("%d",fp);
		printf("\n\n������ ã�� �� �����ϴ�.\n3�� �� ���α׷��� �ٽ� ���۵˴ϴ�.");
		Sleep(3000);
		return -1;		
	}
	
	while(!feof(fp)){ //������ �������� true 
		fscanf(fp,"%lf,%lf,%lf,%lf",&comp[index].date,&comp[index].dangi,&comp[index].yeop,&comp[index].stck);
//		printf("%5.5lf:date %5d:dangi %5d:yeop %5.5lf:stck\n",comp[index].date,comp[index].dangi,comp[index].yeop,comp[index].stck);
//		char p[150]; 
//		fgets(line,1024,fp); //�� ���ΰ��� �޾ƿ� �� p�� �����Ų��. 
//		char *ptr = strtok(p,",");
//		scanf("%s",comp[index].date);
//		ptr=strtok(NULL,",");
//		while(ptr != NULL){
//			scanf("%f",com)
//		}

//		sscanf(line, "%lf %d %lf %lf",&comp[index].date,&comp[index].dangi,&comp[index].yeop,&comp[index].stck); // �⵵_�б�, ��������, ��������, ��� �ְ� �Է� �ޱ� 
		index++;
	}
	return (index-1);
//	for (int i = 1; i<(index); i++){  //���� �о �Է����ֱ� (test�뵵) 
//		printf("%5.1lf:date, %5.3lf:dangi, %5.3lf:yeop, %5.0lf:stck\n",comp[i].date,comp[i].dangi,comp[i].yeop,comp[i].stck);
//	}
} 

double mami_data(int start_data, int index){ //max��,min�� ��ȯ���ִ� �Լ� 
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

int dan_gr(int max_a_y, int min_a_y,int wid, int dangiwid,int start_company ,int start_company_Q,int finish_company,int finish_company_Q){ //��� ������ �׷��� �׷��ִ� �Լ� 
	int po_ind=(start_company-2010)*4+start_company_Q; //�����ϴ� ������ ������ comp����ü�� ���° index�� ��ġ���ִ��� Ȯ�����ִ� �����̴�.
	float dangi_y=0; //���������� �׷������� ��� ��ġ�� �ִ��� �������ִ� ���� 
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

int yeop_gr(int max_b_y, int min_b_y, int wid, int dangiwid, int start_company, int start_company_Q, int finish_company, int finish_company_Q){ //�������� �׷��� �׸��� 
	int po_ind=(start_company-2010)*4+start_company_Q; //�����ϴ� ������ ������ comp����ü�� ���° index�� ��ġ���ִ��� Ȯ�����ִ� �����̴�.
	float yeop_y=0; //���������� �׷������� ��� ��ġ�� ����Ʈ �ؾ��ϴ��� �Է����ִ� ����
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



int graph(int max_a_y, int min_a_y,int max_st, int min_st,int wid, int dangiwid, int stockwid,int start_company ,int start_company_Q,int finish_company,int finish_company_Q ){ //�׷����� ������ ���� *�� ǥ�����ִ� �Լ� 
	
} 
