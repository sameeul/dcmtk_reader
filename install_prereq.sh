#!/bin/bash
# Usage: $bash install_prereq_linux.sh $INSTALL_DIR
# Default $INSTALL_DIR = ./local_install
#
if [ -z "$1" ]
then
      echo "Creating local_install directory"
      DEP_INSTALL_DIR="local_install"
else
     DEP_INSTALL_DIR=$1
fi
echo $DEP_INSTALL_DIR
mkdir -p $DEP_INSTALL_DIR
mkdir -p $DEP_INSTALL_DIR/include

curl -L https://github.com/glennrp/libpng/archive/refs/tags/v1.6.39.zip -o v1.6.39.zip
unzip v1.6.39.zip
cd libpng-1.6.39/
mkdir build_man
cd build_man/
cmake -DCMAKE_INSTALL_PREFIX=../../$DEP_INSTALL_DIR/   -DCMAKE_PREFIX_PATH=../../$DEP_INSTALL_DIR/   ..
make install
cd ../../

curl -L https://github.com/uclouvain/openjpeg/archive/refs/tags/v2.5.0.zip -o v2.5.0.zip
unzip v2.5.0.zip
cd openjpeg-2.5.0/
mkdir build_man
cd build_man/
cmake -DCMAKE_INSTALL_PREFIX=../../$DEP_INSTALL_DIR/   -DCMAKE_PREFIX_PATH=../../$DEP_INSTALL_DIR/   ..
make install
cd ../../


curl -L https://github.com/DCMTK/dcmtk/archive/refs/tags/DCMTK-3.6.7.zip -o DCMTK-3.6.7.zip
unzip DCMTK-3.6.7.zip
cd dcmtk-DCMTK-3.6.7/
mkdir build_man
cd build_man/
cmake -DCMAKE_INSTALL_PREFIX=../../$DEP_INSTALL_DIR/   -DCMAKE_PREFIX_PATH=../../$DEP_INSTALL_DIR/  -DDCMTK_WITH_ICONV=OFF -DBUILD_SHARED_LIBS=ON  ..
make install
cd ../../
