#pragma once
// Каждый узел в связанном списке хранит ненулевой член многочлена, включая поля данных коэффициента и экспоненты 
class TMonom
{
private:
	double coef;
	int ind;
public:
	TMonom() {
		coef = 0;
		ind = 0;
	}

	TMonom(double _coef, int degX, int degY, int degZ) {
		coef = _coef;
		ind = 100 * degX + 10 * degY + degZ;
	}

	void SetCoef(int cval) { coef = cval; }
	int GetCoef(void) { return coef; }

	void SetIndex(int ival) { ind = ival; }
	int GetIndex(void) { return ind; }


	bool operator==(const TMonom& other) {
		if (coef != other.coef) return false;
		if (ind != other.ind) return false;
		return true;
	}

	bool operator!=(const TMonom& other) {
		if (coef != other.coef) return true;
		if (ind != other.ind) return true;
		return false;
	}

	bool operator>(const TMonom& other) {
		if (coef < other.coef) return false;
		if (ind < other.ind) return false;
		return true;
	}

	bool operator<(const TMonom& other) {
		if (coef > other.coef) return false;
		if (ind > other.ind) return false;
		return true;
	}



};