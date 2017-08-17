#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <mutex>
#include <future>

struct thread_safe_ofstream{
  thread_safe_ofstream(std::ofstream& ofs):ofs(ofs){};
  std::ofstream& ofs;
  std::mutex ofs_mutex;
};

class file_io{
public:
  file_io(std::ifstream& input_file_stream,
	  thread_safe_ofstream& output_file_stream):
    ifs_(input_file_stream),
    ts_ofs_(output_file_stream){}
  
  unsigned operator()(){
    // read from ifs and then write to ofs
    unsigned lines_written = 0;
    while(!ifs_.eof()){
      std::string line;
      std::getline(ifs_, line);
      if(!line.empty()){
	std::lock_guard<std::mutex> guard(ts_ofs_.ofs_mutex);	
	ts_ofs_.ofs << line << std::endl;
	lines_written++;
      }
      std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
    return lines_written;
  }
  
private:
  std::ifstream& ifs_;
  thread_safe_ofstream& ts_ofs_;      
};

int main(){
  const std::string DATA_PATH(std::getenv("DATA_PATH"));
  std::ifstream ifs1(DATA_PATH + std::string("all_work_and_no_play.txt"));
  std::ifstream ifs2(DATA_PATH + std::string("All_Work_And_No_Play.txt"));
  std::ifstream ifs3(DATA_PATH + std::string("ALL_WORK_AND_NO_PLAY.txt"));
  
  std::ofstream ofs("interleaved_file.txt");
  thread_safe_ofstream ts_ofs(ofs);

  file_io rw1(ifs1, ts_ofs);
  file_io rw2(ifs2, ts_ofs);
  file_io rw3(ifs3, ts_ofs);

  std::future<unsigned> l1 = std::async(rw1);
  std::future<unsigned> l2 = std::async(rw2);
  std::future<unsigned> l3 = std::async(rw3);

  std::cout<<"total number of lines written = "
	   <<(l1.get() + l2.get() + l3.get())
	   <<std::endl;

}










