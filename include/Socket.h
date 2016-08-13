#pragma once

#include <stdint.h>
#include <exception>
#include <string>
#include <sstream>
#include "SerialDevice.h"

#ifdef WIN32

#else // WIN32
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif // WIN32

namespace ssr {

  class SocketException : public std::exception {
  private:
    std::string msg;
  public:
  SocketException() : msg("Unknown") {}
  SocketException(const char* msg_) : msg(msg_) {}
    ~SocketException() throw() {}


  public:
    const char* what() const throw() {
      return (("SocketException: ") + msg).c_str();
    }

  };

  /**
   * class Socket.
   */
  class Socket : public SerialDevice {
  private:

#ifdef WIN32


#else // WIN32
    int m_Socket;
    struct sockaddr_in  m_SockAddr;
    struct hostent*     m_HostEnt;
#endif // WIN32


  public:
    /**
     * Constructor
     */
    Socket(const char* address, const uint32_t port) {
      if ((m_Socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
	throw SocketException("socket function failed.");
      }

      memset((char*)&m_SockAddr, 0, sizeof(m_SockAddr));

      if( (m_HostEnt=gethostbyname(address))==NULL) {
	throw SocketException("gethostbyname failed.");
      }

      bcopy(m_HostEnt->h_addr, &m_SockAddr.sin_addr, m_HostEnt->h_length);
      m_SockAddr.sin_family = AF_INET;
      m_SockAddr.sin_port   = htons(port);

      if (connect(m_Socket, (struct sockaddr *)&m_SockAddr, sizeof(m_SockAddr)) < 0){
	std::ostringstream ss;
	ss << "Connect Failed. (address=" << address << ", port=" << port << ")";
	throw SocketException(ss.str().c_str());
      }
    }

    /**
     * Desctructor
     */
    ~Socket() {
      close(m_Socket);
    }

    int GetSizeInRxBuffer() {
      return -1;
    }

    int Write(const void* src, const unsigned int size) {
      return -1;
    }

    int Read(void* dst, const unsigned int size) {
      return -1;
    }

    int Close() {
      if (close(m_Socket)< 0) {
	return -1;
      }
      return 0;
    }
  };
};
