#include "bs.h"


void open_menu(void)
{
	welcome_screen();
	game_control();
	//high_score();

}
void welcome_screen(void)
{

	printf("welcome\n");
	printf("rules\n");

	system ("pause");
}
Stats update_stats (Stats player_stats, int hit_miss)
{
	(player_stats.total_num_shots)++;

	if(hit_miss == 1)
	{
		(player_stats.num_hits)++;
	}

	player_stats.num_misses = (player_stats.total_num_shots) - (player_stats.num_hits);
	if((player_stats.num_misses) >= 1)
	{
	player_stats.hits_misses_ratio = (((double)(player_stats.num_hits)) / ((double)(player_stats.num_misses)));
	}

	return player_stats;
}
Ship_control check_ship(Ship_control ships, FILE * log)
{
	if(ships.cruiser <= 0)
	{
		if(ships.cruiser_life == 'f')
		{
			fprintf(log,"the cruiser has been sunk\n");
			printf("the cruiser has been sunk\n");
			ships.cruiser_life = 's';
			system("pause");
		}
	}
	
	if(ships.battle_ship <= 0)
	{
		if(ships.battle_ship_life == 'f')
		{
			fprintf(log,"the battle ship has been sunk\n");
			printf("the battle ship has been sunk\n");
			ships.battle_ship_life = 's';
			system("pause");
		}
	}

	if(ships.submarine <= 0)
	{
		if(ships.submarine_life == 'f')
		{
			fprintf(log,"the submarine has been sunk\n");
			printf("the submarine has been sunk\n");
			ships.submarine_life = 's';
			system("pause");
		}
	}

	if(ships.destroyer <= 0)
	{
		if(ships.destroyer_life == 'f')
		{
			fprintf(log,"the destroyer has been sunk\n");
			printf("the destroyer has been sunk\n");
			ships.destroyer_life = 's';
			system("pause");
		}
	}
	
	if(ships.patrol_boat <= 0)
	{
		if(ships.patrol_boat_life == 'f')
		{
			fprintf(log,"the patrol boat has been sunk\n");
			printf("the patrol boat has been sunk\n");
			ships.patrol_boat_life = 's';
			system("pause");
		}
	}

	return ships;
}
void game_control(void)
{
	int end_game = 0, player_check = 0, hit_miss = 0, shot_row = 0, shot_col = 0;
	char player_board[ROWS][COLS], comp_board[ROWS][COLS];
	char name[25];
	Stats player_stats = {"name", 0, 0, 0.0}, comp_stats = {"computer", 0, 0, 0.0};
	Ship_control player_ships = {5, 'f', 4, 'f', 3, 'f', 3, 'f', 2, 'f'}, comp_ships = {5, 'f', 4, 'f', 3, 'f', 3, 'f', 2, 'f'};
	FILE * log = fopen ("log.txt", "w");


	printf("please enter your name");
	scanf("%s", name);
	strcpy (player_stats.player_name, name);

	player_check =  intitalize_game(player_board,comp_board); 
	
	print_board(player_board, ROWS, COLS, 1);
	printf("this is your board %s\n",player_stats.player_name);
	
	system ("pause");

	if (player_check = 0)
	{
		printf("the computer will go first\n");
		hit_miss = comp_shot(&player_ships, player_board, &shot_row, &shot_col, log);
		comp_ships = check_ship(player_ships, log);
		comp_stats = update_stats(comp_stats, hit_miss);
	}
	else
	{printf("you will go first\n");}

	while(end_game == 0)
	{
		hit_miss = take_shot(comp_board, &shot_row, &shot_col, &comp_ships, log);
		player_ships = check_ship(comp_ships, log);
		player_stats = update_stats(player_stats, hit_miss);

		hit_miss = comp_shot(&player_ships, player_board, &shot_row, &shot_col, log);
		//search = hit_miss;
		comp_ships = check_ship(player_ships, log);
		comp_stats = update_stats(comp_stats, hit_miss);
		end_game = check_winner(player_ships,  comp_ships, log);
	}
	fprintf(log,"%s stats\nhits %d \nmisses %d \ntotal shots %d \nshot_ratio %d\n", player_stats.player_name,
		player_stats.num_hits, player_stats.num_misses, player_stats.total_num_shots, player_stats.hits_misses_ratio);

	fclose(log);
}
int check_winner(Ship_control player_ships, Ship_control comp_ships, FILE * log)
{
	int end_game = 0;

		if(player_ships.cruiser_life == 's' && player_ships.battle_ship_life == 's' &&player_ships.submarine_life == 's' &&
			player_ships.destroyer_life == 's' && player_ships.patrol_boat_life == 's')
		{			
			system("cls");
			fprintf(log,"comp won");
			printf("YOU LOST");
			end_game = -1;
		}

		if(comp_ships.cruiser_life == 's' && comp_ships.battle_ship_life == 's' &&comp_ships.submarine_life == 's' &&
			comp_ships.destroyer_life == 's' &&	comp_ships.patrol_boat_life == 's')
		{
			system("cls");
			fprintf(log,"player won");
			printf("YOU WON");
			end_game = 1;
		}

	return end_game;
}
int take_shot(char board[ROWS][COLS], int *shot_row, int *shot_col, Ship_control *comp_ships, FILE * log)
{
	int check = 0;
	char shot;
	do
	{
		system("cls");
		print_board(board, ROWS, COLS, TEST);
		printf("\nenter a row");
		scanf("%d", shot_row);
		printf("\nenter a collum");
		scanf("%d", shot_col);

		*shot_row = *shot_row - 1;
		*shot_col = *shot_col - 1;
		shot = board[(*shot_row)][(*shot_col)];
	}while(shot == 'H' || shot == '*');

	if(shot == '~')
	{
		system("cls");
		board[*shot_row][*shot_col] = '*';
		print_board(board, ROWS, COLS, TEST);
		*shot_row = *shot_row + 1;
		*shot_col = *shot_col + 1;
		fprintf(log,"you miss at %d  %d\n", *shot_row, *shot_col);
		printf("miss at %d  %d\n", *shot_row, *shot_col);
		check = -1;
	}
	else
	{
		if(shot == 'C')
		{
			comp_ships->cruiser = comp_ships->cruiser - 1;
		}
		else if(shot == 'B')
		{
			comp_ships->battle_ship = comp_ships->battle_ship - 1;
		}
		else if(shot == 'R')
		{
			comp_ships->destroyer = comp_ships->destroyer - 1;
		}
		else if(shot == 'S')
		{
			comp_ships->submarine = comp_ships->submarine - 1;
		}
		else if(shot == 'D')
		{
			comp_ships->patrol_boat = comp_ships->patrol_boat - 1;
		}

		board[*shot_row][*shot_col] = 'H';
		system("cls");
		print_board(board, ROWS, COLS, TEST);
		*shot_row = *shot_row + 1;
		*shot_col = *shot_col + 1;
		fprintf(log,"player hit's at %d  %d\n", *shot_row, *shot_col);
		printf("hit at %d  %d\n", *shot_row, *shot_col);
		check = 1;
	}
	*shot_row = *shot_row - 1;
	*shot_col = *shot_col - 1;
	system ("pause");

	return check;
}


void generate_start_pt (int *row, int *col, int length, int direction)
{

	if (direction == 0) // horizontal
	{
		*row = rand () % 10;
		*col = rand () % (10 - length + 1);
	}
	else // vertical
	{
		*row = rand () % (10 - length + 1);
		*col = rand () % 10;
	}
}

void generate_direction (int *direction)
{
	*direction = rand () % 2; 
	// 0 - horizontal, 1 - vertical
}


//Create a function update_board() that updates the board every time a shot is taken. '*' indicates a hit and 'm' indicates a miss.
//Create a function display_board() that displays a board to the screen. Note that Player1's board should be displayed differently than Player2's board (see above).
//Hint: pass in a flag (int) that stores whether or not you just passed in Player1's or Player2's board.