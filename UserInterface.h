#pragma once

#include <QMainWindow>
#include <qtablewidget.h>
#include <qheaderview.h>
#include "ui_UserInterface.h"
#include "Matrix.h"


class UserInterface : public QMainWindow
{
	Q_OBJECT

public:
	UserInterface(QWidget *parent = nullptr);
	~UserInterface();

private:
	std::unique_ptr<Ui::UserInterfaceClass> ui;		//указатель на юзеринтерфейс(умный, но как я понял нет разницы в qt)
	std::unique_ptr<QTableWidget> answerWidget;		//указатель на окно с матрицей результата

	QVector <QTableWidget*> matrixVec;				//вектор виджетов
	QVector <Matrix> matrices;						//вектор самих матриц



public slots:
	void addMatrixClicked();
	void updateMatrix(QTableWidget* sender,int row, int col);
	void sumMatrices();
	void diffMatrices();
};
