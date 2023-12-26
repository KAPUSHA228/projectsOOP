#pragma once
template <class T>
class TQueue {
protected:
	int size;
	int start;
	int end;
	int count;
	T* mas;

public:
	TQueue(int n = 0) {
		if (n < 0) throw "Нельзя создать очередь с отрицательной длиной";
		mas = new T[n];
		size = n;
		end = 0;
		start = 0;
		count = 0;
	}
	TQueue(TQueue <T>& q) {
		size = q.size;
		start = q.start;
		end = q.end;
		count = q.count;
		mas = new T[size];
		for (size_t i = 0; i < size; i++)
		{
			mas[i] = q.mas[i];
		}
	}
	~TQueue() { delete[] mas; }

	void Push(T a) {
		if (IsFull()) throw "Очередь забита";
		mas[end] = a;
		end = (end + 1) % size;
		count++;
	}
	T Pop() {
		if (IsEmpty()) throw "Очередь пуста";
		T res = mas[start];
		start = (start + 1) % size;
		count--;
		return res;
	}
	int GetSize() { return count; }
	T SeeTop() {
		if (IsEmpty()) throw "Очередь пуста";
		return mas[end];
	}
	int TopIndex() { return end; }
	bool IsFull() { return count == size; }
	bool IsEmpty() { return count == 0; }
	TQueue<T>& operator=(const TQueue<T>& q) {
		if (&q == this) return *this;
		size = q.size;
		start = q.start;
		end = q.end;
		count = q.count;
		delete[] mas;
		mas = new T[size];
		for (size_t i = 0; i < size; i++)
		{
			mas[i] = q.mas[i];
		}
		return *this;
	}
	bool operator==(const TQueue<T> q) {
		if (size != q.size || start != q.start || end != q.end || count != q.count)
			return false;
		for (size_t i = start; i < end; i++)
		{
			if (mas[i] != q.mas[i]) return false;
		}
		return true;
	}
	bool operator!=(const TQueue<T> q) {
		if (size != q.size || start != q.start || end != q.end || count != q.count)
			return true;
		for (size_t i = start; i < end; i++)
		{
			if (mas[i] != q.mas[i];) return true;
		}
		return false;
	}
};
