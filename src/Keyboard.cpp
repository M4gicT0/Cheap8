/*
 * Keyboard.cpp
 * Copyright (C) 2018 transpalette <transpalette@translaptop>
 *
 * Distributed under terms of the MIT license.
 */

#include "Keyboard.h"

#include <thread>
#include <ncurses.h>

Keyboard* Keyboard::mInstance = nullptr;

Keyboard::Keyboard()
{
	mListening = false;
	for (auto& key : mKeys)
		key = false;
}

Keyboard::~Keyboard()
{
	delete mInstance;
}

uint8_t
Keyboard::ReadKey()
{
	bool noKeyPress = true;
	uint8_t key;
	while (noKeyPress) {
		for (int i = 0; i < 16; i++) {
			if (Keyboard::mKeys[i]) {
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
	while (mListening) {
		nodelay(mWindow, TRUE); // <- de-blocking
		int c = getch(); // Blocking!
		switch (c) {
			case ERR: // No input
				break;
			case 'W':
				break;
			case 'A':
				break;
			case 'S':
				break;
			case 'D':
				break;
		}
	}
}

void
Keyboard::StartListening(WINDOW* win)
{
	if (!mListening) {
		mListening = true;
		mWindow = win;
		std::thread(&Keyboard::ListenerThread, this).detach();
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

Keyboard*
Keyboard::GetInstance()
{
    if (!Keyboard::mInstance)
		Keyboard::mInstance = new Keyboard();

    return Keyboard::mInstance;
}
