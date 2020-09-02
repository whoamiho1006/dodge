#pragma once
#include "Dodge/Types.h"

namespace dodge {
	struct FColor;

	struct DODGE_API FByteColor {
		uint8_t R, G, B, A;

		constexpr FByteColor(uint8_t Graytone = 255, uint8_t A = 255)
			:R(Graytone), G(Graytone), B(Graytone), A(A)
		{
		}

		constexpr FByteColor(uint8_t R, uint8_t G, uint8_t B, uint8_t A = 255)
			: R(R), G(G), B(B), A(A)
		{
		}

		inline FColor ToColor() const;
	};

	struct DODGE_API FColor {
		float R, G, B, A;

		constexpr FColor(float Graytone = 1.0f, float A = 1.0f) 
			:R(Graytone), G(Graytone), B(Graytone), A(A)
		{
		}

		constexpr FColor(float R, float G, float B, float A = 1.0f)
			: R(R), G(G), B(B), A(A)
		{
		}

		inline FByteColor ToByteColor() const;
	};


	inline FColor FByteColor::ToColor() const {
		return FColor((uint8_t)(R / 255.0f), (uint8_t)(G / 255.0f), 
					  (uint8_t)(B / 255.0f), (uint8_t)(A / 255.0f));
	}

	inline FByteColor FColor::ToByteColor() const {
		return FByteColor(
			(uint8_t)(R * 255.0f), (uint8_t)(G * 255.0f),
			(uint8_t)(B * 255.0f), (uint8_t)(A * 255.0f)
		);
	}

	struct EColor {
		static constexpr FColor White = FColor(1, 1, 1, 1);
		static constexpr FColor Black = FColor(0, 0, 0, 1);
		static constexpr FColor Transparent = FColor(0, 0, 0, 0);
	};
}