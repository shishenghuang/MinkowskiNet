# MinkowskiNet
**Authors:** [Shi-Sheng Huang], please contact with me via shishenghuang.net@gmail.com

This is a C++ Inteface of MinkowskiNet, tested in Ubuntu 16.04,The details can be found in the following [CVPR 2019 paper](https://arxiv.org/abs/1904.08755)

Christopher B. Choy, JunYoung Gwak, Silvio Savarese:
4D Spatio-Temporal ConvNets: Minkowski Convolutional Neural Networks. CVPR 2019: 3075-3084


# 2. Prerequisites
We have tested the library in **16.04**, but it should be easy to compile in other platforms. A powerful computer (e.g. i7) will ensure real-time performance and provide more stable and accurate results.

## C++11 or C++0x Compiler
We use the new thread and chrono functionalities of C++11.

## CUDA, ONLY CUDA 10.1 is ok in Ubuntu 16.04
REQUIRED for all GPU accelerated code at least with cmake it is still possible to compile the CPU part without available at https://developer.nvidia.com/cuda-downloads

If you have installed CUDA 10.1, just change your cuda to CUDA 10.1 if more than one CUDA version is installed

## Glog
```
sudo apt-get install libgflags-dev libgoogle-glog-dev
```

## Python 3.6, ONLY python 3.6 is OK
```
sudo add-apt-repository ppa:deadsnakes/ppa
sudo apt update
sudo apt install python3.6
sudo apt-get install python3.6-dev
```

# 3. Compile

## install python virtual environment
```
./python_env.sh
```
then you have install python3.6 virtual environment.

## download the Res16UNet34C model weight for ScanNet dataset
```
wget https://node1.chrischoy.org/data/publications/minknet/MinkUNet34C-train-conv1-5.pth
```

## Set the **MINKOWSKINET_WEIGHT_FILE** in the CMakeLists file
just set MinkUNet34C-train-conv1-5.pth path located in your computer.

## Complile
```
mkdir build
cd build
cmake ..
make -j8
```


# 4. Usage
<!-- the executive file is generated in Examples/RGB-D/rgbd_tum_fusion, note the calib file: Examples/RGB-D/config/calib.txt is the calib file for the reconstruction as shown in InfiniTAM, you can change the file according to your dataset and sensor -->

## how to use
### 1. Run the test
```
cd bin
./test
```

# More Info
If any problem, please check [Spatio-Temporal Segmentation](https://github.com/shishenghuang/SpatioTemporalSegmentation)

<!-- the usage is:
```
Usage: ./runDynaSeg path_to_settings path_to_sequence path_to_association (see the source code for more details)
``` -->
<!-- 
### 2. Run the example

```
cd bin
./example [path_to_rgbd_files]
``` -->




