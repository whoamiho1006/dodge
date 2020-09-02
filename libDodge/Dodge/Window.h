#pragma once
#include "Dodge/Types.h"
#include "Dodge/Math/Vector.h"
#include "Dodge/Math/Rectangle.h"

namespace dodge {
	class FEngine;
	class FGraphics;
	class FWindowClass;

	/* 창 인스턴스를 표현합니다. */
	class DODGE_API FWindow : public IObject {
		friend class FEngine;
		friend class FWindowClass;

	protected:
		FWindow(const FIntVector2& Resolution);

	public:
		virtual ~FWindow();

	public:
		static bool DoEvents(bool& bOutExit);

	private:
		FIntVector2 Size;
		FString Title;
		void* hWnd;

	public:
		inline bool IsValid() const { return hWnd != nullptr; }
		inline void* GetRawWindow() const { return hWnd; }

	public:
		/* 창 크기를 획득합니다. */
		inline const FIntVector2& GetSize() const { return Size; }

		/* 창 제목을 획득합니다. */
		inline const FString& GetTitle() const { return Title; }

		/* 창 제목을 설정합니다.*/
		void SetTitle(const FString&);

		/* 이 창을 닫습니다. (엔진 창은 닫으면 엔진이 종료됩니다) */
		void Close();

		inline float GetAspectRatio() const { return Size.X / Size.Y; }
	};
}