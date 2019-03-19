#ifndef VTKDICOMSERIESSIMPLEREADERFUNCTION_H
#define VTKDICOMSERIESSIMPLEREADERFUNCTION_H

#include <itkImage.h>
#include <itkGDCMImageIO.h>
#include <itkGDCMImageIOFactory.h>
#include <itkGDCMSeriesFileNames.h>
#include <itkImageSeriesReader.h>

#include <itkImage.h>
#include <itkExtractImageFilter.h>
#include <itkResampleImageFilter.h>
#include <itkNearestNeighborInterpolateImageFunction.h>

#include <itkImageToVTKImageFilter.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>

namespace vtk
{
    //.................................................................................................
    // A FUNCTION FOR READING DICOM SERIES
    //.................................................................................................
    void DICOMSeriesSimpleReaderFunction(
            std::string dicomFilesPath,
            vtkSmartPointer<vtkImageData> &image3d);
}

#endif // VTKDICOMSERIESSIMPLEREADERFUNCTION_H
