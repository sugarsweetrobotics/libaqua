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
#else // WIN32
    int m_ServerSocket;

    struct sockaddr_in m_SockAddr;//,caddr;
    //    char buf[BUFSIZ];

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
      close(m_ServerSocket);
    }

    void Bind(const unsigned int port) {
      memset((char*)&m_SockAddr, 0, sizeof(m_SockAddr));
      m_SockAddr.sin_family      = AF_INET;
      m_SockAddr.sin_addr.s_addr = INADDR_ANY;
      m_SockAddr.sin_port        = htons(port);

      if(bind(m_ServerSocket, (struct sockaddr*)&m_SockAddr, sizeof(m_SockAddr))<0) {
	throw SocketException("Bind Failed.");
      }
    }

    void Listen(const unsigned int backlog = 5) {
      if (listen(m_ServerSocket, backlog) < 0) {
	throw SocketException("Listen Failed.");
      }
    }


    Socket Accept() {
      struct sockaddr_in sockaddr_;
      int client_sock;
      socklen_t len;
      len = sizeof(sockaddr_);
      if ((client_sock = accept(m_ServerSocket, (struct sockaddr*)&sockaddr_, &len)) < 0) {
	throw SocketException("Accept Failed.");
      }
      return Socket(client_sock, sockaddr_);
    }

    
  };

};
