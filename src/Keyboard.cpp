/*
 * Keyboard.cpp
 * Copyright (C) 2018 transpalette <transpalette@translaptop>
 *
 * Distributed under terms of the MIT license.
 */

#include "Keyboard.h"
#include "Chip8.h"
#include "Screen.h"
#include "Timer.h"

#include <ncurses.h>
#include <string>
#include <thread>

using namespace std::chrono_literals;

Keyboard::Keyboard(Chip8* chip)
{
  mChip = chip;
  mListening = false;
  for (int i = 0; i < 16; i++)
    mKeys[i] = false;
}

Keyboard::~Keyboard() {}

uint8_t
Keyboard::ReadKey()
{
  bool noKeyPress = true;
  uint8_t key;
  while (noKeyPress && mListening) {
    for (int i = 0; i < 16; i++) {
      if (mKeys[i]) {
        key = i;
        noKeyPress = false;
      }
    }
  }

  return key;
}

void
Keyboard::ListenerThread()
{
  Timer timer;
  while (mListening) {
    for (int i = 0; i < 16; i++) {
      if ((mKeys[i] && timer.ElapsedMilliseconds() >= 300)) {
        mKeys[i] = false;
        timer.Stop();
        timer.Reset();
      }
    }

    int c = getch();
    std::string mapping("0123456789abcdef");
    if (c != ERR) {
      if (c == 27 || c == 'q') // ESC or Q
        mChip->Stop();

      if (mapping.find(c)) {
        mKeys[mapping.find(c)] = true;
        timer.Start();
      }
    }

    std::this_thread::sleep_for(20ms);
  }
  timer.Stop();
}

void
Keyboard::StartListening()
{
  if (!mListening) {
    mListening = true;
    std::thread tListener(&Keyboard::ListenerThread, this);
    tListener.detach();
  }
}

void
Keyboard::StopListening()
{
  mListening = false;
}

bool
Keyboard::IsKeyPressed(uint8_t x)
{
  return mKeys[x];
}
