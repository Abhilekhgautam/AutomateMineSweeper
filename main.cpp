#include <opencv2/core.hpp>
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/traits.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <vector>
#include <thread>

using namespace cv;

// global baby
// lets bring sync problem fella...
std::vector<std::vector<float>> descriptors[5];

void LoadDescriptor(const std::string& FileName){
  const std::string root = "/home/abhilekh/Downloads/";

  std::string File = root + FileName;
  Mat input_img = imread(File, IMREAD_GRAYSCALE);
  Mat segmented_img;

  imshow("Original Image", input_img);

  //threshold as a binary value
  threshold(255 - input_img, segmented_img, 127, 255, 0);


  imshow("Display Image", segmented_img);

  std::cout << segmented_img;


  HOGDescriptor hog (Size(20, 20), Size(5,5), Size(5,5), Size(5,5),9);

  hog.compute(segmented_img, descriptors[0][0]);

  waitKey();
}

int main(){
 std::thread t1(LoadDescriptor, "one.png");
 std::thread t2(LoadDescriptor, "two.png");
 std::thread t3(LoadDescriptor, "three.png");
 std::thread t4(LoadDescriptor, "four.png");
 std::thread t5(LoadDescriptor, "five.png");

 //wait for all threads to complete their job..
 t1.join();
 t2.join();
 t3.join();
 t4.join();
 t5.join();
}


