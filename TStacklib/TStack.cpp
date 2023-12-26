template <class T>
class TStack {
protected:
	int size;
	int top;
	T* mas;

public:
	TStack(int n = 0) {
		this->top = -1;
		this->size = n;
		this->mas = new T[n];
	}
	TStack(TStack<T>& stack) {
		this->size = stack.size;
		this->top = stack.top;
		std::copy(stack.mas, stack.mas + stack.size, this->mas);
	}
	~TStack() {
		delete[] this->mas;
	}
	void Clear() {
		for (size_t i = 0; i < size; i++) mas[i] = 0;
	}
	/*void Push(T a) {
		if (IsFull()) {
			throw - 1;
		}
		mas[++top] = a;
	}*/
	/*T Get() {
		if (IsEmpty()) {
			throw - 1;
		}
		top–;
		return mas[top];
	}*/
	

	int GetSize() {
		return top + 1;
	}

	void Push(T x) {  // Втолкнуть x в стек
		if (IsFull()) throw - 1;
		mas[++top] = x;
	} 
    T GetTop() {  // Вытолкнуть последний элемент из стека
		if (IsEmpty()) {
			throw - 1;
		}
		return mas[top];
	}
	T Pop()  // Вытолкнуть последний элемент из стека
	{
		if (IsEmpty()) {
			throw - 1;
		}
		else {
			return mas[top--];
		}
	}
	T TopView() {  // Подгядеть последний элемент
		if (IsEmpty()) throw - 1;
		return mas[top];
	} 
	
	//операторы вводы и выводы

	bool IsFull() {
		return top == size - 1;
	}
	bool IsEmpty() {
		return top == -1;
	}

	TStack<T>& operator=(const TStack<T>& stack) {
		if (this == &stack) return *this;
		if (this->size != stack.size) {
			if (this->mas != nullptr)
				delete mas;
			this->size = stack.size;
			this->mas = new T[this->size];
		}
		std::copy(stack.mas, stack.mas + stack.size, this->mas);
		return *this;
	}
	
	bool operator==(const TStack<T>& stack) {
		if (this == &stack) return true;
		if (this->size != stack.size) return false;
		for (size_t i = 0; i < stack.size; i++)
		{
			if (mas[i] != stack.mas[i]) return false;
		}
		return true;
	}

	bool operator!=(const TStack<T>& stack) {
		if (this->size != stack.size) return true;
		if (this == &stack) return false;
		else return true;
	}
	};
