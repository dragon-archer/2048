#ifndef MainWindow_H
#define MainWindow_H

#include <Pch.h>
#include <Common.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	//void keyPressEvent(QKeyEvent* event);
	void print();

private:
	Ui::MainWindow *ui;
	uint8_t table[4][4];
	size_t score;
	size_t bestScore;
};
#endif // MainWindow_H
