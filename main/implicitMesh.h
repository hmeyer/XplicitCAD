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

#ifndef IMPLICITMESH_H
#define IMPLICITMESH_H

#include <QVTKWidget.h>
#include <boost/shared_ptr.hpp>
#include <vtkSmartPointer.h>

class vtkSampleFunction;
class Primitive;


/// QT-Widget displaying an Implicit Function
class ImplicitMesh : public QVTKWidget
{
  public:
  ImplicitMesh(QWidget* parent = NULL, Qt::WFlags f = 0);
  ~ImplicitMesh();  
  void setFunction(boost::shared_ptr<Primitive> func);
  vtkSmartPointer<vtkSampleFunction> getSampler() {return m_sampler;}
  virtual void resizeEvent( QResizeEvent * event );
  
  protected:
  vtkSmartPointer<vtkSampleFunction> m_sampler; 
  boost::shared_ptr<Primitive> m_func;
};

#endif // IMPLICITWIDGET_H
