#include <string>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include "..\TStacklib\TStack.h"
using namespace std;

#pragma once
class TPostfixCalc
{
private:
	string infix;
	string postfix;
	TStack<char> operationStack;
	TStack<double> operandStack;
	double res;

protected:
	int Priority(char c) {
		switch (c)
		{
		case '(':
		case ')':
			return 1;

		case '+':
		case '-':
			return 2;
		case '*':
		case '/':
			return 3;
		default: throw - 1;
		}
	}
public:

	TPostfixCalc() {
		postfix = "";
		infix = "";
		operationStack = TStack<char>(0);
		operandStack = TStack<double>(0);
		res = 0;
	}

	TPostfixCalc(string eq) {
		if (eq.length() <= 0) throw std::runtime_error{"������ ������"};
		postfix = "";
		infix = eq;
		operationStack = TStack<char>(eq.length());
		operandStack = TStack<double>(eq.length());
		res = 0;
	}

	TPostfixCalc(const TPostfixCalc& c) {
		if (&c == this) throw std::runtime_error{"�� ����� ���� �������� ������� ������ ����"};
		postfix = c.postfix;
		infix = c.infix;
		operationStack = c.operationStack;
		operandStack = c.operandStack;
		res = c.res;
	}


	~TPostfixCalc() {}

	void ChangeEquation(string s) { 
		infix = s;
		operationStack = TStack<char>(s.length());
		operandStack = TStack<double>(s.length());
	}

	string GetInf() { return infix; }
	string GetPost() { return postfix; }
	double GetRes() { return res; }
	void ToPostfix() {
		char el = '!';
		postfix = "";
		string s = "(" + infix + ")";
		for (size_t i = 0; i < s.size(); i++)
		{
			if (s[i] <= '9' && s[i] >= '0') postfix += s[i];
			if (s[i] == '/' || s[i] == '*' || s[i] == '+' || s[i] == '-') {
				postfix += " ";
				el = operationStack.Pop();
				while (Priority(s[i]) <= Priority(el)) {
					postfix += el;
					postfix += " ";
					el = operationStack.Pop();
				}
				operationStack.Push(el);
				operationStack.Push(s[i]);
			}
			if (s[i] == '(') operationStack.Push(s[i]);
			if (s[i] == ')') {
				el = operationStack.Pop();
				
				while (el != '(') {
					postfix += el;
					el = operationStack.Pop();
				}
			}
		}
	}
	void CalcPostfix() {
		for (size_t i = 0; i < postfix.size(); i++)
		{
			if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/') {
				double d1, d2;
				switch (postfix[i]) {
					case '+': 
						d1 = operandStack.Pop();
						d2 = operandStack.Pop();
						operandStack.Push(d1 + d2);
						break;
					case '-':
						d2 = operandStack.Pop();
						d1 = operandStack.Pop();
						operandStack.Push(d1 - d2);
						break;
					case '*':
						d1 = operandStack.Pop();
						d2 = operandStack.Pop();
						operandStack.Push(d1 * d2);
						break;
					case '/':
						d1 = operandStack.Pop();
						d2 = operandStack.Pop();
						operandStack.Push(d1 / d2);
						break;
					default: throw "����� �� ���� ��";
				}
			}
			if (postfix[i] <= '9' && postfix[i] >= '0') {
				size_t count;
				double t = std::stod(&postfix[i], &count);
				operandStack.Push(t);
				i += count - 1;
			}
		}
		res = operandStack.TopView();
	}
	
	void Build() {
		ToPostfix();
		CalcPostfix();
	}

	TPostfixCalc& operator=(const TPostfixCalc& c) {
		if (&c == this) return *this;
		postfix = c.postfix;
		infix = c.infix;
		operationStack = c.operationStack;
		operandStack = c.operandStack;
		return *this;
	}

	bool operator==(const TPostfixCalc& c) {
		if (infix != c.infix || postfix != c.postfix || operandStack != c.operandStack || operationStack != c.operationStack)
			return false;
		return true;
	}
	bool operator!=(const TPostfixCalc& c) {
		if (infix != c.infix || postfix != c.postfix || operandStack != c.operandStack || operationStack != c.operationStack)
			return true;
		return false;
	}

	friend istream& operator>>(istream& istr, TPostfixCalc& c)
	{
		string exp; 
		cout << "������� ���� ���������:";
		istr >> exp;
		c.ChangeEquation(exp);
	}
	friend ostream& operator<<(ostream& ostr, const TPostfixCalc& c)
	{
		ostr << "��������� ���������: " << c.infix << endl;
		if (c.postfix.size() == 0) { ostr
			<< "��������� ������ ��� �� �������� ������������" << endl; }
		else { ostr << "���������: " << c.postfix << endl; }
		ostr << "�������� �������: " << c.res << endl;
		
		return ostr;
	}
};
