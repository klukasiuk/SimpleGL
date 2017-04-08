#pragma once

enum KeyboardKey
{
	Key_Unknown = -1,

	Key_A = 65,
	Key_B = 66,
	Key_C = 67,
	Key_D = 68,
	Key_E = 69,
	Key_F = 70,
	Key_G = 71,
	Key_H = 72,
	Key_I = 73,
	Key_J = 74,
	Key_K = 75,
	Key_L = 76,
	Key_M = 77,
	Key_N = 78,
	Key_O = 79,
	Key_P = 80,
	Key_Q = 81,
	Key_R = 82,
	Key_S = 83,
	Key_T = 84,
	Key_U = 85,
	Key_V = 86,
	Key_W = 87,
	Key_X = 88,
	Key_Y = 89,
	Key_Z = 90,

	Key_0 = 48,
	Key_1 = 49,
	Key_2 = 50,
	Key_3 = 51,
	Key_4 = 52,
	Key_5 = 53,
	Key_6 = 54,
	Key_7 = 55,
	Key_8 = 56,
	Key_9 = 57,

	Key_Space  =  32,
	Key_Escape = 256,
	Key_Enter  = 257,
	Key_Tab    = 258,
	Key_Delete = 261,

	Key_Up    = 265,
	Key_Down  = 264,
	Key_Left  = 263,
	Key_Right = 262
};

enum MouseButton
{
	Mouse_Left   = 0,
	Mouse_Right  = 1,
	Mouse_Middle = 2
};

enum InputAction
{
	Released = 0,			// Key/Button was released
	Pressed  = 1,			// Key/Button was pressed
	Repeat   = 2			// Key/Button was hold until it repeated
};