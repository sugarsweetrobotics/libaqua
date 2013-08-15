/********************************************************
 * SerialPort.h
 *
 * Portable Thread Class Library for Windows and Unix.
 * @author ysuga@ysuga.net
 * @date 2010/11/02
 ********************************************************/

#ifndef THREAD_HEADER_INCLUDED
#define THREAD_HEADER_INCLUDED

#ifdef WIN32
// �ȉ��� ifdef �u���b�N�� DLL ����̃G�N�X�|�[�g��e�Ղɂ���}�N�����쐬���邽�߂� 
// ��ʓI�ȕ��@�ł��B���� DLL ���̂��ׂẴt�@�C���́A�R�}���h ���C���Œ�`���ꂽ LIBROOMBA_EXPORTS
// �V���{���ŃR���p�C������܂��B���̃V���{���́A���� DLL ���g���v���W�F�N�g�Œ�`���邱�Ƃ͂ł��܂���B
// �\�[�X�t�@�C�������̃t�@�C�����܂�ł��鑼�̃v���W�F�N�g�́A 
// LIBREVAST_API �֐��� DLL ����C���|�[�g���ꂽ�ƌ��Ȃ��̂ɑ΂��A���� DLL �́A���̃}�N���Œ�`���ꂽ
// �V���{�����G�N�X�|�[�g���ꂽ�ƌ��Ȃ��܂��B
#ifdef _USRDLL
#define LIBTHREAD_API __declspec(dllexport)
#else
#define LIBTHREAD_API __declspec(dllimport)
#endif

#else
#define LIBTHREAD_API 


#endif // ifdef WIN32


#ifdef WIN32
#include <windows.h>
#define THREAD_ROUTINE DWORD WINAPI
#else
#include <pthread.h>
#define THREAD_ROUTINE void*
#endif


namespace net {
	namespace ysuga {

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

		class Thread
		{
		private:
#ifdef WIN32
			HANDLE m_Handle;
			DWORD m_ThreadId;
#else
			pthread_t m_Handle;
#endif
		public:
			LIBTHREAD_API Thread(void);
			LIBTHREAD_API virtual ~Thread(void);

		public:
			LIBTHREAD_API void Start();

			LIBTHREAD_API virtual void Run() {};

			LIBTHREAD_API void Join();

			LIBTHREAD_API void Exit(unsigned long exitCode);

		public:
			LIBTHREAD_API static void Sleep(unsigned long milliSeconds);
		};

	};
};


#endif

/*******************************************************
 * Copyright  2010, ysuga.net all rights reserved.
 *******************************************************/
