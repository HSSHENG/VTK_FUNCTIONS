#include "vtkDICOMSeriesSimpleReaderFunction.h"

// sub function for Regularization
static void ImageDataRegularization(itk::Image<float,3>::Pointer &image);

//.................................................................................................
// A FUNCTION FOR READING DICOM SERIES
//.................................................................................................
void vtk::DICOMSeriesSimpleReaderFunction(
        std::string dicomFilesPath,
        vtkSmartPointer<vtkImageData> &image3d)
{
    //typedef here we always use float to read image
    typedef itk::Image<float, 3> ImageType;

    // initializing
    image3d = vtkSmartPointer<vtkImageData>::New();

    //.............................................................................................
    // read dicom files
    //.............................................................................................
    std::cout<<"Beigin read dicom..........................."<<std::endl;
    // typedef
    typedef itk::ImageSeriesReader<ImageType> ReaderType;
    ReaderType::Pointer reader = ReaderType::New();
    typedef itk::GDCMImageIO ImageIOType;
    ImageIOType::Pointer dicomIO = ImageIOType::New();
    reader->SetImageIO(dicomIO);

    typedef itk::GDCMSeriesFileNames NameGeneratorType;
    NameGeneratorType::Pointer nameGenerator = NameGeneratorType::New();

    nameGenerator->SetUseSeriesDetails(true);
    //nameGenerator->AddSeriesRestriction(dicomChar);
    nameGenerator->SetDirectory(dicomFilesPath);

    typedef std::vector<std::string> seriesIdContainer;
    const seriesIdContainer & seriesUID = nameGenerator->GetSeriesUIDs();

    seriesIdContainer::const_iterator seriesItr = seriesUID.begin();
    seriesIdContainer::const_iterator seriesEnd = seriesUID.end();
    while(seriesItr!=seriesEnd)
    {
        std::cout<<seriesItr->c_str()<<std::endl;
        ++seriesItr;
    }

    typedef std::vector<std::string> FilesNamesContainer;
    FilesNamesContainer filesNames;
    filesNames = nameGenerator->GetFileNames(seriesUID.begin()->c_str());

    reader->SetFileNames(filesNames);

    try
    {
        reader->Update();
    }
    catch(itk::ExceptionObject &ex)
    {
        std::cout<<ex<<std::endl;
        return;
    }

    ImageType::Pointer imageItk = reader->GetOutput();

    // regularization
    ImageDataRegularization(imageItk);

    // to vtkImage
    typedef itk::ImageToVTKImageFilter<ImageType> ToVTKImageFilterType;
    ToVTKImageFilterType::Pointer toVTKFilter = ToVTKImageFilterType::New();
    toVTKFilter->SetInput(imageItk);
    try
    {
        toVTKFilter->Update();
    }
    catch(itk::ExceptionObject &ex)
    {
        std::cout<<ex<<std::endl;
        return;
    }
    image3d->DeepCopy(toVTKFilter->GetOutput());
    std::cout<<"End read dicom..........................."<<std::endl;
    return;
}

//.................................................................................................
// SUBFUNCTION: REGULARIZATION
//.................................................................................................
static void ImageDataRegularization(itk::Image<float,3>::Pointer &image)
{
    // typedef
    typedef itk::Image<float,        3> ImageType;

    // region start size spacing direction of 3d image
    ImageType::RegionType region3d = image->GetLargestPossibleRegion();
    ImageType::IndexType start3d = region3d.GetIndex();
    ImageType::SizeType size3d = region3d.GetSize();
    ImageType::SpacingType spacing3d = image->GetSpacing();
    ImageType::DirectionType direction3d = image->GetDirection();
    float r00 = direction3d.GetVnlMatrix()[0][0];
    float r11 = direction3d.GetVnlMatrix()[1][1];
    float r22 = direction3d.GetVnlMatrix()[2][2];

    // check the direction is identity or not if not
    if (abs(r00-1)>1e-6 || abs(r11-1)>1e-6 || abs(r22-1)>1e-6)
    {
        // only god and I know what is this part mean!
        // direction martix
        float r01 = direction3d.GetVnlMatrix()[0][1];
        float r02 = direction3d.GetVnlMatrix()[0][2];
        float r10 = direction3d.GetVnlMatrix()[1][0];
        float r12 = direction3d.GetVnlMatrix()[1][2];
        float r20 = direction3d.GetVnlMatrix()[2][0];
        float r21 = direction3d.GetVnlMatrix()[2][1];

        // start(Index) with 0 is good
        ImageType::PointType origin = image->GetOrigin();
        ImageType::IndexType startIndex;
        startIndex.Fill(0);

        double corner[3];
        double minX = 1E10;
        double maxX = -1E10;
        double minY = 1E10;
        double maxY = -1E10;
        double minZ = 1E10;
        double maxZ = -1E10;

        int indexI[2]{0, int(size3d[0]-1)};
        int indexJ[2]{0, int(size3d[1]-1)};
        int indexK[2]{0, int(size3d[2]-1)};

        for(int I=0;I<2;++I)
        {
            for(int J=0;J<2;++J)
            {
                for(int K=0;K<2;++K)
                {
                    corner[0] =  origin[0] + spacing3d[0]*(indexI[I]+start3d[0])*r00 +
                                             spacing3d[1]*(indexJ[J]+start3d[1])*r01 +
                                             spacing3d[2]*(indexK[K]+start3d[2])*r02;
                    corner[1] =  origin[1] + spacing3d[0]*(indexI[I]+start3d[0])*r10 +
                                             spacing3d[1]*(indexJ[J]+start3d[1])*r11 +
                                             spacing3d[2]*(indexK[K]+start3d[2])*r12;
                    corner[2] =  origin[2] + spacing3d[0]*(indexI[I]+start3d[0])*r20 +
                                             spacing3d[1]*(indexJ[J]+start3d[1])*r21 +
                                             spacing3d[2]*(indexK[K]+start3d[2])*r22;
                    minX = minX<corner[0]?minX:corner[0];
                    maxX = maxX>corner[0]?maxX:corner[0];
                    minY = minY<corner[1]?minY:corner[1];
                    maxY = maxY>corner[1]?maxY:corner[1];
                    minZ = minZ<corner[2]?minZ:corner[2];
                    maxZ = maxZ>corner[2]?maxZ:corner[2];

                }
            }
        }
        // new origion
        ImageType::PointType originResample;
        originResample[0] = minX;
        originResample[1] = minY;
        originResample[2] = minZ;

        //new size
        ImageType::SizeType sizeResample;
        sizeResample[0] = round((maxX-minX)/spacing3d[0])+1;
        sizeResample[1] = round((maxY-minY)/spacing3d[1])+1;
        sizeResample[2] = round((maxZ-minZ)/spacing3d[2])+1;


        ImageType::DirectionType desiredDirection;
        desiredDirection.SetIdentity();
        typedef itk::ResampleImageFilter<ImageType, ImageType> ResampleImageFilterType;
        ResampleImageFilterType::Pointer resampleFilter = ResampleImageFilterType::New();
        typedef itk::NearestNeighborInterpolateImageFunction<ImageType, double> InterpolatorType;
        InterpolatorType::Pointer interpolator = InterpolatorType::New();
        resampleFilter->SetInterpolator( interpolator );
        resampleFilter->SetOutputDirection(desiredDirection);
        resampleFilter->SetDefaultPixelValue(-1024);
        resampleFilter->SetSize(sizeResample);
        resampleFilter->SetOutputOrigin(originResample);
        resampleFilter->SetOutputSpacing(spacing3d);
        resampleFilter->SetOutputStartIndex(startIndex);
        resampleFilter->SetInput(image);
        try
        {
            resampleFilter->Update();
        }
        catch( itk::ExceptionObject & error )
        {
            std::cout<< "Error Update in CTCoachSegmentation3DFunction"<<std::endl;
            std::cout << "Error: " << error << std::endl;
            return;
        }

        // give back
        image = resampleFilter->GetOutput();
    }

}
