#pragma once


#include <stdint.h>
#include "SerialDevice.h"
#include "Socket.h"

namespace ssr {


  class ServerSocket {
    
  public:
    ServerSocket(const unsigned int port) {

    }


    ~ServerSocket() {
    }


  public:
    
    int bind() {
      return -1;
    }


    int listen(const unsigned int backlog = 5) {
      return -1;
    }


    Socket* accept() {
      return NULL;
    }


  };
};
