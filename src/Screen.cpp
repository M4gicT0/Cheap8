/*
 * Screen.cpp
 * Copyright (C) 2018 transpalette <transpalette@translaptop>
 *
 * Distributed under terms of the MIT license.
 */

#include "Screen.h"

#include <cstring>
#include <iostream>

Screen::Screen()
{
  /* ncurses */
  initscr();
  cbreak();
  noecho();
  /* Clear the buffer */
  Clear();
  mWindow = newwin(SCREEN_HEIGHT + 2, SCREEN_WIDTH + 2, 5, 5);
  nodelay(stdscr, TRUE); // <- de-blocking the user input
  keypad(stdscr, TRUE);
  box(mWindow, 0, 0);
  wrefresh(mWindow);
}

Screen::~Screen()
{
  Terminate();
}

void
Screen::Terminate()
{
  delwin(mWindow);
  endwin();
}

void
Screen::Clear()
{
  memset(mBuffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(mBuffer[0][0]));
}

bool
Screen::TogglePixel(uint8_t x, uint8_t y)
{
  if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
    return false;

  bool collision = mBuffer[x][y] == 1;
  mBuffer[x][y] ^= 1;

  return collision;
}

void
Screen::Draw()
{
  for (int x = 0; x < SCREEN_WIDTH; x++) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
      mvwaddch(mWindow, y + 1, x + 1, mBuffer[x][y] == 1 ? ACS_BLOCK : ' ');
    }
  }
  box(mWindow, 0, 0);
  wrefresh(mWindow);
}

void
Screen::Resize()
{
  // TODO
  int nh, nw;
  getmaxyx(stdscr, nh, nw); /* get the new screen size */
}

void
Screen::Beep(int duration)
{
  std::cout << "\a";
  beep();
  printf("beeping");
}
