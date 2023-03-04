#ifndef LIGHTNING_CORE
#define LIGHTNING_CORE

#include <SDL.h>

#include <bitset>

inline SDL_Window* window{};
inline SDL_Renderer* renderer{};
inline SDL_Event e{};
inline SDL_DisplayMode screen{};
inline SDL_Texture* monitor{};
inline Uint8* pixels{};

inline int pixelsSize{};
inline int pixelsPitch{};

inline constexpr int SYSCALLS	{ 0x000000 };
inline constexpr int VIDEO		{ 0xa11000 };

namespace Lightning::Core
{
	inline bool running{};
	inline bool chipSelected{}; // 0 for ROM, 1 for RAM

	inline unsigned char RAM[1 << 24]{};	// 16MB virtual
	inline constexpr unsigned char ROM[1 << 12]	// 4KB virtual
	{
		0b00000'1'00, 0x00, 0x00, 0x20,

		0b10010'0'00, 0x00, 0x00, 0x00,
		0b10011'1'00, 0x00, 0x00, 0x01,
		0b01000'1'00, 0x00, 0x00, 0x3f,
		0b01111'1'00, 0x00, 0x00, 0x04,

		0b01001'1'01, 0x00, 0x00, 0x00,
	};

	inline constexpr unsigned char font[]
	{
		// 0x00
		0xff, 0xff, 0xff,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0x80, 0x00, 0x01,
		0xff, 0xff, 0xff,

		// 0x01
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x02
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x03
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x04
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x05
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x06
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x07
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x08
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x09
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x0a
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x0b
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x0c
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x0d
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x0e
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x0f
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x10
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x11
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x12
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x13
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x14
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x15
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x16
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x17
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x18
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x19
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x1a
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x1b
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x1c
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x1d
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x1e
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x1f
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,

		// 0x20
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,

		// 0x21
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00111100, 0b00000000,
		0b00000000, 0b00111100, 0b00000000,
		0b00000000, 0b00111100, 0b00000000,
		0b00000000, 0b00111100, 0b00000000,
		0b00000000, 0b00111100, 0b00000000,
		0b00000000, 0b00111100, 0b00000000,
		0b00000000, 0b00111100, 0b00000000,
		0b00000000, 0b00111100, 0b00000000,
		0b00000000, 0b00111100, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00111100, 0b00000000,
		0b00000000, 0b00111100, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,

		// 0x22
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b11000011, 0b00000000,
		0b00000000, 0b11000011, 0b00000000,
		0b00000000, 0b11000011, 0b00000000,
		0b00000000, 0b11000011, 0b00000000,
		0b00000000, 0b11000011, 0b00000000,
		0b00000000, 0b11000011, 0b00000000,
		0b00000000, 0b11000011, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,

		// 0x23
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b11000000, 0b11000000,
		0b00000000, 0b11000000, 0b11000000,
		0b00000000, 0b11000000, 0b11000000,
		0b00000000, 0b11000000, 0b11000000,
		0b00000000, 0b11000000, 0b11000000,
		0b00000000, 0b11000000, 0b11000000,
		0b00000001, 0b11000001, 0b11000000,
		0b00000001, 0b11000001, 0b11000000,
		0b00011111, 0b11111111, 0b11111000,
		0b00000001, 0b10000001, 0b10000000,
		0b00000001, 0b10000001, 0b10000000,
		0b00000001, 0b10000001, 0b10000000,
		0b00000001, 0b10000001, 0b10000000,
		0b00000001, 0b10000001, 0b10000000,
		0b00000011, 0b10000011, 0b10000000,
		0b00000011, 0b10000011, 0b10000000,
		0b00000011, 0b00000011, 0b00000000,
		0b00011111, 0b11111111, 0b11111000,
		0b00000011, 0b00000011, 0b00000000,
		0b00000011, 0b00000011, 0b00000000,
		0b00000011, 0b00000011, 0b00000000,
		0b00000111, 0b00000111, 0b00000000,
		0b00000111, 0b00000111, 0b00000000,
		0b00000110, 0b00000110, 0b00000000,
		0b00000110, 0b00000110, 0b00000000,
		0b00000110, 0b00000110, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,

		// 0x24
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b11111111, 0b00000000,
		0b00000001, 0b11011011, 0b10000000,
		0b00000011, 0b00011001, 0b11000000,
		0b00000110, 0b00011000, 0b01100000,
		0b00001100, 0b00011000, 0b00110000,
		0b00001100, 0b00011000, 0b00000000,
		0b00001100, 0b00011000, 0b00000000,
		0b00001100, 0b00011000, 0b00000000,
		0b00000110, 0b00011000, 0b00000000,
		0b00000011, 0b10011000, 0b00000000,
		0b00000000, 0b11111000, 0b00000000,
		0b00000000, 0b00011111, 0b00000000,
		0b00000000, 0b00011001, 0b11000000,
		0b00000000, 0b00011000, 0b01100000,
		0b00000000, 0b00011000, 0b00110000,
		0b00000000, 0b00011000, 0b00110000,
		0b00000000, 0b00011000, 0b00110000,
		0b00001100, 0b00011000, 0b00110000,
		0b00000110, 0b00011000, 0b01100000,
		0b00000011, 0b10011000, 0b11000000,
		0b00000001, 0b11011011, 0b10000000,
		0b00000000, 0b11111111, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,

		// 0x25
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00110000,
		0b00000111, 0b10000000, 0b00110000,
		0b00001100, 0b01100000, 0b01100000,
		0b00011000, 0b00110000, 0b11000000,
		0b00011000, 0b00110000, 0b11000000,
		0b00011000, 0b00110001, 0b10000000,
		0b00011000, 0b00110011, 0b00000000,
		0b00001100, 0b01100011, 0b00000000,
		0b00000111, 0b10000110, 0b00000000,
		0b00000000, 0b00001100, 0b00000000,
		0b00000000, 0b00001100, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00110000, 0b00000000,
		0b00000000, 0b00110000, 0b00000000,
		0b00000000, 0b01100001, 0b11100000,
		0b00000000, 0b11000110, 0b00110000,
		0b00000000, 0b11001100, 0b00011000,
		0b00000001, 0b10001100, 0b00011000,
		0b00000011, 0b00001100, 0b00011000,
		0b00000011, 0b00001100, 0b00011000,
		0b00000110, 0b00000110, 0b00110000,
		0b00001100, 0b00000001, 0b11100000,
		0b00001100, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,

		// 0x26
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b01111110, 0b00000000,
		0b00000000, 0b11000011, 0b00000000,
		0b00000001, 0b10000001, 0b10000000,
		0b00000001, 0b10000001, 0b10000000,
		0b00000001, 0b10000001, 0b10000000,
		0b00000001, 0b10000001, 0b10000000,
		0b00000000, 0b11000011, 0b00000000,
		0b00000000, 0b01100110, 0b00000000,
		0b00000000, 0b00111100, 0b00000000,
		0b00000000, 0b00111000, 0b00000000,
		0b00000000, 0b01111000, 0b00000000,
		0b00000001, 0b11011000, 0b00110000,
		0b00000011, 0b00001100, 0b00110000,
		0b00000110, 0b00001100, 0b01100000,
		0b00000110, 0b00000110, 0b01100000,
		0b00001100, 0b00000110, 0b01100000,
		0b00001100, 0b00000011, 0b11000000,
		0b00001100, 0b00000011, 0b11000000,
		0b00001100, 0b00000001, 0b11000000,
		0b00001100, 0b00000001, 0b10000000,
		0b00001110, 0b00000011, 0b11000000,
		0b00000111, 0b00000110, 0b11110000,
		0b00000001, 0b11111100, 0b01111000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,

		// 0x27
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,

		// 0x28
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00001100, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00110000, 0b00000000,
		0b00000000, 0b00110000, 0b00000000,
		0b00000000, 0b01100000, 0b00000000,
		0b00000000, 0b01100000, 0b00000000,
		0b00000000, 0b01100000, 0b00000000,
		0b00000000, 0b11000000, 0b00000000,
		0b00000000, 0b11000000, 0b00000000,
		0b00000000, 0b11000000, 0b00000000,
		0b00000000, 0b11000000, 0b00000000,
		0b00000000, 0b11000000, 0b00000000,
		0b00000000, 0b11000000, 0b00000000,
		0b00000000, 0b11000000, 0b00000000,
		0b00000000, 0b11000000, 0b00000000,
		0b00000000, 0b11000000, 0b00000000,
		0b00000000, 0b11000000, 0b00000000,
		0b00000000, 0b11000000, 0b00000000,
		0b00000000, 0b11000000, 0b00000000,
		0b00000000, 0b01100000, 0b00000000,
		0b00000000, 0b01100000, 0b00000000,
		0b00000000, 0b01100000, 0b00000000,
		0b00000000, 0b00110000, 0b00000000,
		0b00000000, 0b00110000, 0b00000000,
		0b00000000, 0b00011000, 0b00000000,
		0b00000000, 0b00001100, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
		0b00000000, 0b00000000, 0b00000000,
	};

	namespace Threads
	{
		inline SDL_Thread* CPU{};
	}

	void init();
	int cycle();
	void quit();
}

#endif