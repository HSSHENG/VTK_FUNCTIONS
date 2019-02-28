#include "itkQuickView3DFunction.h"

//.................................................................................................
// A VTK-ITK FUNCTION FOR 3D ITK IMAGE DATA QUICK VIEW unsigned char
//.................................................................................................
void itk::QuickView3DFunction(
        itk::Image<unsigned char,3>::Pointer image)
{
    // typedef
    typedef itk::Image<unsigned char,3> ImageType3dC;

    // regulization
    itk::ImageDataRegularization3DFunction(image);

    // convert to vtk image
    typedef itk::ImageToVTKImageFilter<ImageType3dC> ImageToVTKImageFilterType;
    ImageToVTKImageFilterType::Pointer toVtkFilter = ImageToVTKImageFilterType::New();
    toVtkFilter->SetInput(image);
    try
    {
        toVtkFilter->Update();
    }
    catch(itk::ExceptionObject &ex)
    {
        std::cout<<ex<<std::endl;
        return;
    }
    vtkSmartPointer<vtkImageData> imageData = toVtkFilter->GetOutput();

    // Visualize
    // Create the renderer, the render window, and the interactor. The renderer
    // draws into the render window, the interactor enables mouse- and
    // keyboard-based interaction with the scene.
    vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer(ren);
    vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renWin);

    // The volume will be displayed by ray-cast alpha compositing.
    // A ray-cast mapper is needed to do the ray-casting.
    vtkObjectFactory::RegisterFactory(vtkRenderingVolumeOpenGL2ObjectFactory::New());
    vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> volumeMapper =
    vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
    volumeMapper->SetSampleDistance(5.0);
    volumeMapper->SetInputData(imageData);

    // The color transfer function maps voxel intensities to colors.
    // It is modality-specific, and often anatomy-specific as well.
    // The goal is to one color for flesh (between 500 and 1000)
    // and another color for bone (1150 and over).
    vtkSmartPointer<vtkColorTransferFunction>volumeColor =
    vtkSmartPointer<vtkColorTransferFunction>::New();
    volumeColor->AddRGBPoint(0,    0.0, 0.0, 0.0);
    volumeColor->AddRGBPoint(200,  0.0, 0.5, 0.3);
//    volumeColor->AddRGBPoint(0,    0.0, 0.0, 0.0);
//    volumeColor->AddRGBPoint(500,  1.0, 0.5, 0.3);
//    volumeColor->AddRGBPoint(1000, 1.0, 0.5, 0.3);
//    volumeColor->AddRGBPoint(1150, 1.0, 1.0, 0.9);

    // The opacity transfer function is used to control the opacity
    // of different tissue types.
    vtkSmartPointer<vtkPiecewiseFunction> volumeScalarOpacity =
    vtkSmartPointer<vtkPiecewiseFunction>::New();
    volumeScalarOpacity->AddPoint(0,    0.00);
    volumeScalarOpacity->AddPoint(255,  0.85);
//    volumeScalarOpacity->AddPoint(0,    0.00);
//    volumeScalarOpacity->AddPoint(500,  0.15);
//    volumeScalarOpacity->AddPoint(1000, 0.15);
//    volumeScalarOpacity->AddPoint(1150, 0.85);

    // The gradient opacity function is used to decrease the opacity
    // in the "flat" regions of the volume while maintaining the opacity
    // at the boundaries between tissue types.  The gradient is measured
    // as the amount by which the intensity changes over unit distance.
    // For most medical data, the unit distance is 1mm.
    vtkSmartPointer<vtkPiecewiseFunction> volumeGradientOpacity =
    vtkSmartPointer<vtkPiecewiseFunction>::New();
    volumeGradientOpacity->AddPoint(0,   0.0);
    volumeGradientOpacity->AddPoint(90,  0.5);
    volumeGradientOpacity->AddPoint(100, 1.0);

    // The VolumeProperty attaches the color and opacity functions to the
    // volume, and sets other volume properties.  The interpolation should
    // be set to linear to do a high-quality rendering.  The ShadeOn option
    // turns on directional lighting, which will usually enhance the
    // appearance of the volume and make it look more "3D".  However,
    // the quality of the shading depends on how accurately the gradient
    // of the volume can be calculated, and for noisy data the gradient
    // estimation will be very poor.  The impact of the shading can be
    // decreased by increasing the Ambient coefficient while decreasing
    // the Diffuse and Specular coefficient.  To increase the impact
    // of shading, decrease the Ambient and increase the Diffuse and Specular.
    vtkSmartPointer<vtkVolumeProperty> volumeProperty =
    vtkSmartPointer<vtkVolumeProperty>::New();
    volumeProperty->SetColor(volumeColor);
    volumeProperty->SetScalarOpacity(volumeScalarOpacity);
    volumeProperty->SetGradientOpacity(volumeGradientOpacity);
    volumeProperty->SetInterpolationTypeToLinear();
    volumeProperty->ShadeOn();
    volumeProperty->SetAmbient(0.4);
    volumeProperty->SetDiffuse(0.6);
    volumeProperty->SetSpecular(0.2);

    // The vtkVolume is a vtkProp3D (like a vtkActor) and controls the position
    // and orientation of the volume in world coordinates.
    vtkSmartPointer<vtkVolume> volume =
    vtkSmartPointer<vtkVolume>::New();
    volume->SetMapper(volumeMapper);
    volume->SetProperty(volumeProperty);

    // axes
    vtkSmartPointer<vtkAxesActor> axes =
    vtkSmartPointer<vtkAxesActor>::New();
    vtkSmartPointer<vtkOrientationMarkerWidget> axesWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    axesWidget->SetOrientationMarker(axes);
    axesWidget->SetViewport( 0.0, 0.0, 0.2, 0.2 );
    axesWidget->SetInteractor(iren);
    axesWidget->On();
    axesWidget->SetInteractive(0);

    // Finally, add the volume to the renderer
    ren->AddViewProp(volume);

    // Set a background color for the renderer
    double cent[3];
    double origin[3];
    double spacing[3];
    int extent[6];
    imageData->GetOrigin(origin);
    imageData->GetSpacing(spacing);
    imageData->GetExtent(extent);
    cent[0] = origin[0] + (extent[1]-extent[0])*spacing[0]/2.0;
    cent[1] = origin[1] + (extent[3]-extent[2])*spacing[1]/2.0;
    cent[2] = origin[2] + (extent[5]-extent[4])*spacing[2]/2.0;

    ren->SetBackground(.2, .3, .4);
    ren->GetActiveCamera()->SetFocalPoint(cent[0],cent[1],cent[2]);
    ren->ResetCamera();

    renWin->SetSize(640, 480);
    // Increase the size of the render window
    renWin->SetSize(640, 480);

    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    iren->SetInteractorStyle(style);

    // Interact with the data.
    iren->Initialize();
    iren->Start();
}

//.................................................................................................
// A VTK-ITK FUNCTION FOR 3D ITK IMAGE DATA QUICK VIEW signed short
//.................................................................................................
void itk::QuickView3DFunction(
        itk::Image<signed short,3>::Pointer image)
{
    // typedef
    typedef itk::Image<signed short,3> ImageType3dS;

    // regulization
    itk::ImageDataRegularization3DFunction(image);

    // convert to vtk image
    typedef itk::ImageToVTKImageFilter<ImageType3dS> ImageToVTKImageFilterType;
    ImageToVTKImageFilterType::Pointer toVtkFilter = ImageToVTKImageFilterType::New();
    toVtkFilter->SetInput(image);
    try
    {
        toVtkFilter->Update();
    }
    catch(itk::ExceptionObject &ex)
    {
        std::cout<<ex<<std::endl;
        return;
    }
    vtkSmartPointer<vtkImageData> imageData = toVtkFilter->GetOutput();

    // Visualize
    // Create the renderer, the render window, and the interactor. The renderer
    // draws into the render window, the interactor enables mouse- and
    // keyboard-based interaction with the scene.
    vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer(ren);
    vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renWin);

    // The volume will be displayed by ray-cast alpha compositing.
    // A ray-cast mapper is needed to do the ray-casting.
    vtkObjectFactory::RegisterFactory(vtkRenderingVolumeOpenGL2ObjectFactory::New());
    vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> volumeMapper =
    vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
    volumeMapper->SetInputData(imageData);
    volumeMapper->SetSampleDistance(5);

    // The color transfer function maps voxel intensities to colors.
    // It is modality-specific, and often anatomy-specific as well.
    // The goal is to one color for flesh (between 500 and 1000)
    // and another color for bone (1150 and over).
    vtkSmartPointer<vtkColorTransferFunction>volumeColor =
    vtkSmartPointer<vtkColorTransferFunction>::New();
    volumeColor->AddRGBPoint(-1000,    0.0, 0.0, 0.0);
    volumeColor->AddRGBPoint(-500,  1.0, 0.5, 0.3);
    volumeColor->AddRGBPoint(250, 1.0, 0.5, 0.3);
    volumeColor->AddRGBPoint(550, 1.0, 1.0, 0.9);

    // The opacity transfer function is used to control the opacity
    // of different tissue types.
    vtkSmartPointer<vtkPiecewiseFunction> volumeScalarOpacity =
    vtkSmartPointer<vtkPiecewiseFunction>::New();
    volumeScalarOpacity->AddPoint(-1000,    0.00);
    volumeScalarOpacity->AddPoint(-500,  0.05);
    volumeScalarOpacity->AddPoint(250, 0.08);
    volumeScalarOpacity->AddPoint(550, 0.85);

    // The gradient opacity function is used to decrease the opacity
    // in the "flat" regions of the volume while maintaining the opacity
    // at the boundaries between tissue types.  The gradient is measured
    // as the amount by which the intensity changes over unit distance.
    // For most medical data, the unit distance is 1mm.
    vtkSmartPointer<vtkPiecewiseFunction> volumeGradientOpacity =
    vtkSmartPointer<vtkPiecewiseFunction>::New();
    volumeGradientOpacity->AddPoint(0,   0.0);
    volumeGradientOpacity->AddPoint(90,  0.5);
    volumeGradientOpacity->AddPoint(100, 1.0);

    // The VolumeProperty attaches the color and opacity functions to the
    // volume, and sets other volume properties.  The interpolation should
    // be set to linear to do a high-quality rendering.  The ShadeOn option
    // turns on directional lighting, which will usually enhance the
    // appearance of the volume and make it look more "3D".  However,
    // the quality of the shading depends on how accurately the gradient
    // of the volume can be calculated, and for noisy data the gradient
    // estimation will be very poor.  The impact of the shading can be
    // decreased by increasing the Ambient coefficient while decreasing
    // the Diffuse and Specular coefficient.  To increase the impact
    // of shading, decrease the Ambient and increase the Diffuse and Specular.
    vtkSmartPointer<vtkVolumeProperty> volumeProperty =
    vtkSmartPointer<vtkVolumeProperty>::New();
    volumeProperty->SetColor(volumeColor);
    volumeProperty->SetGradientOpacity(volumeGradientOpacity);
    volumeProperty->SetScalarOpacity(volumeScalarOpacity);
    volumeProperty->SetInterpolationTypeToNearest();
    volumeProperty->ShadeOn();
    volumeProperty->SetAmbient(0.4);
    volumeProperty->SetDiffuse(0.6);
    volumeProperty->SetSpecular(0.2);

    // The vtkVolume is a vtkProp3D (like a vtkActor) and controls the position
    // and orientation of the volume in world coordinates.
    vtkSmartPointer<vtkVolume> volume =
    vtkSmartPointer<vtkVolume>::New();
    volume->SetMapper(volumeMapper);
    volume->SetProperty(volumeProperty);

    // axes
    vtkSmartPointer<vtkAxesActor> axes =
    vtkSmartPointer<vtkAxesActor>::New();
    vtkSmartPointer<vtkOrientationMarkerWidget> axesWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    axesWidget->SetOrientationMarker(axes);
    axesWidget->SetViewport( 0.0, 0.0, 0.2, 0.2 );
    axesWidget->SetInteractor(iren);
    axesWidget->On();
    axesWidget->SetInteractive(0);

    // Finally, add the volume to the renderer
    ren->AddViewProp(volume);

    // Set a background color for the renderer
    double cent[3];
    double origin[3];
    double spacing[3];
    int extent[6];
    imageData->GetOrigin(origin);
    imageData->GetSpacing(spacing);
    imageData->GetExtent(extent);
    cent[0] = origin[0] + (extent[1]-extent[0])*spacing[0]/2.0;
    cent[1] = origin[1] + (extent[3]-extent[2])*spacing[1]/2.0;
    cent[2] = origin[2] + (extent[5]-extent[4])*spacing[2]/2.0;

    ren->SetBackground(.2, .3, .4);
    ren->GetActiveCamera()->SetFocalPoint(cent[0],cent[1],cent[2]);
    ren->ResetCamera();

    renWin->SetSize(640, 480);
    // Increase the size of the render window
    renWin->SetSize(640, 480);

    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    iren->SetInteractorStyle(style);

    // Interact with the data.
    iren->Initialize();
    iren->Start();
}

//.................................................................................................
// A VTK-ITK FUNCTION FOR 3D ITK IMAGE DATA QUICK VIEW signed short
//.................................................................................................
void itk::QuickView3DFunction(
        itk::Image<float,3>::Pointer image)
{
    // typedef
    typedef itk::Image<float,3> ImageType3dF;

    // regulization
    itk::ImageDataRegularization3DFunction(image);

    // convert to vtk image
    typedef itk::ImageToVTKImageFilter<ImageType3dF> ImageToVTKImageFilterType;
    ImageToVTKImageFilterType::Pointer toVtkFilter = ImageToVTKImageFilterType::New();
    toVtkFilter->SetInput(image);
    try
    {
        toVtkFilter->Update();
    }
    catch(itk::ExceptionObject &ex)
    {
        std::cout<<ex<<std::endl;
        return;
    }
    vtkSmartPointer<vtkImageData> imageData = toVtkFilter->GetOutput();

    // Visualize
    // Create the renderer, the render window, and the interactor. The renderer
    // draws into the render window, the interactor enables mouse- and
    // keyboard-based interaction with the scene.
    vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer(ren);
    vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renWin);

    // The volume will be displayed by ray-cast alpha compositing.
    // A ray-cast mapper is needed to do the ray-casting.
    vtkObjectFactory::RegisterFactory(vtkRenderingVolumeOpenGL2ObjectFactory::New());
    vtkSmartPointer<vtkGPUVolumeRayCastMapper> volumeMapper =
    vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
    volumeMapper->SetInputData(imageData);
    volumeMapper->SetSampleDistance(5);

    // The color transfer function maps voxel intensities to colors.
    // It is modality-specific, and often anatomy-specific as well.
    // The goal is to one color for flesh (between 500 and 1000)
    // and another color for bone (1150 and over).
    vtkSmartPointer<vtkColorTransferFunction>volumeColor =
    vtkSmartPointer<vtkColorTransferFunction>::New();
    volumeColor->AddRGBPoint(-1000,    0.0, 0.0, 0.0);
    volumeColor->AddRGBPoint(-500,  1.0, 0.5, 0.3);
    volumeColor->AddRGBPoint(250, 1.0, 0.5, 0.3);
    volumeColor->AddRGBPoint(550, 1.0, 1.0, 0.9);

    // The opacity transfer function is used to control the opacity
    // of different tissue types.
    vtkSmartPointer<vtkPiecewiseFunction> volumeScalarOpacity =
    vtkSmartPointer<vtkPiecewiseFunction>::New();
    volumeScalarOpacity->AddPoint(-1000,    0.00);
    volumeScalarOpacity->AddPoint(-500,  0.05);
    volumeScalarOpacity->AddPoint(250, 0.08);
    volumeScalarOpacity->AddPoint(550, 0.85);

    // The gradient opacity function is used to decrease the opacity
    // in the "flat" regions of the volume while maintaining the opacity
    // at the boundaries between tissue types.  The gradient is measured
    // as the amount by which the intensity changes over unit distance.
    // For most medical data, the unit distance is 1mm.
    vtkSmartPointer<vtkPiecewiseFunction> volumeGradientOpacity =
    vtkSmartPointer<vtkPiecewiseFunction>::New();
    volumeGradientOpacity->AddPoint(0,   0.0);
    volumeGradientOpacity->AddPoint(90,  0.5);
    volumeGradientOpacity->AddPoint(100, 1.0);

    // The VolumeProperty attaches the color and opacity functions to the
    // volume, and sets other volume properties.  The interpolation should
    // be set to linear to do a high-quality rendering.  The ShadeOn option
    // turns on directional lighting, which will usually enhance the
    // appearance of the volume and make it look more "3D".  However,
    // the quality of the shading depends on how accurately the gradient
    // of the volume can be calculated, and for noisy data the gradient
    // estimation will be very poor.  The impact of the shading can be
    // decreased by increasing the Ambient coefficient while decreasing
    // the Diffuse and Specular coefficient.  To increase the impact
    // of shading, decrease the Ambient and increase the Diffuse and Specular.
    vtkSmartPointer<vtkVolumeProperty> volumeProperty =
    vtkSmartPointer<vtkVolumeProperty>::New();
    volumeProperty->SetColor(volumeColor);
    volumeProperty->SetGradientOpacity(volumeGradientOpacity);
    volumeProperty->SetScalarOpacity(volumeScalarOpacity);
    volumeProperty->SetInterpolationTypeToNearest();
    volumeProperty->ShadeOn();
    volumeProperty->SetAmbient(0.4);
    volumeProperty->SetDiffuse(0.6);
    volumeProperty->SetSpecular(0.2);

    // The vtkVolume is a vtkProp3D (like a vtkActor) and controls the position
    // and orientation of the volume in world coordinates.
    vtkSmartPointer<vtkVolume> volume =
    vtkSmartPointer<vtkVolume>::New();
    volume->SetMapper(volumeMapper);
    volume->SetProperty(volumeProperty);

    // axes
    vtkSmartPointer<vtkAxesActor> axes =
    vtkSmartPointer<vtkAxesActor>::New();
    vtkSmartPointer<vtkOrientationMarkerWidget> axesWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    axesWidget->SetOrientationMarker(axes);
    axesWidget->SetViewport( 0.0, 0.0, 0.2, 0.2 );
    axesWidget->SetInteractor(iren);
    axesWidget->On();
    axesWidget->SetInteractive(0);

    // Finally, add the volume to the renderer
    ren->AddViewProp(volume);

    // Set a background color for the renderer
    double cent[3];
    double origin[3];
    double spacing[3];
    int extent[6];
    imageData->GetOrigin(origin);
    imageData->GetSpacing(spacing);
    imageData->GetExtent(extent);
    cent[0] = origin[0] + (extent[1]-extent[0])*spacing[0]/2.0;
    cent[1] = origin[1] + (extent[3]-extent[2])*spacing[1]/2.0;
    cent[2] = origin[2] + (extent[5]-extent[4])*spacing[2]/2.0;

    ren->SetBackground(.2, .3, .4);
    ren->GetActiveCamera()->SetFocalPoint(cent[0],cent[1],cent[2]);
    ren->ResetCamera();

    renWin->SetSize(640, 480);
    // Increase the size of the render window
    renWin->SetSize(640, 480);

    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    iren->SetInteractorStyle(style);

    // Interact with the data.
    iren->Initialize();
    iren->Start();
}
