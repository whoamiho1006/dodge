#pragma once
#include "Dodge/Types.h"
#include "Dodge/Graphics/Graphics.h"
#include "Dodge/Graphics/Bitmap.h"

namespace dodge {
	class DODGE_API IScene : public IObject {
	protected:
		IScene(int32_t SceneId) : SceneId(SceneId) { }
		virtual ~IScene() { }

	private:
		int32_t SceneId;

	public:
		inline int32_t GetSceneId() const { return SceneId; }

	public:
		virtual void Begin() { }
		virtual void End() { }

		virtual void Tick(float DeltaSeconds) { }

		/* 씬을 그립니다. */
		virtual void Render(TObjectPtr<FGraphics> Graphics) { }
	};
}