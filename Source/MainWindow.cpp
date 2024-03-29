#include <MainWindow.h>

std::mt19937 MainWindow::engine(time(nullptr));

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setFocusPolicy(Qt::FocusPolicy::StrongFocus);
	grabKeyboard();
	setupUi();
	score = 0;
	bestScore = ReadBestScore(dataFileName);
	LabelScore->setText("0");
	LabelBestScore->setText(QString::number(bestScore));
	TableData->setSelectionMode(QAbstractItemView::NoSelection);
	TableData->setEditTriggers(QAbstractItemView::NoEditTriggers);
	QFont qf;
	qf.setPointSize(20);
	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < 4; ++j) {
			auto p = new QTableWidgetItem;
			TableData->setItem(i, j, p);
			p->setTextAlignment(Qt::AlignCenter);
			p->setFont(qf);
			p->setFlags(Qt::ItemFlag::NoItemFlags);
			table[i][j] = 0;
		}
	}
	// Init color table
	color[0] = {238, 228, 218, 90};
	color[1] = {238, 228, 218};
	color[2] = {237, 224, 200};
	color[3] = {242, 177, 121};
	color[4] = {245, 149, 99};
	color[5] = {246, 124, 95};
	color[6] = {246, 94, 59};
	color[7] = {237, 207, 114};
	color[8] = {237, 204, 97};
	color[9] = {237, 200, 80};
	color[10] = {237, 197, 63};
	color[11] = {237, 194, 46};
	color[12] = {237, 190, 29};
	color[13] = Qt::green;
	color[14] = Qt::cyan;
	color[15] = Qt::blue;

	generate();
	generate();
	print();
}

MainWindow::~MainWindow()
{
	if(!WriteBestScore(dataFileName, bestScore)) {
		QMessageBox::critical(this, tr("Error save data"), tr("Cannot save best score"), QMessageBox::Ok, QMessageBox::NoButton);
	}
}

void MainWindow::setupUi()
{
	if (objectName().isEmpty())
		setObjectName(QString::fromUtf8("this"));
	resize(540, 540);
	QFont font;
	font.setPointSize(12);
	setFont(font);
	CentralWidget = new QWidget(this);
	CentralWidget->setObjectName(QString::fromUtf8("CentralWidget"));
	TableData = new QTableWidget(CentralWidget);
	if (TableData->columnCount() < 4)
		TableData->setColumnCount(4);
	if (TableData->rowCount() < 4)
		TableData->setRowCount(4);
	TableData->setObjectName(QString::fromUtf8("TableData"));
	TableData->setGeometry(QRect(70, 60, 405, 405));
	QFont font1;
	font1.setFamilies({QString::fromUtf8("Cascadia Code")});
	font1.setPointSize(30);
	font1.setBold(true);
	TableData->setFont(font1);
	TableData->setFrameShape(QFrame::Box);
	TableData->setFrameShadow(QFrame::Raised);
	TableData->setMidLineWidth(2);
	TableData->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	TableData->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	TableData->setRowCount(4);
	TableData->setColumnCount(4);
	TableData->horizontalHeader()->setVisible(false);
	TableData->horizontalHeader()->setHighlightSections(false);
	TableData->verticalHeader()->setVisible(false);
	TableData->verticalHeader()->setDefaultSectionSize(100);
	TableData->verticalHeader()->setHighlightSections(false);
	Label1 = new QLabel(CentralWidget);
	Label1->setObjectName(QString::fromUtf8("Label1"));
	Label1->setGeometry(QRect(70, 20, 100, 30));
	Label2 = new QLabel(CentralWidget);
	Label2->setObjectName(QString::fromUtf8("Label2"));
	Label2->setGeometry(QRect(270, 20, 100, 30));
	LabelScore = new QLabel(CentralWidget);
	LabelScore->setObjectName(QString::fromUtf8("LabelScore"));
	LabelScore->setGeometry(QRect(170, 20, 100, 30));
	LabelBestScore = new QLabel(CentralWidget);
	LabelBestScore->setObjectName(QString::fromUtf8("LabelBestScore"));
	LabelBestScore->setGeometry(QRect(370, 20, 100, 30));
	setCentralWidget(CentralWidget);
	MenuBar = new QMenuBar(this);
	MenuBar->setObjectName(QString::fromUtf8("MenuBar"));
	MenuBar->setGeometry(QRect(0, 0, 540, 32));
	MenuFile = new QMenu(MenuBar);
	MenuFile->setObjectName(QString::fromUtf8("MenuFile"));
	MenuSettings = new QMenu(MenuBar);
	MenuSettings->setObjectName(QString::fromUtf8("MenuSettings"));
	setMenuBar(MenuBar);
	StatusBar = new QStatusBar(this);
	StatusBar->setObjectName(QString::fromUtf8("StatusBar"));
	setStatusBar(StatusBar);

	MenuBar->addAction(MenuFile->menuAction());
	MenuBar->addAction(MenuSettings->menuAction());

	retranslateUi();
}

void MainWindow::retranslateUi()
{
	setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
	Label1->setText(QCoreApplication::translate("MainWindow", "Score:", nullptr));
	Label2->setText(QCoreApplication::translate("MainWindow", "Best Score:", nullptr));
	LabelScore->setText(QString());
	LabelBestScore->setText(QString());
	MenuFile->setTitle(QCoreApplication::translate("MainWindow", "Game", nullptr));
	MenuSettings->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
}

void MainWindow::print()
{
	QTableWidgetItem* p;
	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < 4; ++j) {
			p = TableData->item(i, j);
			if(table[i][j] != 0) {
				p->setText(QString::number(size_t(std::pow(2, table[i][j]))));
			} else {
				p->setText("");
			}
			p->setBackground(QBrush(color[table[i][j]]));
			if(table[i][j] > 2) {
				p->setForeground(QBrush({249, 246, 242}));
			} else if(table[i][j] > 0) {
				p->setForeground(QBrush({119, 110, 101}));
			} else {
				p->setForeground(QBrush({205, 193, 180}));
			}
		}
	}
	LabelScore->setNum((int)score);
	LabelBestScore->setNum((int)bestScore);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
	bool result = false;
	switch(event->key()) {
		case Qt::Key_Up:
		case Qt::Key_W:
			result = moveUp();
			break;
		case Qt::Key_S:
		case Qt::Key_Down:
			result = moveDown();
			break;
		case Qt::Key_A:
		case Qt::Key_Left:
			result = moveLeft();
			break;
		case Qt::Key_D:
		case Qt::Key_Right:
			result = moveRight();
			break;
		default:
			QWidget::keyPressEvent(event);
			break;
	}
	if(result) {
		if(bestScore < score) {
			bestScore = score;
		}
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
			table[i][j] = (MainWindow::engine() % 10) ? 1 : 2;
			result = true;
		}
	} while(!result);
	return result;
}

bool MainWindow::moveUp() {
	bool result = false;
	for(int j = 0; j < 4; ++j) {
		std::vector<uint8_t> a {table[0][j], table[1][j], table[2][j], table[3][j]};
        auto e = std::remove(a.begin(), a.end(), 0);
        for(auto i = a.begin(); i != e && (i + 1) != e; ++i) {
            if(*i == *(i + 1)) {
                *i += 1;
                score += std::pow(2, *i);
                *(i + 1) = 0;
                e = std::remove(a.begin(), e, 0);
            }
        }
        for(auto i = e; i != a.end(); ++i) {
            *i = 0;
        }
        for(int i = 0; i < 4; ++i) {
			if(table[i][j] != a[i]) {
				result = true;
			}
            table[i][j] = a[i];
        }
	}
	return result;
}

bool MainWindow::moveDown() {
	bool result = false;
	for(int j = 0; j < 4; ++j) {
		std::vector<uint8_t> a {table[3][j], table[2][j], table[1][j], table[0][j]};
        auto e = std::remove(a.begin(), a.end(), 0);
        for(auto i = a.begin(); i != e && (i + 1) != e; ++i) {
            if(*i == *(i + 1)) {
                *i += 1;
                score += std::pow(2, *i);
                *(i + 1) = 0;
                e = std::remove(a.begin(), e, 0);
            }
        }
        for(auto i = e; i != a.end(); ++i) {
            *i = 0;
        }
        for(int i = 0; i < 4; ++i) {
			if(table[i][j] != a[3 - i]) {
				result = true;
			}
            table[i][j] = a[3 - i];
        }
	}
	return result;
}

bool MainWindow::moveLeft() {
	bool result = false;
	for(int j = 0; j < 4; ++j) {
		std::vector<uint8_t> a {table[j][0], table[j][1], table[j][2], table[j][3]};
        auto e = std::remove(a.begin(), a.end(), 0);
        for(auto i = a.begin(); i != e && (i + 1) != e; ++i) {
            if(*i == *(i + 1)) {
                *i += 1;
                score += std::pow(2, *i);
                *(i + 1) = 0;
                e = std::remove(a.begin(), e, 0);
            }
        }
        for(auto i = e; i != a.end(); ++i) {
            *i = 0;
        }
        for(int i = 0; i < 4; ++i) {
			if(table[j][i] != a[i]) {
				result = true;
			}
            table[j][i] = a[i];
        }
	}
	return result;
}

bool MainWindow::moveRight() {
	bool result = false;
	for(int j = 0; j < 4; ++j) {
		std::vector<uint8_t> a {table[j][3], table[j][2], table[j][1], table[j][0]};
        auto e = std::remove(a.begin(), a.end(), 0);
        for(auto i = a.begin(); i != e && (i + 1) != e; ++i) {
            if(*i == *(i + 1)) {
                *i += 1;
                score += std::pow(2, *i);
                *(i + 1) = 0;
                e = std::remove(a.begin(), e, 0);
            }
        }
        for(auto i = e; i != a.end(); ++i) {
            *i = 0;
        }
        for(int i = 0; i < 4; ++i) {
			if(table[j][i] != a[3 - i]) {
				result = true;
			}
            table[j][i] = a[3 - i];
        }
	}
	return result;
}

