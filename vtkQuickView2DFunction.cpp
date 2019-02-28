#include "itkQuickView2DFunction.h"

//.................................................................................................
// A VTK-ITK FUNCTION FOR 2D ITK IMAGE DATA QUICK VIEW unsigned char
//.................................................................................................
void itk::QuickView2DFunction(
        itk::Image<unsigned char,2>::Pointer image)
{
    // ImageToVTKImageFilter
    typedef itk::Image<unsigned char, 2> ImageType2dC;
    typedef itk::ImageToVTKImageFilter< ImageType2dC > itkTovtkFilterType;
    itkTovtkFilterType::Pointer itkTovtkImageFilter = itkTovtkFilterType::New();
    itkTovtkImageFilter->SetInput(image);
    try
    {
        itkTovtkImageFilter->Update();
    }
    catch( itk::ExceptionObject & error )
    {
        std::cout << "Error: " << error << std::endl;
        return;
    }

    // vtkImageData
    vtkSmartPointer<vtkImageData> imageData = itkTovtkImageFilter->GetOutput();
    // display construct the pipeline
    vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
    actor->SetInputData(imageData);
    actor->InterpolateOff();
    actor->Update();

    vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
    render->AddActor(actor);

    // spacing origin extent setting camera
    render->ResetCamera();
    double spacingCamera[3];
    double originCamera[3];
    int extentCamera[6];
    imageData->GetSpacing(spacingCamera);
    imageData->GetExtent(extentCamera);
    imageData->GetOrigin(originCamera);
    double xc = originCamera[0] + 0.5*(extentCamera[0] + extentCamera[1])*spacingCamera[0];
    double yc = originCamera[1] + 0.5*(extentCamera[2] + extentCamera[3])*spacingCamera[1];
    double zc = originCamera[2] + 0.5*(extentCamera[4] + extentCamera[5])*spacingCamera[2];
    double h = (extentCamera[3] - extentCamera[2] + 1)*spacingCamera[1];
    double d = render->GetActiveCamera()->GetDistance();
    render->GetActiveCamera()->ParallelProjectionOn();
    render->GetActiveCamera()->SetParallelScale(0.5*h);
    render->GetActiveCamera()->SetFocalPoint(xc,yc,zc);
    render->GetActiveCamera()->SetPosition(xc,yc,zc-d);
    render->GetActiveCamera()->SetViewUp(0,-1,0);
    render->GetActiveCamera()->SetClippingRange(d-0.1,d+0.1);

    vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
    window->SetSize(800, 600);
    window->AddRenderer(render);


    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(window);

    // axes
    vtkSmartPointer<vtkAxesActor> axes =
    vtkSmartPointer<vtkAxesActor>::New();
    vtkSmartPointer<vtkOrientationMarkerWidget> axesWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    axesWidget->SetOrientationMarker(axes);
    axesWidget->SetViewport( 0.0, 0.0, 0.2, 0.2 );
    axesWidget->SetInteractor(interactor);
    axesWidget->On();
    axesWidget->SetInteractive(0);

    axes->SetTotalLength( 300, 300, 300 );
    render->AddActor(axes);

    vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
    interactor->SetInteractorStyle(style);
    interactor->Initialize();
    interactor->Start();
}

//.................................................................................................
// A VTK-ITK FUNCTION FOR 2D ITK IMAGE DATA QUICK VIEW short
//.................................................................................................
void itk::QuickView2DFunction(
        itk::Image<short,2>::Pointer image)
{
    // ImageToVTKImageFilter
    typedef itk::Image<short, 2> ImageType2dS;
    typedef itk::ImageToVTKImageFilter< ImageType2dS > itkTovtkFilterType;
    itkTovtkFilterType::Pointer itkTovtkImageFilter = itkTovtkFilterType::New();
    itkTovtkImageFilter->SetInput(image);
    try
    {
        itkTovtkImageFilter->Update();
    }
    catch( itk::ExceptionObject & error )
    {
        std::cout << "Error: " << error << std::endl;
        return;
    }

    // vtkImageData
    vtkSmartPointer<vtkImageData> imageData = itkTovtkImageFilter->GetOutput();
    // display construct the pipeline
    vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
    actor->SetInputData(imageData);
    actor->InterpolateOff();
    actor->Update();

    vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
    render->AddActor(actor);

    // spacing origin extent setting camera
    render->ResetCamera();
    double spacingCamera[3];
    double originCamera[3];
    int extentCamera[6];
    imageData->GetSpacing(spacingCamera);
    imageData->GetExtent(extentCamera);
    imageData->GetOrigin(originCamera);
    double xc = originCamera[0] + 0.5*(extentCamera[0] + extentCamera[1])*spacingCamera[0];
    double yc = originCamera[1] + 0.5*(extentCamera[2] + extentCamera[3])*spacingCamera[1];
    double zc = originCamera[2] + 0.5*(extentCamera[4] + extentCamera[5])*spacingCamera[2];
    double h = (extentCamera[3] - extentCamera[2] + 1)*spacingCamera[1];
    double d = render->GetActiveCamera()->GetDistance();
    render->GetActiveCamera()->ParallelProjectionOn();
    render->GetActiveCamera()->SetParallelScale(0.5*h);
    render->GetActiveCamera()->SetFocalPoint(xc,yc,zc);
    render->GetActiveCamera()->SetPosition(xc,yc,zc-d);
    render->GetActiveCamera()->SetViewUp(0,-1,0);
    render->GetActiveCamera()->SetClippingRange(d-0.1,d+0.1);

    vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
    window->SetSize(800, 600);
    window->AddRenderer(render);


    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(window);

    // axes
    vtkSmartPointer<vtkAxesActor> axes =
    vtkSmartPointer<vtkAxesActor>::New();
    vtkSmartPointer<vtkOrientationMarkerWidget> axesWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    axesWidget->SetOrientationMarker(axes);
    axesWidget->SetViewport( 0.0, 0.0, 0.2, 0.2 );
    axesWidget->SetInteractor(interactor);
    axesWidget->On();
    axesWidget->SetInteractive(0);

    axes->SetTotalLength( 300, 300, 300 );
    render->AddActor(axes);

    vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
    interactor->SetInteractorStyle(style);
    interactor->Initialize();
    interactor->Start();
}

//.................................................................................................
// A VTK-ITK FUNCTION FOR 2D ITK IMAGE DATA QUICK VIEW float
//.................................................................................................
void itk::QuickView2DFunction(
        itk::Image<float,2>::Pointer image)
{
    // ImageToVTKImageFilter
    typedef itk::Image<float, 2> ImageType2dF;
    typedef itk::ImageToVTKImageFilter< ImageType2dF > itkTovtkFilterType;
    itkTovtkFilterType::Pointer itkTovtkImageFilter = itkTovtkFilterType::New();
    itkTovtkImageFilter->SetInput(image);
    try
    {
        itkTovtkImageFilter->Update();
    }
    catch( itk::ExceptionObject & error )
    {
        std::cout << "Error: " << error << std::endl;
        return;
    }

    // vtkImageData
    vtkSmartPointer<vtkImageData> imageData = itkTovtkImageFilter->GetOutput();
    // display construct the pipeline
    vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
    actor->SetInputData(imageData);
    actor->InterpolateOff();
    actor->Update();

    vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
    render->AddActor(actor);

    // spacing origin extent setting camera
    render->ResetCamera();
    double spacingCamera[3];
    double originCamera[3];
    int extentCamera[6];
    imageData->GetSpacing(spacingCamera);
    imageData->GetExtent(extentCamera);
    imageData->GetOrigin(originCamera);
    double xc = originCamera[0] + 0.5*(extentCamera[0] + extentCamera[1])*spacingCamera[0];
    double yc = originCamera[1] + 0.5*(extentCamera[2] + extentCamera[3])*spacingCamera[1];
    double zc = originCamera[2] + 0.5*(extentCamera[4] + extentCamera[5])*spacingCamera[2];
    double h = (extentCamera[3] - extentCamera[2] + 1)*spacingCamera[1];
    double d = render->GetActiveCamera()->GetDistance();
    render->GetActiveCamera()->ParallelProjectionOn();
    render->GetActiveCamera()->SetParallelScale(0.5*h);
    render->GetActiveCamera()->SetFocalPoint(xc,yc,zc);
    render->GetActiveCamera()->SetPosition(xc,yc,zc-d);
    render->GetActiveCamera()->SetViewUp(0,-1,0);
    render->GetActiveCamera()->SetClippingRange(d-0.1,d+0.1);

    vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
    window->SetSize(800, 600);
    window->AddRenderer(render);


    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(window);

    // axes
    vtkSmartPointer<vtkAxesActor> axes =
    vtkSmartPointer<vtkAxesActor>::New();
    vtkSmartPointer<vtkOrientationMarkerWidget> axesWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    axesWidget->SetOrientationMarker(axes);
    axesWidget->SetViewport( 0.0, 0.0, 0.2, 0.2 );
    axesWidget->SetInteractor(interactor);
    axesWidget->On();
    axesWidget->SetInteractive(0);

    axes->SetTotalLength( 300, 300, 300 );
    render->AddActor(axes);

    vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
    interactor->SetInteractorStyle(style);
    interactor->Initialize();
    interactor->Start();
}
