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
		/* �� �׷��� ��ü�� ��ȿ���� �˻��մϴ�. */
		inline bool IsValid() const { return Bitmap; }

		/* �� �׷��� ��ü�� �׸��� ��忡 �����ߴ��� �˻��մϴ�. */
		inline bool IsBegan() const { return Bitmap && hDC; }

		/* �� �׷��� ��ü�� ���� �׸��ϴ�. */
		bool Begin(bool bClear = false, const FColor& Color = FColor());

		/* �� �׷��� ��ü�� �׸��� ���� �ߴ��մϴ�. */
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