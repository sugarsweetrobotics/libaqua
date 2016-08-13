#pragma once


#include <stdint.h>
#include "SerialDevice.h"
#include "Socket.h"

#ifdef WIN32

#else // WIN32

#endif

namespace ssr {


  class ServerSocket {

  private:
#ifdef WIN32
    int m_SeverSocket;

    struct sockaddr_in m_SockAddr;//,caddr;
    char buf[BUFSIZ];
#else // WIN32

#endif

    
  public:
    ServerSocket() {
      if( (m_ServerSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) { 
	throw SocketException("socket failed.");
      }
    }

    ~ServerSocket() {
    }


  public:

    void Close() {
      throw SocketException("Close failed.");
    }

    void Bind(const unsigned int port) {
      memset((char*)&m_SockAddr, 0, sizeof(saddr));
      m_SockAddr.sin_family      = AF_INET;
      m_SockAgit ddr.sin_addr.s_addr = INADDR_ANY;
  saddr.sin_port        = htons(PORT);

  if( bind(s1, (struct sockaddr*)&saddr, sizeof(saddr))<0) {
    perror("bind");    exit(1);
  }

      throw SocketException("Bind Failed.");
    }


    void Listen(const unsigned int backlog = 5) {
      throw SocketException("Listen Failed.");
    }


    Socket Accept() {
      throw SocketException("Accept Failed.");
    }
  };

};
