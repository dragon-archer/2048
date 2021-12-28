#ifndef MainWindow_H
#define MainWindow_H

#include <Pch.h>
#include <Common.h>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	void keyPressEvent(QKeyEvent* event);
	void print();
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();
	bool generate();

	void setupUi();
	void retranslateUi();

private:
	uint8_t table[4][4];
	size_t score;
	size_t bestScore;
	QColor color[16];
	static std::mt19937 engine;

    QWidget *CentralWidget;
    QTableWidget *TableData;
    QLabel *Label1;
    QLabel *Label2;
    QLabel *LabelScore;
    QLabel *LabelBestScore;
    QMenuBar *MenuBar;
    QMenu *MenuFile;
    QMenu *MenuSettings;
    QStatusBar *StatusBar;
};
#endif // MainWindow_H
