#include <stdio.h> //standar input output
#include <time.h> // library untuk time, karena digunakan di srand(time(NULL))
#include <stdlib.h> //untuk system cls, system pause, srand, rand
#include <string.h> //karena menggunakan strcpy
#include <unistd.h> //untuk fungsi sleep()

void generateWord(char *wordRandom);
void saveShow(char (*kataRandom)[6]);
void game();
void createTable(char (*string)[6], int dummy);
void gotoxy(int x, int y);
void winner();
void search();
struct player{
	int score;
	char nama[50];
};
int main(){
	int menu;
	char kataRandom[17][6], wordRandom[6];
	memset(kataRandom,0,sizeof(kataRandom));
	do{
		system("@cls||clear");
		printf("\t\t\t M   A   I   N		M   E   N   U\n");
		printf("\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n\n\n");
		printf("1. Generate Word\n");
		printf("2. Save and Show Generate Word\n");
		printf("3. Start Game\n");
		printf("4. Show The Winner\n");
		printf("0. Exit\n");
		printf("\n\nEnter Your choice : ");
		scanf("%d", &menu);
		
		switch(menu){
			case 1:
				menu = 10;
				memset(kataRandom,0,sizeof(kataRandom));
				for (int i = 0; i<16; i++){
					generateWord(wordRandom);
					strcpy(kataRandom[i],wordRandom);
				}
				printf("\n\t\tThe Word Has Been Generated Successfully!\n\n");
			break;
			case 2:
				menu = 10;
				saveShow(kataRandom);
				memset(kataRandom,0,sizeof(kataRandom));
			break;
			case 3:
				menu = 10;
				game();
			break;
			case 4:
				menu = 10;
				winner();
			break;
		}
		printf("Enter anything to continue : ");
		scanf("%*s");
		printf("\n\n");
	}while(menu!=0);
}
void generateWord(char *wordRandom){
	static int seed = 0;
	srand((unsigned int)(time(NULL))+seed);
	seed++;
	char *word = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";	
	for(int j=0; j<5; j++){
		int angkaRandom = rand()%52;
		wordRandom[j] = word[angkaRandom];
	}
}
void saveShow(char (*kataRandom)[6]){
	if (kataRandom[0][0] == 0){
		printf("Error saving, generate the word first!!\n");
	}
	else{
		FILE *data = fopen("data.txt", "w+");
		for (int i = 0; i<16; i++){
			fprintf(data, "%s\n", kataRandom[i]);
			printf("%s ", kataRandom[i]);
		}
		printf("\nData saved succesfully :)\n");
		fclose(data);
	}
}
void gotoxy(int x, int y){
	printf("\033[%d;%df",y,x);
}
void createTable(char (*string)[6], int dummy){
	system("@cls||clear");
	printf("+-------+-------+-------+-------+\n");
	printf("|       |       |       |       |\n");
	printf("+-------+-------+-------+-------+\n");
	printf("|       |       |       |       |\n");
	printf("+-------+-------+-------+-------+\n");
	printf("|       |       |       |       |\n");
	printf("+-------+-------+-------+-------+\n");
	printf("|       |       |       |       |\n");
	printf("+-------+-------+-------+-------+\n");
	int counter = 0;
	for (int i = 2; i<=8; i+=2){
		for (int j = 2+dummy; j<=26+dummy; j+=8){
			gotoxy(j,i);
			printf("%s", string[counter]);
			counter++;
		}
	}

}
void game(){
	FILE *data = fopen("data.txt", "r");
	char kataRandom[16][6];
	if (data == NULL){
		printf("Error reading file\n");
		scanf("%*s");
		return;
	}
	else {
		for (int i = 0; i<16; i++){
			fscanf(data, "%s\n", kataRandom[i]);
		}
	}
	fclose(data);
	struct player human;
	struct player computer;
	human.score = 0; 
	computer.score = 0;
	createTable(kataRandom,1);
	char temp;
	gotoxy(1,10);
	printf("Apakah anda sudah siap bermain [Y\\N]? ");
	while (temp != 'Y'){
		scanf(" %c", &temp);
		if (temp == 'N'){
			return;
		}
	}
	if (temp == 'Y'){
		system("@cls||clear");
		printf("Masuukan nama : ");
		scanf(" %[^\n]", &human.nama);
		char number[16][6];
		memset(number,0,sizeof(number));
		for (int i = 0; i<16; i++){
			number[i][0] = i+49;
			if (i>8){
				number[i][0] = 49;
				number[i][1] = i+39;
			}
		}
		int soalRandom;
		static int seed = 435456;
		srand((unsigned int)(time(NULL))+seed);
		seed++;
		int counter = 0;
		int sudahDikunjungi[16];
		for (int i = 0; i<16; i++){
			system("@cls||clear");
			createTable(number,1);
			soalRandom = rand()%16;
			while(sudahDikunjungi[soalRandom] == 1){
				soalRandom = rand()%16;
			}
			sudahDikunjungi[soalRandom] = 1;
			if (counter == 0){
				gotoxy(1,10);
				printf("Game dimulai...\n");
			}
			gotoxy(1,10);
			printf("Dimanakah tulisan %s berada?\n\n", kataRandom[soalRandom]);
			printf("Giliran %s menebak kotak : ", human.nama);
			int jawaban, sudahDijawab[16];
			scanf("%d", &jawaban);
			if (jawaban == soalRandom+1){
				printf("\033[0;32m Correct answer [V]\033[0m (+10 poin)\n");
				sudahDijawab[soalRandom] = 1;
				human.score += 10;
				counter++;
				strcpy(number[soalRandom],kataRandom[soalRandom]);
				printf("Enter anything to continue : ");
				scanf(" %*s");
			}
			else{
				static int seedComputer = 12312343;
				srand((unsigned int)(time(NULL))+seed);
				seed++;
				int jawabKomp = rand()%16;
				while (jawabKomp+1 == jawaban|| sudahDijawab[jawabKomp] == 1){
					jawabKomp = rand()%16;
				}
				printf("\033[0;31mYour answer is wrong [x]\033[0m\n");
				printf("                                 ");
				sleep(1);
				gotoxy(1,12);
				printf("[...]Gilaran Kompie untuk menjawab\n");
				printf("                                        ");
				sleep(1);
				gotoxy(1,13);
				printf("[...]Kompie menjawab %d\n", jawabKomp+1);
				sleep(1);
				if (jawabKomp == soalRandom){
					printf("\033[0;32mCorrect Answer [V]\033[0m\n");
					sudahDijawab[soalRandom] = 1;
					sleep(1);
					strcpy(number[soalRandom],kataRandom[soalRandom]);
					computer.score += 10;
					printf("Input anything to continue : ");
					scanf(" %*s");
				}
				else {
					printf("\033[0;31mWrong answer [x]\033[0m\n");
					sleep(1);
					printf("input anything to continue : ");
					scanf(" %*s");
				}
				counter++;
			}
		}
		printf("Game Selesai!!\n");
		printf("Simpan Hasil permainan [Y\\N] ? ");
		int dum;
		while (dum != 'Y'){
			scanf("%c", &dum);
			if (dum == 'N'){
				return;
			}
		}
		if (dum == 'Y'){
			FILE *data = fopen("score.txt", "a");
			fprintf(data, "%s=%d||Kompie=%d\n", human.nama,human.score,computer.score);
			fclose(data);
			printf("File berhasil disimpan!!\n");
		}
	}

}
void bubbleSort(int count, struct player *winner){
	for (int i = 0; i<count; i++){
		for (int j = i+1; j<count; j++){
			if (winner[j].score >= winner[i].score){
				struct player temp = winner[j];
				winner[j] = winner[i];
				winner[i] = temp;
			}
		}
	}
}
void winner(){
	system("@cls||clear");
	struct player winner[100];
	int count = 0;
	char playername[100];
	int player, kompie;
	printf("Name         ||       Score  \n");
	printf("==============================\n");
	FILE *data = fopen("score.txt", "r");
	if (data == NULL){
		printf("Error membaca score.txt\n");
		sleep(1);
		return;
	}
	while (!feof(data)){
		fscanf(data, "%[^'=']=%d||%*[^'=']=%d\n",playername,&player,&kompie);
		if (player > kompie){
			winner[count].score = player;
			strcpy(winner[count].nama,playername);
		}
		else if (player < kompie){
			winner[count].score = kompie;
			strcpy(winner[count].nama,"Kompie");
		}
		else {
			winner[count].score = kompie;
			strcpy(winner[count].nama,playername);
			strcat(winner[count].nama,"&Kompie");
		}
		count++;
	}
	for (int i = 0; i<count; i++){
		printf("             ||           \n");
	}

	bubbleSort(count,winner);
	for (int i = 0; i<count; i++){
		gotoxy(1,3+i);
		printf("%s", winner[i].nama);
		gotoxy(19,3+i);
		printf("%d", winner[i].score);
	}
	gotoxy(1,count+4);
	printf("Looking for someone ? [Y\\N] ");
	char dump;
	while (dump != 'Y'){
		scanf("%c", &dump);
		if (dump == 'N'){
			printf("\n");
			return;
		}
	}
	if (dump == 'Y'){
		printf("Enter the name of someone you're looking for (case sensitive): ");
		char nameDump[50];
		memset(nameDump,0,sizeof(nameDump));
		scanf(" %[^\n]", nameDump);
		int def = 0;
		for (int i = 0; i<count; i++){
			if (strcmp(nameDump,winner[i].nama) == 0){
				printf("%s : %d\n", winner[i].nama, winner[i].score);
				def++;
			}
			if (i == count-1 && strcmp(nameDump,winner[i].nama) != 0 && def == 0){
				printf("Sorry, i cant find the person you're looking for!!\n");
			}
		}
	}
	fclose(data);
}

