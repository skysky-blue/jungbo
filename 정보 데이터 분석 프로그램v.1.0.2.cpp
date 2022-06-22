	/* 
   =================================================================
   =                                                               =
   =  ����� �������Ͱ� �ܱ�����Ϳ� ���� �ְ� ��ȭ �� �߼� �ľ�   =
   =                        ������: ������                         =
   =                                                               =
   =                                                     ver.1.0.2 =
   =================================================================
*/

//������ ��ó:https://www.deepsearch.com/ , https://kr.investing.com/equities/yahoo-inc-chart
//

#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<math.h>
#define stx 100 //�ֽ� y�� x��ǥ  

int restart = 0; //������ߴ��� ó�� �����ߴ��� �Ǵ����ִ� ���� 
int position = 0; // start �Լ����� 0�̸� 1�� ������, 1�̸� 2�� ������ ���ϴ� ���� Ȯ���� �� ����  
int company = 1; // ȸ�� ������ �������ִ� ����. 1 : SAMSUNG, 2 : APPL, 3 : AMAZON, 4 : MICROSOFT, 5 : TSMC, 6: SK hynix
int range_company[100]={0,2010,2016,2016,2016,2016,2010}; //����� ������ ��� ���� �ּ� �������� �⵵ ǥ�� �迭 
int range_company_1[100]={0,1,1,1,1,1,1};  //����� ������ ��� ���� �ּ� �������� �б� ǥ�� �迭 
int lim_range_company[100]={0,2021,2020,2020,2020,2020,2021};  //����� ������ ��� ���� �ִ� �������� �⵵ ǥ�� �迭
int lim_range_company_1[100]={0,4,4,4,4,4,4};  //����� ������ ��� ���� �ִ� �������� �⵵ ǥ�� �迭 
const char* company_name[100]={0,"SAMSUNG","APPLE","AMAZON","MICROSOFT","TSMC","SK hynix"};
const char* unit[100]={0,"��","�鸸USD","�鸸USD","�鸸USD","�鸸USD","��"}; //��������, �������� ���� �迭 
const char* unit_st[100]={0,"KRW","USD","USD","USD","USD","KRW"}; //�ֽ� ���� �迭  
int draw_X(int start_company ,int start_company_Q,int finish_company,int finish_company_Q,int max_a_y, int min_a_y );//x�� �׸��� 
void draw_y ( int max_a_y, int min_a_y); //y�� �׸��� unit  
void print_x(int k, int x, int y, int width,int sc ,int scq,int fc,int fcq); //x�� �׸��� �Լ� 
int draw_x_d(int t,int n); // x�� �� �κ� �׸��� �Լ� 
void gotoxy(int x, int y);
void print_com(int k,int x, int y,int sc ,int scq); //x�࿡ �⵵, �б� ���� 
void axis( int start_company ,int start_company_Q,int finish_company,int finish_company_Q,int max_a_y, int min_a_y,int max_st,int min_st ); // ��ǥ�� ��Ÿ���� 
int dif_st(int max_st, int min_st); //�ֽ��� �ִ��� 1/3�� �ּڰ����� ũ�� 1�� ������ 0�� return���ִ� �Լ� 
void draw_st(int max_st,int min_st,int max_a_y, int min_a_y); //�ֽ� �� �׷��� �׸��� �Լ� 
int stc_gap(int max_st); // �ֽ� ���� ������ִ� �Լ�  
void unit_y(); //y �࿡ ���� �Է����ִ� �Լ� 



HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE); //��� ������ �� �����ؾ� �ϴ� ��ɾ� 
int text_data(int re,int i); //�߰��� �ٽ� ���۽�Ű�ڽ��ϱ� Ȥ�� ���۽�Ű�ڽ��ϱ� ������ ������ִ� �Լ� 
int text_company(int company); //ȸ�� ��Ÿ���� ���� ������ִ� �Լ� 
int start();   // ó�� ���� â�� ���� �Լ� 
int select();  // ȸ�縦 �����ϴ� �Լ�  
int menu_2(int company); // ȸ�縦 ������ �� ������ ������ �������ִ� �Լ� 
int y_a_dif(int max_a_y, int min_a_y); // y�� max���� 1/3�� min������ ū�� ������ �˷��ִ� �Լ�   
int y_a_gap(int max_a_y, int min_a_y); // y ��� ������ ���� ��� ���ִ� �Լ� 
void draw_y (int n,int max_a_y, int min_a_y); //y�� �׸���
int s_com=0,s_comQ=0,f_com=0,f_comQ =0; // menu_2���� ���� �޾ƿ��� 
int  coms=0; //x�࿡ ������ �Է��� �� ���� ���� ��Ÿ���ִ� ���� 
int st_term=0; //�ֽ����� �� ���� �� �� �ָ� �Ҵ��ϴ��� Ȯ�����ִ� ���� 



int main(){
	int company_position=1;
	while(1){
		coms=0; 
//		start();
//		if (position == 1){
//			break;
//		}
//		company_position=select();
		menu_2(company_position); //������ ���� ����� ������ ���� ���� �⵵, �б�, ������ �⵵, �б� �ޱ� 
		
		axis(s_com,s_comQ,f_com,f_comQ,720,300,500,250);
		
		while (true){
			int i=1;
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

int y_a_dif(int max_a_y, int min_a_y){ // y�� max���� 1/3�� min������ ū�� ������ �˷��ִ� �Լ� ũ�� 1�� ������ 0�� return�Ѵ�.  
	return max_a_y/3 > min_a_y;
}

int y_a_gap(int max_a_y, int min_a_y){ // y���� ��� ���ִ� �Լ� max_a_y, min_a_y �� �� ��� �ֽ��� �ִ� �������Ͱ� �ּ� ���������� �Է����ش�. 
	int y_a_gap = 0;
	y_a_gap = max_a_y / 36 ;
	return y_a_gap;
} 

void unit_y(){ //y �࿡ ���� �Է����ִ� �Լ�
	gotoxy(1,3);
	printf("(%s)",unit[company]);
	gotoxy(95,3);
	printf("(%s)",unit_st[company]);	
}

void draw_y ( int max_a_y, int min_a_y){ //y�� �׸���   
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
			gotoxy(1,i);
			printf("%d",((36-k)*y_a_gap(max_a_y,min_a_y)));
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
				printf("%d",((36-k)*stc_gap(max_st)));
			}
			k++;
			
		}
	} 
	if ((y_a_dif(max_a_y,min_a_y))==0){ // max���� 1/3���� min���� ũ�� ~�� y�� �߰��� �־�� �ϹǷ� ���ǹ� ��� 
		gotoxy(stx,n+1);
		printf("~");
		gotoxy(stx,n+2);
		printf("~");
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
	int term = 0;
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
	return width+9;
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
void axis( int start_company ,int start_company_Q,int finish_company,int finish_company_Q,int max_a_y, int min_a_y,int max_st,int min_st ) { // ��ǥ�� ��Ÿ���� 
	int i;
	draw_y(max_a_y,min_a_y);
	draw_x(start_company,start_company_Q,finish_company,finish_company_Q,max_a_y,min_a_y);
	draw_st(max_st,min_st,max_a_y,min_a_y);
}

