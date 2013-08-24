/********************************************************
 * SerialPort.h
 *
 * Portable Thread Class Library for Windows and Unix.
 * @author ysuga@ysuga.net
 * @date 2010/11/02
 ********************************************************/
#pragma once

#include "aqua.h"

#ifdef WIN32
#include <windows.h>
#define THREAD_ROUTINE DWORD WINAPI
#else
#include <time.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#define THREAD_ROUTINE void*
#endif

namespace ssr {

  /**
   *
   */
  class Mutex {
  private:
#ifdef WIN32
    HANDLE m_Handle;
#else
    pthread_mutex_t m_Handle;
#endif
    
    
  public:
    Mutex() {
#ifdef WIN32
      m_Handle = ::CreateMutex(NULL, 0, NULL);
#else
      pthread_mutex_init(&m_Handle, NULL);
#endif
    }
    
    virtual ~Mutex() {
#ifdef WIN32
      ::CloseHandle(m_Handle);
#else
      pthread_mutex_destroy(&m_Handle);
#endif
    }
    
  public:
    void Lock() {
#ifdef WIN32
      ::WaitForSingleObject(m_Handle, INFINITE);
#else
      pthread_mutex_lock(&m_Handle);
#endif
    }
    
    void Unlock() {
#ifdef WIN32
      ::ReleaseMutex(m_Handle);
#else
      pthread_mutex_unlock(&m_Handle);
#endif
    }
  };

  /**
   *
   */
  class MutexBinder {
  private:
    Mutex& m_mutex;
  public:
  MutexBinder(Mutex& mutex) : m_mutex(mutex) {m_mutex.Lock();}
    ~MutexBinder() {m_mutex.Unlock();}
  };

  static THREAD_ROUTINE StartRoutine(void* arg)
  {
    Thread* threadObject = (Thread*)arg;
    threadObject->Run();
    threadObject->Exit(0);
#ifdef WIN32
    ExitThread(0);
#else 
    pthread_exit(0);
#endif
    return 0;
  }
  
  /**
   *
   */
  class Thread {
  private:
#ifdef WIN32
    HANDLE m_Handle;
    DWORD m_ThreadId;
#else
    pthread_t m_Handle;
#endif
  public:

    /**
     *
     */
    Thread(void) {
    }

    virtual ~Thread(void) {
    }
    
  public:
    void Start() {
#ifdef WIN32
	m_Handle = CreateThread(NULL, 0, StartRoutine, (LPVOID)this, 0, &m_ThreadId);
#else
	int ret = pthread_create(&m_Handle, NULL, StartRoutine, (void*)this);
	if(ret != 0) {
	  perror("pthread_create");
	}
#endif
    }

    
    virtual void Run() = 0;
    
    void Join() {
#ifdef WIN32
      WaitForSingleObject(m_Handle, INFINITE);
#else
      void* retval;
      pthread_join(m_Handle, &retval);
#endif
    }
    
    void Exit(unsigned long exitCode) {
#ifdef WIN32
	::Sleep(milliSeconds);
#else
  struct timespec interval;
  interval.tv_sec = milliSeconds / 1000;
  interval.tv_nsec = (milliSeconds % 1000) * 1000000;
  nanosleep(&interval, NULL);
#endif
    }
    
  public:
    static void Sleep(unsigned long milliSeconds) {
#ifdef WIN32
	ExitThread(exitCode);
#else
	pthread_exit(0);
#endif
    }
  };
};



/*******************************************************
 * Copyright  2010, ysuga.net all rights reserved.
 *******************************************************/
