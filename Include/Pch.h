#ifndef _PCH_H
#define _PCH_H

#include <QApplication>
#include <QHeaderView>
#include <QKeyEvent>
#include <QLabel>
#include <QLocale>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QTableWidget>
#include <QTranslator>
#ifndef NDEBUG
    #include <QDebug>
#endif

#include <fstream>
#include <random>
#include <algorithm>

constexpr const char* dataFileName = "2048.dat";

#endif /* _PCH_H */