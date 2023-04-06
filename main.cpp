#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstring>
#include "dcmtk/dcmdata/dctk.h"

#include "dcmtk/dcmimgle/dcmimage.h"
#include "nyxus_dicom_loader.h"
#include "dcmtk/dcmjpeg/djdecode.h"  /* for JPEG decoders */
#include "dcmtk/dcmjpls/djdecode.h"  /* for JPEG-LS decoders */
#include "dcmtk/dcmdata/dcrledrg.h"  /* for RLE decoder */
#include "dcmtk/dcmjpeg/dipijpeg.h"  /* for dcmimage JPEG plugin */

int test_1()
{
    std::cout << "Hola" << std::endl;
    std::string file_path{"/mnt/hdd8/axle/dev/dcmtk_reader/0002.DCM"};
    DcmFileFormat file_format;
    OFCondition status = file_format.loadFile(file_path.c_str());
    if (status.bad()) {
        std::cerr << "Problem openning file:" << file_path << std::endl;
        return 1;
    }
    DcmDataset* dataset = file_format.getDataset();

    OFString patient_name;


    OFCondition condition;
    condition = dataset->findAndGetOFStringArray(DCM_PatientName, patient_name);

    if (condition.good())  {
        std::cout << "Patient name is: " << patient_name << std::endl;
    } else {
        std::cerr << "Could not get patient name" << std::endl;
    }

    std::cout << "Program finish." << std::endl;
    return 0;
}

void test_2(){
    std::string file_path{"/mnt/hdd8/axle/dev/dcmtk_reader/data/pydicom-data/data/eCT_Supplemental.dcm"};
    // auto dicom_image = DicomImage(file_path.c_str(),0,0,0);
    // std::cout << dicom_image.getString(dicom_image.getStatus())<<std::endl;
    // std::cout << "width = "<< dicom_image.getWidth()<<std::endl;
    // std::cout << "height = "<< dicom_image.getHeight()<<std::endl;
    // std::cout << "depth = "<< dicom_image.getDepth()<<std::endl;
    // std::cout << "num frames = "<< dicom_image.getNumberOfFrames()<<std::endl;
    // std::cout << "photometric interception " << DicomImage::getString(dicom_image.getPhotometricInterpretation())<<std::endl;
    // std::cout << "Is monochrome = " << dicom_image.isMonochrome() << std::endl;
    // std::cout << "Output data size = "<< dicom_image.getOutputDataSize()<<std::endl;


    // for (int i=0; i< dicom_image.getNumberOfFrames(); i++){
    //     const uint16_t* data = (uint16_t*)(dicom_image.getOutputData(16, i, 0));
    //     auto width = dicom_image.getWidth();
    //     auto height = dicom_image.getHeight();
    //     size_t sum = 0;
    //     for(auto i=0; i< height; i++){
    //         for(auto j=0; j< width; j++){
    //             //std::cout<< *(data+i*width+j) << " ";
    //             sum += (*(data+i*width+j));
    //         }
    //         //std::cout << "\n";
    //     }
    //     std::cout << "sum = "<< sum <<std::endl; 

    // }
    DJDecoderRegistration::registerCodecs(); 
    // register JPEG-LS decoder
    DJLSDecoderRegistration::registerCodecs();
    // register RLE decoder
    DcmRLEDecoderRegistration::registerCodecs();
    auto dcm_ff = DcmFileFormat();
    dcm_ff.loadFile("/mnt/hdd8/axle/dev/dcmtk_reader/data/pydicom-data/data/SC_rgb_16bit_2frame.dcm");
    //dcm_ff.loadFile("/mnt/hdd8/axle/dev/dcmtk_reader/data/pydicom-data/data/liver.dcm");
    auto dcm_tag_total_width = DcmTagKey(0x0048,0x0006) ;
    auto dcm_tag_total_height = DcmTagKey(0x0048,0x0007) ;
    auto dcm_tag_frame_width = DcmTagKey(0x0028,0x0011) ;
    auto dcm_tag_frame_height = DcmTagKey(0x0028,0x0010) ;
    auto dcm_tag_spp = DcmTagKey(0x0028,0x0002);
    auto dcm_tag_num_frames = DcmTagKey(0x0028,0x0008) ;

    const char* wsi_uid = "1.2.840.10008.5.1.4.1.1.7";
    auto dcm_tag_sop_class_uid = DcmTagKey(0x0008, 0x0016);
    const char* sop_class_uid = NULL;
    unsigned int total_height, total_width;
    uint16_t frame_height, frame_width,spp;
    int32_t num_frames;
    dcm_ff.getDataset()->findAndGetString(dcm_tag_sop_class_uid, sop_class_uid);
    OFString test(sop_class_uid);
    std::cout << sop_class_uid <<"tata" <<strcmp(sop_class_uid, wsi_uid) <<std::endl;

    if (strcmp(sop_class_uid, wsi_uid) == 0) {std::cout << "match" <<std::endl;}
    dcm_ff.getDataset()->findAndGetUint32(dcm_tag_total_height, total_height);
    dcm_ff.getDataset()->findAndGetUint32(dcm_tag_total_width, total_width);
    dcm_ff.getDataset()->findAndGetUint16(dcm_tag_frame_height, frame_height);
    dcm_ff.getDataset()->findAndGetUint16(dcm_tag_frame_width, frame_width);
    dcm_ff.getDataset()->findAndGetSint32(dcm_tag_num_frames, num_frames);
    dcm_ff.getDataset()->findAndGetUint16(dcm_tag_spp, spp);

    std::cout<< "total height = " << total_height << std::endl; 
    std::cout<< "total width  = " << total_width << std::endl; 
    std::cout<< "frame height = " << frame_height << std::endl;
    std::cout<< "frame width  = " << frame_width << std::endl;
    std::cout<< "spp          = " << spp << std::endl;
    std::cout<< "num frames   = " << num_frames << std::endl; 

    auto num_row_tiles = static_cast<int>(ceil(total_height/frame_height));
    auto num_col_tiles = static_cast<int>(ceil(total_width/frame_width));

    std::cout <<"num of row tiles = " << num_row_tiles << std::endl;
    std::cout <<"num of col tiles = " << num_col_tiles << std::endl;
    
    auto dcm_tag_pixel_data = DcmTagKey(0x7fe0,0x0010) ;
    uint32_t frame_size = 0;

    DcmElement* pixel_data_ptr = nullptr;
    auto stat = dcm_ff.getDataset()->findAndGetElement(DCM_PixelData, pixel_data_ptr);
    DcmPixelData* pixel_data = OFreinterpret_cast(DcmPixelData*, pixel_data_ptr);
    std::cout << stat.text() << std::endl;
    // std::cout<<"status is " <<dcm_ff.getDataset()->canWriteXfer(EXS_LittleEndianExplicit) <<std::endl;
    // if( dcm_ff.getDataset()->chooseRepresentation(EXS_LittleEndianExplicit, NULL).good() &&  dcm_ff.getDataset()->canWriteXfer(EXS_LittleEndianExplicit) ){
    //     // force the meta-header UIDs to be re-generated when storing the file
    //     std::cout << "Compressed image successfully decompressed\n";

    // }
    
    pixel_data->getUncompressedFrameSize(dcm_ff.getDataset(),frame_size);


    frame_size % 2 == 0 ? frame_size = frame_size : frame_size = frame_size + 1;
    
    auto buffer = std::vector<uint16_t>(frame_size);


    std::cout << "here" <<  frame_size<<std::endl;
    uint32_t start_fragment = 0;
    OFString decompressed_color_model;
    const uint32_t offset = 8;
    uint32_t frame_no = 0;
    DcmPixelSequence *dseq = 0;
    E_TransferSyntax xferSyntax = EXS_Unknown;
    const DcmRepresentationParameter *rep = NULL;
    // pixel_data->getOriginalRepresentationKey( xferSyntax, rep );
    // auto tmp = pixel_data->getEncapsulatedRepresentation(xferSyntax, rep, dseq);
    // std::cout << tmp.text() << std::endl;

    auto status = pixel_data->getUncompressedFrame(dcm_ff.getDataset(), 
                                    frame_no,  
                                    start_fragment, 
                                    buffer.data(),
                                    frame_size,
                                    decompressed_color_model, NULL);

    std::cout << status.text()<<std::endl;

    int64_t sum = 0;
    for(int i=0; i<10; i++){
        std::cout<<buffer[i]<<std::endl;;
    }
    for(int i=0; i<frame_size; i++){
        sum += buffer[i];
    }

    std::cout << "sum is "<< sum << std::endl;


    // for (int i=0; i< 10; i++){
    //     std::cout << buffer[i] << "\n";
    // }

}   

void test_3(){
    std::string file_path{"/mnt/hdd8/axle/dev/dcmtk_reader/data/pydicom-data/data/eCT_Supplemental.dcm"};
    // auto dicom_image = DicomImage(file_path.c_str(),0,0,0);
    // std::cout << dicom_image.getString(dicom_image.getStatus())<<std::endl;
    // std::cout << "width = "<< dicom_image.getWidth()<<std::endl;
    // std::cout << "height = "<< dicom_image.getHeight()<<std::endl;
    // std::cout << "depth = "<< dicom_image.getDepth()<<std::endl;
    // std::cout << "num frames = "<< dicom_image.getNumberOfFrames()<<std::endl;
    // std::cout << "photometric interception " << DicomImage::getString(dicom_image.getPhotometricInterpretation())<<std::endl;
    // std::cout << "Is monochrome = " << dicom_image.isMonochrome() << std::endl;
    // std::cout << "Output data size = "<< dicom_image.getOutputDataSize()<<std::endl;


    // for (int i=0; i< dicom_image.getNumberOfFrames(); i++){
    //     const uint16_t* data = (uint16_t*)(dicom_image.getOutputData(16, i, 0));
    //     auto width = dicom_image.getWidth();
    //     auto height = dicom_image.getHeight();
    //     size_t sum = 0;
    //     for(auto i=0; i< height; i++){
    //         for(auto j=0; j< width; j++){
    //             //std::cout<< *(data+i*width+j) << " ";
    //             sum += (*(data+i*width+j));
    //         }
    //         //std::cout << "\n";
    //     }
    //     std::cout << "sum = "<< sum <<std::endl; 

    // }
}

void test_4(){
    std::string file_path{"/mnt/hdd8/axle/data/dicom_test_data/seg/p0_y1_r1_c0.dicom"};
 
    auto tl = NyxusGrayscaleDicomLoader<uint16_t>(1, file_path);
    std::cout <<tl.tileHeight(0)<<std::endl;
    std::cout <<tl.tileWidth(0)<<std::endl;
    auto data_buf = std::make_shared<std::vector<uint16_t>>(tl.tileHeight(0)*tl.tileWidth(0));
    tl.loadTileFromFile(data_buf, 0,0,0,0);
    size_t sum = 0;
    for(auto x: *data_buf){
        sum +=x;
    }

    std::cout << "sum is " << sum << std::endl;

}
 void test_5(){
    // register JPEG decoder
    DJDecoderRegistration::registerCodecs();
    // register JPEG-LS decoder
    DJLSDecoderRegistration::registerCodecs();
    // register RLE decoder
    DcmRLEDecoderRegistration::registerCodecs();
DcmFileFormat fileformat;
if (fileformat.loadFile("/mnt/hdd8/axle/dev/dcmtk_reader/data/pydicom-data/data/JPGLosslessP14SV1_1s_1f_8b.dcm").good())
{
  DcmDataset *dataset = fileformat.getDataset();
  // decompress data set if compressed
  std::cout<<dataset->chooseRepresentation(EXS_LittleEndianExplicit, NULL).text()<<std::endl;
  // check if everything went well
  if (dataset->canWriteXfer(EXS_LittleEndianExplicit))
  {
    fileformat.saveFile("test_decompressed.dcm", EXS_LittleEndianExplicit);
  }
}
DJDecoderRegistration::cleanup(); // deregister JPEG codecs
   
 }

int main(){
    test_2();
    
}