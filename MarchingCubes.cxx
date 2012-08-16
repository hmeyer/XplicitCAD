#include <vtkSmartPointer.h>
#include <vtkContourFilter.h>
#include <vtkMarchingCubes.h>
#include <vtkVoxelModeller.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkImageCast.h>
#include <vtkXMLImageDataWriter.h>
 
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
 
int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetPhiResolution(20);
  sphereSource->SetThetaResolution(20);
  sphereSource->Update();
 
  double bounds[6];
  sphereSource->GetOutput()->GetBounds(bounds);
  for (unsigned int i = 0; i < 6; i += 2)
    {
    double range = bounds[i+1] - bounds[i];
    bounds[i]   = bounds[i] - .1 * range;
    bounds[i+1] = bounds[i+1] + .1 * range;
    }
  vtkSmartPointer<vtkVoxelModeller> voxelModeller = 
    vtkSmartPointer<vtkVoxelModeller>::New();
  voxelModeller->SetSampleDimensions(30,30,30);
  voxelModeller->SetModelBounds(bounds);
  voxelModeller->SetScalarTypeToFloat();
  voxelModeller->SetMaximumDistance(.1);
 
  voxelModeller->SetInputConnection(sphereSource->GetOutputPort());
 
  vtkSmartPointer<vtkMarchingCubes> surface = 
    vtkSmartPointer<vtkMarchingCubes>::New();
 
  surface->SetInputConnection(voxelModeller->GetOutputPort());
  surface->ComputeNormalsOn();
  surface->SetValue(0, 0.5);
 
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(.1, .2, .3);
 
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
 
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(surface->GetOutputPort());
 
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
 
  renderer->AddActor(actor);
 
  renderWindow->Render();
  interactor->Start();
  return EXIT_SUCCESS;
}
