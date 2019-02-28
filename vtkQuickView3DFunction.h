#ifndef ITKQUICKVIEW3DFUNCTION_H
#define ITKQUICKVIEW3DFUNCTION_H

#include <itkImage.h>
#include <itkImageToVTKImageFilter.h>
#include "itkImageDataRegularization3DFunction.h"

#include <vtkImageData.h>
#include <vtkMetaImageReader.h>
#include <vtkSmartPointer.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkObjectFactory.h>
#include <vtkRenderingVolumeOpenGL2ObjectFactory.h>
#include <vtkRenderingOpenGL2ObjectFactory.h>
#include <vtkAxesActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkCamera.h>
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

namespace itk
{
    //.................................................................................................
    // A VTK-ITK FUNCTION FOR 3D ITK IMAGE DATA QUICK VIEW unsigned char
    //.................................................................................................
    void QuickView3DFunction(
            itk::Image<unsigned char,3>::Pointer image);

    //.................................................................................................
    // A VTK-ITK FUNCTION FOR 3D ITK IMAGE DATA QUICK VIEW signed short
    //.................................................................................................
    void QuickView3DFunction(
            itk::Image<signed short,3>::Pointer image);

    //.................................................................................................
    // A VTK-ITK FUNCTION FOR 3D ITK IMAGE DATA QUICK VIEW float
    //.................................................................................................
    void QuickView3DFunction(
            itk::Image<float,3>::Pointer image);

}

#endif // ITKQUICKVIEW3DFUNCTION_H
