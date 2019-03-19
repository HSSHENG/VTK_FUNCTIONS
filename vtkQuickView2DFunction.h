#ifndef ITKQUICKVIEW2DFUNCTION_H
#define ITKQUICKVIEW2DFUNCTION_H

#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include "vtkImageActor.h"
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkInteractorStyleImage.h>
#include <vtkAutoInit.h>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkCamera.h>
#include <vtkTextRenderer.h>
#include <vtkPolyDataMapper.h>
#include <vtkLineSource.h>
#include <vtkPolyLine.h>
#include <vtkPoints.h>
#include <vtkProperty.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkImageData.h>
//VTK_MODULE_INIT(vtkRenderingFreeType);
//VTK_MODULE_INIT(vtkRenderingOpenGL2);
//VTK_MODULE_INIT(vtkInteractionStyle);

namespace vtk
{
    //.................................................................................................
    // A VTK FUNCTION FOR 2D VTK IMAGE DATA QUICK VIEW
    //.................................................................................................
    void QuickView2DFunction(
            vtkSmartPointer<vtkImageData> imageData);

    //.................................................................................................
    // A VTK FUNCTION FOR VTK POLY DATA QUICK VIEW
    //.................................................................................................
    void QuickView2DFunction(
            vtkSmartPointer<vtkPolyData> poly);
}

#endif // ITKQUICKVIEW2DFUNCTION_H
