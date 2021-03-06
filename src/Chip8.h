/*
 * Chip8.h
 * Copyright (C) 2018 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef CHIP8_H
#define CHIP8_H

#include "CPU.h"

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <mutex>
#include <thread>

class Chip8
{
private:
  std::atomic<bool> mRunning;
  CPU* mCpu;
  Memory* mRam;
  Screen* mScreen;
  Keyboard* mKeyboard;
  std::condition_variable mDrawAction;
  std::mutex mtx;
  std::thread tUI;
  std::thread tCPU;
  std::thread tTimers;

  void UpdateTimers();
  void Init();
  void CPULoop();
  void UILoop();

public:
  Chip8(Screen* screen);
  ~Chip8();
  void Run();
  void Stop();
  void Load(const char* file_name);
};

#endif /* !CHIP8_H */
