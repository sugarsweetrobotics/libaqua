/**
 * @file Timer.h 
 * @author Yuki Suga (ysuga.net), Yuki Nakagawa (RT Corp.), Motomasa Tanaka (Mayekawa MFC Co., Ltd.)
 * @copyright RT Corp. 2012 All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "type.h"
#include "TimeSpec.h"

#ifdef WIN32
#include <windows.h>
#include <mmsystem.h>
#else
#include <string.h>
#endif

/**
 * @if jp
 * @brief Ssrライブラリ用の名前空間
 * @else
 * @brief Namespace for Ssr Library
 * @endif
 */
namespace ssr {

  /**
   * @class Timer
   * @if jp
   * @brief タイマー（時間計測）のラッパークラス
   * @else
   * @brief Timer class
   * @endif
   */
  class AQUA_API Timer
  {
  private:
#ifdef WIN32
    LARGE_INTEGER m_Frequency;
    LARGE_INTEGER m_Before;
    LARGE_INTEGER m_After;
#endif

  public:
    
    
    /**
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    Timer(void) {
#ifdef WIN32
      memset(&m_Frequency, 0, sizeof(LARGE_INTEGER));
      memset(&m_Before, 0, sizeof(LARGE_INTEGER));
      memset(&m_After, 0, sizeof(LARGE_INTEGER));
      QueryPerformanceFrequency(&m_Frequency);
#endif

    }
    
    /**
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~Timer(void) {
    }
    
  public:

    /**
     * @if jp
     * @brief 計測開始
     * @else
     * @brief Start Measurement
     * @endif
     */
    void tick(void) {
#ifdef WIN32
      ::QueryPerformanceCounter(&m_Before);	
#else

#endif
    }
    
    /**
     * @if jp
     * @brief 計測処理（タイマは停止せず）
     * @param currentTime [OUT] Measured Time
     * @else
     * @brief Measure
     * @endif
     */
    void tack(TimeSpec* currentTime) {
#ifdef WIN32
	QueryPerformanceCounter(&m_After);
	DWORD dwTime = (DWORD)((m_After.QuadPart - m_Before.QuadPart) * 1000000 / m_Frequency.QuadPart);
	pCurrentTime->sec =  dwTime / 1000000;
	pCurrentTime->usec = dwTime % 1000000;
#else

#endif
    }

  };
}

