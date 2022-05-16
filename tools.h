#pragma once

#include <stack>
#include <string>
#include <vector>
#include <stack>

// класс для скобок, чтобы удобнее следить за строкой ошибки, типом скобки
// и направлением
class Bracket {

// 	в private хранятся информация о классе, защищено от изменений
private:

	unsigned int type;
	bool direction;
	unsigned int position;
	
//	в public находятся методы класса
public:

	Bracket(unsigned int t, bool d, unsigned int p);

	unsigned int get_pos();

	bool get_dir();

	unsigned int get_type();

};

//	функции из tools.cpp, которые используются в main.cpp 
void bracket_tool(std::stack<Bracket>* bracket_stack, char cur, int str);

bool word_check(std::string word, std::string word_clear, int str);

bool syntax_check(char prev, int str);

bool quote_check(int quote1, int quote2, int str);

bool bracket_check(std::stack<Bracket> bracket_stack);
