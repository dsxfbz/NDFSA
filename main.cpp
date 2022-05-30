/*
 * main.cpp
 * 
 * Copyright 2022 Daniel Xiang <daniel@debian-11-school>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include "ndfsa.h"

#include <iostream>

int main(int argc, char **argv)
{
	ndfsa automata("sample_input.txt");
	
	std::cout<<"\n";
	automata.print();
	
	std::string curr_word = "hello!";
	std::cout<<"Processing \""<<curr_word<<"\"\n";
	if (automata.process(curr_word)) {
		std::cout<<"  Matches!\n";
	}
	else {
		std::cout<<"  Doesn't match.\n";
	}
	
	curr_word = "hello";
	std::cout<<"Processing \""<<curr_word<<"\"\n";
	if (automata.process(curr_word)) {
		std::cout<<"  Matches!\n";
	}
	else {
		std::cout<<"  Doesn't match.\n";
	}
	
	curr_word = "goodbye.";
	std::cout<<"Processing \""<<curr_word<<"\"\n";
	if (automata.process(curr_word)) {
		std::cout<<"  Matches!\n";
	}
	else {
		std::cout<<"  Doesn't match.\n";
	}
	
	curr_word = "Goodbye.";
	std::cout<<"Processing \""<<curr_word<<"\"\n";
	if (automata.process(curr_word)) {
		std::cout<<"  Matches!\n";
	}
	else {
		std::cout<<"  Doesn't match.\n";
	}
	
	curr_word = "hell";
	std::cout<<"Processing \""<<curr_word<<"\"\n";
	if (automata.process(curr_word)) {
		std::cout<<"  Matches!\n";
	}
	else {
		std::cout<<"  Doesn't match.\n";
	}
	return 0;
}

