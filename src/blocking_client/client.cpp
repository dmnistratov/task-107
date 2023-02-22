#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <thread>

using boost::asio::ip::tcp;

enum { max_length = 1024 };

void run_client(char* host, char* port, int loops){  
  try
  {
    boost::asio::io_context io_context;

    tcp::socket s(io_context);
    tcp::resolver resolver(io_context);
    boost::asio::connect(s, resolver.resolve(host, port));

    for (auto i = 0; i < loops; i++){
      std::string message = "Hello, world!";
      boost::asio::write(s, boost::asio::buffer(message.c_str(), message.size()));
      
      char reply[max_length];
      boost::asio::read(s,boost::asio::buffer(reply, message.size()));
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
}

int main(int argc, char* argv[])
{
  if (argc != 5){
    std::cerr << "Usage: blocking_tcp_echo_client <host> <port> <threads> <loops>\n";
    return 1;
  }

  std::vector <std::thread> thread_pool;
  size_t thread_pool_size = std::stoi(argv[3]);
  thread_pool.reserve(thread_pool_size);

  for(int i = 0; i < thread_pool_size; i++){   
      thread_pool.push_back(std::thread(run_client, argv[1], argv[2], std::stoi(argv[4])));
  } 

  for(auto &t: thread_pool){
       t.join();
   }
  return 0;
}