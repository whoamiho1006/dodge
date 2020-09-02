#include "SceneIntro.h"
#include "../Game/Dot.h"
#include "../Game/SceneGame.h"

namespace game {

	const TObjectPtr<FSceneIntro>& FSceneIntro::Get() {
		static TObjectPtr<FSceneIntro> _Instance = new FSceneIntro();
		return _Instance;
	}

	void FSceneIntro::Begin() {
		Inputs = Engine.GetInputs();

		for (int32_t i = 0; i < 1000; i++) {
			Dots.push_back(new FDot(
				FVector2::Rand() * Engine.GetWindow()->GetSize(),
				FVector2::Rand(), FVector2::Rand().X * 100.0f
			));
		}
	}

	void FSceneIntro::End() {
		Dots.clear();
	}

	void FSceneIntro::Tick(float DeltaSeconds) {
		IScene::Tick(DeltaSeconds);

		if (Inputs->IsKeyUpNow(EKEY_DOWN)) {
			Selection = (Selection + 1) % 2;
		}

		if (Inputs->IsKeyUpNow(EKEY_UP)) {
			Selection = Selection > 0 ? (Selection - 1) % 2 : 1;
		}

		if (Inputs->IsKeyUpNow(EKEY_ENTER)) {
			switch (Selection) {
				case 0:
					Engine.SetScene(FSceneGame::Get());
					break;

				case 1:
					Engine.DeInit();
					break;
			}
		}

		BounceAndRespawn(DeltaSeconds);

	}

	void FSceneIntro::BounceAndRespawn(float DeltaSeconds) {
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

		for (int32_t i = Dots.size(); i < 1000; i++) {
			Dots.push_back(new FDot(
				FVector2::Rand() * Engine.GetWindow()->GetSize(),
				FVector2::Rand(), FVector2::Rand().X * 100.0f
			));
		}
	}

	void FSceneIntro::Render(TObjectPtr<FGraphics> Graphics) {
		IScene::Render(Graphics);
		for (auto& Each : Dots) {
			Each->Render(Graphics);
		}

		float BottomY = Engine.GetWindow()->GetSize().Y - 200.0f;
		float SelectorY = Selection * 30.0f;

		Graphics->DrawString(FVector2(50, BottomY + SelectorY), ">", FColor(1, 0, 0));
		Graphics->DrawString(FVector2(60, BottomY), "1. Start New Game", FColor(0, 0, 0, 1));
		Graphics->DrawString(FVector2(60, BottomY + 30.0f), "2. Exit", FColor(0, 0, 0, 1));
		Graphics->DrawString(FVector2(10, BottomY + 130.0f), "Copyright (C) 2020 Jay K, all rights reserved.", FColor(0, 0, 0, 1));
	}

}