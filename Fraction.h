#pragma once
template<typename T>
class Fraction {
private:
	/// <summary>
	/// числитель
	/// </summary>
	T numerator;
	/// <summary>
	/// делитель
	/// </summary>
	T denominator;
	T GetGCD(T a, T b) {
		while (a != b)
		{
			if (a > b)
				a -= b;
			if (a < b)
				b -= a;
		}
		return a;
	}
public:
	Fraction() {
		if (typeid(T) == typeid(double) || typeid(T) == typeid(int) || typeid(T) == typeid(float)) {
			numerator = 0;
			denominator = 0;
		}
	}
	/// <summary>
	/// Создает дробь с указанными значениями
	/// </summary>
	/// <param name="numerator">числитель</param>
	/// <param name="denominator">знаменатель</param>
	Fraction(T numerator, T denominator) {
		this->numerator = numerator;
		this->denominator = denominator;
	}
	Fraction(T numerator) {
		this->numerator = numerator;
		this->denominator = 1;
	}
	void SetNumerator(T numerator) {
		this->numerator = numerator;
	}
	T GetNumerator() {
		return this->numerator;
	}
	void SetDenominator(T denominator) {
		this->denominator = denominator;
	}
	T GetDenominator() {
		return this->denominator;
	}

	Fraction<T> Reduce() {
		T gcd = this->GetGCD(this->GetNumerator(), this->GetDenominator());
		return Fraction<T>(this->GetNumerator() / gcd, this->GetDenominator() / gcd);
	}

	template<typename T>
	Fraction<T> operator+ (Fraction<T> a) {
		Fraction<T> result = Fraction<T>();
		if (this->denominator == a.GetDenominator()) {
			result.SetNumerator(this->numerator + a.GetNumerator());
			result.SetDenominator(this->denominator);
		}

		else {
			T gcd = GetGCD(this->denominator, a.GetDenominator());
			result.SetNumerator((a.GetDenominator() / gcd)*this->numerator + (this->denominator / gcd)*a.GetNumerator());
			result.SetDenominator(a.GetDenominator()*this->denominator / gcd);
		}
		return result;
	}

	/*template<typename T>
	friend Fraction<T> operator+ (Fraction<T> a, Fraction<T> b) {
		Fraction<T> result = Fraction<T>();
		if (b.denominator == a.GetDenominator()) {
			result.SetNumerator(b.numerator + a.GetNumerator());
			result.SetDenominator(b.denominator);
		}
		else {
			T gcd = a.GetGCD(b.denominator, a.GetDenominator());
			result.SetNumerator((a.GetDenominator() / gcd)*b.numerator + (b.denominator / gcd)*a.GetNumerator());
			if (b.denominator > a.GetDenominator())
				result.SetDenominator(b.denominator);
			else
				result.SetDenominator(a.GetDenominator());
		}
		return result;
	}*/

	template<typename T>
	friend Fraction<T> operator+= (Fraction<T> a, Fraction<T> b) {
		return a + b;
	}

	/*template<typename T>
	Fraction<T> operator+= (Fraction<T> a) {
		return  a + *this;
	}*/

	template<typename T>
	Fraction<T> operator- (Fraction<T> a) {
		Fraction<T> result = Fraction<T>();
		if (this->denominator == a.GetDenominator()) {
			result.SetNumerator(this->numerator - a.GetNumerator());
			result.SetDenominator(this->denominator);
		}
		else {
			T gcd = GetGCD(this->denominator, a.GetDenominator());
			result.SetNumerator((a.GetDenominator() / gcd)*this->numerator - (this->denominator / gcd)*a.GetNumerator());
			if (this->denominator > a.GetDenominator())
				result.SetDenominator(this->denominator);
			else
				result.SetDenominator(a.GetDenominator());
		}

		return result;
	}

	template<typename T>
	friend Fraction<T> operator* (Fraction<T> a, Fraction<T> b) {
		Fraction<T> result = Fraction<T>();
		result.SetNumerator((b.GetNumerator()) * (a.GetNumerator()));
		result.SetDenominator((b.GetDenominator()) * (a.GetDenominator()));

		return result;
	}

	friend Fraction<T> operator* (T a, Fraction<T> b) {
		Fraction<T> result = Fraction<T>(a);
		return b * result;
	}
	friend Fraction<T> operator* (Fraction<T> b, T a) {
		Fraction<T> result = Fraction<T>(a);
		return b * result;
	}

	template<typename T>
	Fraction<T> operator/ (Fraction<T> a) {
		Fraction<T> result = Fraction<T>();
		result.SetNumerator((this->numerator) * (a.GetDenominator()));
		result.SetDenominator((this->denominator) * (a.GetNumerator()));
		return result;
	}

	template<typename T>
	friend bool operator== (Fraction<T> a, Fraction<T> b) {
		return (b.GetNumerator()) == (a.GetNumerator()) && (b.GetDenominator()) == (a.GetDenominator());
	}

	template<typename T>
	friend bool operator!= (Fraction<T> a, Fraction<T> b) {
		return !(b == a);
	}

	template<typename T>
	friend bool operator!= (T a, Fraction<T> b) {
		Fraction<T> temp = Fraction<T>(a, 1);
		return b == temp;
	}

	template<typename T>
	friend bool operator!= (Fraction<T> a, T b) {
		Fraction<T> temp = Fraction<T>(b);
		return !(a == temp);
	}

	template<typename T>
	friend ostream& operator<< (ostream& out, Fraction<T> a) {
		out << a.ToString();
		return out;
	}

	template<typename T>
	friend istream& operator>> (istream& in, Fraction<T> &a) {
		in >> a.numerator;
		in >> a.denominator;
		return in;
	}

	operator string &()
	{
		return ToString();
	}

	string ToString() {
		return  to_string(numerator) + "/" + to_string(denominator);
	}
};