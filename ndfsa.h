#ifndef NDFSA_H
#define NDFSA_H

#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <algorithm>
//"U" must be a pointer to an array of type "T", and "len" must be the array's size.
template <class T, class U>
bool in_arr(const T & elem, const U & arr, const int & len) {
	U ptr = arr;
	for (int i=0; i<len; i++) {
		if (*ptr == elem) {
			return true;
		}
		ptr++;
	}
	return false;
}

//Doubles size of array "arr" and changes "len" to match new size
//Fills leftover spaces with '\0'
void expand_char_arr(char * & arr, int & len) {
	char * ptr = arr;
	char * new_arr = new char[len*2];
	char * new_ptr = &new_arr[0];
	
	for (int i=0; i<len; i++) {
		*new_ptr = *ptr;
		ptr++;
		new_ptr++;
	}
	
	delete[] arr;
	arr = new_arr;
	len *= 2;
	
	return;
}

class ndfsa {
	public:
		ndfsa();
		ndfsa(const std::string & filename);
		ndfsa(const ndfsa & source);
		
		ndfsa operator = (const ndfsa & source);
		
		~ndfsa();
		
		void get_data(const std::string & filename);
		
		bool process(const std::string & input);
		
		void print();
		
	private:
		//int m_num_states;
		//char * m_curr_states;
		std::deque<char> m_curr_states;
		int m_num_starts;
		char * m_start_states;
		int m_num_rules;
		char * m_rule_starts;
		char * m_rule_symbols;
		char * m_rule_ends;
		int m_num_ends;
		char * m_end_states;
		
		bool step(const char & symbol);
		
		bool valid();
		
		void parse_starts(const std::string & line);
		void parse_rules(const std::string & line);
		void parse_ends(const std::string & line);
};

#include "ndfsa.hpp"

#endif
