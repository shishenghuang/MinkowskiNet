

#ifndef _SEMANTICS_UTIL_H
#define _SEMANTICS_UTIL_H

#include <iostream>
#include <memory>

//#include <torch/script.h>
//#include <torch/torch.h>
#include <Python.h>

//#include "MaskNet.h"

using namespace std;
using namespace cv;

namespace DeepVoxel{


    class SemanticsUtil{

            PyObject* mpPythonModule;
            PyObject* mpPythonExecute;
            void* initializeMinkowskiNet();
            inline PyObject* getPyObject(const char* name);
            void extractClassIDs(int* result);

            std::vector<cv::Vec3b> mClsColor;

        public:
            SemanticsUtil();
            ~SemanticsUtil();

        public:

            // detect the semantic label of a given pointcloud:
            // input: double* input_points_colors, a pointcloud with position and colors in each row, this is a 6*points_num Dimension vector
            // input: points_num, the pointcloud number
            // output: int* label, the class IDs for each point, this is a points_num Dimension vector.
            void predict(/*input*/ double* input_points_colors, const int& points_num , /*output*/int* labels);

    };
}

#endif