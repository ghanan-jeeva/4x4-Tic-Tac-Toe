/*
 * Name: Ghanan Jeevaretnam

 * I hereby declare that this code, submitted for credit for the course
 * SYDE121, is a product of my own efforts.  This coded solution has
 * not been plagiarized from other sources and has not been knowingly
 * plagiarized by others.
 *
 * Project: Tic Tac Toe
 * Purpose: Create a 2 player tic tac toe game
 * Steps:
 * 1. Decide how to set up board (4x4 of strings)
 * 2. Create functions (update board, check win, get user input, etc.)
 * 3. Use these functions to help create the functionality of tic tac toe
 */

#include <iostream>
#include <string>
using namespace std;

//Purpose: Function that creates the array for the tic tac toe board, takes the user input and calls certain functions to check if there is a winner
//Input: The number of games, the number of wins that Player "X" has, the number of wins that Player "O", and the user inputs the location where they want to place their charcater
//Output: Null return but prints whether "X" or "O" won
void run_tic_tac_toe(int number_of_games, int& wins_X, int& wins_O);

//Purpose: Prints the tictactoe board based on the elements within the initialized array
//Input: The tic_tac_toe_board 2-D array
//Output: Null output but prints the array with 4 rows and columns 
void print_board(string tic_tac_toe_board[][4]);

//Purpose: Updates boards based on player inputs "X" or "O" based on location on board
//Input: The tic_tac_toe_board 2-D array, location of the "X" or "O" charcter specified by the user, and who the player is("X" or "O")
//Output:  Null output but updates boards with new value
void update_board(string tic_tac_toe_board[][4], int position, string player);

//Purpose: Checks tic tac toe board to see if all four elements in the same row are the same characters to satisfy win condition
//Input: The tic_tac_toe_board 2-D array, and who the player is("X" or "O")
//Output: Returns 1 if win condition is satisfied, if not, returns 0
int check_horizontal(string tic_tac_toe_board[][4], string player);

//Purpose: Checks tic tac toe board to see if all four elements in the same column are the same characters to satisfy win condition
//Input: The tic_tac_toe_board 2-D array, and who the player is("X" or "O")
//Output: Returns 1 if win condition is satisfied, if not, returns 0
int check_vertical(string tic_tac_toe_board[][4], string player);

//Purpose: Checks tic tac toe board to see if the diagonal from the top left to bottom right are the same characters to satisfy win condition
//Input: The tic_tac_toe_board 2-D array, and who the player is("X" or "O")
//Output: Returns 1 if win condition is satisfied, if not, returns 0
int check_diagonal_1(string tic_tac_toe_board[][4], string player);

//Purpose: Checks tic tac toe board to see if the diagonal from the bottom left to top right are the same characters to satisfy win condition
//Input: The tic_tac_toe_board 2-D array, and who the player is("X" or "O")
//Output: Returns 1 if win condition is satisfied, if not, returns 0
int check_diagonal_2(string tic_tac_toe_board[][4], string player);

//Purpose: Checks if any of the 4 win conditions are satisfied
//Input: The tic_tac_toe_board 2-D array, and who the player is("X" or "O")
//Output: Returns true if a player has won, if not, false is returned
bool check_win(string tic_tac_toe_board[][4], string player);

//Purpose: Checks to see if the user input is valid
//Input: The tic_tac_toe_board 2-D array and the user input for where they want to place their character
//Output: Returns true if the input is valid and false if it isnt
bool check_input(string tic_tac_toe_board[][4], int input);


int main() 
{

	int number_of_games = 0;
	int wins_X = 0;
	int wins_O = 0;
	string play_again = "";

	do 
	{
		number_of_games += 1;
		run_tic_tac_toe(number_of_games, wins_X, wins_O);
		cout << "Would you like to play again? Enter \"yes\" for another game or \"no\" if you want to quit\n";
		cin >> play_again;
	} while (play_again == "yes");

	cout << "\nNumber of Games " << number_of_games;
	cout << "\nX Wins: " << wins_X;
	cout << "\nO Wins: " << wins_O;

	return 0;
}

void run_tic_tac_toe(int number_of_games, int& wins_X, int& wins_O)
{
	string tic_tac_toe_board[4][4] = { {"1","2","3","4"},{"5","6","7","8"},{"9","10","11","12"},{"13","14","15","16"} };

	
	for (int row = 0; row < 4; row++)           
	{
		for (int column = 0; column < 4; column++)
		{
			tic_tac_toe_board[row][column] = to_string((row * 4) + (column + 1));     //Resets Board
		}
	}
	

	int input = 0;
	int number_of_inputs = 0;
	string player = "";
	if (number_of_games % 2 == 1)        // Every odd game, player X starts
	{
		player = "X";
	}
	else
	{
		player = "O";
	}


	while (check_win(tic_tac_toe_board, "X") == false && check_win(tic_tac_toe_board, "O") == false && number_of_inputs != 16)
	{

		print_board(tic_tac_toe_board);
		
		do
		{
			cout << "Player " << player << ": Enter the space you want to choose\n";
			cin >> input;
		} while (!check_input(tic_tac_toe_board, input));    //While loop condition is set so that it loops until user inputs a valid location

		number_of_inputs += 1;   // Checks the number of total user inputs in the case of a tie game
		
		update_board(tic_tac_toe_board, input, player);     //Updates board based on user input
		if (player == "X")                                  // Once valid move is made, player switches from X to O or vice versa
		{
			player = "O";
		}
		else
		{
			player = "X";
		}
	}
	
	if (check_win(tic_tac_toe_board, "X"))   //Checks if Player X has won
	{
		wins_X += 1;
		print_board(tic_tac_toe_board);
		cout << "Player X Wins!\n";
	}
	else if (check_win(tic_tac_toe_board, "O"))    //Checks if Player O has won
	{
		wins_O += 1;
		print_board(tic_tac_toe_board);
		cout << "Player O Wins!\n";
	}
	else
	{
		print_board(tic_tac_toe_board);         //Checks if there is a tie game
		cout << "Tie Game!\n";
	}

}

bool check_input(string tic_tac_toe_board[][4], int input)
{
	for (int row = 0; row < 4; row++) {                   
		
		for (int column = 0; column < 4; column++) {                	//checks all places of the board if the input exists on the board
			
			if (tic_tac_toe_board[row][column] == to_string(input)) {
				return true;
			}
		}
	}
	return false;
}

bool check_win(string tic_tac_toe_board[][4], string player)
{
	if (check_horizontal(tic_tac_toe_board, player) || check_vertical(tic_tac_toe_board, player) || check_diagonal_1(tic_tac_toe_board, player) || check_diagonal_2(tic_tac_toe_board, player)) 	//checks all possible win scenarios(by calling other functions created to check win)

	{
		return true;
	}
	else {
		return false;
	}
}

int check_horizontal(string tic_tac_toe_board[][4], string player)
{
	int count;
	for (int row = 0; row < 4; row++)
	{
		count = 0;
		for (int column = 0; column < 4; column++)
		{
			if (tic_tac_toe_board[row][column] == player)
			{
				count++;
			}
			if (count == 4)
			{
				return 1;
			}
		}
	}
	return 0;
}

int check_vertical(string tic_tac_toe_board[][4], string player)
{
	int count;
	for (int row = 0; row < 4; row++)
	{
		count = 0;
		for (int column = 0; column < 4; column++) {
			if (tic_tac_toe_board[column][row] == player)
			{
				count++;
			}
			if (count == 4)
			{
				return 1;
			}
		}
	}
	return 0;
}

int check_diagonal_1(string tic_tac_toe_board[][4], string player)
{
	if (tic_tac_toe_board[0][0] == player && tic_tac_toe_board[1][1] == player && tic_tac_toe_board[2][2] == player && tic_tac_toe_board[3][3] == player)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int check_diagonal_2(string tic_tac_toe_board[][4], string player)
{
	if (tic_tac_toe_board[0][3] == player && tic_tac_toe_board[1][2] == player && tic_tac_toe_board[2][1] == player && tic_tac_toe_board[3][0] == player)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void update_board(string tic_tac_toe_board[][4], int position, string player)
{
	tic_tac_toe_board[position / 4][position % 4 - 1] = player;
}


void print_board(string tic_tac_toe_board[][4])
{
	cout << "\n";
	
	for (int x = 0; x < 4; x++) {
		
		for (int i = 0; i < 4; i++) {
			cout << tic_tac_toe_board[x][i] << "\t";
		}
		cout << "\n";
	}
}


