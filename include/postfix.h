#ifndef _POSTFIX_H_
#define _POSTFIX_H_

#include "TStack.h"
#include <string>
#include <vector>
#include <map>
#include <cctype>

class TArithmeticExpression 
{
private:
	string infix;
	string postfix;
	map <string, int> priority;
	vector <string> lexems;
	vector <string> infLexems;
	
public:
	TArithmeticExpression(string infx) : infix(infx) {
		int c = 0;
		//проверка, что количество "(" и ")" равное количество 
		for (char i : infix) {
			if (i == '(') {
				c++;
			}
			else if (i == ')') {
				c--;
				if (c < 0) {
					throw runtime_error("incorrect brackets");
				}
			}
		}
		if (c != 0) {
			throw runtime_error("incorrect brackets");
		}
		//расстановка приоритетов арифметических операций
		priority = { {"+", 1},
					{"-", 1},
					{"*", 2},
					{"/", 2}, };
	}

	string GetInfix() { return infix; };
	string GetPostfix() { return postfix; };
	vector <string> GetLexs() { return infLexems; }

	void ParseInf() {//разбиение на строку чисел, используемых в инфиксной записи и на вектор лексем
		string st = infix;
		string tmp = "";

		for (auto i : st) {
			if (isdigit(i) || i == '.') {
				tmp += i;
			}
			else if (i == '+' || i == '-' || i == '*' || i == '/') {
				if (!tmp.empty()) {
					lexems.push_back(tmp);
					tmp = "";
				}
				lexems.push_back(string(1, i));
			}
			else if (i == '(' || i == ')') {
				if (!tmp.empty()) {
					lexems.push_back(tmp);
					tmp = "";
				}
				lexems.push_back(string(1, i));
			}
			else if (i != ' ') {
				throw runtime_error("Incorrect");
			}
		}

		if (!tmp.empty()) {
			lexems.push_back(tmp);
		}
	}

	string ToPostfix() {
		this->ParseInf();
		TStack<string> st;
		string tmp = "";

		for (string item : lexems) {
			if (item == "(") {
				st.push(item);
			}
			else if (item == ")") {
				tmp = st.Top();
				st.pop();
				while (tmp != "(") {
					postfix += tmp;
					postfix += " ";
					infLexems.push_back(tmp);
					tmp = st.Top();
					st.pop();
				}
			}
			else if (item == "+" || item == "-" || item == "*" || item == "/") {
				while (!st.isEmpty()) {
					tmp = st.Top();
					st.pop();
					if (priority[item] <= priority[tmp]) {
						postfix += tmp;
						postfix += " ";
						infLexems.push_back(tmp);
					}
					else {
						st.push(tmp);
						break;
					}
				}
				st.push(item);
			}
			else {
				postfix += item;
				postfix += " ";
				infLexems.push_back(item);
			}
		}
		cout << "\n";
		while (!st.isEmpty()) {
			tmp = st.Top();
			st.pop();
			postfix += tmp;
			postfix += " ";
			infLexems.push_back(tmp);
		}
		return postfix;
	}

	double Calculate() {
		TStack<double> st;
		double r;
		double l;
		for (auto lexem : infLexems) 
		{
			if (lexem == "+" || lexem == "-" || lexem == "*" || lexem == "/") {
				if (!st.isEmpty())
				{
					r = st.Top();
					st.pop();
				}
				else { throw runtime_error("No right argument");}
				if (!st.isEmpty()) 
				{
					l = st.Top();
					st.pop();
				}
				else { throw runtime_error("No left argument");}

				if (lexem == "+") { st.push(l+r);}
				else 
					if (lexem == "-") {st.push(l-r);}
					else 
						if (lexem == "*") {st.push(l*r);}
						else 
							if (lexem == "/") {st.push(l/r);}}
			else {st.push(stod(lexem));}
		}
		return st.Top();
	}
};
#endif