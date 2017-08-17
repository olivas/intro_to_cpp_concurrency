
#include <iostream>
#include <thread>
#include <map>

void hello(){
  std::cout<<"Hello worlds!"<<std::endl;
}

struct background_task{
  void operator()() const {
    std::cout<<"background...\n";
  }
};

int main(){
  auto lambda = []{
    std::cout<<"Hello lambda!"<<std::endl;
  };

  background_task bt;
  
  std::thread t(hello);
  std::thread lthread(lambda);
  std::thread bthread(bt);

  std::map<std::thread::id, std::thread> threads;
  threads[t.get_id()] = std::move(t);
  threads[lthread.get_id()] = std::move(lthread); 
  threads[bthread.get_id()] = std::move(bthread);

  for(auto& id_thread: threads)
    if(id_thread.second.joinable())
      id_thread.second.detach();
}





