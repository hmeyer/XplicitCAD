
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
