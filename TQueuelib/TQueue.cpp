template <class T>
class TQueue {
protected:
	int size;
	int start;
	int end;
	int count;
	T* mas;

public:
	TQueue(int n = 0);
	TQueue(TQueue <T>& q);
	~TQueue();

	void Push(T a);
	int GetSize();
	T Get();
	T See();
	bool IsFull();
	bool IsEmpty();

	//операторы вводы и выводы
};

template<class T>
inline TQueue<T>::TQueue(int n)
{
	mas = new T[n];
	size = n;
	end = 0;
	start = -1;
	count = 0;
}

template<class T>
inline TQueue<T>::TQueue(TQueue<T>& q)
{
	mas = q.mas;
	size = q.size;
	start = q.start;
	end = q.end;
	count = q.count;
}

template<class T>
inline TQueue<T>::~TQueue()
{
	delete[] mas;
}

template<class T>
inline void TQueue<T>::Push(T a)
{
	if (IsFull()) throw - 1;
	start = (start + 1) % size;
	mas[start] = a;
	count++;
}

template<class T>
inline T TQueue<T>::Get()
{
	if (IsEmpty()) throw - 1;
	T res = mas[end];
	end = (end + 1) % size;
	count--;
	return res;
}

template<class T>
inline int TQueue<T>::GetSize()
{
	return count;
}

template<class T>
inline T TQueue<T>::See()
{
	if (IsEmpty()) throw - 1;
	return mas[end];
}

template<class T>
inline bool TQueue<T>::IsFull()
{
	return count == size;
}

template<class T>
inline bool TQueue<T>::IsEmpty()
{
	return size == 0;
}
