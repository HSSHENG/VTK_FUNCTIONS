#ifndef VTKQUICKVIEW3DFUNCTION_H
#define VTKQUICKVIEW3DFUNCTION_H

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
#include <vtkMarchingCubes.h>
#include <vtkPolyDataMapper.h>
#include <vtkLODActor.h>
#include <vtkProperty.h>
#include <vtkPolyDataNormals.h>
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

namespace vtk
{
    //.................................................................................................
    // A VTK FUNCTION FOR 3D VTK IMAGE DATA QUICK VIEW
    //.................................................................................................
    void QuickView3DVolumeRenderingFunction(
            vtkSmartPointer<vtkImageData> imageData);

    //.................................................................................................
    // A VTK FUNCTION FOR 3D VTK IMAGE DATA QUICK VIEW surface rendering
    //.................................................................................................
    void QuickView3DSurfaceRenderingFunction(
            vtkSmartPointer<vtkImageData> imageData,
            float isoValue);

}

#endif // VTKQUICKVIEW3DFUNCTION_H
