//MASTERMIND C++ IMPLEMETATION
//  BY NAUT VAN DER WINDEN/
//     WeeScottishPuffin
//       21-01-2006

#include <iostream>
#include <array>
#include <vector>
#include "includes/visualiser.h"
#include "includes/colours.h"
#include "includes/consts.h"

//Function to clear the screen (print 500 newlines)
void clear(){
	for (int i = 0; i < 500; ++i){
		std::cout << std::endl;
	}
}
//Function to check if an item exists in a vector
bool is_in_vec(auto c, std::vector<auto> v){
	if (v.empty() || typeid(c).name() != typeid(v.at(0)).name()){
		return false;
	}
	for (auto i : v){
		if (c == i){
			return true;
		} 
	}
	return false;
}

bool check_win(std::array<char,consts::CODE_LENGTH> guess, std::vector<char> solution){
	for (int i = 0; i < solution.size(); i++){
		if (guess[i] != solution.at(i)){
			return false;
		}
	} 
	return true;
}

int main(){
	//Variables
	//Flags
	bool win = false;							//flag to check wincondition
	bool quit = false;							//flag to check if the player quits (since we need to break more than once)
	//Arrays
	std::vector<char> solution;						//Solution, generated later. While an array would be ideal for a small, fixed-length set like this, I use std::vector so I can use is_in_vec()
	std::array<char,consts::CODE_LENGTH> last_guess;//Last guessed code
	std::array<std::array<char,consts::CODE_LENGTH>,consts::TURNS> results; //Array of the result of players guesses
	std::array<std::array<char,consts::CODE_LENGTH>,consts::TURNS> guesses; //Array of the players guesses
	//Fill arrays, since we need (empty elements) to check if a guess is empty (not guessed yet) or a solution hasn't been checked yet
	std::array<char,consts::CODE_LENGTH> fill_arr;
	std::fill(fill_arr.begin(), fill_arr.end(), ' ');
	std::fill(guesses.begin(), guesses.end(), fill_arr);
	std::fill(results.begin(), results.end(), fill_arr);
	//Misc
	std::string guesslog;		//user friendly string representation of our guesses and results so far
	int guessnum = -1;		//
	//Splash screen
	std::string splash = "\u001B[31m8b    d8 \u001B[32m   db    \u001B[33m.dP\"Y8 \u001B[34m888888 \u001B[35m888888 \u001B[36m88\"\"Yb\u001B[0m 8b    d8 88 88b 88 8888b.\n\u001B[31m88b  d88 \u001B[32m  dPYb   \u001B[33m`Ybo.\" \u001B[34m  88   \u001B[35m88__   \u001B[36m88__dP\u001B[0m 88b  d88 88 88Yb88  8I  Yb\n\u001B[31m88YbdP88 \u001B[32m dP__Yb  \u001B[33mo.`Y8b \u001B[34m  88   \u001B[35m88\"\"   \u001B[36m88\"Yb\u001B[0m  88YbdP88 88 88 Y88  8I  dY\n\u001B[31m88 YY 88 \u001B[32mdP\"\"\"\"Yb \u001B[33m8bodP' \u001B[34m  88   \u001B[35m888888 \u001B[36m88  Yb\u001B[0m 88 YY 88 88 88  Y8 8888Y\"";
	//Generate solution
	for (int i = 0; i < consts::CODE_LENGTH; i++){
		char r = colours::letters[std::rand()%6];	
		solution.push_back(r);
	}
	//Print splash and credits
	clear();
	std::cout << splash << std::endl;
	std::cout << "By WeeScottishPuffin (Naut van der Winden)" << std::endl;
	std::cout << "Press <RETURN> to start";
	//Wait for user to press enter
	while (std::cin.get() != '\n'){}
	clear();
	//Mainloop
	for (int guess_n = 0; guess_n < consts::TURNS; guess_n++){
		for (int j = 0; j < consts::CODE_LENGTH; j++){
			//generate guesslog ascii art thing
			char guess_ = ' ';
			guesslog = visualiser::visualise_guess(consts::CODE_LENGTH, guesses, results);
			//Guess loop (loop untill a valid option is selected
			while (guess_ != 'e' && !is_in_vec(guess_,colours::letters)){
				clear();
				std::cout << guesslog << std::endl; //Print an overview of the players guesses and their results
				if (guess_n > 0 && check_win(guesses[guess_n-1], solution)){ //Only check if the player won after the first guess
					std::cout << "You win! You guessed the code in " << std::to_string(guess_n) << ((guess_n > 1) ? " guesses" : "guess") << std::endl;
					return 0;
				}
				std::cout << "Guess " << std::to_string(guess_n+1) << "/" << std::to_string(consts::TURNS) << ":" << std::endl;
				std::cout << "What colour for position " << std::to_string(j+1) << " (\u001B[31m[R]ed, \u001B[32m[G]reen, \u001B[33m[Y]ellow, \u001B[34m[B]lue, \u001B[35m[M]agenta, \u001B[36m[C]yan\u001B[0m or [E]xit):" << std::endl;
				guess_ = std::cin.get(); //Get the players action
			}
			if (guess_ == 'e'){ //Exit if they entered 'e'
				std::cout << "Goodbye!" << std::endl;
				return 0;
			} else {
				guesses[guess_n][j] = guess_; //Since we have already validated the guess is correct, we can add it to the md array of guesses			
			}
		}
		//Check last guess angainst the solution
		for (int z = 0; z < consts::CODE_LENGTH; z++){
			char char_g = guesses[guess_n][z];
			char char_s = solution[z];
			
			if (char_g == char_s){ //Both the guess and solution have this colour at the same place
				results[guess_n][z] = 'g';
			} else if(is_in_vec(char_g, solution)){ //The guessed colour exists SOMEWHERE in the solution
				results[guess_n][z] = 'y'; 
			} else { //The guessed colour does not exist in the solution
				results[guess_n][z] = 'r';
			}
		}
	}
	//Runs after the last guess, check win condition one last time
	if (check_win(guesses[consts::TURNS-1], solution)){
		std::cout << "You win! You guessed the code in " << std::to_string(consts::TURNS) << " guesses" << std::endl;
	} else {
		std::cout << "You lost!" << std::endl;
	}
	return 0;
}
