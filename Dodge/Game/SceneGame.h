#pragma once
#include "Dodge/Dodge.h"
#include <vector>

namespace game {
	using namespace dodge;
	class FDot;

	class FSceneGame : public IScene {
	private:
		FEngine& Engine;

		TObjectPtr<FInputManager> Inputs;
		std::vector<TObjectPtr<FDot>> Dots;

		int32_t Level;
		int32_t MaxDots;
		float InputSeconds;
		float TextBlink;

		FVector2 Player;
		bool GameOver;

	private:
		FSceneGame()
			: IScene(0), Engine(FEngine::Get())
		{
		}

	public:
		~FSceneGame() { }

	public:
		static const TObjectPtr<FSceneGame>& Get();

	public:
		virtual void Begin() override;
		virtual void End() override;

	public:
		virtual void Tick(float DeltaSeconds) override;

		void HandleInputs(float DeltaSeconds);

		void BounceAndDelete(float DeltaSeconds);
		virtual void Render(TObjectPtr<FGraphics> Graphics) override;
	};

}
