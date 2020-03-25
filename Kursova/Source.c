#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include<windows.h>
#include <time.h>

#pragma warning(disable : 4996)

int Playing_Field[40][60];
#define LEFT 65 97


struct Coordinates {
	int x;
	int y;
	struct Coordinates* Next;
	struct Coordinates* p;
	struct Coordinates* Current_Position;
	struct Coordinates* Previous;
	struct Coordinates* Tail;
	struct Coordinates* p_Tail;
	
};



struct Coordinates* Head = NULL;


struct Coordinates Area;
struct Coordinates Food;
struct Coordinates Body;
struct Coordinates Previous_Position;


void Scan_Field();
void Field_Draw();
int Worm( int *KBhit, char *C);
void Food_Spawn();
void Linked_List_Create();
void Linked_List_Movement();
int Case_Change(int Change_Char);


int RightSize = 60;
int DownSize = 40;

int EndOfGame = 0;
int Is_There_Food = 0;

int Start_Of_Game = 1;
int Starting_Position = 1;




char c = 0;
int Gamewon = 0;
int FOOD_COUNT = 0;

int main() {
	int Key;	
	
	printf("Press Enter To start");
	Start_Of_Game = 1;
	Head = (struct Coordinates*)malloc(sizeof(struct Coordinates));
	Head->Next = NULL;
	Head->Previous = NULL;
	Head->x = 30;
	Head->y = 20;
	

	Area.x = 60;
	Area.y=40;
	

	
	
	
	srand(time(NULL));
	
	if(getchar() == 10) {
		
		

		while (EndOfGame == 0) {

			Scan_Field();//Zapisva vuv masiva poleto.+		Head	{x=0 y=0 }	Coordinates
			

			EndOfGame=Worm(&Key, &c);//Zadava vuv masiva tochkite na cherveq.
			if (FOOD_COUNT == 2204) {
				return("Congratulation, you WON!!!");
			}
			Food_Spawn();

			Field_Draw();//Izprintva poleto.
		
			_sleep(100);

			system("cls");
			
			
		}
		printf("Sorry, try again : :)");
	}

}


void Scan_Field() {
	for (int Down = 0; Down < Area.y; Down++) {
		for (int Right = 0; Right < Area.x; Right++) {
			if (Down == 0) {
				Playing_Field[Down][Right] = '+';
			}
			else if (Down == (Area.y - 1)) {//Сканира предпоследен ред.
				Playing_Field[Down][Right] = '+';
			}
			else if (Down != 0 && Down != (Area.y - 1)) {//Между 1ви и последен ред.
				if (Right == 0 || Right == (Area.x - 1)) {
					Playing_Field[Down][Right] = '+';
				}
				Playing_Field[Down][Right + 1] = ' ';// Сканира празните полета. GRESHAKA IZLIZA TUK PRI DOWN= 38, RIGHT =58.
			}
		}
	}
}

void Field_Draw() {
	for (int Nadolu = 0; Nadolu < DownSize; Nadolu++) {
		for (int Nadqsno = 0; Nadqsno < RightSize; Nadqsno++) {
			printf("%c", Playing_Field[Nadolu][Nadqsno]);
		}
		printf("\n");
	}
}

int Worm( int *KBhit, char *C)
{
	
	
	int CurrentKeyPress;
	*KBhit = kbhit();

	int next_X;
	int next_Y;

	if (KBhit!= 0)

	{
		if (CurrentKeyPress = kbhit() != 0) { // Promqna
			int Key_Check = getch();
			Key_Check = Case_Change(Key_Check);
			
			if ((Key_Check == 65)||( Key_Check == 68 )||( Key_Check == 83) || (Key_Check == 87) ||( Key_Check == 97) ) {
				*C = Key_Check;
				
			}
			
		}
		if (*C != NULL){
			
			switch (*C)
			{
			case 'A':
				
				if (Playing_Field[Head->y][Head->x] == '+') {
					return 1;
				}
				else if ((Head->x == Food.x) && (Head->y == Food.y)) {
					Linked_List_Create();
					Playing_Field[Head->y][Head->x] = " ";
					FOOD_COUNT++;

					Linked_List_Movement();
					(Head->x)--;
					if (Playing_Field[Head->y][Head->x] == '*') {
						return 1;
					}

					Playing_Field[Head->y][Head->x] = '*';
					Is_There_Food = 0;
				}

				next_X = Head->x;
				--next_X;
				if (Playing_Field[Head->y][next_X] == '*') {
					return 1;
				}
				else{
					Linked_List_Movement();
					(Head->x)--;
					if (Head->Next == NULL) {
						break;
					}
					else {
						Playing_Field[Head->y][Head->x] = '*';
					}
			    }
				
				
				break;
			case'S':
				
				if (Playing_Field[Head->y][Head->x] == '+') {
					return 1;
				}
				else if ((Head->x == Food.x) && (Head->y == Food.y)) {
					Linked_List_Create();
					Playing_Field[Head->y][Head->x] = " ";
					FOOD_COUNT++;
					Linked_List_Movement();
					(Head->y)++;
					if (Playing_Field[Head->y][Head->x] == '*') {
						return 1;
					}
					Playing_Field[Head->y][Head->x] = '*';
					Is_There_Food = 0;

					next_Y = Head->y;
					++next_Y;
					if (Playing_Field[next_Y][Head->x] == '*') {
						return 1;
					}
				}
				
				else {
					Linked_List_Movement();
					(Head->y)++;
					if (Head->Next == NULL) {
						break;
					}
					else {
						Playing_Field[Head->y][Head->x] = '*';
					}
					next_Y = Head->y;
					++next_Y;
					if (Playing_Field[next_Y][Head->x] == '*') {
						return 1;
					}
				}
				
				break;
			case'W':
				
				if (Playing_Field[Head->y][Head->x] == '+') {
					return 1;
				}
				else if ((Head->x == Food.x) && (Head->y == Food.y)) {
					Linked_List_Create();
					Playing_Field[Head->y][Head->x] = ' ';
					FOOD_COUNT++;
					Linked_List_Movement();
					(Head->y)--;
					if (Playing_Field[Head->y][Head->x] == '*') {
						return 1;
					}

					Playing_Field[Head->y][Head->x] = '*';
					Is_There_Food = 0;

					next_Y = Head->y;
					--next_Y;
					if (Playing_Field[next_Y][Head->x] == '*') {
						return 1;
					}
				}
				else {
					Linked_List_Movement();
					(Head->y)--;
					if (Head->Next == NULL) {
						break;
					}
					else {
						Playing_Field[Head->y][Head->x] = '*';
					}

					next_Y = Head->y;
					--next_Y;
					if (Playing_Field[next_Y][Head->x] == '*') {
						return 1;
					}
				}
				break;
			case'D':
				
				if (Playing_Field[Head->y][Head->x] == '+') {
					return 1;
				}
				else if ((Head->x ==Food.x)&&(Head->y ==Food.y)) {
					Linked_List_Create();
					FOOD_COUNT++;

					Playing_Field[Head->y][Head->x] = " ";

					Linked_List_Movement();
					(Head->x)++;
					if (Playing_Field[Head->y][Head->x] == '*') {
						return 1;
					}
					
					Playing_Field[Head->y][Head->x] = '*';
					Is_There_Food = 0;
				}

				next_X = Head->x;
				++next_X;

				if (Playing_Field[Head->y][next_X] == '*') {
					return 1;
				}
				else {
					Linked_List_Movement();
					(Head->x)++;
					if (Head->Next == NULL) {
						break;
					}
					else {
						Playing_Field[Head->y][Head->x] = '*';
					}

					next_X = Head->x;
					++next_X;
					if (Playing_Field[Head->y][next_X] == '*') {
						return 1;
					}
				}
			default:
				Playing_Field[Head->y][Head->x] = '*';
				break;
			}
		}else {
			Playing_Field[Head->y][Head->x] = '*';

		}
	}
	return 0;
}

void Food_Spawn()
{
	if (Is_There_Food == 0) {
		Food.x = (rand() % 60);
		Food.y = (rand() % 40);

		Is_There_Food = 1;

		if ((Playing_Field[Food.y][Food.x] == '+') || (Playing_Field[Food.y][Food.x] == '*')) {
			while ((Playing_Field[Food.y][Food.x] == '+') || (Playing_Field[Food.y][Food.x] == '*')) {
				Food.x = (rand() % 60);
				Food.y = (rand() % 40);
			}
			
		}
	}
	Playing_Field[Food.y][Food.x] = 'O';
}

void Linked_List_Create()

{
	
	struct Coordinates* temp =(struct Coordinates*)malloc(sizeof(struct Coordinates));//Zadelq se pamet
	if (temp == NULL) {
		printf("Error!!");

	}
	if (Head->Next == NULL) {//Suzdavane na 2ri element v spisuka.
		Head->Next = temp;
		temp->Previous = Head;
		temp->Next = NULL;
		Head->p = temp;
		Head->Tail = temp;
	}
	else {
		int *temp_P = Head->p;
		Head->p->Next = temp;
		temp->Next=NULL;
		Head->p = temp;
		Head->Tail = temp;
		Head->p->Previous = temp_P;
	}
}

void Linked_List_Movement()
{
	Head->p_Tail = Head->Tail;
	if (Head->Next == NULL) {
		Playing_Field[Head->y][Head->x] = '*';
	}
	else {
		while (Head->p_Tail->Previous != NULL) {
			Head->p_Tail->x = Head->p_Tail->Previous->x;
			Head->p_Tail->y = Head->p_Tail->Previous->y;

			Playing_Field[Head->p_Tail->y][Head->p_Tail->x] = '*';

			Head->p_Tail = Head->p_Tail->Previous;
		
		}
	}
}

int Case_Change(int Change_Char)
{
	if (Change_Char >= 97 && Change_Char <= 122) {
		Change_Char -= 32;
	}
	return Change_Char;
}
