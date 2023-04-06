cmake_minimum_required(VERSION 3.20)
project(DicomReader)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(SOURCE main.cpp)

add_executable(dicom_reader ${SOURCE})

#target_link_libraries(dicom_reader ${ZLIB_LIBRARIES} )
#set(DCMTK_DIR /mnt/hdd8/axle/dev/dcmtk_reader/lib/dcmtk_install/usr/local)
find_package(DCMTK REQUIRED)
include_directories(${DCMTK_INCLUDE_DIRS})
#target_link_libraries(dicom_reader dcmdata)
target_link_libraries(dicom_reader ${DCMTK_LIBRARIES})
#message(STATUS  ${DCMTK_LIBRARIES})


#find_package(ZLIB REQUIRED)
#target_link_libraries(dicom_reader ${ZLIB_LIBRARIES} )



#find_package(Iconv)
#target_link_libraries(dicom_reader ${Iconv_LIBRARIES})
# message(STATUS "${Iconv_LIBRARIES}")