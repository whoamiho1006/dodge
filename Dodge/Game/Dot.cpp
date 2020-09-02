#include "Dot.h"

namespace game {

	void FDot::Tick(float DeltaSeconds) {
		auto Size = FEngine::Get().GetWindow()->GetSize();
		Position += Direction * DeltaSeconds * Speed;

		if (Position.X < 0 || Position.Y < 0 ||
			Position.X > Size.X || Position.Y > Size.Y)
		{
			Direction *= -1.0f;
			++Bounces;
		}
	}

	void FDot::Render(TObjectPtr<FGraphics> Graphics) {
		Graphics->DrawRectangle(
			FRectangle(
				Position - FVector2(2),
				Position + FVector2(2)
			),
			Color
		);
	}

}