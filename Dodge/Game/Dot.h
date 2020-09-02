#pragma once
#include "Dodge/Dodge.h"

namespace game {
	using namespace dodge;

	class FDot : public IScene {
	private:
		FVector2 Position, Direction;
		FVector2 Size;
		float Speed;
		int32_t Bounces;

		FColor Color;
		
	public:
		FDot(const FVector2& Position, const FVector2& Direction, float Speed)
			: IScene(0x1000), Position(Position), Direction(Direction), Speed(Speed)
		{
			auto R = FVector2::Rand() * 0.75f;
			Size = FVector2(1, 1);
			Color = FColor(R.X, R.Y, (R.X + R.Y) * 0.5f);
			Bounces = 0;
		}

		~FDot() { }

	public:
		void Tick(float DeltaSeconds) override;
		void Render(TObjectPtr<FGraphics> Graphics) override;

	public:
		inline const FVector2& GetPosition() const { return Position; }
		inline const FVector2& GetDirection() const { return Direction; }
		inline const FVector2& GetSize() const { return Size; }
		inline const FColor& GetColor() const { return Color; }
		inline float GetSpeed() const { return Speed; }
		inline int32_t GetBounces() const { return Bounces; }

		inline void SetPosition(const FVector2& Position) { this->Position = Position; }
		inline void SetDirection(const FVector2& Direction) { this->Direction = Direction; }
		inline void SetSize(const FVector2& Size) { this->Size = Size; }
		inline void SetSpeed(float Speed) { this->Speed = Speed; }

	public:

	};
}