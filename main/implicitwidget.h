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

#ifndef IMPLICITWIDGET_H
#define IMPLICITWIDGET_H

#include <QVTKWidget.h>

class vtkSampleFunction;
class vtkImplicitFunction;


/// QT-Widget displaying an Implicit Function
class ImplicitWidget : public QVTKWidget
{
  public:
  ImplicitWidget(QWidget* parent = NULL, Qt::WFlags f = 0);
  ~ImplicitWidget();  
  void setFunction(vtkImplicitFunction *func);
  virtual void resizeEvent( QResizeEvent * event );
  
  protected:
  vtkSampleFunction *m_sampler; 
};

#endif // IMPLICITWIDGET_H
