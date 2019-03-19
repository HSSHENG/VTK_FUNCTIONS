#include "vtkQuickView3DFunction.h"

//.................................................................................................
// A VTK FUNCTION FOR 3D VTK IMAGE DATA QUICK VIEW
//.................................................................................................
void vtk::QuickView3DVolumeRenderingFunction(
        vtkSmartPointer<vtkImageData> imageData)
{
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
    volumeColor->AddRGBPoint(-500,    0.0, 0.0, 0.0);
    volumeColor->AddRGBPoint(-200,  1.0, 0.5, 0.3);
    volumeColor->AddRGBPoint(200, 1.0, 0.5, 0.3);
    volumeColor->AddRGBPoint(800, 1.0, 1.0, 0.9);

    // The opacity transfer function is used to control the opacity
    // of different tissue types.
    vtkSmartPointer<vtkPiecewiseFunction> volumeScalarOpacity =
    vtkSmartPointer<vtkPiecewiseFunction>::New();
    volumeScalarOpacity->AddPoint(-500,    0.00);
    volumeScalarOpacity->AddPoint(-200,  0.05);
    volumeScalarOpacity->AddPoint(200, 0.15);
    volumeScalarOpacity->AddPoint(800, 0.85);

    // The gradient opacity function is used to decrease the opacity
    // in the "flat" regions of the volume while maintaining the opacity
    // at the boundaries between tissue types.  The gradient is measured
    // as the amount by which the intensity changes over unit distance.
    // For most medical data, the unit distance is 1mm.
    vtkSmartPointer<vtkPiecewiseFunction> volumeGradientOpacity =
    vtkSmartPointer<vtkPiecewiseFunction>::New();
    volumeGradientOpacity->AddPoint(0.,   0.0);
    volumeGradientOpacity->AddPoint(90.,  0.5);
    volumeGradientOpacity->AddPoint(100., 1.0);

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
// A VTK FUNCTION FOR 3D VTK IMAGE DATA QUICK VIEW surface rendering
//.................................................................................................
void vtk::QuickView3DSurfaceRenderingFunction(
        vtkSmartPointer<vtkImageData> imageData,
        float isoValue)
{
    // marching cubes
    vtkSmartPointer<vtkMarchingCubes> contourExtract = vtkSmartPointer<vtkMarchingCubes>::New();
    contourExtract->SetInputData(imageData);
    contourExtract->ComputeNormalsOn();
    contourExtract->SetValue(0,isoValue);

    // normal
    vtkSmartPointer<vtkPolyDataNormals> normals = vtkSmartPointer<vtkPolyDataNormals>::New();
    normals->SetComputePointNormals(1);
    normals->SetComputeCellNormals(0);
    normals->SetAutoOrientNormals(1);
    normals->SetSplitting(0);

    // mapper
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(contourExtract->GetOutputPort());
    mapper->ScalarVisibilityOff();

    // actor
    vtkSmartPointer<vtkLODActor> actor = vtkSmartPointer<vtkLODActor>::New();
    actor->SetNumberOfCloudPoints(10000000);
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(0,0.9,0.8);
    actor->GetProperty()->SetInterpolationToPhong();
    actor->GetProperty()->SetDiffuse(0.9);
    actor->GetProperty()->SetSpecular(0.8);
    actor->GetProperty()->SetSpecularPower(100);

    // renderer
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(0.9412,1.0000,1.0000);
    renderer->AddActor(actor);

    // renWin
    vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer(renderer);
    renWin->SetSize(800,600);

    // style
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

    // iren
    vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renWin);
    iren->SetInteractorStyle(style);

    // axes
    vtkSmartPointer<vtkAxesActor> axes =
    vtkSmartPointer<vtkAxesActor>::New();
    vtkSmartPointer<vtkOrientationMarkerWidget> axesWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    axesWidget->SetOrientationMarker(axes);
    axesWidget->SetViewport( 0.0, 0.0, 0.2, 0.2 );
    axesWidget->SetInteractor(iren);
    axesWidget->On();
    axesWidget->SetInteractive(0);

    renderer->ResetCamera();
    iren->Initialize();
    renWin->Render();
    iren->Start();
}

