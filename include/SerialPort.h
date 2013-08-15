/********************************************************
 * SerialPort.h
 *
 * Portable Serial Port Class Library for Windows and Unix.
 * @author ysuga (Sugar Sweet Robotics Co., LTD.
 * @date 2010/11/02
 ********************************************************/

#pragma once

#include <exception>
#include <string>

#ifdef WIN32
#include <windows.h>
#endif



#include <exception>
#include <string>

namespace ssr {
  class ComException : public std::exception {
  private:
    std::string msg;
  public:
    ComException(const char* msg) {this->msg = msg;}
    ~ComException() throw() {}

 public:
  virtual const char* what() const throw() {return msg.c_str();}
  };

  /**
   * @brief This exception is thrown when Accessing COM Port (Read/Write) is failed.
   */
  class  ComAccessException : public ComException {
  public:
  ComAccessException(void) : ComException("COM Access") {}
    ~ComAccessException(void) throw()	{}
  };

  /**
   * @brief This exception is thrown when Opening COM port is failed.
   */
  class ComOpenException : public ComException  {
  public:
  ComOpenException(void) : ComException ("COM Open Error") {}
    ~ComOpenException(void) throw() {}
  };

  /**
   * @brief  This exception is thrown when COM port state is wrong.
   */
  class ComStateException : public ComException {
  public:
  ComStateException(void) : ComException ("COM State Exception") {}      
    ~ComStateException(void) throw() {}
  };


  /***************************************************
   * SerialPort
   *
   * @brief Portable Serial Port Class
   ***************************************************/
  class SerialPort {
  private:
#ifdef WIN32
    HANDLE m_hComm;
#else

    /**
     * @brief file descriptor
     */
    int m_Fd;
#endif
    
  public:
    /**
     * @brief Constructor
     * 
     * @param filename Filename of Serial Port (eg., "COM0", "/dev/tty0")
     * @baudrate baudrate. (eg., 9600, 115200)
     */
    SerialPort(const char* filename, int baudrate);
    
    /**
     * @brief Destructor
     */
    ~SerialPort();
    
  public:
    /**
     * @brief flush receive buffer.
     * @return zero if success.
     */
    void FlushRxBuffer();
    
    /**
     * @brief flush transmit buffer.
     * @return zero if success.
     */
    void FlushTxBuffer();
    
  public:
    /**
     * @brief Get stored datasize of in Rx Buffer
     * @return Stored Data Size of Rx Buffer;
     */
    int GetSizeInRxBuffer();
    
    /**
     * @brief write data to Tx Buffer of Serial Port.
     *
     */
    int Write(const void* src, const unsigned int size);
    
    /**
     * @brief read data from RxBuffer of Serial Port 
     */
    int Read(void *dst, const unsigned int size);
    
  };
  
};//namespace ssr



/*******************************************************
 * Copyright  2010, ysuga.net all rights reserved.
 *******************************************************/
