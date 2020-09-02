#include "Dodge/Engine.h"
#include "Dodge/Window.h"
#include "Dodge/Graphics/Graphics.h"
#include "Dodge/Graphics/Bitmap.h"
#include "Dodge/Inputs/InputManager.h"

#include <Windows.h>

namespace dodge {

	FEngine& FEngine::Get() {
		static FEngine Engine;
		return Engine;
	}

	FEngine::FEngine() 
		: bInitialized(false), bFirstStep(true)
	{
	
	}

	FEngine::~FEngine() {

	}

	bool FEngine::Init(const FIntVector2& Resolution) {
		if (!bInitialized) {
			bInitialized = true;

			if (!(Window = new FWindow(Resolution))->IsValid()) {
				bInitialized = false;
				return false;
			}

			Graphics = new FGraphics(Window);
			Inputs = new FInputManager();
			LatestTicks = uint64_t(GetTickCount64());

			srand((uint32_t) LatestTicks);
			return true;
		}

		return false;
	}

	bool FEngine::Step() {
		if (bInitialized) {
			bool bExit = false;
			
			if (!FWindow::DoEvents(bExit)) {
				uint64_t Ticks = uint64_t(GetTickCount64());
				float ElapsedTicks = (LatestTicks > Ticks ? 
					Ticks : Ticks - LatestTicks) * 0.001f;

				TObjectPtr<IScene> Scene = this->Scene;

				LatestTicks = Ticks;
				if (Scene) {
					if (bFirstStep) {
						bFirstStep = false;

						Scene->Begin();
					}

					/* ¾ÀÀ» ¾÷µ¥ÀÌÆ®ÇÏ°í, */
					Scene->Tick(ElapsedTicks);

					if (Graphics->Begin(true, FColor(1, 1))) {
						/* ¾ÀÀ» ·»´õ¸µÇÕ´Ï´Ù. */
						Scene->Render(Graphics);
						Graphics->End();
					}
				}

				if (Scene != this->Scene) {
					if (this->Scene) {
						this->Scene->Begin();
					}

					if (Scene) {
						Scene->End();
					}
				}

				Inputs->Update();
			}

			if (bExit) {
				Window = nullptr;
			}

			return !bExit;
		}

		return false;
	}

	
	void FEngine::DeInit() {
		if (Window) { 
			Window->Close(); 
		}
	}

}