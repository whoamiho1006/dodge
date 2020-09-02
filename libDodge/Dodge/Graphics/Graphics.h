#pragma once
#include "Dodge/Types.h"
#include "Dodge/Color.h"
#include "Dodge/Window.h"
#include "Dodge/Math/Rectangle.h"

namespace dodge {
	class FWindow;
	class FEngine;
	class FBitmap;

	class DODGE_API FGraphics : public IObject {
		friend class FEngine;

	protected:
		FGraphics(const TObjectPtr<FWindow>& Window);

	public:
		FGraphics(const TObjectPtr<FBitmap>& Bitmap);

	public:
		virtual ~FGraphics() { }

	private:
		TObjectPtr<FWindow> Window;
		TObjectPtr<FBitmap> Bitmap;
		void* hDC, *hWndDC;
		void* hOldBitmap;
		void* hPen, *hBrush;
		bool bFromWindow;

	private:
		FColor Brush;
		FColor Pen;

	public:
		/* 이 그래픽 객체가 유효한지 검사합니다. */
		inline bool IsValid() const { return Bitmap; }

		/* 이 그래픽 객체가 그리기 모드에 진입했는지 검사합니다. */
		inline bool IsBegan() const { return Bitmap && hDC; }

		/* 이 그래픽 객체로 뭔가 그립니다. */
		bool Begin(bool bClear = false, const FColor& Color = FColor());

		/* 이 그래픽 객체로 그리던 것을 중단합니다. */
		bool End();

	private:
		bool SetColor(const FColor& Brush, const FColor& Pen);

	public:
		bool DrawRectangle(const FRectangle& Rect, const FColor& Color = FColor());
		bool DrawLine(const FVector2& Starts, const FVector2& Ends, const FColor& Color = FColor());
		bool DrawDot(const FVector2& Point, const FColor& Color = FColor());
		bool DrawString(const FVector2& Point, const FString& Text, const FColor& Color = FColor());
	};

}