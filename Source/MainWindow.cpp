#include <MainWindow.h>
#include "../Ui/ui_MainWindow.h"

std::mt19937 MainWindow::engine(time(nullptr));

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow)
{
	this->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
	this->grabKeyboard();
	// engine.seed(time(nullptr));
	ui->setupUi(this);
	//memset(table, 0, sizeof(table));
	score = 0;
	bestScore = ReadBestScore();
	ui->LabelScore->setText("0");
	ui->LabelBestScore->setText(QString(std::to_string(bestScore).c_str()));
	ui->TableData->setSelectionMode(QAbstractItemView::NoSelection);
	ui->TableData->setEditTriggers(QAbstractItemView::NoEditTriggers);

	// QTableWidgetItem* p;
	QFont qf;
	qf.setPointSize(20);
	// qDebug() << qf.family() << Qt::endl;
	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < 4; ++j) {
			auto p = new QTableWidgetItem;
			ui->TableData->setItem(i, j, p);
			p->setTextAlignment(Qt::AlignCenter);
			p->setFont(qf);
			p->setFlags(Qt::ItemFlag::NoItemFlags);
			table[i][j] = 0;
		}
	}

	color[0] = {238, 228, 218, 90};
	color[1] = {238, 228, 218};
	color[2] = {237, 224, 200};
	color[3] = {242, 177, 121};
	color[4] = {245, 149, 99};
	color[5] = {246, 124, 95};

	table[0][1] = 2;
	table[0][2] = 1;
	table[1][1] = 3;
	table[1][3] = 4;
	table[2][3] = 5;
	print();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::print()
{
	QTableWidgetItem* p;
	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < 4; ++j) {
			p = ui->TableData->item(i, j);
			if(table[i][j] != 0) {
				p->setText(std::to_string(size_t(std::pow(2, table[i][j]))).c_str());
			}
			p->setBackground(QBrush(color[table[i][j]]));
		}
	}
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
	bool result = false;
	// qDebug() << event->text();
	switch(event->key()) {
		// case Qt::Key_Space:
		// 	qDebug() << "Space" << Qt::endl;
		// 	break;
		case Qt::Key_Up:
		case Qt::Key_W:
			result = moveUp();
			qDebug() << "Up" << Qt::endl;
			break;
		case Qt::Key_S:
		case Qt::Key_Down:
			// result = moveDown();
			qDebug() << "Down" << Qt::endl;
			break;
		case Qt::Key_A:
		case Qt::Key_Left:
			// result = moveLeft();
			qDebug() << "Left" << Qt::endl;
			break;
		case Qt::Key_D:
		case Qt::Key_Right:
			// result = moveRight();
			qDebug() << "Right" << Qt::endl;
			break;
		default:
			QWidget::keyPressEvent(event);
			break;
	}
	if(result) {
		if(generate()) {
			print();
		}
	}
}

bool MainWindow::generate() {
	bool result = false;
	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < 4; ++j) {
			if(table[i][j] == 0) {
				result = true;
				break;
			}
		}
		if(result) {
			break;
		}
	}
	if(!result) {
		return false;
	}
	result = false;
	do {
		int i = MainWindow::engine() % 4;
		int j = MainWindow::engine() % 4;
		if(table[i][j] == 0) {
			table[i][j] = MainWindow::engine() % 2 + 1;
			result = true;
		}
	} while(!result);
	return result;
}

bool MainWindow::moveUp() {
	return true;
}
