#pragma once
#include "pch.h"

template <class T>
/// <summary>
/// Полином
/// </summary>
class Polynom {
private:
#pragma region Fields
	/// <summary>
/// степень полинома
/// </summary>
	size_t length;
	/// <summary>
	/// коэффициенты
	/// </summary>
	vector<T> items;
	/// <summary>
	/// значение независимой переменной
	/// </summary>
	T x;
#pragma endregion
#pragma region Methods
	vector<T> Reverse(vector<T> items) {
		vector<T> result;
		for (int i = items.size() - 1; i >= 0; i--)
			result.push_back(items[i]);
		return result;
	}
	
	void Init(T x, vector<T> items, size_t length) {
		this->x = x;
		this->length = length;
		this->items = Reverse(items);
	}
	
	void Init(vector<T> items, size_t length) {
		Init(0, items, length);
	}
	
	void Init(vector<T> items) {
		Init(0, items, items.size());
	}
	
	void Init(size_t length) {
		Init(0, vector<T>(length), length);
	}
	
	T Power(T value, size_t power) {
		T result = 1;
		while (power > 0) {
			result = result * value;
			power--;
		}
		return result;
	}
#pragma endregion
public:
#pragma region Constructors
	
	Polynom() {
		Init(0);
	}
	
	Polynom(T x, size_t length) {
		Init(x, length);
	}
	
	Polynom(size_t length) {
		Init(length);
	}
	
	Polynom(vector<T> items) {
		Init(items);
	}
	
	Polynom(vector<T> items, size_t length) {
		Init(items, length);
	}
	
	~Polynom() {

	}
#pragma endregion
#pragma region GET
	
	T* Get(int i) {
		if (Check(-1, this->items.size(), i))
			return &this->items[i];
		return NULL;
	}
	
	T GetValue(T value) {
		T result = 0;
		for (int i = 0; i < this->GetLength(); i++)
			result = result + (this->Get(i) * Power(value, i));
		return result;
	}
	
	Polynom<T> GetDerivative() {
		vector<T> copy = this->items;
		for (int i = 0; i < copy.size(); i++)
			copy[i] = copy[i] * i;
		copy.erase(copy.begin());
		return Polynom<T>(Reverse(copy));
	}
	
	size_t GetLength() {
		return this->items.size();
	}
	
	
#pragma endregion
#pragma region SET
	
	void Set(int i, T value) {
		if (Check(-1, items.size(), i))
			this->items[i] = value;
	}
#pragma endregion
#pragma region Other
	
	bool Check(int from, int to, int value) {
		return (value > from) && (value < to);
	}
	
	void PushBack(T value) {
		this->items.push_back(value);
	}
	
	void PushFront(T value) {
		this->items.insert(this->items.begin(), value);
	}
	
	vector<Polynom<T>> Division(Polynom<T> a, Polynom<T> b) {
		vector<Polynom<T>> result(2);
		if (a == b)
		{
			result[0].PushBack(1);
		}
		if (a > b) {
			Polynom<T> rest = a;

			vector<T> quotientItems;
			while (rest > b) {
				T aFront = *rest.Get(rest.GetLength() - 1);
				T bFront = *b.Get(b.GetLength() - 1);
				T k = aFront / bFront;
				int dLength = rest.GetLength() - b.GetLength();
				vector<T> items;
				for (int i = 0; i < dLength; i++)
					items.push_back(0);
				items.push_back(k);
				Polynom<T> multiplier = Polynom<T>(Reverse(items));
				//quotient = quotient + multiplier;
				for (int i = 0; i < items.size(); i++)
					quotientItems.push_back(items[i]);
				Polynom<T> divisor = b * multiplier;
				rest = rest - divisor;
			}
			Polynom<T> quotient = Polynom<T>(quotientItems);
			quotient.Update();
			result[0] = quotient;
			result[1] = rest;
		}
		else
		{
			result[0].PushBack(0);
		}
		return result;
	}
	/// <summary>
	/// Удаляет незначащие нули
	/// </summary>
	void Update() {
		vector<T> copy;
		for (int i = 0; i < this->items.size(); i++)
			if (this->items[i] != 0)
				copy.push_back(this->items[i]);
		this->items = copy;
	}
#pragma endregion
#pragma region Operators
	template <typename T>
	friend  istream&  operator >> (istream &in, Polynom<T> &a) {
		size_t length;
		in >> length;
		vector<T> items;
		for (int i = 0; i < length; i++) {
			T value;
			in >> value;
			items.push_back(value);
		}
		a = Polynom<T>(items);
		return in;
	}
	template <typename T>
	friend  ostream&  operator << (ostream &out, Polynom<T> &a) {
		for (int i = a.items.size() - 1; i >= 0; i--) {
			if (a.items[i] != 0) {
				if (i == a.items.size() - 1)
					out << a.items[i] << "*x^" << i;
				else {
					if (a.items[i] > 0)
						out << '+';
					out << a.items[i];
					if (i > 0)
						out << "*x^" << i;
				}
			}
		}
		return out;
	}
	template <typename T>
	friend Polynom<T> operator+ (Polynom<T> a, Polynom<T> b) {
		Polynom<T> result;
		while (a.GetLength() > b.GetLength())
			b.PushFront(0);
		while (a.GetLength() < b.GetLength())
			a.PushFront(0);
		for (int i = 0; i < a.GetLength(); i++)
			result.PushBack(a.items[i] + b.items[i]);
		return result;
	}
	template <typename T>
	friend Polynom<T> operator- (Polynom<T> a, Polynom<T> b) {
		Polynom<T> result;
		while (a.GetLength() > b.GetLength())
			b.PushFront(0);
		while (a.GetLength() < b.GetLength())
			a.PushFront(0);
		for (int i = 0; i < a.GetLength(); i++)
			result.PushBack(a.items[i] - b.items[i]);
		result.Update();
		return result;
	}
	template <typename T>
	friend Polynom<T> operator* (Polynom<T> a, T b) {
		Polynom<T> result;
		for (int i = 0; i < a.GetLength(); i++)
			result.Set(i, a.items[i] * b);
		return result;
	}
	template <typename T>
	friend Polynom<T> operator* (Polynom<T> a, Polynom <T> b) {
		Polynom<T> result;
		for (int i = 0; i < a.GetLength(); i++) {
			Polynom<T> item(a.GetLength() + b.GetLength() - 1);
			for (int j = 0; j < b.GetLength(); j++)
			{
				T itemA = *(a.Get(i));
				T itemB = *(b.Get(j));
				item.Set(i + j, itemA*itemB);
			}
			result = result + item;
		}
		return result;
	}
	template <typename T>
	friend Polynom<T> operator/ (Polynom<T> a, T b) {
		Polynom<T> result;
		for (int i = 0; i < a.GetLength(); i++) {
			result.Set(i, a.items[i] / b);
		}
		return result;
	}
	template <typename T>
	Polynom<T> operator/ (Polynom<T> a) {
		return this->Division(*this, a)[0];
	}
	template <typename T>
	Polynom<T> operator% (Polynom<T> a) {
		return this->Division(*this, a)[1];
	}
	template <typename T>
	friend bool operator> (Polynom<T> a, Polynom<T> b) {
		if (a.GetLength() > b.GetLength())
			return true;
		if (a.GetLength() < b.GetLength())
			return false;
		if (a.GetLength() == b.GetLength())
			for (int i = 0; i < a.GetLength(); i++)
				if (*a.Get(i) > *b.Get(i))
					return true;
		return false;
	}
	template <typename T>
	friend bool operator< (Polynom<T> a, Polynom<T> b) {
		if (a.GetLength() < b.GetLength())
			return true;
		if (a.GetLength() > b.GetLength())
			return false;
		if (a.GetLength() == b.GetLength())
			for (int i = 0; i < a.GetLength(); i++)
				if (a.Get(i) < b.Get(i))
					return true;
		return false;
	}
	template <typename T>
	friend bool operator== (Polynom<T> a, Polynom<T> b) {
		if (a.GetLength() == b.GetLength()) {
			for (int i = 0; i < a.GetLength(); i++)
				if (*a.Get(i) != *b.Get(i))
					return false;
			return true;
		}
		return false;
	}
#pragma endregion
};
