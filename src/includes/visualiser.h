#include <vector>
#include <array>
#include <string>
#include "consts.h"

#ifndef VISUALISER_H
#define VISUALISER_H
namespace visualiser{	
	std::string visualise_guess(int code_length, std::array<std::array<char,consts::CODE_LENGTH>,consts::TURNS> guesses, std::array<std::array<char,consts::CODE_LENGTH>,consts::TURNS> results);
}
#endif
