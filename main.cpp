#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <fstream>
#include <string>
#include <stack>

#include "tools.h"

using namespace std;

int main() {
	// ввод названия файла
   	cout << "Enter name of file: ";
	string file_name;
	cin >> file_name;
	ifstream file;
	file.open(file_name, ios::in);
	// если файл не открылся, н-р его не существует
	if (!file){
		cout << "Error";
		return -1;
	}

	// объявление стека и переменных
	// в стеке хранятся встреченные скобки 
	stack <Bracket> bracket_stack;
	char cur, prev;
	string word, word_clear;
	int str = 1, quote1 = 1, quote2 = 1;
	
	while (1) {
		// ввод из файла
		file >> noskipws >> cur;
		
		bracket_tool(&bracket_stack, cur, str);

		// если слово закончилось, т.е. встретилась не буква или цифра
		if (!isdigit(cur) && !isalpha(cur))
		{
			// проверка на кавычки
			if (cur == '\"') quote1 *= (-1);
			if (cur == '\'') quote2 *= (-1);

			// если слово есть в word_data и в нем есть ошибка
			if (word_check(word, word_clear, str)) return -1;
			//очистка слов
			word.clear();
			word_clear.clear();
		}
		else{
			// запись слов
			word += cur;
			if (islower(cur)) word_clear +=cur;
		} 

		// если текущий символ это перенос строки, т.е. последний символ
		if (cur == '\n'){
			// если строка оканчивается не на ; < > или скобки, то ошибка
			if (syntax_check(prev, str)) return -1;
			// проверка закрытых скобок (если quote положительный)
			if (quote_check(quote1, quote2, str)) return -1;
			
			str++;
		}
		prev = cur;

		// если конец файла, выход
		if (file.eof()) break;
	}

	// если в стеке остались скобки, т.е. какие то не закрылись парой, то ошибка
	file.close();
	// проверка стека
	if (bracket_check(bracket_stack)) return -1;
	
	//
	cout << "Exit code 0\n";
	cout << ">>No errors found<<\n";
	return 0;
}
