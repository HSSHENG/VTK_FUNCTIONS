#include <iostream>
#include "vtkDICOMSeriesSimpleReaderFunction.h"
#include "vtkQuickView2DFunction.h"
#include "vtkQuickView3DFunction.h"

using namespace std;

int main()
{
    std::string path = "C:\\Users\\Administrator\\Desktop\\1";
    vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();
    vtk::DICOMSeriesSimpleReaderFunction(path, image);
    vtk::QuickView2DFunction(image);
    vtk::QuickView3DSurfaceRenderingFunction(image,-100);
    return 0;
}
