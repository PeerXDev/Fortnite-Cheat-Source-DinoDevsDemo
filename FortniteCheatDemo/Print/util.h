#pragma once

#include <iostream>
#include <Windows.h>
#include <winsvc.h>
#include <random>
#include <winioctl.h>
#pragma warning(disable:4191 4099)
#pragma warning(disable:4996)

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LVGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

namespace Abdul
{
	RECT rc;

	/* set the gay fucking color */
	void SetPenisRep(unsigned short color)
	{
		HANDLE con = 0;
		con = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(con, color);
	}

	/* clear the console */
	void Clear()
	{
		COORD topLeft = { 0, 0 };
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO screen;
		DWORD written;
		GetConsoleScreenBufferInfo(console, &screen);
		FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
		FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
		SetConsoleCursorPosition(console, topLeft);
		return;
	}

}