#pragma once
#include "Dodge/Types.h"
#include "Dodge/Scenes/Scene.h"
#include <vector>

namespace dodge {
	class DODGE_API FOverlayedScene : public IScene {
	public:
		FOverlayedScene(int32_t SceneId) : IScene(SceneId) { }
		virtual ~FOverlayedScene() { }

	protected:
		std::vector<TObjectPtr<IScene>> Scenes;

	public:
		inline std::vector<TObjectPtr<IScene>>& GetScenes() { return Scenes; }
		inline const std::vector<TObjectPtr<IScene>>& GetScenes() const { return Scenes; }

	public:
		virtual void Tick(float DeltaSeconds);

		/* 씬을 그립니다. */
		virtual void Render(TObjectPtr<FGraphics> Graphics);
	};
}