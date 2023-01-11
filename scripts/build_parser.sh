SRC=src/parser/yolov5_parser
CUDA_VERSION=11.6

cd $SRC
CUDA_VER=$CUDA_VERSION make
CUDA_VER=$CUDA_VERSION make install