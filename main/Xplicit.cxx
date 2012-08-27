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
#include <vtkAlgorithmOutput.h>

#include "vtkSmartPointer.h"
#include "vtkMatrix4x4.h"
#include "vtkImageReslice.h"
#include "vtkLookupTable.h"
#include "vtkImageMapToColors.h"
#include "vtkImageActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleImage.h"
#include "vtkCommand.h"
#include "vtkImageData.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformation.h"
 
#include <vtkSphere.h>
#include <vtkQuadric.h>
#include <vtkImplicitBoolean.h>

#include "luabridge.h"

 
void DisplayMesh(vtkAlgorithmOutput *image);
void DisplayImage(vtkAlgorithmOutput *image);

int main (int argc, char *argv[])
{
  luatest();
  vtkSmartPointer<vtkSphere> sphere = 
    vtkSmartPointer<vtkSphere>::New();
  sphere->SetCenter(0.3,0,0);

  vtkSmartPointer<vtkQuadric> quad = 
    vtkSmartPointer<vtkQuadric>::New();
  quad->SetCoefficients(1,3,9,0,0,0,0,0,0,-1);

  vtkSmartPointer<vtkImplicitBoolean> bimp = 
    vtkSmartPointer<vtkImplicitBoolean>::New();
  bimp->AddFunction(quad);
  bimp->AddFunction(sphere);
  bimp->SetOperationTypeToIntersection();
  bimp->SetOperationTypeToDifference();
  bimp->Print(std::cerr);

  // Sample the function
  vtkSmartPointer<vtkSampleFunction> sample = 
    vtkSmartPointer<vtkSampleFunction>::New();
  sample->SetSampleDimensions(100,100,100);
  sample->SetImplicitFunction(bimp);
  double value = 1.0;
  double xmin = -value, xmax = value,
    ymin = -value, ymax = value,
    zmin = -value, zmax = value;
  sample->SetModelBounds(xmin, xmax, ymin, ymax, zmin, zmax);
  sample->Update();
 
  DisplayMesh(sample->GetOutputPort());
//  DisplayImage(sample->GetOutputPort());
  return EXIT_SUCCESS;
}

void DisplayMesh(vtkAlgorithmOutput *image) {
  // Create the 0 isosurface
  vtkSmartPointer<vtkContourFilter> contours = 
    vtkSmartPointer<vtkContourFilter>::New();
  contours->SetInputConnection(image);
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
}

// The mouse motion callback, to turn "Slicing" on and off
class vtkImageInteractionCallback : public vtkCommand
{
public:

  static vtkImageInteractionCallback *New() {
    return new vtkImageInteractionCallback; };

  vtkImageInteractionCallback() {
    this->Slicing = 0;
    this->ImageReslice = 0;
    this->Interactor = 0; };

  void SetImageReslice(vtkImageReslice *reslice) {
    this->ImageReslice = reslice; };

  vtkImageReslice *GetImageReslice() {
    return this->ImageReslice; };

  void SetInteractor(vtkRenderWindowInteractor *interactor) {
    this->Interactor = interactor; };

  vtkRenderWindowInteractor *GetInteractor() {
    return this->Interactor; };

  virtual void Execute(vtkObject *, unsigned long event, void *)
    {
    vtkRenderWindowInteractor *interactor = this->GetInteractor();

    int lastPos[2];
    interactor->GetLastEventPosition(lastPos);
    int currPos[2];
    interactor->GetEventPosition(currPos);

    if (event == vtkCommand::LeftButtonPressEvent)
      {
      this->Slicing = 1;
      }
    else if (event == vtkCommand::LeftButtonReleaseEvent)
      {
      this->Slicing = 0;
      }
    else if (event == vtkCommand::MouseMoveEvent)
      {
      if (this->Slicing)
        {
        vtkImageReslice *reslice = this->ImageReslice;

        // Increment slice position by deltaY of mouse
        int deltaY = lastPos[1] - currPos[1];

        reslice->Update();
        double sliceSpacing = reslice->GetOutput()->GetSpacing()[2];
        vtkMatrix4x4 *matrix = reslice->GetResliceAxes();
        // move the center point that we are slicing through
        double point[4];
        double center[4];
        point[0] = 0.0;
        point[1] = 0.0;
        point[2] = sliceSpacing * deltaY;
        point[3] = 1.0;
        matrix->MultiplyPoint(point, center);
        matrix->SetElement(0, 3, center[0]);
        matrix->SetElement(1, 3, center[1]);
        matrix->SetElement(2, 3, center[2]);
        interactor->Render();
        }
      else
        {
        vtkInteractorStyle *style = vtkInteractorStyle::SafeDownCast(
          interactor->GetInteractorStyle());
        if (style)
          {
          style->OnMouseMove();
          }
        }
      }
    };

private:

  // Actions (slicing only, for now)
  int Slicing;

  // Pointer to vtkImageReslice
  vtkImageReslice *ImageReslice;

  // Pointer to the interactor
  vtkRenderWindowInteractor *Interactor;
};

// The program entry point
void DisplayImage(vtkAlgorithmOutput *image)
{
  int extent[6];
  double spacing[3];
  double origin[3];

/*
  image->GetOutputInformation(0)->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent);
  image->GetOutput()->GetSpacing(spacing);
  image->GetOutput()->GetOrigin(origin);
*/
  double center[3];
/*
  center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);
  center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);
  center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);
*/
  // Matrices for axial, coronal, sagittal, oblique view orientations
  //static double axialElements[16] = {
  //         1, 0, 0, 0,
  //         0, 1, 0, 0,
  //         0, 0, 1, 0,
  //         0, 0, 0, 1 };

  //static double coronalElements[16] = {
  //         1, 0, 0, 0,
  //         0, 0, 1, 0,
  //         0,-1, 0, 0,
  //         0, 0, 0, 1 };

  static double sagittalElements[16] = {
/*
           0, 0,-1, 0,
           1, 0, 0, 0,
           0,-1, 0, 0,
           0, 0, 0, 1 };*/
           1, 0, 0, 0,
           0, 1, 0, 0,
           0, 0, 1, 0,
           0, 0, 0, 1 };

  //static double obliqueElements[16] = {
  //         1, 0, 0, 0,
  //         0, 0.866025, -0.5, 0,
  //         0, 0.5, 0.866025, 0,
  //         0, 0, 0, 1 };

  // Set the slice orientation
  vtkSmartPointer<vtkMatrix4x4> resliceAxes =
    vtkSmartPointer<vtkMatrix4x4>::New();
  resliceAxes->DeepCopy(sagittalElements);
  // Set the point through which to slice
  resliceAxes->SetElement(0, 3, center[0]);
  resliceAxes->SetElement(1, 3, center[1]);
  resliceAxes->SetElement(2, 3, center[2]);

  // Extract a slice in the desired orientation
  vtkSmartPointer<vtkImageReslice> reslice =
    vtkSmartPointer<vtkImageReslice>::New();
  reslice->SetInputConnection(image);
  reslice->SetOutputDimensionality(2);
  reslice->SetResliceAxes(resliceAxes);
  reslice->SetInterpolationModeToLinear();

  // Create a greyscale lookup table
  vtkSmartPointer<vtkLookupTable> table =
    vtkSmartPointer<vtkLookupTable>::New();
  table->SetRange(-0.2, 0.1); // image intensity range
  table->SetValueRange(0.0, 1.0); // from black to white
  table->SetSaturationRange(0.0, 0.0); // no color saturation
  table->SetRampToLinear();
  table->Build();

  // Map the image through the lookup table
  vtkSmartPointer<vtkImageMapToColors> color =
    vtkSmartPointer<vtkImageMapToColors>::New();
  color->SetLookupTable(table);
  color->SetInputConnection(reslice->GetOutputPort());

  // Display the image
  vtkSmartPointer<vtkImageActor> actor =
    vtkSmartPointer<vtkImageActor>::New();
  actor->SetInput(color->GetOutput());

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);

  vtkSmartPointer<vtkRenderWindow> window =
    vtkSmartPointer<vtkRenderWindow>::New();
  window->AddRenderer(renderer);

  // Set up the interaction
  vtkSmartPointer<vtkInteractorStyleImage> imageStyle =
    vtkSmartPointer<vtkInteractorStyleImage>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetInteractorStyle(imageStyle);
  window->SetInteractor(interactor);
  window->Render();

  vtkSmartPointer<vtkImageInteractionCallback> callback =
    vtkSmartPointer<vtkImageInteractionCallback>::New();
  callback->SetImageReslice(reslice);
  callback->SetInteractor(interactor);

  imageStyle->AddObserver(vtkCommand::MouseMoveEvent, callback);
  imageStyle->AddObserver(vtkCommand::LeftButtonPressEvent, callback);
  imageStyle->AddObserver(vtkCommand::LeftButtonReleaseEvent, callback);

  // Start interaction
  // The Start() method doesn't return until the window is closed by the user
  interactor->Start();
}
