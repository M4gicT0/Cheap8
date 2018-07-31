/*
 * Screen.h
 * Copyright (C) 2018 transpalette <transpalette@translaptop>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SCREEN_H
#define SCREEN_H

#include <atomic>
#include <cstdint>
#include <ncurses.h>

#define SCALE_FACTOR 1
#define SCREEN_WIDTH 64 * SCALE_FACTOR
#define SCREEN_HEIGHT 32 * SCALE_FACTOR

class Screen
{
private:
  std::atomic<uint8_t> mBuffer[SCREEN_WIDTH][SCREEN_HEIGHT];
  WINDOW* mWindow;

public:
  Screen();
  ~Screen();
  bool TogglePixel(uint8_t x, uint8_t y);
  void Draw();
  void Clear();
  WINDOW* GetHandle();
  void Resize();
  void Terminate();
};

#endif /* !SCREEN_H */
