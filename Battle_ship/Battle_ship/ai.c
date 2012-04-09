#include "bs.h"
int comp_shot(Ship_control *player_ships, char board[ROWS][COLS], int *shot_row, int *shot_col, FILE * log)
{
	int check = 0;
	char shot;
	do
	{
		*shot_row = rand() % 10;
		*shot_col = rand() % 10;
		
		shot = board[*shot_row][*shot_col];

	}while(shot == 'H' || shot == '*');
	print_board(board, ROWS, COLS, 1);



	if(shot == '~')
	{
		system("cls");
		board[*shot_row][*shot_col] = '*';
		print_board(board, ROWS, COLS, 1);
		*shot_row = *shot_row + 1;
		*shot_col = *shot_col + 1;
		fprintf(log,"comp miss at %d  %d\n", *shot_row, *shot_col);
		printf("miss at %d  %d\n", *shot_row, *shot_col);
		check = -1;
	}
	else
	{
		if(shot == 'C')
		{
			player_ships->cruiser = player_ships->cruiser - 1;
		}
		else if(shot == 'B')
		{
			player_ships->battle_ship = player_ships->battle_ship - 1;
		}
		else if(shot == 'R')
		{
			player_ships->destroyer = player_ships->destroyer - 1;
		}
		else if(shot == 'S')
		{
			player_ships->submarine = player_ships->submarine - 1;
		}
		else if(shot == 'D')
		{
			player_ships->patrol_boat = player_ships->patrol_boat - 1;
		}

		board[*shot_row][*shot_col] = 'H';
		system("cls");
		print_board(board, ROWS, COLS, 1);
		*shot_row = *shot_row + 1;
		*shot_col = *shot_col + 1;
		fprintf(log,"comp hit's at %d  %d\n", *shot_row, *shot_col);
		printf("hit at %d  %d\n", *shot_row, *shot_col);
		check = 1;
	}

	*shot_row = *shot_row - 1;
	*shot_col = *shot_col - 1;
	system ("pause");

	return check;
}