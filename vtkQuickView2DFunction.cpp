#include "vtkQuickView2DFunction.h"

//.................................................................................................
// A VTK FUNCTION FOR 2D VTK IMAGE DATA QUICK VIEW
//.................................................................................................
void vtk::QuickView2DFunction(
        vtkSmartPointer<vtkImageData> imageData)
{
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

    vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
    interactor->SetInteractorStyle(style);
    interactor->Initialize();
    interactor->Start();
}

//.................................................................................................
// A VTK FUNCTION FOR VTK POLY DATA QUICK VIEW
//.................................................................................................
void vtk::QuickView2DFunction(
        vtkSmartPointer<vtkPolyData> poly)
{
    // display construct the pipeline
    vtkSmartPointer<vtkPolyDataMapper> mapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(poly);

    vtkSmartPointer<vtkActor> actor =
        vtkSmartPointer<vtkActor>::New();
    actor->GetProperty()->SetColor(0.8, 0.8, 0.5);
    actor->GetProperty()->SetLineWidth(2);
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
    render->AddActor(actor);
    render->SetBackground(0.8,0.95,0.95);

    vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
    window->SetSize(800, 600);
    window->AddRenderer(render);

    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(window);

    vtkSmartPointer<vtkAxesActor> axes =
        vtkSmartPointer<vtkAxesActor>::New();

    vtkSmartPointer<vtkOrientationMarkerWidget> widget =
        vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    widget->SetOutlineColor( 0.9300, 0.5700, 0.1300 );
    widget->SetOrientationMarker( axes );
    widget->SetInteractor( interactor );
    widget->SetViewport( 0.0, 0.0, 0.4, 0.4 );
    widget->SetEnabled( 1 );
    widget->InteractiveOff();

    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    interactor->SetInteractorStyle(style);
    interactor->Initialize();
    interactor->Start();
}
