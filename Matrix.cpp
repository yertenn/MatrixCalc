#include "Matrix.h"

void Matrix::input() {
	for (auto r = 0; r < rows; ++r) {
		for (auto c = 0; c < cols; ++c) {
			double number;
			std::cin >> number;
			matrix[r][c]=number;
		}
	}
}

Matrix Matrix::residueRingSum(const Matrix& other, int modulus) const
{
	assert(modulus >= 2);
	Matrix answer(rows, cols);
	if (rows != other.rows || cols != other.cols) {
		throw std::invalid_argument("Матрицы должны быть одинакового размера!");
	}
	else {
		for (auto r = 0; r < answer.rows; ++r) {
			for (auto c = 0; c < answer.cols; ++c) {
				int sum = static_cast<int>(matrix[r][c] + other.matrix[r][c]);  //приводим число из плавающей точки в целое
				answer.matrix[r][c] = (sum % modulus + modulus) % modulus;		//делаем число по модулю Zn, 	
			}
		}
	}
	return answer;
}

Matrix Matrix::residueRingMul(const Matrix& other, int modulus) const
{
	assert(modulus >= 2);
	Matrix answer(rows, other.cols);
	if (cols != other.rows) {
		throw std::invalid_argument("матрицы не могут перемножиться");
	}
	else {
		for (auto r = 0; r < rows; ++r) {
			for (auto c = 0; c < other.cols; ++c) {
				for (auto k = 0; k < cols; ++k) {
					answer.matrix[r][c] += (static_cast<int>(matrix[r][k]) * static_cast<int>(other.matrix[k][c])) % modulus; 
				}
				answer.matrix[r][c] = static_cast<int>(static_cast<int>(answer.matrix[r][c]) % modulus + modulus) % modulus; //
			}
		}
	}
	return answer;	
}

void Matrix::output() const {
	for (auto r : matrix) {
		for (auto c : r) {
			std::cout << c << ' ';
		}
		std::cout << std::endl;
	}
}

Matrix Matrix::operator+(const Matrix& other) const {
	Matrix answer(rows, cols);
	if (rows != other.rows || cols != other.cols) {
		throw "other matrix has another size";
	}
	else {
		for (auto r = 0; r < matrix.size(); ++r) {
			for (auto c = 0; c < matrix[r].size(); ++c) {
				answer.matrix[r][c] = matrix[r][c] + other.matrix[r][c];//каждый элемент первой матрицы складывается с соответству.щим элементом из второй матрицы
			}
		}
	}
	return answer;
}

Matrix Matrix::operator-(const Matrix& other) const {
	Matrix answer(rows, cols);
	if (rows != other.rows || cols != other.cols) {
		throw "other matrix has another size";
	}
	else {
		for (auto r = 0; r < matrix.size(); ++r) {
			for (auto c = 0; c < matrix[r].size(); ++c) {
				answer.matrix[r][c] = matrix[r][c] - other.matrix[r][c]; //каждый элемент второй матрицы вычитается из соответственнгого элемента первой
			}
		}
	}
	return answer;
}

Matrix Matrix::operator*(double scalar) 
{
	for (auto i = 0; i < rows; ++i) {
		for (auto j = 0; j < cols; ++j) {
			matrix[i][j] *= scalar; //каждый элемент матрицы умножается на скаляр
		}
	}

	return *(this);
}

Matrix Matrix::operator*(const Matrix& other) const
{
	if (cols != other.rows) {
		throw "Матрицы невозможно умножить";
	}
	Matrix answer(rows, other.cols);
	for (auto r = 0; r < rows; ++r) {
		for (auto c = 0; c < other.cols; ++c) {
			for (auto k = 0; k < cols; ++k) {
				answer.matrix[r][c] += matrix[r][k] * other.matrix[k][c]; // A(
			}
		}
	}

	return answer;
}