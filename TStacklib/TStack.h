
#pragma once
template <class T>
class TStack {
protected:
	int size;
	int top;
	T* mas;

public:
	TStack(int n = 0) {
		if (n < 0) throw std::runtime_error{"������ ������� ���� � ������������� ������"};
		top = -1;
		size = n;
		mas = new T[n];
	}
	TStack(const TStack<T>& s) {
		size = s.size;
		top = s.top;
		mas = new T[size];
		for (size_t i = 0; i < size; i++)
		{
			mas[i] = s.mas[i];
		}
	}
	~TStack() {
		delete[] mas;
	}

	void Clear() {
		for (size_t i = 0; i < size; i++) mas[i] = 0;
	}
	int GetSize() {
		return top + 1;
	}
	void Push(T x) {  // ������� � �� �������
		if (IsFull()) throw std::runtime_error{"���� �����"};
		mas[++top] = x;
	} 
    T GetTop() {  // ������� � � �������
		if (IsEmpty()) throw std::runtime_error{"���� ����"};
		return mas[top];
	}
	T Pop()  // ������ ��������� �������
	{
		if (IsEmpty()) throw std::runtime_error{"���� ����"};
		return mas[top--];
	}
	T TopView() {  // ���������� ��������� �������
		if (IsEmpty()) throw std::runtime_error{"���� ����"};
		return mas[top];
	} 
	

	bool IsFull() {
		return top == size - 1;
	}
	bool IsEmpty() {
		return top == -1;
	}

	TStack<T>& operator=(const TStack<T>& s){
		if (&s == this) return *this;
		delete[] mas;
		size = s.size;
		top = s.top;
		mas = new T[size];
		for (size_t i = 0; i < size; i++) mas[i] = s.mas[i];
		return *this;
	}
	
	bool operator==(const TStack<T>& stack) {
		if (size != stack.size) return false;
		for (size_t i = 0; i < stack.size; i++)
		{
			if (mas[i] != stack.mas[i]) return false;
		}
		return true;
	}
	bool operator!=(const TStack<T>& stack) {
		if (size != stack.size) return true;
		for (size_t i = 0; i < size; i++) {
			if (mas[i] != stack.mas[i]) return true;
		}
		return false;
	}
	};
