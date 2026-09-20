#include "UserInterface.h"

UserInterface::UserInterface(QWidget *parent)
	: QMainWindow(parent)
{
	ui = std::make_unique<Ui::UserInterfaceClass>();	//инициализируем юник поинтер
	ui.get()->setupUi(this);							//кстати .get() можно не писать, просто при нажатиии на . не по€вл€етс€ -> и нужно эти два символа вводить руками, а get(). сразу вызывает ->



	//сигналы - слоты
	connect(ui.get()->pushButton, &QPushButton::clicked, this, &UserInterface::addMatrixClicked);	//сигнал на нажатие кнопки - слот - функци€ добавлени€ матрицы
	connect(ui->sumButton, &QPushButton::clicked, this, &UserInterface::sumMatrices);				//сигнал на нажатие кнопки суммы
	connect(ui->differenceButton, &QPushButton::clicked, this, &UserInterface::diffMatrices);				//сигнал на нажатие кнопки суммы
}
UserInterface::~UserInterface() {} 

void UserInterface::updateMatrix(QTableWidget* sender,int row, int col)	//функци€ обновл€ет значение в €чейке текущей матрицы 
{
	auto item = sender->item(row, col)->text().toDouble();				//получаем число из €чейки текущей таблицы
	for (auto i = 0; i < matrixVec.size(); ++i) {						//проходим по вектору tablewidgets
		if (matrixVec[i] == sender) {									//сравниваем та ли эта матрица(виджет)
			matrices[i].getMatrix()[row][col] = item;					//т.к tablewidgets и matrix синхронизированы по индексам, то tablewidget[i] = matrix[i]
			qDebug() << item;											//отладка
			break;
		}
	}
	
}

void UserInterface::sumMatrices()//функци€ дл€ суммы матриц
{
	if (matrixVec.size() == 2) {													//пока что действи€ можно будет делать с двум€ матрицами
		Matrix answer = matrices[0] + matrices[1];									//сумма матриц 
		answerWidget = std::make_unique<QTableWidget>();							//передача в указатель виджета без родител€, чтобы оно было отдельным окном
		
		answerWidget->setRowCount(answer.getRow());									//количество строк
		answerWidget->setColumnCount(answer.getCols());								//количество столбцов

		QFont font("Consolas", 10);
		font.setBold(false);

		for (auto i = 0; i < answer.getRow(); ++i) {								//цикл по строкам
			for (auto j = 0; j < answer.getCols(); ++j) {							//по столбцам
				QTableWidgetItem* item = new QTableWidgetItem(QString::number(answer.getMatrix()[i][j]));	//число, которое беретс€ из матрицы суммы и передаетс€ в виджет
				item->setFont(font);
				answerWidget->setItem(i, j, item);											
			}
		}
		answerWidget->resize(matrixVec[0]->size());
		answerWidget->verticalHeader()->setDefaultSectionSize(5);					//размер €чеек 5 на 5, чтобы матрица выгл€дела квадратной
		answerWidget->horizontalHeader()->setDefaultSectionSize(5);
		answerWidget->show();
	}
	else {
		qDebug() << "error: need 2 matrices";
	}
}

void UserInterface::diffMatrices()//функци€ дл€ разности матриц
{
	if (matrixVec.size() == 2) {													
		Matrix answer = matrices[0] - matrices[1];									
		answerWidget = std::make_unique<QTableWidget>();							

		answerWidget->setRowCount(answer.getRow());									
		answerWidget->setColumnCount(answer.getCols());								

		QFont font("Consolas", 10);
		font.setBold(false);

		for (auto i = 0; i < answer.getRow(); ++i) {								
			for (auto j = 0; j < answer.getCols(); ++j) {							
				QTableWidgetItem* item = new QTableWidgetItem(QString::number(answer.getMatrix()[i][j]));	
				item->setFont(font);
				answerWidget->setItem(i, j, item);
			}
		}
		answerWidget->resize(matrixVec[0]->size());
		answerWidget->verticalHeader()->setDefaultSectionSize(5);				
		answerWidget->horizontalHeader()->setDefaultSectionSize(5);
		answerWidget->show();
	}
	else {
		qDebug() << "error: need 2 matrices";
	}
}


void UserInterface::addMatrixClicked() {
	if (matrixVec.size()!=2) {
		QTableWidget* m;													//создаетс€ нова€ матрица (виджет)
		m = new QTableWidget();

		m->setRowCount(ui.get()->lineEdit->text().toInt());				//пользователь вводит количество строк и столбцов
		m->setColumnCount(ui.get()->lineEdit_2->text().toInt());

		m->verticalHeader()->setDefaultSectionSize(5);					//размер €чеек 5 на 5, чтобы матрица выгл€дела квадратной
		m->horizontalHeader()->setDefaultSectionSize(5);

		int width = m->horizontalHeader()->length() + m->verticalHeader()->width() + 2 * m->frameWidth();	//выравнивание матрицы матрицы
		int height = m->verticalHeader()->length() + m->horizontalHeader()->height() + 2 * m->frameWidth();
		m->setFixedSize(width, height);

		ui->gridLayout->addWidget(m, matrixVec.size() / 2, matrixVec.size() % 2);	//чтобы матрицы не ставились вертикально на grid layout, 

		matrixVec.push_back(m);

		Matrix matrix(m->rowCount(), m->columnCount());								//создание объекта класса ћатрица
		matrices.push_back(matrix);

		connect(m, &QTableWidget::cellChanged, this, [this, m](int row, int col) {
			updateMatrix(m, row, col);												//подключение сигнала на л€мбду, котора€ потом передает данные в updateMatrix,															
			});//т.к сигнал на изменение €чейки не может передать текущую матрицу(виджет)
	}
	else {
		qDebug() << "пока что поддерживаетс€ только 2 матрицы";
	}
}