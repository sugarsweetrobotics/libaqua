#include <stdlib.h>
#include <exception>

#include <iostream>
#include "ServerSocket.h"
using namespace ssr;

int main(int argc, char* argv[]) {
  std::cout << "Server Test." << std::endl;
  try {
    if (argc <= 1) throw SocketException("Invalid Argument");
    ServerSocket socket;
    socket.bind(atoi(argv[1]));
    socket.listen();
  
  } catch (std::exception& ex) {
    std::cout << "exception: " << ex.what() << std::endl;
    return -1;
  }
  return 0;
}
