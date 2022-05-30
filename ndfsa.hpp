#ifndef NDFSA_HPP
#define NDFSA_HPP

ndfsa::ndfsa() {
	//m_curr_states
	
	m_num_starts = 0;
	m_start_states = nullptr;
	
	m_num_rules = 0;
	m_rule_starts = nullptr;
	m_rule_symbols = nullptr;
	m_rule_ends = nullptr;
	
	m_num_ends = 0;
	m_end_states = nullptr;
}
ndfsa::ndfsa(const std::string & filename) {
	//m_curr_states;
	
	m_num_starts = 0;
	m_start_states = nullptr;
	
	m_num_rules = 0;
	m_rule_starts = nullptr;
	m_rule_symbols = nullptr;
	m_rule_ends = nullptr;
	
	m_num_ends = 0;
	m_end_states = nullptr;
	
	get_data(filename);
}
ndfsa::ndfsa(const ndfsa & source) {
	/*
	m_num_states = source.m_num_states;
	delete[] m_curr_states;
	m_curr_states = new char[m_num_states];
	for (int i=0; i<m_num_states; i++) {
		m_curr_states[i] = source.m_curr_states[i];
	}
	*/
	m_curr_states = source.m_curr_states;
	
	m_num_starts = source.m_num_starts;
	delete[] m_start_states;
	m_start_states = new char[m_num_starts];
	for (int i=0; i<m_num_starts; i++) {
		m_start_states[i] = source.m_start_states[i];
	}
	
	m_num_rules = source.m_num_rules;
	delete[] m_rule_starts;
	delete[] m_rule_symbols;
	delete[] m_rule_ends;
	m_rule_starts = new char[m_num_rules];
	m_rule_symbols = new char[m_num_rules];
	m_rule_ends = new char[m_num_rules];
	for (int i=0; i<m_num_rules; i++) {
		m_rule_starts[i] = source.m_rule_starts[i];
		m_rule_symbols[i] = source.m_rule_symbols[i];
		m_rule_ends[i] = source.m_rule_ends[i];
	}
	
	m_num_ends = 0;
	delete[] m_end_states;
	m_end_states = new char[m_num_ends];
	for (int i=0; i<m_num_ends; i++) {
		m_end_states[i] = source.m_end_states[i];
	}
}

ndfsa ndfsa::operator = (const ndfsa & source) {
	/*
	m_num_states = source.m_num_states;
	delete[] m_curr_states;
	m_curr_states = new char[m_num_states];
	for (int i=0; i<m_num_states; i++) {
		m_curr_states[i] = source.m_curr_states[i];
	}
	*/
	m_curr_states = source.m_curr_states;
	
	m_num_starts = source.m_num_starts;
	delete[] m_start_states;
	m_start_states = new char[m_num_starts];
	for (int i=0; i<m_num_starts; i++) {
		m_start_states[i] = source.m_start_states[i];
	}
	
	m_num_rules = source.m_num_rules;
	delete[] m_rule_starts;
	delete[] m_rule_symbols;
	delete[] m_rule_ends;
	m_rule_starts = new char[m_num_rules];
	m_rule_symbols = new char[m_num_rules];
	m_rule_ends = new char[m_num_rules];
	for (int i=0; i<m_num_rules; i++) {
		m_rule_starts[i] = source.m_rule_starts[i];
		m_rule_symbols[i] = source.m_rule_symbols[i];
		m_rule_ends[i] = source.m_rule_ends[i];
	}
	
	m_num_ends = 0;
	delete[] m_end_states;
	m_end_states = new char[m_num_ends];
	for (int i=0; i<m_num_ends; i++) {
		m_end_states[i] = source.m_end_states[i];
	}
	
	return *this;
}

ndfsa::~ndfsa() {
	delete[] m_start_states;
	delete[] m_rule_starts;
	delete[] m_rule_symbols;
	delete[] m_rule_ends;
	delete[] m_end_states;
}

void ndfsa::get_data(const std::string & filename) {
	std::string curr_line;
	
	std::ifstream data;
	data.open(filename, std::ios::in);
	
	while (std::getline(data, curr_line)) {
		switch (int(curr_line[0])) {
			case int('S'):
				parse_starts(curr_line+"\0");
				break;
			case int('R'):
				parse_rules(curr_line+"\0");
				break;
			case int('E'):
				parse_ends(curr_line+"\0");
				break;
			default:
				std::cout<<"ERROR: Invalid line \""<<curr_line<<"\"\n";
		}
	}
	
	data.close();
}

bool ndfsa::process(const std::string & input) {
	for (int i=0; i<m_num_starts; i++) {
		m_curr_states.push_back(m_start_states[i]);
	}
	
	for (int i=0; i<input.size(); i++) {
		step(input[i]);
	}
	
	if (valid()) {
		return true;
	}
	return false;
}

void ndfsa::print() {
	std::cout<<"S ";
	for (int i=0; i<m_num_starts; i++) {
		std::cout<<m_start_states[i];
	}
	std::cout<<"\n";
	
	std::cout<<"E ";
	for (int i=0; i<m_num_ends; i++) {
		std::cout<<m_end_states[i];
	}
	std::cout<<"\n";
	
	std::cout<<"R ";
	for (int i=0; i<m_num_rules; i++) {
		std::cout<<m_rule_starts[i];
		std::cout<<m_rule_symbols[i];
		std::cout<<m_rule_ends[i];
		std::cout<<",";
	}
	std::cout<<"\n";
}

bool ndfsa::step(const char & symbol) {
	char * start;
	char * symb;
	char * end;
	bool valid;
	
	char curr_state;
	
	std::deque<char> next_states;
	
	//Iterate through curr states
	while (m_curr_states.size() > 0) {
		curr_state = m_curr_states.front();
		m_curr_states.pop_front();
		
		//Iterate through rules
		start = &m_rule_starts[0];
		symb = &m_rule_symbols[0];
		end = &m_rule_ends[0];
		for (int r=0; r<m_num_rules; r++) {
			if (curr_state == *start) {
				if (symbol == *symb) {
					//If state not in next states
					if (std::find(next_states.begin(), next_states.end(), *end) == next_states.end()) {
						//Add state to next states
						next_states.push_back(*end);
					}
				}
			}
			start++;
			symb++;
			end++;
		}
	}
	
	//Save new states
	m_curr_states = next_states;
	
	//Cleanup
	
	//If new states
	return (m_curr_states.size() > 0);
}

bool ndfsa::valid() {
	std::deque<char> states = m_curr_states;
	while (states.size() > 0) {
		if (in_arr(states.front(), m_end_states, m_num_ends)) {
			return true;
		}
		states.pop_front();
	}
	return false;
}

void ndfsa::parse_starts(const std::string & line) {
	delete[] m_start_states;
	m_num_starts = 0;
	
	for (int i=2; line[i]!='\0'; i++)
		m_num_starts++;
	m_start_states = new char[m_num_starts];
	
	for (int i=0; i<m_num_starts; i++)
		m_start_states[i] = line[i+2];
	
	return;
}
void ndfsa::parse_rules(const std::string & line) {
	delete[] m_rule_starts;
	delete[] m_rule_symbols;
	delete[] m_rule_ends;
	m_num_rules = 0;
	
	for (int i=2; line[i]!='\0'; i++)
		if (line[i] == ',')
			m_num_rules++;
	m_rule_starts = new char[m_num_rules];
	m_rule_symbols = new char[m_num_rules];
	m_rule_ends = new char[m_num_rules];
	
	int indx = 0;
	for (int i=2; line[i]!='\0'; i++) {
		if (line[i]==',') {
			indx++;
		}
		else {
			//std::cout<<"  line["<<i<<"]->"<<(i-2-indx)%3<<": "<<line[i]<<"\n";
			switch ((i-2-indx)%3) {
				//Start state
				case 0:
					m_rule_starts[indx] = line[i];
					break;
				//Symbol
				case 1:
					m_rule_symbols[indx] = line[i];
					break;
				//End state
				case 2:
					m_rule_ends[indx] = line[i];
					break;
			}
		}
	}
	
	return;
}
void ndfsa::parse_ends(const std::string & line) {
	delete[] m_end_states;
	m_num_ends = 0;
	
	for (int i=2; line[i]!='\0'; i++)
		m_num_ends++;
	m_end_states = new char[m_num_ends];
	
	for (int i=0; i<m_num_ends; i++)
		m_end_states[i] = line[i+2];
	
	return;
}

#endif
