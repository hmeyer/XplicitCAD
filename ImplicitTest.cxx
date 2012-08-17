#include <vtkSmartPointer.h>
 
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
 
#include <vtkSphere.h>
#include <vtkQuadric.h>
#include <vtkImplicitBoolean.h>
 
int main (int argc, char *argv[])
{
  vtkSmartPointer<vtkSphere> sphere = 
    vtkSmartPointer<vtkSphere>::New();
  sphere->SetCenter(0.5,0,0);

  vtkSmartPointer<vtkQuadric> quad = 
    vtkSmartPointer<vtkQuadric>::New();
  quad->SetCoefficients(1,3,9,0,0,0,0,0,0,-1);

  vtkSmartPointer<vtkImplicitBoolean> bimp = 
    vtkSmartPointer<vtkImplicitBoolean>::New();
  bimp->AddFunction(quad);
  bimp->AddFunction(sphere);
  bimp->SetOperationTypeToUnion();
  bimp->Print(std::cerr);
 
  // Sample the function
  vtkSmartPointer<vtkSampleFunction> sample = 
    vtkSmartPointer<vtkSampleFunction>::New();
  sample->SetSampleDimensions(50,50,50);
  sample->SetImplicitFunction(bimp);
  double value = 2.0;
  double xmin = -value, xmax = value,
    ymin = -value, ymax = value,
    zmin = -value, zmax = value;
  sample->SetModelBounds(xmin, xmax, ymin, ymax, zmin, zmax);
 
  // Create the 0 isosurface
  vtkSmartPointer<vtkContourFilter> contours = 
    vtkSmartPointer<vtkContourFilter>::New();
  contours->SetInputConnection(sample->GetOutputPort());
  contours->GenerateValues(1, 1, 1);
 
  // Map the contours to graphical primitives
  vtkSmartPointer<vtkPolyDataMapper> contourMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  contourMapper->SetInputConnection(contours->GetOutputPort());
  contourMapper->ScalarVisibilityOff();
 
  // Create an actor for the contours
  vtkSmartPointer<vtkActor> contourActor = 
    vtkSmartPointer<vtkActor>::New();
  contourActor->SetMapper(contourMapper);
 
  // Visualize
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
 
  renderer->AddActor(contourActor);
  renderer->SetBackground(.2, .3, .4);
 
  renderWindow->Render();
  interactor->Start();

  // second round - now as difference
  bimp->SetOperationTypeToDifference();
  bimp->Print(std::cerr);
  renderWindow->Render();
  interactor->Start();
  
 
  return EXIT_SUCCESS;
}

