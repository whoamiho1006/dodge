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
		/* ���� ������ �ʱ�ȭ�մϴ�. */
		bool Init(const FIntVector2& Resolution = FIntVector2(1024, 768));

		/* ���� â �޽����� ó���ϰ�, ���� �������� �������� �غ� �մϴ�. */
		bool Step();

		/* ���� ������ �����ŵ�ϴ�. */
		void DeInit();

		/* ���� ���� ȹ���մϴ�. */
		const TObjectPtr<IScene>& GetScene() const { return Scene; }

		/* ���� ���� �����մϴ�.*/
		void SetScene(TObjectPtr<IScene> Scene) {
			this->Scene = Scene;
		}
		
	public:
		/* Ÿ�� â�� ȹ���մϴ�. */
		const TObjectPtr<FWindow>& GetWindow() const { return Window; }

		/* Ÿ�� �׷��� ��ü�� ȹ���մϴ�. */
		const TObjectPtr<FGraphics>& GetGraphics() const { return Graphics; }

		/* Ÿ�� �Է� ������ ��ü�� ȹ���մϴ�. */
		const TObjectPtr<FInputManager>& GetInputs() const { return Inputs; }
	};
}