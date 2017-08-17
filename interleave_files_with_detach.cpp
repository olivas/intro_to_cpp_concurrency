#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <mutex>

class file_io{
public:
  file_io(std::ifstream& input_file_stream,
	  std::ofstream& output_file_stream):
    ifs_(input_file_stream),
    ofs_(output_file_stream){}

  void operator()(){
    // read from ifs and then write to ofs
    while(!ifs_.eof()){
      std::string line;
      std::getline(ifs_, line);
      if(!line.empty())
	ofs_ << line << std::endl;
      std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
  }
  
private:
  std::ifstream& ifs_;
  std::ofstream& ofs_;      
};

int main(){
  const std::string DATA_PATH(std::getenv("DATA_PATH"));
  std::ifstream ifs1(DATA_PATH + std::string("all_work_and_no_play.txt"));
  std::ifstream ifs2(DATA_PATH + std::string("All_Work_And_No_Play.txt"));
  std::ifstream ifs3(DATA_PATH + std::string("ALL_WORK_AND_NO_PLAY.txt"));

  std::ofstream ofs("interleaved_file.txt");

  file_io rw1(ifs1, ofs);
  file_io rw2(ifs2, ofs);
  file_io rw3(ifs3, ofs);

  std::thread t1(rw1);
  std::thread t2(rw2);
  std::thread t3(rw3);

  // this should interleave...right?
  t1.detach();
  t2.detach();
  t3.detach();

  // wait for a while before exiting.
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
}









