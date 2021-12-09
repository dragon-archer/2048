#include <MainWindow.h>
#include "../Ui/ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	//memset(table, 0, sizeof(table));
	score = 0;
	bestScore = ReadBestScore();
	ui->LabelScore->setText("0");
	ui->LabelBestScore->setText(QString(std::to_string(bestScore).c_str()));
	ui->TableData->setSelectionMode(QAbstractItemView::NoSelection);
	ui->TableData->setEditTriggers(QAbstractItemView::NoEditTriggers);

	// QTableWidgetItem* p;
	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < 4; ++j) {
			ui->TableData->setItem(i, j, new QTableWidgetItem());
			table[i][j] = 0;
		}
	}

	table[0][1] = 2;
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
			if(table[i][j] != 0) {
				p = ui->TableData->item(i, j);
				p->setText(std::to_string(size_t(std::pow(2, table[i][j]))).c_str());
				ui->TableData->setItem(i, j, p);
			}
		}
	}
}
