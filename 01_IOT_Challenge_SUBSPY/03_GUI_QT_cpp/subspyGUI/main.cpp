/********************************************************           
    * 			SubSpy Graphical User Interface	           *   
    *                                                      *   
    * Author:  Marcio, Menezes                         	   *   
    * Date: 29.06.17                                       *   
    * Additional: this program is based on the GNU   	   *
	*	project Serial Port Plotter by Borislav  		   *   
    ********************************************************/  

#include "mainwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/StyleSheet/StyleSheet/style.qss");                            // Apply style sheet
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        a.setStyleSheet(file.readAll());
        file.close();
    }

    MainWindow w;
    QIcon appIcon(":/Icons/Spy_icon.ico");                       // Get the icon for the right corner
    w.setWindowIcon(appIcon);
    w.setWindowTitle("SubSpy");
    w.show();

    return a.exec();
}
