#include "implicitwidget.h"
#include <vtkRenderWindow.h>
#include <vtkSampleFunction.h>
#include <vtkContourFilter.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageData.h>
#include <vtkAlgorithmOutput.h>
#include <vtkSmartPointer.h>

/** Default Constructor.
Nothing fancy - just basic setup */
ImplicitWidget::ImplicitWidget(QWidget* parent, Qt::WFlags f):
  QVTKWidget(parent, f),
  m_sampler(vtkSampleFunction::New())
{
  vtkSmartPointer<vtkContourFilter> contours = 
    vtkSmartPointer<vtkContourFilter>::New();
  contours->SetInputConnection(m_sampler->GetOutputPort());
  contours->GenerateValues(1, 0, 0);
 
  // Map the contours to graphical primitives
  vtkSmartPointer<vtkPolyDataMapper> contourMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  contourMapper->SetInputConnection(contours->GetOutputPort());
  contourMapper->ScalarVisibilityOff();
 
  // Create an actor for the contours
  vtkSmartPointer<vtkActor> contourActor = 
    vtkSmartPointer<vtkActor>::New();
  contourActor->SetMapper(contourMapper);
  contourActor->GetProperty()->SetInterpolationToFlat();;
 
  // Visualize
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkRenderWindow *renderWindow = this->GetRenderWindow();
  renderWindow->AddRenderer(renderer);
 
  renderer->AddActor(contourActor);
  renderer->SetBackground(.2, .3, .4);
}

/** Destructor*/
ImplicitWidget::~ImplicitWidget() {
  this->hide();
  if (m_sampler) m_sampler->Delete();
}

void ImplicitWidget::resizeEvent( QResizeEvent * event ) {
  QVTKWidget::resizeEvent(event);
  int xres = this->size().width();
  int yres = this->size().height();
}

/** Function Setter*/
void ImplicitWidget::setFunction(vtkImplicitFunction *func/**<[in] 3d implicit function */) {
  m_sampler->SetImplicitFunction(func);
  this->update();
  vtkRenderWindow *renderWindow = this->GetRenderWindow();
  renderWindow->Render();
}

