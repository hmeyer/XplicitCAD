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
#include <QtGui>
#include <boost/assign.hpp>
#include <boost/foreach.hpp>
#include "primitives.h"

MainWindow::MainWindow() {
  setupUi( this );
}

MainWindow::~MainWindow() {
}



void MainWindow::on_action_About_triggered() {
     QMessageBox::about(this, tr("About Xplicit"),
             tr("C++/VTK based Scripting Implicit CAD\n\n")+
                 
	      "Xplicit is free software: you can redistribute it and/or modify"
	      "it under the terms of the GNU General Public License as published by"
	      "the Free Software Foundation, either version 3 of the License, or"
	      "(at your option) any later version.\n\n"

	      "Xplicit is distributed in the hope that it will be useful,"
	      "but WITHOUT ANY WARRANTY; without even the implied warranty of"
	      "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the"
	      "GNU General Public License for more details.\n\n"

	      "You should have received a copy of the GNU General Public License"
	      "along with Xplicit.  If not, see <http://www.gnu.org/licenses/>.\n\n"

	      "Copyright 2012 Henning Meyer"

             );
}

void MainWindow::on_action_Quit_triggered() {
  qApp->exit();
}


void MainWindow::on_action_Compile_triggered() {
  Sphere s(1);
  implicitView->setFunction( s.getFunction() );
}

void MainWindow::on_action_OpenFile_triggered() {
  QStringList fnames = QFileDialog::getOpenFileNames(
    this,
    tr("Select one or more files to open"),
    ".",
    "", 0, QFileDialog::ReadOnly|QFileDialog::HideNameFilterDetails);
}


void MainWindow::on_action_SaveProject_triggered() {
  QString pname;
  if (pname.isEmpty()) pname = "./unnamed.xplct";
  pname = QFileDialog::getSaveFileName( this,
    tr("Save"),
    pname,
    tr("Project Files (*.perfproj)"));
  if (!pname.isEmpty()) {
    // Todo: SAVE
  }
}

void MainWindow::on_action_OpenProject_triggered() {
  QString pname = QFileDialog::getOpenFileName( this,
    tr("Open"),
    "./unnamed.xplct",
    tr("Xplicit Files (*.xplct)"));
  if (!pname.isEmpty()) {
    // Todo: LOAD
  }
}

void MainWindow::setFile(const QString &name) {
  if (!name.isEmpty()) {
    // Todo: LOAD
  }
}

