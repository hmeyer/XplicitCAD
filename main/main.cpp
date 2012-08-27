/*
    This file is part of Xplicit.
    Copyright 2012 Henning Meyer

    Xplicit is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Xplicit is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Xplicit.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "mainwindow.h"
#include <QApplication>
#include <iostream>


using namespace std;


class applicationClass : public QApplication {
  public: 
   applicationClass(int _argc, char **_argv): QApplication(_argc, _argv)
    { 
    }
  bool notify(QObject *receiver, QEvent *e)
    {
      cout << "Notify()! receiver:" << receiver->objectName().toAscii().data() << endl;
      return QApplication::notify(receiver, e);
    } 
 };


int main( int argc, char **argv ) {
  QApplication app(argc, argv);
  
  QCoreApplication::setOrganizationName("tutmann");
  QCoreApplication::setOrganizationDomain("tutmann.org");
  QCoreApplication::setApplicationName("Xplicit");  
  
  MainWindow window;
  QStringList args = app.arguments();
  args.removeFirst();
  if (!args.isEmpty()) window.setFile( args.first() );
  window.show();
  
  app.exec();
  return 0;
}
