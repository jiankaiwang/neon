#include <iostream>
#include <cstdlib>
#include <arm_neon.h>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void deinterleave(uint8_t *r, uint8_t *g, uint8_t *b, uint8_t *rgb, int length) {
  int num8x16 = length / 16;  // 16 = 128 (neon bit width) / 8 bit, 3 is for rgb
  uint8x16x3_t intlv_rgb;
  for(int i = 0 ; i < num8x16 ; i++) {
    intlv_rgb = vld3q_u8(rgb + 3*16*i);
    vst1q_u8(r + 16*i, intlv_rgb.val[0]);
    vst1q_u8(g + 16*i, intlv_rgb.val[1]);
    vst1q_u8(b + 16*i, intlv_rgb.val[2]);
  }
}

enum {
  CV_LOAD_IMAGE_UNCHANGED = 1, 
  CV_LOAD_IMAGE_GRAYSCALED = 0,
  CV_LOAD_IMAGE_COLOR = 1
};

void mat_uint8(uint8_t *rgb, int height, int width, const Mat *getImage) {
  int increasing = 0;
  for (int h = 0 ; h < height ; h++) {
    for (int w = 0 ; w < width ; w++) {
      for (int c = 0 ; c < 3 ; c++) {
        rgb[increasing++] = (*getImage).at<cv::Vec3b>(h, w)[c];
      }
    }
  }
}

Mat uint8_mat(uint8_t *rgb, int height, int width, int channel) {
  Mat rgbImg;  
  if(channel == 3) {
    // CV_8UC3 for color
    rgbImg.create(height, width, CV_8UC3);
    memcpy(rgbImg.data, rgb, height * width * 3);
  } else if (channel == 1) {
    // CV_8UC1 for gray
    rgbImg.create(height, width, CV_8UC1);
    memcpy(rgbImg.data, rgb, height * width); 
    
  }
  return rgbImg;
}

int main(int argc, char* args[]) {

  
  Mat image = imread("../../data/cat_224x224.jpg", CV_LOAD_IMAGE_COLOR);

  // show the image on the standard output
  // namedWindow("Simple_Image");
  // imshow("Simple_Image", image);
  // waitKey(0);

  int imgWidth = image.size().width;
  int imgHeight = image.size().height;
  int imgChannel = image.channels();

  cout << "Image width: " << imgWidth << endl;
  cout << "Image height: " << imgHeight << endl;
  cout << "Image Channels: " << imgChannel << endl;

  int size = imgWidth * imgHeight;

  uint8_t *rgb = new uint8_t[size*3];
  mat_uint8(rgb, imgHeight, imgWidth, &image);

  // write out the image
  Mat getImage = uint8_mat(rgb, imgHeight, imgWidth, imgChannel);
  imwrite("../../data/cat.jpg", getImage);
  
  uint8_t r[size];
  uint8_t g[size];
  uint8_t b[size];

  deinterleave(r, g, b, rgb, size);

  Mat getRedChan = uint8_mat(r, imgHeight, imgWidth, 1);
  imwrite("../../data/cat_red.jpg", getRedChan);

  Mat getGreenChan = uint8_mat(g, imgHeight, imgWidth, 1);
  imwrite("../../data/cat_green.jpg", getGreenChan);

  Mat getBlueChan = uint8_mat(b, imgHeight, imgWidth, 1);
  imwrite("../../data/cat_blue.jpg", getBlueChan);    

  return 0;
}