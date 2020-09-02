#define _CRT_SECURE_NO_WARNINGS 1
#include "SceneGame.h"
#include "../Intro/SceneIntro.h"
#include "Dot.h"

#include <stdio.h>

namespace game {

	const dodge::TObjectPtr<game::FSceneGame>& FSceneGame::Get() {
		static dodge::TObjectPtr<game::FSceneGame> _Instance = new FSceneGame();
		return _Instance;
	}

	void FSceneGame::Begin() {
		Inputs = Engine.GetInputs();
		Level = 0; MaxDots = 150;
		InputSeconds = 0;
		GameOver = false;

		(Player = Engine.GetWindow()->GetSize()) *= 0.5f;
	}

	void FSceneGame::End() {
		
	}

	void FSceneGame::Tick(float DeltaSeconds) {
		if (!GameOver) {
			if (Dots.size() <= 0) {
				++Level; MaxDots *= 2;

				for (int32_t i = 0; i < MaxDots; i++) {
					float RS = FVector2::Rand().X;

					if (RS < 0.02) {
						RS = 0.02;
					}

					Dots.push_back(new FDot(
						FVector2::Rand() * Engine.GetWindow()->GetSize(),
						FVector2::Rand(), RS * 100.0f
					));
				}
			}

			BounceAndDelete(DeltaSeconds);
			HandleInputs(DeltaSeconds);

			for (auto& Dot : Dots) {
				const auto& Pos = Dot->GetPosition();
			
				if ((Player.X - 5 < Pos.X && Player.X + 5 > Pos.X) &&
					(Player.Y - 5 < Pos.Y && Player.Y + 5 > Pos.Y))
				{
					// 충돌 발생. 게임오버.
					GameOver = true;
					break;
				}
			}
		}

		else if (Inputs->IsKeyDownNow(EKEY_ENTER)) {
			Engine.SetScene(FSceneIntro::Get());
			Inputs->Reset();
		}

		TextBlink += DeltaSeconds;
	}

	void FSceneGame::BounceAndDelete(float DeltaSeconds)
	{
		std::vector<int32_t> Deletes;
		int32_t i = 0;

		for (auto& Each : Dots) {
			Each->Tick(DeltaSeconds);

			if (Each->GetBounces() >= 3) {
				Deletes.push_back(i);
			}

			++i;
		}

		for (auto iter = Deletes.rbegin(); iter != Deletes.rend(); iter++) {
			this->Dots.erase(this->Dots.begin() + *iter);
		}
	}

	void FSceneGame::HandleInputs(float DeltaSeconds)
	{
		FVector2 Direction, MaxVector = Engine.GetWindow()->GetSize();

		if (Inputs->IsKeyDown(EKEY_UP)) { Direction.Y -= 1; }
		if (Inputs->IsKeyDown(EKEY_DOWN)) { Direction.Y += 1; }

		if (Inputs->IsKeyDown(EKEY_LEFT)) { Direction.X -= 1; }
		if (Inputs->IsKeyDown(EKEY_RIGHT)) { Direction.X += 1; }


		if (Direction.GetSizeSquad() > 0) {
			Player += Direction.Normalize() * DeltaSeconds * 200.0f;
			InputSeconds = 0.0f;
		}

		Player.X = Player.X < 0 ? 0 : Player.X;
		Player.X = Player.X > MaxVector.X ? MaxVector.X : Player.X;

		Player.Y = Player.Y < 0 ? 0 : Player.Y;
		Player.Y = Player.Y > MaxVector.Y ? MaxVector.Y : Player.Y;
	}

	void FSceneGame::Render(TObjectPtr<FGraphics> Graphics) {
		char Buffer[256] = { 0, };
		char Buffer2[256] = { 0, };
		IScene::Render(Graphics);

		for (auto& Each : Dots) {
			Each->Render(Graphics);
		}

		/* 플레이어 도트를 그립니다.*/
		Graphics->DrawRectangle(FRectangle(
			Player - FVector2(5, 5),
			Player + FVector2(5, 5)
		), FColor(1, 0, 0));

		if (GameOver) {
			sprintf(Buffer, "Level: %d (%d / %d) - GAME OVER!", Level, Dots.size(), MaxDots);

			if (TextBlink > 0.5f) {
				sprintf(Buffer2, "PRESS ENTER TO RETURN BACK.", Level, Dots.size(), MaxDots);
				if (TextBlink > 1.0f) {
					TextBlink = 0.0f;
				}
			}
		}

		else {
			sprintf(Buffer, "Level: %d (%d / %d)", Level, Dots.size(), MaxDots);
		}

		Graphics->DrawString(FVector2(20, 20), Buffer, FColor(0, 1));
		Graphics->DrawString(FVector2(20, 40), Buffer2, FColor(0, 1));
	}

}

