#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/* MAU QUAN LY SO LUONG SACH CUA MOT NHA SACH
	-CAC DOI TUONG QUAN LY: 
		+ Ten sach: ten
		+ Nha xuat ban: nxb
		+ Tac gia: tgia
		+ So luong: sluong
		+ Gia: gia
*/
int getchoice(){
	int choice;
    printf("\n=======================MENU========================");
    printf("\n| 1- Them mot loai sach moi               Nhan: 1 |");
    printf("\n| 2- Hien thi danh sach                   Nhan: 2 |");
    printf("\n| 3- Xoa mot loai sach                    Nhan: 3 |");
    printf("\n| 4- Cap nhat thong tin mot loai sach     Nhan: 4 |");
    printf("\n| 5- Thoat                                Nhan: 5 |");
    printf("\n===================================================\n");
    printf("\nNhap lua chon cua ban: ");
    
    while (scanf("%d", &choice) != 1) {
        while (getchar() != '\n');
        printf("Thao tac khong hop le. Chon thao tac: ");
        while (getchar() != '\n');
    }
	return choice;
}

// Ham kiem tra: mang da day phan tu chua?
int isFull(char a[][30],int n){
	return n == 200;
}

// Ham kiem tra: mang co rong khong?
int empty(char a[][30],int n){
	return n == 0;
}

char* lTrim (char s[]){
	int i=0;
	while (s[i]==' ') i++;
	if (i>0) strcpy(&s[0], &s[i]);
	return s;
}

char* rTrim (char s[]){
	int i=strlen(s)-1;
	while (s[i]==' ') i--;
	s[i+1]= '\0';
	return s;
}

char* Trim (char s[]){ 
	rTrim(lTrim(s));
	char *ptr = strstr(s,"  ");
	while(ptr!=NULL){
		strcpy(ptr,ptr+1);
		ptr=strstr(s,"  ");
	}
	return s;
}

char* nameStr(char s[]){
	Trim(s);
	strlwr(s);
	int L=strlen(s);
	int i;
	for(i=0;i<L;i++){
		if(i==0||(i>0 && s[i-1] ==' ')){
			s[i]=toupper(s[i]);
		}
	}
	return s;
}

//Ham hoan doi cac gia tri 2 chuoi
void swapStrings(char str1[], char str2[]){
    char temp[50];
    strcpy(temp, str1);
    strcpy(str1, str2);
    strcpy(str2, temp);
}

//Ham hoan doi so nguyen
void swapIntegers(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//Ham hoan doi kiem double
void swapDouble(double *a, double *b){
    double temp = *a;
    *a = *b;
    *b = temp;
}

// Doc file cua cac so roi gan vao cac mang
void readFile(char *filename, char ten[][30], char nxb[][50], char tgia[][50], int *sluong, double *gia, int *pn){
	*pn = 0;
	FILE* f = fopen(filename, "r");
	if (f != NULL){
		while(fscanf(f," %29[^;];%49[^;];%49[^;];%d%*c%lf", ten[*pn], nxb[*pn], tgia[*pn], &sluong[*pn], &gia[*pn]) == 5){
			(*pn)++;
		}
		fclose(f);
	}
}

//In mang vao file
void writeFileB(char *filename, char ten[][30], char nxb[][50], char tgia[][50], int *sluong, double *gia, int n){
	FILE* f = fopen(filename, "wb");
	int i;
	for (i = 0; i < n; i++){
		fprintf(f,"%s;%s;%s;%d;%.0lf\n", ten[i], nxb[i], tgia[i], sluong[i], gia[i]);
	}
	fclose(f);
}

// Ham in mang sau khi da doc file 
void inbang(char ten[][30], char nxb[][50], char tgia[][50], int *sluong, double *gia, int n) {
    int i;

    printf("\t\t\t\t\t   DANH SACH CAC LOAI SACH HIEN TAI\n");
    printf("---------------------------------------------------------------------------------------------------------------------------\n");
    printf("|%-6s|%-30s|%-30s|%-30s|%-8s|%-12s|\n", "STT", "Ten sach", "NXB", "Tac gia", "So luong", "Gia");
    printf("|------|------------------------------|------------------------------|------------------------------|--------|------------|\n");

    for (i = 0; i < n; i++){
       printf("|%-6d|%-30s|%-30s|%-30s|%-8d|%-12.0lf|\n", i + 1, ten[i], nxb[i], tgia[i], sluong[i], gia[i]);
    }

    printf("---------------------------------------------------------------------------------------------------------------------------\n");
}

//Ham them thong tin vao cac mang
void them(char ten[][30], char nxb[][50], char tgia[][50], int sluong[], double gia[], int n){
    char tens[30], nxbs[50], tgias[50];
	int sluongs;
	double gias;
	
	printf("\n--Nhap thong tin cua sach--\n");
	printf("Ten sach: ");
	scanf(" %[^\n]", tens);
	while(getchar()!='\n'); 
	
	printf("Nha xuat ban: ");
	scanf(" %[^\n]", nxbs);
	while(getchar()!='\n'); 
	
	printf("Tac gia: ");
	scanf(" %[^\n]", tgias);
	while(getchar()!='\n'); 
	
	printf("So luong: ");
	scanf("%d", &sluongs);
	
	printf("Gia tien(VND): ");
	scanf("%lf", &gias);
	
	nameStr(tgias);
	nameStr(nxbs);
	strupr(tens);
	
	strcpy(ten[n-1], tens);
	strcpy(nxb[n-1], nxbs);
	strcpy(tgia[n-1], tgias);
	sluong[n-1] = sluongs;
	gia[n-1] = gias;
}

// Ham delete mot thong tin nhat dinh
void xoamotstt(char ten[][30], char nxb[][50], char tgia[][50], int sluong[], double gia[], int n, int *pn){
	int i,j;
	int rstt;
	
	printf("Nhap STT cua loai sach can xoa:");
	scanf("%d",&rstt);
	
	if(rstt<=0||rstt>*pn){
		printf("STT nhap vao khong ton tai trong danh sach\n");
	}else{
		for(i = rstt-1; i < n; i++){
        swapStrings(ten[i], ten[i+1]);
        swapStrings(nxb[i], nxb[i+1]);
        swapStrings(tgia[i], tgia[i+1]);
        swapIntegers(&sluong[i], &sluong[i+1]);
        swapDouble(&gia[i], &gia[i+1]);
		}
		printf("Xoa thanh cong!!!\n");
		(*pn)--;
	}
}

// Ham sua doi mot so thong tin cua danh sach
void suadoi(char ten[][30], char nxb[][50], char tgia[][50], int sluong[], double gia[], int n){
	int i;
	int sdoi;
	char nxbs[50];
	int sluongs;
	double gias;
	
	
	printf("Nhap STT cua loai sach can sua doi: ");
	scanf("%d",&sdoi);
	printf("\n");
	
	if(sdoi<0||sdoi>=n){
		printf("STT nhap vao khong ton tai trong danh sach\n");
	}else{		
		printf("Thong tin truoc khi chinh sua cua %s - %s:\n", ten[sdoi-1], tgia[sdoi-1] );
		printf("NXB: %s\n",nxb[sdoi-1]);
		printf("So luong: %d\n",sluong[sdoi-1]);
		printf("Gia: %.0lf\n",gia[sdoi-1]);
		
		//chi sua doi nxb,sluong va gia vi neu doi ten sach va tgia thi do la mot sach moi, thi khi do ta chi can them tt sach do vao thoi
		printf("\nNhap thong tin cua sach moi cho loai sach nay\n");
		printf("Nha xuat ban: ");
		scanf(" %[^\n]", nxbs);
		while(getchar()!='\n');  
	
		printf("So luong: ");
		scanf("%d", &sluongs);
	
		printf("Gia tien(VND): ");
		scanf("%lf", &gias);
	
		nameStr(nxbs);
		
		strcpy(nxb[sdoi-1],nxbs);
		sluong[sdoi-1]=sluongs;
		gia[sdoi-1]=gias;
		printf("Sua doi thanh cong!!!\n");
	}	
}

int main(){
	int choice;
	char filename[]="mauquanly.txt";
	char ten[200][30];
	char nxb[200][50];
	char tgia[200][50];
	int sluong[200];
	double gia[200];
	int n=0;
	
	do {
		readFile(filename, ten, nxb, tgia, sluong, gia, &n);
		choice = getchoice();
        switch (choice){
            case 1:
            	if (isFull(ten, n)) {
                    printf("Tep tin da day. Khong the them thong tin!!!\n");
                    printf("\n");
                } else {
                	n++;
               		them(ten, nxb, tgia, sluong, gia, n);
               		printf("Them thong tin thanh cong!!!\n");
                	printf("\n");
                	writeFileB(filename, ten, nxb, tgia, sluong, gia, n);
                }
                break;
            
			case 2:
            	if (empty(ten, n)) {
                    printf("Tep tin chua co phan tu. Hay them thong tin sach truoc\n");
                } else {
                	inbang(ten, nxb, tgia, sluong,gia, n);
                	printf("\n");
           		}
                break;
            
			case 3:
            	if (empty(ten, n)) {
                    printf("Tep tin chua co phan tu. Hay them thong tin sach truoc\n");
                } else {
                    inbang(ten, nxb, tgia, sluong, gia, n);
                	xoamotstt(ten, nxb, tgia, sluong,gia, n, &n);
                	writeFileB(filename, ten, nxb, tgia, sluong, gia, n);
                	printf("\n");
                }
                break;
            
			case 4:
            	if (empty(ten, n)) {
                    printf("Tep tin chua co phan tu. Hay them thong tin sach truoc\n");
                }else{
	                inbang(ten, nxb, tgia, sluong,gia, n);
	                suadoi(ten, nxb, tgia, sluong, gia, n);
	                writeFileB(filename, ten, nxb, tgia, sluong, gia, n);
	                printf("\n");
	            }
                break;
            
			case 5:
            	printf("Hen gap lai!!!");
            	break;
            default:
                printf("Gia tri khong hop le. Hay nhap lai!!!\n");
                break;
    	}
    }while(choice!= 5);
    return 0;
}



