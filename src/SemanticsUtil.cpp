
#include <iostream>
#include <fstream>
#include "SemanticsUtil.h"
#include "glog/logging.h"

#include "../python_env/numpy/ndarraytypes.h"
#include "../python_env/numpy/arrayobject.h"


static const short SCANNET_SUN38_CONVERT[] = {
        0, 1, 5, 2, 7, 8, 6, 3, 15, 14, 5, 4, 0, 18, 34, 11, 9, 33, 10, 0, 0, 16, 23, 5, 7, 0, 29, 24, 35, 3, 0, 27, 21, 25, 32, 12, 17, 0, 0, 18, 0, 22, 36, 0, 7, 7, 0, 37, 0, 0, 0, 0, 30, 0, 0, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 0, 0, 5, 3, 0, 0, 0, 26, 31, 0, 0, 0, 0, 0, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 0, 8, 0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 37, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 37, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 37, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 37, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 37, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 3, 1, 0, 8, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 11, 0, 0, 4, 0, 7, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 8, 0, 0, 0, 0, 23, 0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 22, 0, 0, 0, 0, 37, 0, 37, 0, 0, 0, 0, 0, 37, 0, 0, 0, 0, 1, 0, 29, 0, 0, 0, 0, 0, 0, 37, 29, 31, 0, 0, 33, 0, 0, 0, 0, 0, 0, 37, 0, 0, 20, 0, 0, 0, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 37, 0, 0, 5, 0, 0, 0, 0, 0, 37, 0, 29, 0, 21, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 15, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 5, 0, 0, 0, 21, 0, 0, 8, 0, 2, 0, 4, 0, 0, 0, 0, 0, 7, 37, 0
};

namespace DeepVoxel
{
    
    SemanticsUtil::SemanticsUtil(){
        LOG(INFO) << "Begin to initialize MinkowskiNet";
        initializeMinkowskiNet();
        LOG(INFO) << "* Initialised MinkowskiNet";

        for (int i = 0; i < 50; ++i) {
            mClsColor.push_back(cv::Vec3b(rand() % 255, rand() % 255, rand() % 255));
        }
    }

    void* SemanticsUtil::initializeMinkowskiNet() {
        Py_SetProgramName((wchar_t*)L"MinkowskiNet");
        Py_Initialize();
        wchar_t const * argv2[] = { L"MinkowskiNet.py" };
        PySys_SetArgv(1, const_cast<wchar_t**>(argv2));
        // Load Module
        mpPythonModule = PyImport_ImportModule("MinkowskiNet");
        if (mpPythonModule == nullptr) {
            if(PyErr_Occurred()) {
                std::cout << "Python error indicator is set:" << std::endl;
                PyErr_Print();
            }
            throw std::runtime_error("Could not open MinkowskiNet module.");
        }
        import_array();
        // Get function
        mpPythonExecute = PyObject_GetAttrString(mpPythonModule, "execute");
        if(mpPythonExecute == nullptr || !PyCallable_Check(mpPythonExecute)) {
            if(PyErr_Occurred()) {
                std::cout << "Python error indicator is set:" << std::endl;
                PyErr_Print();
            }
            throw std::runtime_error("Could not load function 'execute' from MinkowskiNet module.");
        }
        return 0;
    }

    SemanticsUtil::~SemanticsUtil(){

    }

    void SemanticsUtil::predict(/*input*/ double* input_points_colors, const int& points_num , /*output*/int* labels){

        Py_XDECREF(PyObject_CallFunctionObjArgs(mpPythonExecute, createArguments(input_points_colors, points_num), NULL));
        extractClassIDs(labels);
    }

    static inline PyObject* createArguments( double* input_points_colors, const int& points_num ){
        npy_intp dims[2] = {points_num , 6} ; // each row is a 6D vector with position and color both double
        return PyArray_SimpleNewFromData(2 , dims , NPY_DOUBLE , input_points_colors);
    }
        // Creating arguments for MaskRCNN to use.
    // static inline PyObject* createArguments(cv::Mat rgbImage) {
    //     assert(rgbImage.channels() == 3);
    //     npy_intp dims[3] = { rgbImage.rows, rgbImage.cols, 3 };
    //     return PyArray_SimpleNewFromData(3, dims, NPY_UINT8, rgbImage.data); // TODO Release?
    // }
    
    PyObject *SemanticsUtil::getPyObject(const char* name){
        PyObject* obj = PyObject_GetAttrString(mpPythonModule, name);
        if(!obj || obj == Py_None) throw std::runtime_error(std::string("Failed to get python object: ") + name);
        return obj;
    }

    void SemanticsUtil::extractClassIDs(int* result){
        //assert(result->size() == 0);
        LOG(INFO) << "Begin to extract class IDs";
        PyObject* pClassList = getPyObject("current_segmentation");
        if(!PySequence_Check(pClassList)) throw std::runtime_error("pClassList is not a sequence.");
        Py_ssize_t n = PySequence_Length(pClassList);
        //result->reserve(n+1);
        //result->push_back(0); // Background
        result = new int[n];
        for (int i = 0; i < n; ++i) {
            PyObject* o = PySequence_GetItem(pClassList, i);
            assert(PyLong_Check(o));
            //result->push_back(PyLong_AsLong(o));
            result[i] = PyLong_AsLong(o);
            Py_DECREF(o);
        }
        Py_DECREF(pClassList);
        LOG(INFO) << "Finish extract class IDs with " << n ;
    }

} // namespace DeepVoxel

