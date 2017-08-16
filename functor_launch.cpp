
#include <iostream>
#include <thread>

void hello(){
  std::cout<<"Hello worlds!"<<std::endl;
}

struct background_task{
  void operator()() const{
    std::cout
      <<"Doing something in the background..."
      <<std::endl;
  }
};

int main(){
  std::thread t(hello);
  t.join();

  background_task btask;
  std::thread bthread(btask);
  bthread.join();
}



