#pragma once
#include <iostream>
using namespace std;


template<class T>
struct TNode
{
	T value;
	TNode<T>* pNext;
public:
	TNode() {
		value = T();
		this->pNext = nullptr;
	}
	TNode(const T& data) {
		this->value = data;
		this->pNext = nullptr;
	}
	TNode(const TNode<T>& node) {
		this->value = node.value;
		this->pNext = node.pNext;
	}
	void SetValue(T val) { this->value = val; }
	void SetPointer(TNode<T>* ptr) { this->pNext = ptr; }
	TNode<T>* GetPointer() { return this->pNext; }
	T* GetValue() { return &this->value; }
};


template<class T>
class TList
{
protected:
	TNode<T>* pFirst; // первое звено
	TNode<T>* pLast; // последнее звено
	TNode<T>* pCurrent; // текущее звено
	TNode<T>* pPrevious; // звено перед текущим
	TNode<T>* pStop; // указатель на конец
	int length; // количество звеньев в списке
public:
	TList();
	~TList();
	TList(const TList<T>& l);
	int GetLength() { return length; }
	bool IsEmpty() { return pFirst == nullptr; } // проверка на пустоту

	// вставка звеньев
	void InsertFirst(T item); // перед первым
	void InsertCurrent(T item); // перед текущим 
	void InsertNextCurrent(T item); // после текущего
	void InsertLast(T item);  // вставить последним 
	// удаление звеньев
	void DeleteFirst(); // удалить первое звено 
	void DeleteCurrent(); // удалить текущее звено
	void GoNext(); // сдвиг вправо текущего звена
	void Reset(); // установить на начало списка
	bool IsEnd();  // проверка на завершённость
	T GetCurrentItem();// получить текущий
	TNode<T>* GetCurrentItemPointer();// получить указатель текущего
	void SetCurrentItem(T item) { pCurrent->value = item; }// установить текущий
	void SetCurrentAt(int ind);// установить текущий по индексу
	TList<T>& operator=(const TList<T>& other);// присваивание
	bool operator==(const TList<T>& other);// оператор ==
	bool operator!=(const TList<T>& other);// оператор !=
};

template <class T>
TList<T>::TList()
{
	pFirst = nullptr;
	pLast = nullptr;
	pCurrent = nullptr;
	pPrevious = nullptr;
	pStop = nullptr;
	length = 0;
}

template <class T>
TList<T>::~TList()
{
	/*while (pFirst != nullptr) {
		TNode<T>* t = pFirst;
		pFirst = pFirst->GetPointer();
		delete t;
	}*/
}

template<class T>
inline TList<T>::TList(const TList<T>& other)
{
	TNode<T>* otherptr = other.pFirst;
	if (other.pFirst != nullptr) {
		pFirst = new TNode<T>(other);
		TNode<T>* nextptr = pFirst;
		while (otherptr->pNext != nullptr) {
			TNode<T>* t = new TNode<T>(otherptr->pNext);
			nextptr->SetPointer(t);
			otherptr = otherptr->pNext;
			nextptr = nextptr->pNext;
		}
	}
	else { this->pFirst = other.pFirst }
	this->length = other.length;
	this->pCurrent = other.pCurrent;
	this->pLast = other.pLast;
	this->pPrevious = other.pPrevious;
	this->pStop = other.pStop;
}

template<class T>
TList<T>& TList<T>::operator=(const TList<T>& other)
{
	TNode<T>* otherptr = other.pFirst;
	if (other.pFirst != nullptr) {
		pFirst = new TNode<T>(other);
		TNode<T>* nextptr = pFirst;
		while (otherptr->pNext != nullptr) {
			TNode<T>* t = new TNode<T>(otherptr->pNext);
			nextptr->SetPointer(t);
			otherptr = otherptr->pNext;
			nextptr = nextptr->pNext;
		}
	}
	else { this->pFirst = other.pFirst; }
	this->length = other.length;
	this->pCurrent = other.pCurrent;
	this->pLast = other.pLast;
	this->pPrevious = other.pPrevious;
	this->pStop = other.pStop;

	return *this;
}

template<class T>
bool TList<T>::operator==(const TList<T>& other)
{
	if (this->length != other.length || this->pCurrent != other.pCurrent || this->pLast != other.pLast || this->pPrevious != other.pPrevious
		|| this->pStop != other.pStop || this->pFirst || other.pFirst) return false;

	TNode<T>* ptr1 = this->pFirst;
	TNode<T>* ptr2 = other.pFirst;

	while (ptr1 != nullptr && ptr2 != nullptr)
	{
		if (ptr1->value != ptr2->value()) return false;
		ptr1 = ptr1->pNext;
		ptr2 = ptr2->pNext;
	}
	return true;
}

template<class T>
bool TList<T>::operator!=(const TList<T>& other)
{
	if (this->length != other.length || this->pCurrent != other.pCurrent || this->pLast != other.pLast || this->pPrevious != other.pPrevious
		|| this->pStop != other.pStop || this->pFirst || other.pFirst) return true;

	TNode<T>* ptr1 = this->pFirst;
	TNode<T>* ptr2 = other.pFirst;

	while (ptr1 != nullptr && ptr2 != nullptr)
	{
		if (ptr1->value != ptr2->value()) return true;
		ptr1 = ptr1->pNext;
		ptr2 = ptr2->pNext;
	}
	return false;
}

template <class T>
void TList<T>::InsertFirst(T item)
{
	TNode<T>* newNode = new TNode<T>(item);
	if (pFirst == nullptr) { // Если список пуст, новое звено становится первым и последним
		pStop = new TNode<T>;
		pFirst = newNode;
		pLast = newNode;
		pCurrent = newNode;
	}
	else {
		//Вставляем новое звено перед первым
		newNode->SetPointer(pFirst);
		pFirst = newNode;
	}
	length++;
}

template <class T>
void TList<T>::InsertLast(T item)
{
	TNode<T>* newNode = new TNode<T>(item);

	if (pFirst == nullptr) {
		pStop = new TNode<T>;
		pFirst = newNode;
		pCurrent = newNode;
	}
	else {
		pLast->SetPointer(newNode);
	}
	pLast = newNode;
	length++;
}

template <class T>
void TList<T>::InsertCurrent(T item)
{
	TNode<T>* newNode = new TNode<T>(item);

	if (pFirst == pCurrent) {
		newNode->SetPointer(pFirst);
		pFirst = newNode;
		pPrevious = newNode;
	}
	else {
		pPrevious->SetPointer(newNode);
		newNode->SetPointer(pCurrent);
	}
	length++;
}

template <class T>
void TList<T>::InsertNextCurrent(T item)
{
	TNode<T>* newNode = new TNode<T>(item);

	if (pLast == pCurrent) {
		pLast->SetPointer(newNode);
		pLast = newNode;
	}
	else {
		newNode->SetPointer(pCurrent->GetPointer());
		pCurrent->SetPointer(newNode);
	}
	length++;
}

template <class T>
void TList<T>::DeleteFirst()
{
	if (pFirst == nullptr) {
		// Если список пуст, ничего не делаем
		return;
	}
	if (pFirst == pCurrent) {
		pCurrent = pCurrent->GetPointer();
	}
	TNode<T>* temp = pFirst;
	pFirst = pFirst->GetPointer();
	delete temp; // Освобождаем память звена
	if (pFirst == nullptr) {
		// Если после удаления первого звена список становится пустым, обновляем указатели на последнее и конечное звено
		pStop = nullptr;
		pLast = nullptr;
	}

	length--;
}

template <class T>
void TList<T>::DeleteCurrent()
{
	if (pCurrent == nullptr || pFirst == nullptr) {
		// Если текущее звено не установлено или список пуст ничего не делаем
		return;
	}

	if (pCurrent == pFirst) {
		// Если текущее звено является первым, удаляем первое звено
		DeleteFirst();
	}
	else {
		pPrevious->SetPointer(pCurrent->GetPointer());
		pCurrent = pCurrent->GetPointer();
		length--;
	}
	if (pCurrent == pStop) pStop = pPrevious;
	if (pCurrent == pLast) pLast = pPrevious;
}

template <class T>
T TList<T>::GetCurrentItem()
{
	if (pCurrent == nullptr)
		throw "current element is Null";
	if (pFirst == nullptr)
		throw "the list is empty";
	return *pCurrent->GetValue();
}

template <class T>
TNode<T>* TList<T>::GetCurrentItemPointer()
{
	if (pCurrent == nullptr)
		throw "current element is Null";
	if (pFirst == nullptr)
		throw "the list is empty";
	return pCurrent;
}

template <class T>
void TList<T>::Reset()
{
	if (pCurrent == pFirst) return;
	pCurrent = pFirst;
	pPrevious = nullptr;
}

template <class T>
void TList<T>::GoNext()
{
	if (IsEmpty()) throw "SimplyList is empty";
	if (IsEnd()) throw "There is no elements to go to";
	pPrevious = pCurrent;
	pCurrent = pCurrent->GetPointer();
}

template <class T>
bool TList<T>::IsEnd()
{
	return pCurrent->GetPointer() == pStop;
}

template <class T>
void TList<T>::SetCurrentAt(int ind) {
	if (ind < 0 || ind >= length) throw "wrong index";
	this->Reset();
	for (size_t i = 0; i < ind; i++) GoNext();
}