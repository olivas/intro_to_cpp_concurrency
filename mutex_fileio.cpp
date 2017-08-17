#include <iostream>
#include <fstream>
#include <thread>

class file_io{
public:
  file_io(std::ifstream& input_file_stream,
	  std::ofstream& output_file_stream):
    ifs_(input_file_stream),
    ofs_(output_file_stream){}

  void operator()(){
    // read from ifs and then write to ofs
    std::string line;
    ifs_ >> line;
    ofs_ << line;
  }
  
private:
  std::ifstream& ifs_;
  std::ofstream& ofs_;      
};

int main(){
  const std::string DATA_PATH(std::getenv("DATA_PATH"));
  std::ifstream ifs(DATA_PATH + std::string("/all_work_and_no_play.txt"));
  std::ifstream ifs();
  std::ifstream ifs();
  std::ofstream ofs();
  std::thread t(hello);
}





