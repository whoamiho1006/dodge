#pragma once
#include "Dodge/Dodge.h"
#include "Dodge/Scenes/OverlayedScene.h"
#include <vector>

namespace game {
	using namespace dodge;
	class FDot;

	class FSceneIntro : public IScene {
	private:
		FEngine& Engine;
		int32_t Selection;

		TObjectPtr<FInputManager> Inputs;
		std::vector<TObjectPtr<FDot>> Dots;

	private:
		FSceneIntro() 
			: IScene(0), Engine(FEngine::Get())
		{
			Selection = 0;
		}

	public:
		~FSceneIntro() { }

	public:
		static const TObjectPtr<FSceneIntro>& Get();

	public:
		virtual void Begin() override;
		virtual void End() override;

	public:
		virtual void Tick(float DeltaSeconds) override;
		void BounceAndRespawn(float DeltaSeconds);
		virtual void Render(TObjectPtr<FGraphics> Graphics) override;
	};

}
