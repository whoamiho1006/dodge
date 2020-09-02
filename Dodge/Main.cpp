#include "Dodge/Dodge.h"

#include "Game/Dot.h"
#include "Intro/SceneIntro.h"

#include <Windows.h>

#pragma comment(lib, "libdodge.lib")

using namespace dodge;
using namespace game;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
	FEngine& Engine = FEngine::Get();

	if (Engine.Init(FVector2(800, 600))) {
		Engine.GetWindow()->SetTitle("Dodge");
		Engine.SetScene(FSceneIntro::Get());

		while (Engine.Step());

		Engine.DeInit();
		return 0;
	}

	return -1;
}
