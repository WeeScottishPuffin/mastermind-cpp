#include <map>
#include <vector>
#include <string>

#ifndef COLOURS_H
#define COLOURS_H

namespace colours{
	const std::map<char, std::string> colour_map =	//Map of the char denoting a colour and the corresponding (ANSI) coloured 'o' 
	{
		{'r', "\u001B[1m\u001B[31mo\u001B[0m"},
		{'y', "\u001B[1m\u001B[33mo\u001B[0m"},
		{'g', "\u001B[1m\u001B[32mo\u001B[0m"},
		{'b', "\u001B[1m\u001B[34mo\u001B[0m"},
		{'m', "\u001B[1m\u001B[35mo\u001B[0m"},
		{'c', "\u001B[1m\u001B[36mo\u001B[0m"},
	};	
	const std::vector<char> letters = {'r','y','g','b','m','c'};
}
#endif
