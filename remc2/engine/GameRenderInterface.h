#pragma once

#ifndef GAME_RENDER_INTERFACE
#define GAME_RENDER_INTERFACE

#include <cstdint>
#include "engine_support.h"
#include "ViewPort.h"

enum class SpritePass : uint32_t
{
	Shadow = 0,
	Main = 1,
	Reflection = 2
};

inline uint8_t ClampReflectionTexel(int texel, const uint8_t* tile)
{
	if (texel & 0x8000)//row -1 (0xFF..) and lower
		texel &= 0xFF;
	return tile[texel];
};

class GameRenderInterface
{
public:
	virtual ~GameRenderInterface() {}
	virtual void DrawWorld_411A0(int posX, int posY, int16_t yaw, int16_t posZ, int16_t pitch, int16_t roll, int16_t fov) = 0;
	// the in-between frames: the part of a step (0 - 1) over the yaw, pitch and roll of the next DrawWorld_411A0, so the view
	// turns by less than a step (2048 steps a full turn: at 4K a step of the yaw is several pixels); 0 = whole steps
	virtual void SetAngleFractions(double /*yaw*/, double /*pitch*/, double /*roll*/) {}
};

#endif //GAME_RENDER_INTERFACE