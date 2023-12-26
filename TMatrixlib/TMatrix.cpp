// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//
#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__
const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;
#include <iostream>
using namespace std;
/*
// Класс рациональных чисел
class Rational
{
    int nom, dnom;
public:
    Rational()	noexcept
    {
        nom = 0;
        dnom = 1;
    }
    Rational(int a, int b = 1)
    {
        if (b == 0) throw "cant divide by zero";
        nom = a;
        dnom = b;
    }
    Rational(const Rational& z)	noexcept
    {
        nom = z.nom;
        dnom = z.dnom;
    }
    ~Rational()
    {
        nom = 0;
        dnom = 1;
    }
    void rand_fill(int begin, int end)			// Функция заполнения случайными числами от begin до end
    {
        srand((unsigned)time(nullptr));
        double t = (double)rand() / RAND_MAX * (end - begin) + begin; //RAND_MAX = 32767
        double t2 = (double)rand() / RAND_MAX * (end - begin) + begin;
        set((int)t, (int)t2);
    }
    int NOK(int a, int b)			// НОК - Наименьшее общее кратное
    {
        int smallest = (a > b) ? b : a; // если условие правда (a > b), выполняется выражение 1 - count = b,
        // иначе выполняется выражение два 2 - count = a;
        for (int i = 2; i <= smallest; i++) {
            if ((a % i == 0) && (b % i == 0)) {
                return i;
            }
        }
        return 1;
    }
    int NOD(int a, int b)			// НОД - Наибольший общий делитель
    {
        int a1 = abs(a);
        int b1 = abs(b);
        while (a1 > 0 && b1 > 0) {
            if (a1 > b1) {
                a1 %= b1;
            }
            else b1 %= a1;
        }
        return a1 + b1;
    }
    int get_nom()			// Метод получить числитель
    {
        return nom;
    }
    int get_dnom()			// Метод получить знаменатель
    {
        return dnom;
    }
    double get_double()			// Метод перевода в десятичную дробь
    {
        return nom / (double)dnom;
    }
    void set(int a, int b)			// Функция установки числителя и знаменателя
    {
        if (b == 0) throw "cant divide by zero";
        nom = a;
        dnom = b;
    }
    Rational flip()			// Метод "переворота" дроби 
    {
        std::swap(nom, dnom);
        return *this;
    }
    Rational cut()			// Метод сокращения дроби
    {
        int nod = NOD(nom, dnom);
        nom /= nod;
        dnom /= nod;
        return *this;
    }

    Rational operator+(Rational b)
    {
        Rational res;
        res.nom = (nom * b.dnom) + (b.nom * dnom);
        res.dnom = dnom * b.dnom;
        res.cut();
        return res;
    }
    Rational operator-(Rational b)
    {
        Rational res;
        res.nom = (nom * b.dnom) - (b.nom * dnom);
        res.dnom = dnom * b.dnom;
        res.cut();
        return res;
    }
    Rational operator/(Rational b)
    {
        Rational res;
        //b.flip();
        res.nom = nom * b.dnom;
        res.dnom = dnom * b.nom;
        res.cut();
        return res;
    }
    Rational operator*(Rational b)
    {
        Rational res;
        res.nom = nom * b.nom;
        res.dnom = dnom * b.dnom;
        res.cut();
        return res;
    }
    
    // Операторы вывода/ввода
    friend ostream& operator<<(ostream& os, const Rational& z)
    {
        os << "(" << z.nom << ")/(" << z.dnom << ")";
        
        //os << z.nom / z.dnom;
        return os;
    }
    friend istream& operator>>(istream& os, Rational& z)
    {
        cout << "Числитель: ";
        os >> z.nom;
        cout << "Знаменатель: ";
        os >> z.dnom;
        return os;
    }
    // Логические операторы
    bool operator==(Rational& other) noexcept
    {
        return (nom == other.nom && dnom == other.dnom) ? true : false;

    }
    bool operator==(int other) noexcept
    {
        return (nom == other && dnom == 1) ? true : false;
    }
    bool operator!=(Rational& other) noexcept
    {
        return (nom != other.nom || dnom != other.dnom) ? true : false;

    }
    bool operator<(Rational& other)
    {
        double t1 = this->get_double();
        double t2 = other.get_double();
        if (t1 < t2) return true;
        else return false;
    }
    bool operator>(Rational& other)
    {
        double t1 = this->get_double();
        double t2 = other.get_double();
        if (t1 > t2) return true;
        else return false;
    }
    bool operator<=(Rational& other)
    {
        double t1 = this->get_double();
        double t2 = other.get_double();
        if (t1 <= t2) return true;
        else return false;
    }
    bool operator>=(Rational& other)
    {
        double t1 = this->get_double();
        double t2 = other.get_double();
        if (t1 >= t2) return true;
        else return false;
    }
};


// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz <= 0 || sz >= MAX_VECTOR_SIZE)
            throw out_of_range("Vector size should be greater than zero and less than MAX_VECTOR_SIZE");
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + v.sz, pMem);
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        sz = v.sz;
        pMem = nullptr;
        std::swap(pMem, v.pMem);
    }
    ~TDynamicVector()
    {
        if (pMem != nullptr)
			delete[] pMem;

		pMem = nullptr;
		sz = 0;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this == &v)
            return *this;
        if (sz != v.sz)
        {
            if (pMem != nullptr)
                delete[] pMem;
            sz = v.sz;
            pMem = new T[sz];
        }
        std::copy(v.pMem, v.pMem + v.sz, pMem);

        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this == &v) return *this;
        if (pMem != nullptr) {
            delete[] pMem;
            //sz = v.sz;
            pMem = nullptr;
        }
        sz = v.sz;
        std::swap(pMem, v.pMem);
        return *this;
    }
    size_t size() const noexcept { return sz; }
    // индексация
    T& operator[](size_t ind)
    {
        if (ind < 0 || ind >= sz) throw out_of_range("Index out of range!");
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        if (ind < 0 || ind >= sz) throw out_of_range("Index out of range!");
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind < 0 || ind >= sz) throw out_of_range("Index out of range!");
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind < 0 || ind >= sz) throw out_of_range("Index out of range!");
        return pMem[ind];
    }
    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) return false;
        for (size_t i = 0; i < sz; i++) {
            if (pMem[i] != v.pMem[i]) return false;
        }
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) return true;
        for (size_t i = 0; i < sz; i++) {
            if (pMem[i] != v.pMem[i]) return true;   // если хотябы один отличается, то, значит что матрицы разные
        }
        return false;
    }
    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector res(*this);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] += val;
        }
        return res;
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector res(*this);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] -= val;
        }
        return res;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector res(*this);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] *= val;
        }
        return res;
    }
    TDynamicVector operator/(T val)
    {
        TDynamicVector res(*this);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = res.pMem[i] / val;
        }
        return res;
    }
    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz) throw "Different dimensions";
        TDynamicVector res(*this);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] + v.pMem[i];
        }
        return res;
    }
    TDynamicVector operator+=(const TDynamicVector& v)
    {
        if (sz != v.sz) throw "Different dimensions";
        for (size_t i = 0; i < sz; i++) {
            pMem[i] += v.pMem[i];
        }
        return *this;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz) throw "Different dimensions";
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] - v.pMem[i];
        }
        return res;
    }
    TDynamicVector operator-=(const TDynamicVector& v)
    {
        if (sz != v.sz) throw "Different dimensions";
        for (size_t i = 0; i < sz; i++) {
            pMem[i] -= v.pMem[i];
        }
        return *this;
    }
    TDynamicVector operator/(const TDynamicVector& v) {
        if (sz != v.sz) throw "Different dimensions";
        TDynamicVector res = new TDynamicVector();
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] / v.pMem[i];
        }
        return res;
    } 
    TDynamicVector operator*(const TDynamicVector& v) {
        if (sz != v.sz) throw "Different dimensions";
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] * v.pMem[i];
        }
        return res;
    }
    /*T operator*(const TDynamicVector& v)
    {
        if (sz != v.sz) throw "Different dimensions";
        T res = new T();
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] += pMem[i] * v.pMem[i];
        }
        return res;
    }
    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }
    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор >> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz-1; i++)
            ostr << v.pMem[i] << ", "; // требуется оператор<< для типа T
        ostr << v.pMem[v.sz - 1];
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
private:
    TDynamicMatrix Minor( size_t r, size_t c) { // функция которая просто режет матрицу в соотв. с номером строки и столбца
        TDynamicMatrix minor(sz-1);

        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
                minor[i][j] = pMem[i][j];
            for (int j = c; j < sz - 1; j++)
                minor[i][j] = pMem[i][j + 1];
        }

        for (int i = r; i < sz - 1; i++)
        {
            for (int j = c; j < sz - 1; j++)
                minor[i][j] = pMem[i + 1][j + 1];
            for (int j = 0; j < c; j++)
                minor[i][j] = pMem[i + 1][j];
        }
        return minor;
    }
    T Determinant(TDynamicMatrix<T>& m) {

        if (m.sz <= 0 || m.sz >= MAX_MATRIX_SIZE)
            throw out_of_range("Vector size should be greater than zero and less than MAX_MATRIX_SIZE");
        if (m.sz == 1) return m.pMem[0][0];
        if (m.sz == 2) return (m.pMem[0][0] * m.pMem[1][1]) - (m.pMem[0][1] * m.pMem[1][0]); // возвращаем значение в случае размера 2
        else { // рекурсия если размер матрицы больше 2
            T res = T();
            for (size_t j = 0; j < m.sz; j++) // пройдёмся по эл-там первой строчки  (i = 0)
            {
                TDynamicMatrix t(m.sz);
                t[0][j] = m.pMem[0][j] * Determinant(Minor( 0, j));
                res = res + (t[0][j] * std::pow(-1, j));
            }
            return res;
        }
    }
public:
    
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (sz <= 0 || sz >= MAX_MATRIX_SIZE)
            throw out_of_range("Matrix size should be greater than zero and less than MAX_MATRIX_SIZE");
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }
    using TDynamicVector<TDynamicVector<T>>::operator[];
    using TDynamicVector<TDynamicVector<T>>::size;
    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz) return false;
        for (size_t i = 0; i < sz; i++) {
            if (pMem[i] != m.pMem[i]) return false;
        }
        return true;
    }
    bool operator!=(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz) return true;
        for (size_t i = 0; i < sz; i++) {
            if (pMem[i] != m.pMem[i]) return true;
        }
        return false;
    }
    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        if (pMem == nullptr) throw "nullptr error";
        TDynamicMatrix res(*this);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = res.pMem[i] * val;
        }
        return res;
    }
    TDynamicMatrix operator/(const T& val)
    {
        if (pMem == nullptr) throw "nullptr error";
        TDynamicMatrix res(*this);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = res.pMem[i] / val;
        }
        return res;
    }
    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.sz) throw "wrong dimensions";
        TDynamicVector<T> res(sz);
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                res[i] += pMem[i][j] * v[j];
            }
        }
        return res;
    }
    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw "wrong dimensions";
        TDynamicMatrix res(*this);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = res.pMem[i] + m.pMem[i];
        }
        return res;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw "wrong dimensions";
        TDynamicMatrix res(*this);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = res.pMem[i] - m.pMem[i];
        }
        return res;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw "wrong dimensions";
        TDynamicMatrix res(sz);

        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                for (size_t k = 0; k < sz; k++) {
                    res[i][j] = res[i][j] + ( pMem[i][k] * m.pMem[k][j] );
                }
            }
        }
        return res;
    }
    TDynamicMatrix operator/(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw "wrong dimensions";
        TDynamicMatrix t(m);
        return (*this * t.getInvsd());
    }
    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++) {
            istr >> v.pMem[i];
        }
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++) {
            ostr << "|" << v.pMem[i] << "|" << endl;
        }
        return ostr;
    }
    TDynamicMatrix getInvsd() {
        TDynamicMatrix con(*this);
        for (size_t i = 0; i < con.sz; i++)
        {
            for (size_t j = 0; j < con.sz; j++)
            {
                con.pMem[i][j] = Determinant(Minor(i, j));
                con.pMem[i][j] = con.pMem[i][j] * std::pow(-1, i + j);
            }
        }
        T det = Determinant(*this);
        if (det == 0) throw "determinat equals zero, zero division error";
        con = con.getTrspd() / det;
        return con;
    }
    TDynamicMatrix getTrspd() {
        TDynamicMatrix res(*this);
        for (size_t i = 0; i < res.sz; i++) {
            for (size_t j = 0; j < res.sz; j++) {
                std::swap(res.pMem[i][j],pMem[j][i]);
            }
        }
        return res;
    }
};*/
#endif
