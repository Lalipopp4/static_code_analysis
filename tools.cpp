#include <stack>
#include <algorithm>
#include <iostream>

#include "tools.h"

using namespace std;

vector <string> word_data = {"in", "string", "if", "while", "main", "int", "void", "namespace", "using", "main", "bool", "float", "char", "return", "auto", "else", "cout", "cin", "for", "break"}; // список команд

vector <char> brackets = {'(', '{', '[', ')', '}', ']'}; // список скобок

// конструктор
Bracket::Bracket(unsigned int t, bool d, unsigned int p){
	type = t;
	direction = d;
	position = p;
}

// направление скобки
bool Bracket::get_dir(){
	return direction;
}

// строка
unsigned int Bracket::get_pos(){
	return position;
}

// вид скобки
unsigned int Bracket::get_type(){
	return type;
}

void bracket_tool(stack <Bracket>* bracket_stack, char cur, int str){
	// поиск cur в списке скобок
	auto br = find(brackets.begin(), brackets.end(), cur);
	if (br != end(brackets)){ // проверка скобка ли cur
			int type = (br - brackets.begin()) % 3;
			bool dir = (br - brackets.begin()) / 3;
	// если скобки подходят н-р (), то вынимаем из стека последнюю добавленную
			if (bracket_stack->size() > 0 && 
			bracket_stack->top().get_type() == type && 								bracket_stack->top().get_dir() != dir) {
				bracket_stack->pop();
			}
	// иначе добавляем в стек
			else{
				Bracket bracket((br - brackets.begin()) % 3, 							(br - brackets.begin()) / 3, str);
				bracket_stack->push(bracket);
			}		
	}
}

void error_out(int str){
	cout << "\nError!\n";
	cout << "String " << str << "\n";
}

bool word_check(std::string word, std::string word_clear, int str){
	if ((find(word_data.begin(), word_data.end(),word_clear) != 			end(word_data) && word != word_clear) || (word_clear == 				"include" && word != "include")){
		error_out(str);
		cout << ">>> " << word << " <<<\n";
		return 1;
	}
	return 0;
}

bool syntax_check(char prev, int str){
	if (prev != '\n' && prev != '<' && prev != '>' && 
	find(brackets.begin(), brackets.end(), prev)
	== end(brackets) && prev != ';'){
		error_out(str);
		cout << "Did you forget to use ';' ?\n";
		return 1;
	}
	return 0;
}

bool quote_check(int quote1, int quote2, int str){
	if (quote1 < 0 || quote2 < 0){
		error_out(str);
		cout << "Quotes were not closed.\n";
		return 1;
	}
	return 0;
}

bool bracket_check(stack<Bracket> bracket_stack){
	if (bracket_stack.size() > 0){
		error_out(bracket_stack.top().get_pos());
		cout << "\'" <<
		brackets[bracket_stack.top().get_type() + 3 * 
		bracket_stack.top().get_dir()] << "\' " << "bracket was not closed.\n";
		return 1;
	}
	return 0;
}