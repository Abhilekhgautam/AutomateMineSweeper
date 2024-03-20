#include <fstream>
#include <functional>
#include <mutex>
#include <opencv2/core.hpp>
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
#include <iostream>
using namespace cv;

const std::string writefilename = "descriptors.txt";
std::ofstream f(writefilename);
std::mutex file_stream_mutex;

void LoadDescriptor(std::vector<float>& desc, const std::string& FileName){

  const std::string root = "/home/abhilekh/Downloads/";

  std::string File = root + FileName;
  Mat input_img = imread(File, IMREAD_GRAYSCALE);
  Mat segmented_img;

  //threshold as a binary value
  threshold(255 - input_img, segmented_img, 127, 255, 0);

  //std::cout << segmented_img;

  HOGDescriptor hog (Size(20, 20), Size(5,5), Size(5,5), Size(5,5),9);

  hog.compute(segmented_img, desc);

  std::lock_guard<std::mutex> guard(file_stream_mutex);

  for(const float& elt: desc){
   if(f.good()){
     f << elt << " ";	   
   }	  
  }
  f << "File : " <<  FileName << "\nSize: " << desc.size() << '\n';

}

int main(){

 std::vector<float> descriptor1;
 std::vector<float> descriptor2;
 std::vector<float> descriptor3;
 std::vector<float> descriptor4;
 std::vector<float> descriptor5;

 std::thread t1(LoadDescriptor, std::ref(descriptor1), "one.png");
 std::thread t2(LoadDescriptor, std::ref(descriptor2), "two.png");
 std::thread t3(LoadDescriptor, std::ref(descriptor3), "three.png");
 std::thread t4(LoadDescriptor, std::ref(descriptor4), "four.png");
 std::thread t5(LoadDescriptor, std::ref(descriptor5), "five.png");

 //wait for all threads to complete their job..
 t1.join();
 t2.join();
 t3.join();
 t4.join();
 t5.join();
}


