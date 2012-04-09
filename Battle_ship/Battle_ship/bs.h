 #ifndef BS_H
#define BS_H

#define ROWS 10
#define COLS 10
#define TEST 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



typedef struct stats
{
	char player_name[25];
	int num_hits;
	int num_misses;
	int total_num_shots;
	double hits_misses_ratio;
} Stats;

typedef struct ship_control
{
	int cruiser;
	char cruiser_life;

	int battle_ship;
	char battle_ship_life;

	int submarine;
	char submarine_life;

	int destroyer;
	char destroyer_life;

	int patrol_boat;
	char patrol_boat_life;
	
} Ship_control;

//void update_stats (Stats *player_stats);
Stats update_stats (Stats player_stats);


void open_menu(void);
void initialize_game_board(char board[ROWS][COLS], int num_rows, int num_cols);
void welcome_screen(void); 
void game_control(void);
int select_who_starts_first(void);
void print_board (char board[ROWS][COLS], int num_rows, int num_cols, int p_c);
void generate_start_pt (int *row, int *col, int length,int direction);
void generate_direction (int *direction);
void make_ships(char board[ROWS][COLS], char random, int len, char type);
int intitalize_game(char player_board[ROWS][COLS], char comp_board[ROWS][COLS]);
int take_shot(char board[ROWS][COLS], int *shot_row, int *shot_col, Ship_control *comp_ships, FILE * log);
int comp_shot(Ship_control *player_ships, char board[ROWS][COLS], int *shot_row, int *shot_col, FILE * log);
Ship_control check_ship(Ship_control ships, FILE * log);
int check_winner(Ship_control player_ships, Ship_control comp_ships, FILE * log);


#endif