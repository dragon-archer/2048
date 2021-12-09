#include <MainWindow.h>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QTranslator translator;
	if(translator.load(":/Language/2048_zh_CN")) {
		app.installTranslator(&translator);
	}
	MainWindow window;
	window.show();
	return app.exec();
}
