#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <cassert>

class Matrix
{
private:
	unsigned int rows;
	unsigned int cols;
	std::vector <std::vector<double>> matrix;

public:
	
	Matrix(unsigned int r, unsigned int c) : rows(r), cols(c), matrix(r, std::vector<double>(c,0.0))  {}; //заранее заполненая нулями матрица r*c
	Matrix() : rows(0), cols(0) {};
	~Matrix() = default;

	std::vector <std::vector<double>>& getMatrix();
	unsigned int getRow() { return rows; }
	unsigned int getCols() { return cols; }

	void output() const;
	void input();
	Matrix residueRingSum(const Matrix& other, int modulus) const;	//кольцо вычетов для сложения
	Matrix residueRingMul(const Matrix& other, int modulus) const;  //кольцо вычетов для умножения

	//перегрузка
	Matrix operator+(const Matrix& other) const;			//сложение матриц
	Matrix operator-(const Matrix& other) const;			//вычитание матриц
	Matrix operator*(double scalar);						//умножение матрицы на число (т.н скаляр)
	Matrix operator*(const Matrix& other) const;			//умножение матрицы на другую матрицу
};