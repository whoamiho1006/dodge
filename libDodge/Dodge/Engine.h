#pragma once
#include "Dodge/Types.h"
#include "Dodge/Window.h"

#include "Dodge/Inputs/InputManager.h"
#include "Dodge/Graphics/Graphics.h"

#include "Dodge/Math/Vector.h"
#include "Dodge/Scenes/Scene.h"

namespace dodge {
	class DODGE_API FEngine {
	public:
		static FEngine& Get();

	private:
		FEngine();
		~FEngine();

	private:
		bool bInitialized, bFirstStep;
		TObjectPtr<FWindow> Window;
		TObjectPtr<FGraphics> Graphics;
		TObjectPtr<FInputManager> Inputs;
		uint64_t LatestTicks;

		TObjectPtr<IScene> Scene;

	public:
		/* ´åÁö ¿£ÁøÀ» ÃÊ±âÈ­ÇÕ´Ï´Ù. */
		bool Init(const FIntVector2& Resolution = FIntVector2(1024, 768));

		/* ´åÁö Ã¢ ¸Þ½ÃÁö¸¦ Ã³¸®ÇÏ°í, ´ÙÀ½ ÇÁ·¹ÀÓÀ» ·»´õ¸µÇÒ ÁØºñ¸¦ ÇÕ´Ï´Ù. */
		bool Step();

		/* ´åÁö ¿£ÁøÀ» Á¾·á½ÃÅµ´Ï´Ù. */
		void DeInit();

		/* ´åÁö ¾ÀÀ» È¹µæÇÕ´Ï´Ù. */
		const TObjectPtr<IScene>& GetScene() const { return Scene; }

		/* ´åÁö ¾ÀÀ» ÀúÀåÇÕ´Ï´Ù.*/
		void SetScene(TObjectPtr<IScene> Scene) {
			this->Scene = Scene;
		}
		
	public:
		/* Å¸±ê Ã¢À» È¹µæÇÕ´Ï´Ù. */
		const TObjectPtr<FWindow>& GetWindow() const { return Window; }

		/* Å¸±ê ±×·¡ÇÈ °´Ã¼¸¦ È¹µæÇÕ´Ï´Ù. */
		const TObjectPtr<FGraphics>& GetGraphics() const { return Graphics; }

		/* Å¸±ê ÀÔ·Â °ü¸®ÀÚ °´Ã¼¸¦ È¹µæÇÕ´Ï´Ù. */
		const TObjectPtr<FInputManager>& GetInputs() const { return Inputs; }
	};
}