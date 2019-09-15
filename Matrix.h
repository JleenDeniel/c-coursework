#include "pch.h"
#include "Fraction.h"
/// <summary>
/// Матрица
/// </summary>
template<typename T>
class Matrix {
private:
	/// <summary>
	/// элементы марицы
	/// </summary>
	vector<vector<T>>items;
	/// <summary>
	/// количество строк
	/// </summary>
	size_t rows;
	/// <summary>
	/// количество столбцов
	/// </summary>
	size_t columns;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="rows"></param>
	/// <param name="columns"></param>
	void Init(size_t rows, size_t columns) {
		this->rows = rows;
		this->columns = columns;
		for (size_t i = 0; i < rows; i++)
		{
			items.push_back(vector<T>());
			for (size_t j = 0; j < columns; j++)
				items[i].push_back(0);
		}
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="items"></param>	 
	void Init(vector<vector<T> >items) {
		if (items.size() > 0) {
			Init(items.size(), items[0].size());
			for (size_t i = 0; i < rows; i++)
				for (size_t j = 0; j < columns; j++)
					this->items[i][j] = items[i][j];
		}
	}
	/// <summary>
	/// метод проверяющий что значение находится в нормальном диапазоне
	/// </summary>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="value"></param>
	/// <returns></returns>
	bool Check(int from, int to, int value) {
		return (value > from) && (value < to);
	}
	/// <summary>
	/// Получает текущий типа элементов матрицы
	/// </summary>
	/// <returns></returns>
	string GetCurrentType() {
		if (rows > 0 && columns > 0)
			return typeid(this->items[0][0]).name();
		return "NULL";
	}
	/// <summary>
	/// Проверяяет является ли тип элементов матрицы числовым
	/// </summary>
	/// <returns>true - если тип  числовой</returns>
	bool CheckType() {
		if (rows > 0 && columns > 0) {
			vector<string> names = {
				typeid(unsigned char).name(),
				typeid(unsigned int).name(),
				typeid(int).name(),
				typeid(long).name(),
				typeid(double).name(),
				typeid(float).name(),
				"class Fraction<int>",
				"class Fraction<double>"
			};
			for (size_t i = 0; i < names.size(); i++)
				if (names[i] == GetCurrentType())
					return true;
		}
		return false;
	}
public:
	Matrix() {
		Init(0, 0);
	}
	Matrix(size_t n) {
		Init(n, n);
	}
	Matrix(size_t rows, size_t columns)
	{
		Init(rows, columns);
	}
	Matrix(vector<vector<T>>items) {
		Init(items);
	}
	/// <summary>
	/// Получает элемент матрцы
	/// </summary>
	/// <param name="row">строка</param>
	/// <param name="column">столбец</param>
	/// <returns></returns>
	T Get(size_t row, size_t column) {
		if (Check(-1, this->rows, row) && Check(-1, this->columns, column))
			return this->items[row][column];
		else
			return NULL;
	}
	/// <summary>
	/// Устанавливает значение в матрице
	/// </summary>
	/// <param name="row">строка</param>
	/// <param name="column">столбец</param>
	/// <param name="value">значение</param>
	void Set(size_t row, size_t column, T value) {
		if (Check(-1, this->rows, row) && Check(-1, this->columns, column))
			this->items[row][column] = value;
	}
	/// <summary>
	/// Получает минор матрицы по указанным столбцу и строке
	/// </summary>
	/// <param name="row">строка</param>
	/// <param name="column">столбец</param>
	/// <returns></returns>
	Matrix GetMinor(size_t row, size_t column) {
		if (Check(-1, this->rows, row) && Check(-1, this->columns, column)) {
			Matrix minor = Matrix(this->rows - 1, this->columns - 1);
			int currRow = 0, currCol = 0;
			for (size_t i = 0; i < this->rows; i++) {
				for (size_t j = 0; j < this->columns; j++)
					if (i != row && j != column)
						minor.Set(currRow, currCol++, this->Get(i, j));
				if (i != row)
					currRow++;
				currCol = 0;
			}
			return minor;
		}
		return NULL;
	}
	/// <summary>
	/// Получает детерминант матрицы
	/// </summary>
	/// <returns></returns>
	T GetDeterminant() throw (exception) {
		if (rows == 0 && columns == 0)
			return 0;
		if (!CheckType())
		{
			string message = "Тип элементов в матрице не числовой! Текущий тип элементов:" + GetCurrentType();
			throw  exception(message.c_str());
		}
		if (rows != columns) {
			throw exception("Матрица не явлется квадратной!");
		}
		if (rows == 1 && columns == 1)
			return this->Get(0, 0);
		if (rows == 2 && columns == 2) {
			return (items[0][0] * items[1][1]) - (items[0][1] * items[1][0]);
		}
		if (rows > 2 && columns > 2) {
			T sum = 0;
			for (size_t i = 0; i < this->columns; i++)
			{
				T det = this->GetMinor(i, 0).GetDeterminant();
				T v1 = this->Get(i, 0)*det;
				T v2 = v1 * (int)pow(-1, i);
				T v3 = v1 + v2;
				sum = sum + this->Get(i, 0)* this->GetMinor(i, 0).GetDeterminant()*(int)pow(-1, i);
			}
			return sum;
		}
		return NULL;
	}
	/// <summary>
	/// Транспонирует матрицу
	/// </summary>
	/// <returns></returns>
	Matrix GetTransponate() {
		Matrix result = Matrix(this->rows, this->columns);
		for (size_t i = 0; i < this->rows; i++)
			for (size_t j = 0; j < this->columns; j++) {
				result.Set(i, j, this->Get(j, i));
			}
		return result;
	}
	/// <summary>
	/// Представляет матрицу в виде строки
	/// </summary>
	/// <returns></returns>
	string ToString() {
		string result = "";
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < columns; j++) {
				char buffer[20];
				if (this->GetCurrentType() != "class Fraction<int>") {
					if (this->GetCurrentType() == "double")
						sprintf_s(buffer, 20, "%10.2lf", this->Get(i, j));
					else
						sprintf_s(buffer, 20, "%10s", to_string(this->Get(i, j)).c_str());
				}
				else {
					sprintf_s(buffer, 20, "%10s", ((Fraction<int>)this->Get(i, j)).ToString().c_str());
				}
				/*char buffer[20];
				sprintf_s(buffer, 20, "%10s", to_string(this->Get(i, j)).c_str());*/
				result += buffer;
			}
			result += "\n";
		}
		return result;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Matrix GetInverse() {
		T det = this->GetDeterminant();
		if (det != 0) {
			Matrix result = Matrix(this->items);
			for (size_t i = 0; i < result.rows; i++) {
				for (size_t j = 0; j < result.columns; j++) {
					Matrix<T> minor = this->GetMinor(i, j);
					T value = this->GetMinor(i, j).GetDeterminant()*(int)pow(-1, i + j);
					result.Set(i, j, value / det);
				}
			}
			return result.GetTransponate();
		}
		else {
			throw exception("Определитель матрицы равен нулю, обратной не существует!");
		}

	}
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	size_t GetRows() {
		return this->rows;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	size_t GetColumns() {
		return this->columns;
	}

#pragma region Overload
	template<typename T>
	friend bool operator==(Matrix<T> a, Matrix<T> b) {

	}

	template<typename T>
	friend bool operator==(Matrix<T> a, T b) {
		return a.GetDeterminant() == b;
	}

	template<typename T>
	friend bool operator!=(Matrix<T> a, Matrix<T> b) {

	}

	template<typename T>
	friend bool operator!=(Matrix<T> a, T b) {
		return !(a == b);
	}

	template<typename T>
	friend Matrix<T> operator+ (Matrix<T> a, Matrix<T> b) {
		Matrix<T> result;
		if (a.GetRows() == b.GetRows() && a.GetColumns() == b.GetColumns())
		{
			result = Matrix<T>(a.GetRows(), a.GetColumns());
			for (int i = 0; i < a.GetRows(); i++)
				for (int j = 0; j < b.GetColumns(); j++)
					result.Set(i, j, a.Get(i, j) + b.Get(i, j));
		}
		return result;
	}

	template<typename T>
	friend Matrix<T> operator+ (Matrix<T> a, T b) {
		Matrix<T> result;

		result = Matrix<T>(a.GetRows(), a.GetColumns());
		for (int i = 0; i < a.GetRows(); i++)
			for (int j = 0; j < a.GetColumns(); j++)
				result.Set(i, j, a.Get(i, j) + b);

		return result;
	}

	template<typename T>
	friend Matrix<T> operator- (Matrix<T> a, Matrix<T> b) {
		Matrix<T> result;
		if (a.GetRows() == b.GetRows() && a.GetColumns() == b.GetColumns())
		{
			result = Matrix<T>(a.GetRows(), a.GetColumns());
			for (int i = 0; i < a.GetRows(); i++)
				for (int j = 0; j < b.GetColumns(); j++)
					result.Set(i, j, a.Get(i, j) - b.Get(i, j));
		}
		return result;
	}

	template<typename T>
	friend Matrix<T> operator- (Matrix<T> a, T b) {
		Matrix<T> result;

		result = Matrix<T>(a.GetRows(), a.GetColumns());
		for (int i = 0; i < a.GetRows(); i++)
			for (int j = 0; j < a.GetColumns(); j++)
				result.Set(i, j, a.Get(i, j) - b);

		return result;
	}

	template<typename T>
	friend Matrix<T> operator/ (Matrix<T> a, T b) {
		Matrix<T> result;

		result = Matrix<T>(a.GetRows(), a.GetColumns());
		for (int i = 0; i < a.GetRows(); i++)
			for (int j = 0; j < a.GetColumns(); j++)
				result.Set(i, j, a.Get(i, j) / b);

		return result;
	}

	template<typename T>
	friend Matrix<T> operator* (Matrix<T> a, T b) {
		Matrix<T> result;
		result = Matrix<T>(a.GetRows(), a.GetColumns());
		for (int i = 0; i < a.GetRows(); i++)
			for (int j = 0; j < a.GetColumns(); j++)
				result.Set(i, j, a.Get(i, j) * b);

		return result;
	}

	template<typename T>
	friend Matrix<T> operator* (T b, Matrix<T> a) {
		return a * b;
	}

	template<typename T>
	friend Matrix<T> operator* (Matrix<T> a, Matrix<T> b) {
		Matrix<T> result;
		if (a.GetColumns() == b.GetRows()) {
			result = Matrix<T>(a.GetRows(), b.GetColumns());
			for (int i = 0; i < result.GetRows(); i++) {
				for (int j = 0; j < result.GetColumns(); j++) {
					T sum = 0;
					for (int k = 0; k < a.GetColumns(); k++) {
						T item = (a.Get(i, k) * b.Get(k, j));
						sum = sum + item;
					}
					result.Set(i, j, sum);
				}
			}
		}
		return result;
	}

	template<typename T>
	friend ostream& operator<< (ostream& out, Matrix<T> a) {
		out << a.ToString();
		return out;
	}

	template<typename T>
	friend istream& operator>> (istream& in, Matrix<T> &a) {
		int rows, columns;
		in >> rows;
		in >> columns;
		a = Matrix<T>(rows, columns);
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++) {
				T value = 0;
				in >> value;
				a.Set(i, j, value);
			}
		return in;
	}
#pragma endregion Overloads
};