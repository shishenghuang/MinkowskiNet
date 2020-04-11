#!/usr/bin/env bash

# Build Python virtualenv for tensorflow.
if [[ ! -d ./python_env ]]; then
    virtualenv -p /usr/bin/python3.6 python_env
fi

source ./python_env/bin/activate
pip install --upgrade virtualenv -i https://pypi.tuna.tsinghua.edu.cn/simple/
#pip3 install /home/huan/Downloads/torch-1.4.0-cp36-cp36m-manylinux1_x86_64.whl
pip3 install seaborn -i https://pypi.tuna.tsinghua.edu.cn/simple/
pip3 install imageio -i https://pypi.tuna.tsinghua.edu.cn/simple/
pip3 install matplotlib -i https://pypi.tuna.tsinghua.edu.cn/simple/
pip3 install sklearn -i https://pypi.tuna.tsinghua.edu.cn/simple/
pip3 install plyfile -i https://pypi.tuna.tsinghua.edu.cn/simple/
pip3 install pandas -i https://pypi.tuna.tsinghua.edu.cn/simple/
pip3 install datetime -i https://pypi.tuna.tsinghua.edu.cn/simple/
pip3 install tqdm -i https://pypi.tuna.tsinghua.edu.cn/simple/
pip3 install retrying -i https://pypi.tuna.tsinghua.edu.cn/simple/
pip3 install easydict -i https://pypi.tuna.tsinghua.edu.cn/simple/
pip3 install numpy==1.16.4 -i https://pypi.tuna.tsinghua.edu.cn/simple/
pip3 install open3d==0.8.0.0 -i https://pypi.tuna.tsinghua.edu.cn/simple/
pip3 --default-timeout=5000 install -U torch==1.3.0 torchvision==0.4.1 -i https://pypi.tuna.tsinghua.edu.cn/simple/
#pip3 --default-timeout=5000 install -U MinkowskiEngine -i https://pypi.tuna.tsinghua.edu.cn/simple/

cd MinkowskiEngine
python setup.py install
cd ..
# wget -O ./python_env/tensorflow-1.8.0-cp35-cp35m-linux_x86_64.whl https://cloud.tsinghua.edu.cn/f/8535b181129249caad46/?dl=1
# pip install ./python_env/tensorflow-1.8.0-cp35-cp35m-linux_x86_64.whl

# Provide numpy headers to C++
ln -s `python -c "import numpy as np; print(np.__path__[0])"`/core/include/numpy python_env/ || true


deactivate
