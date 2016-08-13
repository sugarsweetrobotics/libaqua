#pragma once

#include <stdint.h>
#include "SerialDevice.h"

namespace ssr {

  /**
   * class Socket.
   */
  class Socket : public SerialDevice {

  public:
    /**
     * Constructor
     */
    Socket(const void* address, const uint32_t port) {

    }

    /**
     * Desctructor
     */
    ~Socket() {

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
      return -1;
    }
  };
};
