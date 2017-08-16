#include <iostream>
#include <thread>

void hello(){
  std::cout<<"Hello worlds!"<<std::endl;
}

int main(){
  std::thread t(hello);
  t.join();
}
