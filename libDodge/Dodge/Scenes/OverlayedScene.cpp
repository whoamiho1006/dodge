#include "OverlayedScene.h"

namespace dodge {

	void FOverlayedScene::Tick(float DeltaSeconds) {
		std::vector<TObjectPtr<IScene>> Scenes = this->Scenes;

		for (auto& Scene : Scenes) {
			if (Scene) {
				Scene->Tick(DeltaSeconds);
			}
		}
	}

	void FOverlayedScene::Render(TObjectPtr<FGraphics> Graphics) {
		std::vector<TObjectPtr<IScene>> Scenes = this->Scenes;

		for (auto& Scene : Scenes) {
			if (Scene) {
				Scene->Render(Graphics);
			}
		}
	}

}

