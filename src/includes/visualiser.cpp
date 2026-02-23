#include <iostream>
#include <vector>
#include <string>
#include "visualiser.h"
#include "colours.h"
#include "consts.h"

namespace visualiser{
    std::string visualise_guess(int code_length, std::array<std::array<char,consts::CODE_LENGTH>,consts::TURNS> guesses, std::array<std::array<char,consts::CODE_LENGTH>,consts::TURNS> results){
        std::string guess_log = "";									//The string printed to screen, a visual represenation of made guesses and results
        guess_log += "┌";										//Corner piece
        for (int x = 0; x < 2 * code_length + 3; x++){guess_log += "─";}				//Top border, length should be twice the length of the code plus 3. Dirty implementation, however since 'char' can only store ASCII characters, this is probably the best option
        guess_log += "┐\n";										//Corner, newline
        for (int j = 0; j < guesses.size(); j++)							//Iterate over the made guesses (array containing arrays of chars)
        {												//
            std::array<char,consts::CODE_LENGTH> guess = guesses[j];					//Get the current (i.c. iteration) guess
            guess_log += "│";										//LEFT border
            for (int i = 0; i < code_length; i++)							//Iterate over singular guess, using 'for' since we need the index (i)
            {												//
                guess_log += (guess[i] != ' ') ? colours::colour_map.at(guess[i]) : "o";		//Append and 'o' character, if the guess has been made, it should be coloured using 'colours.h'
            }												//
            guess_log += " " + std::to_string(((j + 1) % 10)) + " ";					//Guess number
            for (int i = 0; i < code_length; i++)							//Get corresponding solution
            {												//
                guess_log += (results[j][i] != ' ') ? colours::colour_map.at(results[j][i]) : "o";	//Append 'o', coloured according to the result of the guess
            }												//
            guess_log += "│\n";										//Right border + newline
        }												//
        guess_log += "└";										//Lower left corner
        for (int x = 0; x < 2 * code_length + 3; x++){guess_log += "─";}				//Top border
        guess_log += "┘";										//Bottom right corner
        return guess_log;										//Return string guess_log
    }
}
