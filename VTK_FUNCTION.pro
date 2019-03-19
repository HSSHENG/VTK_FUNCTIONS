TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    vtkDICOMSeriesSimpleReaderFunction.cpp \
    vtkQuickView2DFunction.cpp \
    vtkQuickView3DFunction.cpp

#--------------------------------------------------------------------------------------------------
# my own functions path by hssheng
CONFIG(win32, win32|macx){
    MY_FUNCTION_DIR_1 = F:\PROJECTS\INCLUDE_FUNCTIONS
    MY_FUNCTION_DIR_2 = F:\PROJECTS\INCLUDE_VTK_FUNCTIONS
    INCLUDEPATH += $${MY_FUNCTION_DIR_1}
    INCLUDEPATH += $${MY_FUNCTION_DIR_2}
}else{
    MY_FUNCTION_DIR_1 = /Users/hss/Desktop/PROJECTS/INCLUDE_FUNCTIONS
    MY_FUNCTION_DIR_2 = /Users/hss/Desktop/PROJECTS/INCLUDE_VTK_FUNCTIONS
    INCLUDEPATH += $${MY_FUNCTION_DIR_1}
    INCLUDEPATH += $${MY_FUNCTION_DIR_2}
}

#--------------------------------------------------------------------------------------------------
# system libs only windows need this part
CONFIG(win32, win32|macx){
    SYSTEM_LIB_DIR = D:\Windows Kits\10\Lib\10.0.17134.0\um\x64
    SYSTEM_LIB_PREFIX = .lib
    SYSTEM_LIB_NAME = kernel32 user32 gdi32 winspool comdlg32 advapi32 shell32 ole32 oleaut32 uuid odbc32 odbccp32
    for(lib,SYSTEM_LIB_NAME){
        SYSTEM_LIBS += $${lib}$${SYSTEM_LIB_PREFIX}
    }
    QMAKE_LIBDIR +=  $${SYSTEM_LIB_DIR}
    LIBS += $${SYSTEM_LIBS}
}

#--------------------------------------------------------------------------------------------------
# Eigen part
CONFIG(win32, win32|macx){
    EIGEN_DIR = D:\Eigen
    INCLUDEPATH += $${EIGEN_DIR}
}else{
    EIGEN_DIR = /usr/local/Cellar/eigen/3.3.4/include/eigen3
    INCLUDEPATH += $${EIGEN_DIR}
}

#--------------------------------------------------------------------------------------------------
# VTK part
CONFIG(win32, win32|macx){
    VTK_INCLUDE_DIR = D:\VTK\vtkOut\include\vtk-8.1
    VTK_LIB_DIR = D:\VTK\vtkOut\lib
    VTK_LIB_VER = 8.1
    VTK_LIB_PREFIX = $${VTK_LIB_VER}
    VTK_LIB_NAME =  vtkalglib\
                    vtkChartsCore\
                    vtkCommonColor\
                    vtkCommonComputationalGeometry\
                    vtkCommonCore\
                    vtkCommonDataModel\
                    vtkCommonExecutionModel\
                    vtkCommonMath\
                    vtkCommonMisc\
                    vtkCommonSystem\
                    vtkCommonTransforms\
                    vtkDICOMParser\
                    vtkDomainsChemistry\
                    vtkDomainsChemistryOpenGL2\
                    vtkexoIIc\
                    vtkexpat\
                    vtkFiltersAMR\
                    vtkFiltersCore\
                    vtkFiltersExtraction\
                    vtkFiltersFlowPaths\
                    vtkFiltersGeneral\
                    vtkFiltersGeneric\
                    vtkFiltersGeometry\
                    vtkFiltersHybrid\
                    vtkFiltersHyperTree\
                    vtkFiltersImaging\
                    vtkFiltersModeling\
                    vtkFiltersParallel\
                    vtkFiltersParallelImaging\
                    vtkFiltersPoints\
                    vtkFiltersProgrammable\
                    vtkFiltersSelection\
                    vtkFiltersSMP\
                    vtkFiltersSources\
                    vtkFiltersStatistics\
                    vtkFiltersTexture\
                    vtkFiltersTopology\
                    vtkFiltersVerdict\
                    vtkfreetype\
                    vtkGeovisCore\
                    vtkgl2ps\
                    vtkglew\
                    vtkhdf5_hl\
                    vtkhdf5\
                    vtkImagingColor\
                    vtkImagingCore\
                    vtkImagingFourier\
                    vtkImagingGeneral\
                    vtkImagingHybrid\
                    vtkImagingMath\
                    vtkImagingMorphological\
                    vtkImagingSources\
                    vtkImagingStatistics\
                    vtkImagingStencil\
                    vtkInfovisCore\
                    vtkInfovisLayout\
                    vtkInteractionImage\
                    vtkInteractionStyle\
                    vtkInteractionWidgets\
                    vtkIOAMR\
                    vtkIOCore\
                    vtkIOEnSight\
                    vtkIOExodus\
                    vtkIOExport\
                    vtkIOExportOpenGL2\
                    vtkIOGeometry\
                    vtkIOImage\
                    vtkIOImport\
                    vtkIOInfovis\
                    vtkIOLegacy\
                    vtkIOLSDyna\
                    vtkIOMINC\
                    vtkIOMovie\
                    vtkIONetCDF\
                    vtkIOParallel\
                    vtkIOParallelXML\
                    vtkIOPLY\
                    vtkIOSQL\
                    vtkIOTecplotTable\
                    vtkIOVideo\
                    vtkIOXML\
                    vtkIOXMLParser\
                    vtkjpeg\
                    vtkjsoncpp\
                    vtklibharu\
                    vtklibxml2\
                    vtklz4\
                    vtkmetaio\
                    vtkNetCDF\
                    vtknetcdfcpp\
                    vtkoggtheora\
                    vtkParallelCore\
                    vtkpng\
                    vtkproj4\
                    vtkRenderingAnnotation\
                    vtkRenderingContext2D\
                    vtkRenderingContextOpenGL2\
                    vtkRenderingCore\
                    vtkRenderingFreeType\
                    vtkRenderingGL2PSOpenGL2\
                    vtkRenderingImage\
                    vtkRenderingLabel\
                    vtkRenderingLOD\
                    vtkRenderingOpenGL2\
                    vtkRenderingVolume\
                    vtkRenderingVolumeOpenGL2\
                    vtksqlite\
                    vtksys\
                    vtktiff\
                    vtkverdict\
                    vtkViewsContext2D\
                    vtkViewsCore\
                    vtkViewsInfovis\
                    vtkzlib
    for(lib,VTK_LIB_NAME){
        VTK_LIBS += -l$${lib}-$${VTK_LIB_PREFIX}
    }
    INCLUDEPATH += $${VTK_INCLUDE_DIR}
    DEPENDPATH += $${VTK_INCLUDE_DIR}
    LIBS += -L$${VTK_LIB_DIR} $${VTK_LIBS}
}else{
    VTK_INCLUDE_DIR = /Users/hss/packs/VTK/vtkout/include/vtk-8.1
    VTK_LIB_DIR = /Users/hss/packs/VTK/vtkout/lib
    VTK_LIB_VER = 8.1
    VTK_LIB_PREFIX = $${VTK_LIB_VER}
    VTK_LIB_NAME =  vtkChartsCore\
                    vtkCommonColor\
                    vtkCommonComputationalGeometry\
                    vtkCommonCore\
                    vtkCommonDataModel\
                    vtkCommonExecutionModel\
                    vtkCommonMath\
                    vtkCommonMisc\
                    vtkCommonSystem\
                    vtkCommonTransforms\
                    vtkDICOMParser\
                    vtkDomainsChemistry\
                    vtkDomainsChemistryOpenGL2\
                    vtkFiltersAMR\
                    vtkFiltersCore\
                    vtkFiltersExtraction\
                    vtkFiltersFlowPaths\
                    vtkFiltersGeneral\
                    vtkFiltersGeneric\
                    vtkFiltersGeometry\
                    vtkFiltersHybrid\
                    vtkFiltersHyperTree\
                    vtkFiltersImaging\
                    vtkFiltersModeling\
                    vtkFiltersParallel\
                    vtkFiltersParallelImaging\
                    vtkFiltersPoints\
                    vtkFiltersProgrammable\
                    vtkFiltersSMP\
                    vtkFiltersSelection\
                    vtkFiltersSources\
                    vtkFiltersStatistics\
                    vtkFiltersTexture\
                    vtkFiltersTopology\
                    vtkFiltersVerdict\
                    vtkGUISupportQt\
                    vtkGUISupportQtSQL\
                    vtkGeovisCore\
                    vtkIOAMR\
                    vtkIOCore\
                    vtkIOEnSight\
                    vtkIOExodus\
                    vtkIOExport\
                    vtkIOExportOpenGL2\
                    vtkIOGeometry\
                    vtkIOImage\
                    vtkIOImport\
                    vtkIOInfovis\
                    vtkIOLSDyna\
                    vtkIOLegacy\
                    vtkIOMINC\
                    vtkIOMovie\
                    vtkIONetCDF\
                    vtkIOPLY\
                    vtkIOParallel\
                    vtkIOParallelXML\
                    vtkIOSQL\
                    vtkIOTecplotTable\
                    vtkIOVideo\
                    vtkIOXML\
                    vtkIOXMLParser\
                    vtkImagingColor\
                    vtkImagingCore\
                    vtkImagingFourier\
                    vtkImagingGeneral\
                    vtkImagingHybrid\
                    vtkImagingMath\
                    vtkImagingMorphological\
                    vtkImagingSources\
                    vtkImagingStatistics\
                    vtkImagingStencil\
                    vtkInfovisCore\
                    vtkInfovisLayout\
                    vtkInteractionImage\
                    vtkInteractionStyle\
                    vtkInteractionWidgets\
                    vtkLocalExample\
                    vtkNetCDF\
                    vtkParallelCore\
                    vtkRenderingAnnotation\
                    vtkRenderingContext2D\
                    vtkRenderingContextOpenGL2\
                    vtkRenderingCore\
                    vtkRenderingFreeType\
                    vtkRenderingGL2PSOpenGL2\
                    vtkRenderingImage\
                    vtkRenderingLOD\
                    vtkRenderingLabel\
                    vtkRenderingOpenGL2\
                    vtkRenderingQt\
                    vtkRenderingVolume\
                    vtkRenderingVolumeOpenGL2\
                    vtkViewsContext2D\
                    vtkViewsCore\
                    vtkViewsInfovis\
                    vtkViewsQt\
                    vtkalglib\
                    vtkexoIIc\
                    vtkexpat\
                    vtkfreetype\
                    vtkgl2ps\
                    vtkglew\
                    vtkhdf5\
                    vtkhdf5_hl\
                    vtkjpeg\
                    vtkjsoncpp\
                    vtklibharu\
                    vtklibxml2\
                    vtklz4\
                    vtkmetaio\
                    vtknetcdfcpp\
                    vtkoggtheora\
                    vtkpng\
                    vtkproj4\
                    vtksqlite\
                    vtksys\
                    vtktiff\
                    vtkverdict\
                    vtkzlib
    for(lib,VTK_LIB_NAME){
        VTK_LIBS += -l$${lib}-$${VTK_LIB_PREFIX}
        VTK_LIBS += -l$${lib}-$${VTK_LIB_PREFIX}.1
    }
    INCLUDEPATH += $${VTK_INCLUDE_DIR}
    DEPENDPATH += $${VTK_INCLUDE_DIR}
    LIBS += -L$${VTK_LIB_DIR} $${VTK_LIBS}
}

#--------------------------------------------------------------------------------------------------
# ITK part
CONFIG(win32, win32|macx){
    ITK_INCLUDE_DIR = D:\ITK\itkOut\include\ITK-4.13
    ITK_LIB_DIR = D:\ITK\itkOut\lib
    ITK_LIB_VER = 4.13
    CONFIG(debug, debug|release){
        ITK_LIB_PREFIX = $${ITK_LIB_VER}d
    }else{
        ITK_LIB_PREFIX = $${ITK_LIB_VER}
    }
    ITK_LIB_NAME =  ITKWatersheds\
                    ITKVtkGlue\
                    ITKVTK\
                    ITKVNLInstantiation\
                    ITKVideoIO\
                    ITKVideoCore\
                    itktestlib\
                    ITKReview\
                    ITKOptimizersv4\
                    itkopenjpeg\
                    itklbfgs\
                    ITKKLMRegionGrowing\
                    ITKIOVTK\
                    ITKIOTransformMatlab\
                    itkgdcmsocketxx\
                    itkgdcmopenjp2\
                    itkgdcmMEXD\
                    itkgdcmjpeg16\
                    itkgdcmjpeg12\
                    itkgdcmjpeg8\
                    itkgdcmIOD\
                    itkgdcmDSED\
                    itkgdcmCommon\
                    itkgdcmcharls\
                    itkdouble-conversion\
                    itksys\
                    itkvnl_algo\
                    itkvnl\
                    itkv3p_netlib\
                    itknetlib\
                    itkvcl\
                    ITKCommon\
                    itkNetlibSlatec\
                    ITKStatistics\
                    ITKTransform\
                    ITKLabelMap\
                    ITKMesh\
                    itkzlib\
                    ITKMetaIO\
                    ITKSpatialObjects\
                    ITKPath\
                    ITKQuadEdgeMesh\
                    ITKIOImageBase\
                    ITKOptimizers\
                    ITKPolynomials\
                    ITKBiasCorrection\
                    ITKBioCell\
                    ITKDICOMParser\
                    ITKEXPAT\
                    ITKIOXML\
                    ITKIOSpatialObjects\
                    ITKFEM\
                    itkgdcmDICT\
                    itkgdcmMSFF\
                    ITKznz\
                    ITKniftiio\
                    ITKgiftiio\
                    ITKIOBMP\
                    ITKIOBioRad\
                    ITKIOBruker\
                    ITKIOCSV\
                    ITKIOGDCM\
                    ITKIOIPL\
                    ITKIOGE\
                    ITKIOGIPL\
                    ITKIOHDF5\
                    itkjpeg\
                    ITKIOJPEG\
                    itktiff\
                    ITKIOTIFF\
                    ITKIOLSM\
                    itkminc2\
                    ITKIOMINC\
                    ITKIOMRC\
                    ITKIOMesh\
                    ITKIOMeta\
                    ITKIONIFTI\
                    ITKNrrdIO\
                    ITKIONRRD\
                    itkpng\
                    ITKIOPNG\
                    ITKIOSiemens\
                    ITKIOStimulate\
                    ITKTransformFactory\
                    ITKIOTransformBase\
                    ITKIOTransformHDF5\
                    ITKIOTransformInsightLegacy\
                    ITKGPUAnisotropicSmoothing\
                    ITKGPUCommon\
                    ITKGPUFiniteDifference\
                    ITKGPUImageFilterBase\
                    ITKGPUPDEDeformableRegistration\
                    ITKGPUSmoothing\
                    ITKGPUThresholding
    for(lib,ITK_LIB_NAME){
        ITK_LIBS += -l$${lib}-$${ITK_LIB_PREFIX}
    }
    ITK_LIBS += -llibitkhdf5_cpp_Dd -llibitkhdf5_Dd

    INCLUDEPATH += $${ITK_INCLUDE_DIR}
    DEPENDPATH += $${ITK_INCLUDE_DIR}
    LIBS += -L$${ITK_LIB_DIR} $${ITK_LIBS}
}else{
    ITK_INCLUDE_DIR = /Users/hss/packs/ITK/itkout/include/ITK-4.13
    ITK_LIB_DIR = /Users/hss/packs/ITK/itkout/lib
    ITK_LIB_VER = 4.13
    ITK_LIB_PREFIX = $${ITK_LIB_VER}
    ITK_LIB_NAME =  ITKBiasCorrection\
                    ITKBioCell\
                    ITKCommon\
                    ITKDICOMParser\
                    ITKEXPAT\
                    ITKFEM\
                    ITKIOBMP\
                    ITKIOBioRad\
                    ITKIOBruker\
                    ITKIOCSV\
                    ITKIOGDCM\
                    ITKIOGE\
                    ITKIOGIPL\
                    ITKIOHDF5\
                    ITKIOIPL\
                    ITKIOImageBase\
                    ITKIOJPEG\
                    ITKIOLSM\
                    ITKIOMINC\
                    ITKIOMRC\
                    ITKIOMesh\
                    ITKIOMeta\
                    ITKIONIFTI\
                    ITKIONRRD\
                    ITKIOPNG\
                    ITKIOSiemens\
                    ITKIOSpatialObjects\
                    ITKIOStimulate\
                    ITKIOTIFF\
                    ITKIOTransformBase\
                    ITKIOTransformHDF5\
                    ITKIOTransformInsightLegacy\
                    ITKIOTransformMatlab\
                    ITKIOVTK\
                    ITKIOXML\
                    ITKKLMRegionGrowing\
                    ITKLabelMap\
                    ITKMesh\
                    ITKMetaIO\
                    ITKNrrdIO\
                    ITKOptimizers\
                    ITKOptimizersv4\
                    ITKPath\
                    ITKPolynomials\
                    ITKQuadEdgeMesh\
                    ITKSpatialObjects\
                    ITKStatistics\
                    ITKTransform\
                    ITKTransformFactory\
                    ITKVNLInstantiation\
                    ITKVTK\
                    ITKVideoCore\
                    ITKVideoIO\
                    ITKWatersheds\
                    ITKgiftiio\
                    ITKniftiio\
                    ITKznz\
                    ITKNetlibSlatec\
                    ITKdouble-conversion\
                    ITKgdcmCommon\
                    ITKgdcmDICT\
                    ITKgdcmDSED\
                    ITKgdcmIOD\
                    ITKgdcmMEXD\
                    ITKgdcmMSFF\
                    ITKgdcmcharls\
                    ITKgdcmjpeg12\
                    ITKgdcmjpeg16\
                    ITKgdcmjpeg8\
                    ITKgdcmopenjp2\
                    ITKgdcmsocketxx\
                    ITKgdcmuuid\
                    ITKjpeg\
                    ITKlbfgs\
                    ITKminc2\
                    ITKnetlib\
                    ITKpng\
                    ITKsys\
                    ITKtestlib\
                    ITKtiff\
                    ITKv3p_netlib\
                    ITKvcl\
                    ITKvnl\
                    ITKvnl_algo\
                    ITKzlib
    for(lib,ITK_LIB_NAME){
        ITK_LIBS += -l$${lib}-$${ITK_LIB_PREFIX}
        ITK_LIBS += -l$${lib}-$${ITK_LIB_PREFIX}.1
    }
    ITK_LIBS += -lITKhdf5_cpp_debug.1 -lITKhdf5_cpp_debug -lITKhdf5_debug.1 -lITKhdf5_debug

    INCLUDEPATH += $${ITK_INCLUDE_DIR}
    DEPENDPATH += $${ITK_INCLUDE_DIR}
    LIBS += -L$${ITK_LIB_DIR} $${ITK_LIBS}
}

#--------------------------------------------------------------------------------------------------
# OpenCv part
CONFIG(win32, win32|macx){
    OPENCV_INCLUDE_DIR = D:\opencv\opencvOut\include
    OPENCV_LIB_DIR = D:\opencv\opencvOut\x64\vc15\lib
    OPENCV_LIB_VER = 343
    CONFIG(debug, debug|release){
        OPENCV_LIB_PREFIX = $${OPENCV_LIB_VER}d
    }else{
        OPENCV_LIB_PREFIX = $${OPENCV_LIB_VER}
    }
    OPENCV_LIB_NAME =   calib3d\
                        core\
                        dnn\
                        features2d\
                        flann\
                        highgui\
                        imgcodecs\
                        imgproc\
                        ml\
                        objdetect\
                        photo\
                        shape\
                        stitching\
                        superres\
                        video\
                        videoio\
                        videostab
    for(lib,OPENCV_LIB_NAME){
        OPENCV_LIBS += -lopencv_$${lib}$${OPENCV_LIB_PREFIX}
    }

    INCLUDEPATH += $${OPENCV_INCLUDE_DIR}
    INCLUDEPATH += $${OPENCV_INCLUDE_DIR}\opencv
    INCLUDEPATH += $${OPENCV_INCLUDE_DIR}\opencv2
    LIBS += -L$${OPENCV_LIB_DIR} $${OPENCV_LIBS}
}else{
    OPENCV_INCLUDE_DIR = /usr/local/include
    OPENCV_LIB_DIR = /usr/local/Cellar/opencv/3.4.1_5/lib
    OPENCV_LIB_VER = 3.4
    OPENCV_LIB_PREFIX = $${OPENCV_LIB_VER}
    OPENCV_LIB_NAME =   aruco\
                        bgsegm\
                        bioinspired\
                        calib3d\
                        ccalib\
                        core\
                        datasets\
                        dnn\
                        dnn_objdetect\
                        dpm\
                        face\
                        features2d\
                        flann\
                        fuzzy\
                        hfs\
                        highgui\
                        img_hash\
                        imgcodecs\
                        imgproc\
                        line_descriptor\
                        ml\
                        objdetect\
                        optflow\
                        phase_unwrapping\
                        photo\
                        plot\
                        reg\
                        rgbd\
                        saliency\
                        shape\
                        stereo\
                        stitching\
                        structured_light\
                        superres\
                        surface_matching\
                        tracking\
                        video\
                        videoio\
                        videostab\
                        xfeatures2d\
                        ximgproc\
                        xobjdetect\
                        xphoto
    for(lib,OPENCV_LIB_NAME){
        OPENCV_LIBS += -lopencv_$${lib}
        OPENCV_LIBS += -lopencv_$${lib}.$${OPENCV_LIB_PREFIX}
        OPENCV_LIBS += -lopencv_$${lib}.$${OPENCV_LIB_PREFIX}.1
    }

    INCLUDEPATH += $${OPENCV_INCLUDE_DIR}
    INCLUDEPATH += $${OPENCV_INCLUDE_DIR}/opencv
    INCLUDEPATH += $${OPENCV_INCLUDE_DIR}/opencv2
    LIBS += -L$${OPENCV_LIB_DIR} $${OPENCV_LIBS}
}

#--------------------------------------------------------------------------------------------------
# GDCM part
CONFIG(win32, win32|macx){
    GDCM_INCLUDE_DIR = D:\GDCM\GDCMout\include\gdcm-2.8
    GDCM_LIB_DIR = D:\GDCM\GDCMout\lib
    GDCM_LIB_VER = 2.8
    CONFIG(debug, debug|release){
        GDCM_LIB_PREFIX = _d
    }
    GDCM_LIB_NAME = gdcmcharls\
                    gdcmCommon\
                    gdcmDICT\
                    gdcmDSED\
                    gdcmexpat\
                    gdcmgetopt\
                    gdcmIOD\
                    gdcmjpeg8\
                    gdcmjpeg12\
                    gdcmjpeg16\
                    gdcmMEXD\
                    gdcmMSFF\
                    gdcmopenjp2\
                    gdcmzlib\
                    socketxx
    for(lib,GDCM_LIB_NAME){
        CONFIG(debug, debug|release){
            GDCM_LIBS += -l$${lib}$${GDCM_LIB_PREFIX}
        }else{
            GDCM_LIBS += -l$${lib}
        }
    }

    INCLUDEPATH += $${GDCM_INCLUDE_DIR}
    LIBS += -L$${GDCM_LIB_DIR} $${GDCM_LIBS}
}else{
    GDCM_INCLUDE_DIR = /Users/hss/packs/GDCM/gdcmout/include/gdcm-2.8
    GDCM_LIB_DIR = /Users/hss/packs/GDCM/gdcmout/lib
    GDCM_LIB_VER = 2.8
    GDCM_LIB_NAME = gdcmcharls\
                    gdcmCommon\
                    gdcmDICT\
                    gdcmDSED\
                    gdcmexpat\
                    gdcmgetopt\
                    gdcmIOD\
                    gdcmjpeg8\
                    gdcmjpeg12\
                    gdcmjpeg16\
                    gdcmMEXD\
                    gdcmMSFF\
                    gdcmopenjp2\
                    gdcmzlib\
                    socketxx
    for(lib,GDCM_LIB_NAME){
        GDCM_LIBS += -l$${lib}
    }

    INCLUDEPATH += $${GDCM_INCLUDE_DIR}
    LIBS += -L$${GDCM_LIB_DIR} $${GDCM_LIBS}
}

HEADERS += \
    vtkDICOMSeriesSimpleReaderFunction.h \
    vtkQuickView2DFunction.h \
    vtkQuickView3DFunction.h

