#pragma once
#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <math.h>

struct screen_vector
{
	int16_t x;
	int16_t y;

	bool operator ==(screen_vector other)
	{
		return other.x == this->x && other.y == this->y;
	}
};

struct tetromino
{
	tetromino(const uint8_t new_color_code, const std::initializer_list<screen_vector> args) : elements(args), color_code(new_color_code) {}

	inline auto operator[] (const size_t index) -> screen_vector&
	{
		return this->elements[index];
	}

	inline auto get_elements() -> std::vector<screen_vector>&
	{
		return this->elements;
	}
	
	inline constexpr auto get_color() -> const uint8_t
	{
		return this->color_code;
	}
	
	inline auto get_size() -> const size_t
	{
		return this->elements.size();
	}

	inline auto rotate(double angle) -> tetromino
	{
		auto degree_to_radian = [](double angle)
		{
			return angle * (M_PI / 180);
		};

		auto copy = *this;

		for (auto& part : copy.get_elements())
		{
			// ROTATING A 2D VECTOR CLOCK-WISE 
			// IS SIMPLE: (y, -x)
			// IN THIS CASE Y COORDINATE IS MIRRORED DUE TO 
			// SCREEN BUFFER STARTING FROM TOP-LEFT (READ CRT WIKIPEDIA)
			// SO CLOCKWISE ROTATION IS (-y, x)
			auto& [x, y] = part;
			const auto old_x = x;
			x = -y;
			y = old_x;
		}

		return copy;
	}

private:
	std::vector<screen_vector> elements;
	uint8_t color_code;
};