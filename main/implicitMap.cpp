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
#include "implicitMap.h"
#include <vtkRenderWindow.h>
#include <vtkSampleFunction.h>
#include "vtkSmartPointer.h"
#include "vtkMatrix4x4.h"
#include "vtkImageReslice.h"
#include <vtkColorTransferFunction.h>
#include "vtkImageMapToColors.h"
#include "vtkImageActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleImage.h"
#include "vtkCommand.h"
#include "vtkImageData.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformation.h"
#include <vtkSmartPointer.h>
#include "primitive.h"
#include <vtkVersion.h>


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

/** Default Constructor.
Nothing fancy - just basic setup */
ImplicitMap::ImplicitMap(QWidget* parent, Qt::WFlags f):
  QVTKWidget(parent, f), m_reslice(vtkSmartPointer<vtkImageReslice>::New())
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
  m_reslice->SetOutputDimensionality(2);
  m_reslice->SetResliceAxes(resliceAxes);
  m_reslice->SetInterpolationModeToCubic();

  // Create a greyscale lookup table
  vtkSmartPointer<vtkColorTransferFunction> table =
    vtkSmartPointer<vtkColorTransferFunction>::New();
  table->RemoveAllPoints();
  table->SetNanColor(0,0,1);
  table->AddRGBPoint(	-1,	1,1,1);
  table->AddRGBPoint(-1e-10,	0,1,0);
  table->AddRGBPoint( 1e-10,	1,0,0);
  table->AddRGBPoint( 	1,	0,0,0);
//  table->SetRange(-0.2, 0.1); // image intensity range
//  table->SetValueRange(0.0, 1.0); // from black to white
//  table->SetSaturationRange(0.0, 0.0); // no color saturation
//  table->SetRampToLinear();
  table->Build();

  // Map the image through the lookup table
  vtkSmartPointer<vtkImageMapToColors> color =
    vtkSmartPointer<vtkImageMapToColors>::New();
  color->SetLookupTable(table);
  color->SetInputConnection(m_reslice->GetOutputPort());

  // Display the image
  vtkSmartPointer<vtkImageActor> actor =
    vtkSmartPointer<vtkImageActor>::New();
#if (VTK_MAJOR_VERSION>5)
  actor->SetInputData(color->GetOutput());
#else
  actor->SetInput(color->GetOutput());
#endif
  
  // Visualize
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkRenderWindow *renderWindow = this->GetRenderWindow();
  renderWindow->AddRenderer(renderer);
  renderer->AddActor(actor);
 
  // Set up the interaction
  vtkSmartPointer<vtkInteractorStyleImage> imageStyle =
    vtkSmartPointer<vtkInteractorStyleImage>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> interactor = renderWindow->GetInteractor();
  interactor->SetInteractorStyle(imageStyle);
  renderWindow->Render();
  vtkSmartPointer<vtkImageInteractionCallback> callback =
    vtkSmartPointer<vtkImageInteractionCallback>::New();
  callback->SetImageReslice(m_reslice);
  callback->SetInteractor(interactor);

  imageStyle->AddObserver(vtkCommand::MouseMoveEvent, callback);
  imageStyle->AddObserver(vtkCommand::LeftButtonPressEvent, callback);
  imageStyle->AddObserver(vtkCommand::LeftButtonReleaseEvent, callback);
}

/** Destructor*/
ImplicitMap::~ImplicitMap() {
  this->hide();
}

void ImplicitMap::resizeEvent( QResizeEvent * event ) {
  QVTKWidget::resizeEvent(event);
  int xres = this->size().width();
  int yres = this->size().height();
}

/** Function Setter*/
void ImplicitMap::setSampler(vtkSmartPointer<vtkSampleFunction> sampler/**<[in] 3d implicit map */) {
  m_reslice->SetInputConnection(sampler->GetOutputPort());
  this->update();
  vtkRenderWindow *renderWindow = this->GetRenderWindow();
  renderWindow->Render();
}


