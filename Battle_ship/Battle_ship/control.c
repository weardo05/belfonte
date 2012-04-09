#include "bs.h"

void initialize_game_board(char board[ROWS][COLS], int num_rows, int num_cols)
{
	int row_index = 0, col_index = 0;

	for (row_index = 0; row_index < num_rows; row_index++)
	{
		for (col_index = 0; col_index < num_cols; col_index++)
		{
			board[row_index][col_index] = '~';
		}
	}
}
void print_board(char board[ROWS][COLS], int num_rows, int num_cols, int p_c)
{
	int row_index = 0, col_index = 0, a = 0, b = 0;
	char shot = 0;


	printf("\n\n\n\t   ");
	a++;
	b++;

	for (col_index = 0; col_index < num_cols; col_index++)
	{
		printf("%d  ",b);
		b++;
	}
	
	putchar('\n');

	for (row_index = 0; row_index < num_rows; row_index++)
	{
		putchar ('\t');
		printf("%d ",a);
		if (a != 10)
		{putchar(' ');}
		for (col_index = 0; col_index < num_cols; col_index++)
		{
			if(p_c == 1)
			{
				printf ("%c  ", board[row_index][col_index]);
			}
			else
			{
				shot = board[row_index][col_index];

				if(shot == '*' || shot == 'H')
				{
					printf ("%c  ", board[row_index][col_index]);
					
				}
				else
				{
					printf ("~  ");
				}
			}
		}
		a++;
		putchar ('\n');
		
	}
}
int intitalize_game(char player_board[ROWS][COLS], char comp_board[ROWS][COLS])
{	
	int player= 0, board = 0, len = 0;
	char random = '\0', type = '\0';

	player = select_who_starts_first();
	
	initialize_game_board(player_board, ROWS, COLS);
	initialize_game_board(comp_board, ROWS, COLS);

	printf("\nenter r to randomly place your ships");
	scanf(" %c",&random);

	type ='C';
	len = 5;
	make_ships(player_board, random, len, type);
	make_ships(comp_board, 'r', len, type);

	type ='B';
	len = 4;
	make_ships(player_board, random, len, type);
	make_ships(comp_board, 'r', len, type);

	type ='R';
	len = 3;
	make_ships(player_board, random, len, type);
	make_ships(comp_board, 'r', len, type);

	type ='S';
	len = 3;
	make_ships(player_board, random, len, type);
	make_ships(comp_board, 'r', len, type);

	type ='D';
	len = 2;
	make_ships(player_board, random, len, type);
	make_ships(comp_board, 'r', len, type);

	return player;
}
int select_who_starts_first(void)
{ int a; a = rand() % 2; return a; }
void make_ships(char board[ROWS][COLS], char random, int len, char type)
{
	int direction = 0, a = 0, row = 0, col = 0,check = 0;
	char type_check;

	system("cls");
	check = 1;
	while(check == 1)
		{
		if (random == 'r')
		{
			generate_direction (&direction);
			generate_start_pt (&row,&col,len,direction);
		}
		else
		{
			print_board(board, ROWS, COLS, 1);
			printf("please enter a start point for your ship");
			printf("\nenter a row");
			scanf("%d", &row);
			printf("\nenter a collum");
			scanf("%d", &col);
			printf("\nenter a direction\"1 for vertical 0 for horizontal\"");
			scanf("%d", &direction);
			row--;
			col--;
		}

		check = 0;
		if (direction == 1)
		{
			a = row;
			do
			{
				type_check = board[a][col];
				if(type_check != '~')
				{check = 1;}
				a++;
			}while(a < (len + row));
		}
		else
		{ 
			a = col;
			do
			{
				type_check = board[row][a];
				if(type_check != '~')
				{check = 1;}
				a++;
			}while(a < (len + col));
		}

		if(check == 0)
		{
			if (direction == 1)
			{
				a = row;
				do
				{
					board[a][col] = type;
					a++;
				}while(a < (len + row));
			}
			else
			{ 
				a = col;
				do
				{board[row][a] = type;
					a++;
				}while(a < (len + col));
			}
		}
	}
}