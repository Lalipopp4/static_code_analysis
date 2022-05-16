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
// 	str считает номер строки
// 	quote1 и quote2 отвечают за кавычки,кавычек должно быть четное число
// 	quote1 и quote2 умножаются на -1 каждый раз, когда встречается кавычка
// 	при нормальной работе программы, то есть четное количество кавычек, переменные будут
// 	перемноежны четное количество раз и следовательно будут больше нуля
// 	если они оказались отрицательными, то в коде нечетное количество кавычек, то есть присутствует ошибка
	int str = 1, quote1 = 1, quote2 = 1;
	
	while (1) {
		// ввод из файла
		file >> noskipws >> cur;
		
		bracket_tool(&bracket_stack, cur, str);

		// если слово закончилось, т.е. встретилась не буква или цифра
		if (!isdigit(cur) && !isalpha(cur))
		{
			// проверка на кавычки и умножение переменных
			if (cur == '\"') quote1 *= (-1);
			if (cur == '\'') quote2 *= (-1);

			// если слово есть в word_data и в нем есть ошибка
			if (word_check(word, word_clear, str)) return -1;
			//очистка слов
// 			в string есть метод clear(), который удаляет строку
// 			тем самым мы очищаем наши строки под новые слова, когда встретился пробел или другой разделитель
			word.clear();
			word_clear.clear();
		}
		else{
// 			запись слов
// 			в word записывается текущий символ
			word += cur;
// 			в word_clear записываются только строчные буквы, так как ключевые слова состоят из строчных букв
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
// 		в prev передается прошлый символ
// 		например, встретили перенос строки '\n', то prev проверяется на ; и другие завершающие строку символы
		prev = cur;

		// если конец файла, выход
		if (file.eof()) break;
	}
	file.close();
	// если в стеке остались скобки, т.е. какие то не закрылись парой, то ошибка
	// проверка стека
	if (bracket_check(bracket_stack)) return -1;
	
// 	если программа не завершила работу еще, то ошибок в коде нет
	cout << "Exit code 0\n";
	cout << ">>No errors found<<\n";
	return 0;
}
