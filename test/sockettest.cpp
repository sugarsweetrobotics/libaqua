
#include <stdlib.h>
#include <iostream>
#include "Socket.h"

using namespace ssr;
int main(int argc, char* argv[]) {
  try {
    std::cout << "Socket Test." << std::endl;

    if (argc <= 2) return -1;
    Socket socket(argv[1], atoi(argv[2]));
    
    if (socket.Close() < 0) {
      std::cout << "Close Failed." << std::endl;
      return -1;
    }
  } catch (std::exception& ex) {
    std::cout << "exception:" << ex.what() << std::endl;
    return -1;
  }
  return 0;
}
