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

#include <itkImage.h>
#include <itkImageToVTKImageFilter.h>

namespace itk
{
    //.................................................................................................
    // A VTK-ITK FUNCTION FOR 2D ITK IMAGE DATA QUICK VIEW unsigned char
    //.................................................................................................
    void QuickView2DFunction(
            itk::Image<unsigned char,2>::Pointer image);

    //.................................................................................................
    // A VTK-ITK FUNCTION FOR 2D ITK IMAGE DATA QUICK VIEW short
    //.................................................................................................
    void QuickView2DFunction(
            itk::Image<short,2>::Pointer image);

    //.................................................................................................
    // A VTK-ITK FUNCTION FOR 2D ITK IMAGE DATA QUICK VIEW float
    //.................................................................................................
    void QuickView2DFunction(
            itk::Image<float,2>::Pointer image);

}

#endif // ITKQUICKVIEW2DFUNCTION_H
