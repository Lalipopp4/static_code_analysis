#include <stack>
#include <algorithm>
#include <iostream>

#include "tools.h"

using namespace std;

vector <string> word_data = {"in", "string", "if", "while", "main", "int", "void", "namespace", "using", "main", "bool", "float", "char", "return", "auto", "else", "cout", "cin", "for", "break"}; // глобальный массив, хранящий список ключевых команд

vector <char> brackets = {'(', '{', '[', ')', '}', ']'}; // глобальный массив, хранящий список скобок

// конструктор
// принимает тип, направление и сктроку
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
	// если элемент в массиве не находится, то возвращается указатель на последний нулевой элемент
	auto br = find(brackets.begin(), brackets.end(), cur);
	// если элемент не нулевой
	if (br != end(brackets)){ // проверка скобка ли cur
// 			br - brackets.begin() это разница между указатель на найденную скобку в массиве 
// 			brackets и указателем на первый элемент, это дает индекс элемента в массиве
// 			скобки расположены в массиве так,что () на 0 и 3 индексе, {} на 1 и 4, [] на 2 и 5
// 			когда находим скобку в списке, например }, то имеем ее индекс 4
// 			скобок 3 вида, поэтому с помощью %3 опрределяем тип скобки
// 			например, 4 (индекс скобки в списке) % 3 = 1
// 			соответственно скобка первого типа
			int type = (br - brackets.begin()) % 3;
// 			здесь хранится направление
// 			оно определяется с помощью /3
// 			например, 4 (индекс скобки в списке, это скобка '}') / 3 = 1, соответственно направление 1
// 			например, 0 (индекс скобки в списке, это скобка '(') / 3 = 0, соответственно направление 0
			bool dir = (br - brackets.begin()) / 3;
	// если скобки подходят н-р (), то вынимаем из стека последнюю добавленную
		// и если стек не пустой
			if (bracket_stack->size() > 0 && 
			bracket_stack->top().get_type() == type && bracket_stack->top().get_dir() != dir) {
// 				вынимаем из стека
				bracket_stack->pop();
			}
	// иначе добавляем в стек
			else{
				// создается экземпляр класса Bracket и вызывается для него конструктор, принимающий тип скобки, направление и строку
				// br - brackets.begin() это разница между указатель на найденную скобку в массиве 
// 				brackets и указателем на первый элемент, это дает индекс элемента в массиве
				Bracket bracket((br - brackets.begin()) % 3, (br - brackets.begin()) / 3, str);
// 				добавляем в стек
				bracket_stack->push(bracket);
			}		
	}
}

//  вывод ошибок
void error_out(int str){
	cout << "\nError!\n";
	cout << "String " << str << "\n";
}

// проверка слов
bool word_check(std::string word, std::string word_clear, int str){
	// если (текущее слово есть в списке ключевых слов и слово без спецсимволов (word_clear) не равно реальному слову (word)) или word_clear равно "include" и word не равно "include")
	if ((find(word_data.begin(), word_data.end(),word_clear) != end(word_data) && word != word_clear) || (word_clear == "include" && word != "include")){
		// вывести ошибку
		error_out(str);
		cout << ">>> " << word << " <<<\n";
		return 1;
	}
	return 0;
}

// проверка на ';'
bool syntax_check(char prev, int str){
	// если последний символ не равен '<' '>' '\n' ';' и скобке
	//  в find текущий элемент ищется в списке скобок
	if (prev != '\n' && prev != '<' && prev != '>' && 
	find(brackets.begin(), brackets.end(), prev)
	== end(brackets) && prev != ';'){
		// вывод ошибки
		error_out(str);
		cout << "Did you forget to use ';' ?\n";
		return 1;
	}
	return 0;
}

// проверка на кавычки
bool quote_check(int quote1, int quote2, int str){
	// если одна зи переменных меньше 0 
	if (quote1 < 0 || quote2 < 0){
		// вывод ошибки
		error_out(str);
		cout << "Quotes were not closed.\n";
		return 1;
	}
	return 0;
}

// проверка стека со скобками
bool bracket_check(stack<Bracket> bracket_stack){
	// если стек не пустой, т е остались незакрытые скобки
	if (bracket_stack.size() > 0){
		// вывести ошибку, передается строка верхней скобки из стека
		error_out(bracket_stack.top().get_pos());
		// вывод элемента из  brackets под индексом [тип верхней скобки из стека + 3 * направление верхней скобки из стека]
		cout << "\'" <<
		brackets[bracket_stack.top().get_type() + 3 * 
		bracket_stack.top().get_dir()] << "\' " << "bracket was not closed.\n";
		return 1;
	}
	return 0;
}
