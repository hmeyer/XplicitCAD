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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include "ui_MainWindow.h"
#include <vector>
#include <memory>


class MainWindow : public QMainWindow, private Ui_MainWindow
{
  Q_OBJECT
  
  public:
    MainWindow();
    ~MainWindow();
    
 public slots:
      void on_actionOpenFile_triggered();
      void on_actionExit_triggered();
      void on_actionAbout_triggered();
     
      void on_actionSaveProject_triggered();
      void on_actionOpenProject_triggered();

 protected:
 private:
};


#endif // MAINWINDOW_H
