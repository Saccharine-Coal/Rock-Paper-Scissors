// Two other contributors + me
// Project v6
// 5/13/2021
// Rock, Paper, Scissors game
// Version #6


#include <iostream>
#include <random>

using namespace std;

/**
	function that compares int values to determine if player win or loss
	@params player_move (1, 2, or 3), computer_move (1, 2, or 3)
	@return (0 = Tie, 1 = Win, -1 = Loss)
*/

int get_player_outcome(int player_move, int computer_move)
{
	int result = player_move - computer_move;
	if (result == 0)
	{
		cout << "Tie Game!" << endl;
		return 0;
	}
	else if (result == 1 || result == -2)
	{
		cout << "Congratulations, you won!" << endl;
		return 1;
	}
	else
	{
		cout << "Sorry, you lost!" << endl;
		return -1;
	}
}


/**
	this function checks the value to a each key and returns the corresponding value
	@params value to check, list of key value pairs
	@return corresponding value from key
*/
string get_value_from_key(
	int val_to_check,
	const int KEY_1,
	const int KEY_2,
	const int KEY_3,
	const string VAL_1,
	const string VAL_2,
	const string VAL_3
)
{
	// (KEY_1, VAL_1)
	if (val_to_check == KEY_1)
	{
		return VAL_1;
	}
	// (KEY_2, VAL_2)
	else if (val_to_check == KEY_2)
	{
		return VAL_2;
	}
	// (KEY_3, VAL_3)
	else if (val_to_check == KEY_3)
	{
		return VAL_3;
	}
	// DEFAULT VALUE 
	else
	{
		return VAL_1;
	}
}


/**
	this function prints player choice (rock, paper, or scissors)
	and the computer choice (rock, paper, or scissors)
	@params player choice string, computer choice string
*/
void print_string_repr(string player_choice_str, string computer_choice_str)
{
	cout << "Your move: " << player_choice_str << " || Computers move: " << computer_choice_str << endl;
}


/**
* function that increments wins, ties, or losses from the game outcome
* @param result of game outcome (0, 1, -1) and wins, ties, losses references
*/
void update_statistics(int game_outcome, int& wins, int& ties, int& losses)
{
	// loss
	if (game_outcome == -1)
	{
		losses++;
	}
	// tie
	else if (game_outcome == 0)
	{
		ties++;
	}
	// win
	else if (game_outcome == 1)
	{
		wins++;
	}
}


/**
	prints to console: player wins, ties, and losses
*/
void print_statistics(int& wins, int& ties, int& losses)
{
	cout << "Getting statistics... ";
	cout << "Wins: " << wins << " Ties: " << ties << " Losses: " << losses << endl;
}


/**
function loops until a valid choice is chosen (1, 2, or 3)
@params key_1, key_2, key_3
@return valid key value
*/

int handle_input_choices(
	const int KEY_1,
	const int KEY_2,
	const int KEY_3
)
{
	cout << "Please Choose between: Rock is 1, Paper is 2, or Scissors is 3: ";
	int player_choice;
	while (true)
	{
		cin >> player_choice;
		// check if non int value is inputted
		if (cin.fail()) 
		{
			cout << "Please enter an integer" << endl;
			// clear failed state
			cin.clear();
			// move input stream to new line
			cin.ignore(10000, '\n');
		}
		// player choice is an integer
		else
		{
			// 1, 2, or 3 are valid choices
			if (player_choice == KEY_1 || player_choice == KEY_2 || player_choice == KEY_3)
			{
				return player_choice;
			}
			// any other int is not a valid choice
			else
			{
				cout << player_choice << " Is not 1, 2, or 3." << endl;
				cout << "Please choose 1 for Rock, 2 for Paper, or 3 Scissors." << endl;
			}
		}
	}
}


/**
	this function determines if the program will reiterate or exit the main game loop
	@params quit sentinel value, value needed for the user to input to quit
	@return running bool
*/
bool handle_quitting(const string& QUIT_SENTINEL)
{
	cout << "Play again?[y/n]: ";
	bool running = true;
	string input;
	cin >> input;
	if (input == QUIT_SENTINEL)
	{
		cout << "Exiting game..." << endl;
		running = false;
	}
	else
	{
		cout << "Resetting game..." << endl;
		running = true;
	}
	return running;
}


int main()
{
	// KEY_1, KEY_2, KEY_3, VAL_1, VAL_2, VAL_3 copy pasteable
	// INITIALIZE VARIABLES
	const int KEY_1 = 1;
	const int KEY_2 = 2;
	const int KEY_3 = 3;
	const string VAL_1 = "Rock";
	const string VAL_2 = "Paper";
	const string VAL_3 = "Scissors";

	// QUIT
	const string QUIT_SENTINEL = "n";

	// PLAYER variables
	int player_choice;

	// COMPUTER variables
	int	computer_choice;

	// Statistics
	int wins = 0;
	int ties = 0;
	int losses = 0;

	//Intialize random number generator
	random_device rd; //Obtain a random number from hardware
	mt19937 eng(rd()); //Send to the genrator
	uniform_int_distribution<>distr(1, 3); //define the range


	// game running
	bool running = true;

	// Instructions
	cout << "Welcome!" << endl;

	// MAIN GAME LOOP
	while (running)
	{
		// validate user input
		player_choice = handle_input_choices(KEY_1, KEY_2, KEY_3);

		//Create a random interger from 1 to 3, to simulate the computers selecting a move
		computer_choice = distr(eng);

		// check player choice against computer choice
		int game_outcome = get_player_outcome(player_choice, computer_choice);

		// get string representation of the numerical values
		string player_choice_str = get_value_from_key(player_choice, KEY_1, KEY_2, KEY_3, VAL_1, VAL_2, VAL_3);
		string computer_choice_str = get_value_from_key(computer_choice, KEY_1, KEY_2, KEY_3, VAL_1, VAL_2, VAL_3);
		print_string_repr(player_choice_str, computer_choice_str);

		// update statistics
		update_statistics(game_outcome, wins, ties, losses);

		// quit sequence
		running = handle_quitting(QUIT_SENTINEL);
	}
	// print statistics before program termination outside the loop
	print_statistics(wins, ties, losses);
	return 0;
}
