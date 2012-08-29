/*
    This file is part of XplicitCAD.
    Copyright 2012 Henning Meyer

    XplicitCAD is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Xplicit is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with XplicitCAD.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include "ui_MainWindow.h"
#include <vector>
#include <boost/scoped_ptr.hpp>
class QsciLexer;

class MainWindow : public QMainWindow, private Ui_MainWindow
{
  Q_OBJECT
  
  public:
    MainWindow();
    ~MainWindow();
    
 public slots:
      void on_action_OpenFile_triggered();
      void on_action_Quit_triggered();
      void on_action_Compile_triggered();
      void on_action_About_triggered();
     
      void on_action_SaveProject_triggered();
      void on_action_OpenProject_triggered();

      void setFile(const QString &name);
 protected:
      boost::scoped_ptr<QsciLexer> sourceLexer;
 private:
};


#endif // MAINWINDOW_H
