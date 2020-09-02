#include "Graphics.h"
#include "Dodge/Engine.h"
#include "Dodge/Window.h"
#include "Dodge/Graphics/Bitmap.h"

#include <Windows.h>

namespace dodge {

	FGraphics::FGraphics(const TObjectPtr<FWindow>& Window)
		: Window(Window), hDC(0), bFromWindow(true)
	{
		if (Window) {
			Bitmap = new FBitmap(Window->GetSize());
		}
	}

	FGraphics::FGraphics(const TObjectPtr<FBitmap>& Bitmap)
		: Bitmap(Bitmap), hDC(0), bFromWindow(false)
	{
		Window = FEngine::Get().GetWindow();
	}

	bool FGraphics::Begin(bool bClear /*= false*/, const FColor& Color /*= FColor()*/) {
		if (Window && Bitmap && !hDC) {
			HWND hWnd = (HWND)Window->GetRawWindow();
			HBITMAP hBitmap = (HBITMAP)Bitmap->GetRawBitmap();

			hWndDC = ::GetDC((HWND)Window->GetRawWindow());
			hDC = ::CreateCompatibleDC((HDC)hWndDC);
			
			// hDC의 타깃 비트맵을 전환합니다.
			hOldBitmap = ::SelectObject((HDC) hDC, hBitmap);
			::SetBkMode((HDC)hDC, TRANSPARENT);
			/*::SetBkColor((HDC)hDC, 0);*/

			if (bClear) {
				RECT Rect;
				SetColor(Color, Color);

				Rect.top = Rect.left = 0; 
				Rect.right = Bitmap->GetSize().X;
				Rect.bottom = Bitmap->GetSize().Y;

				// 비트맵 전체를 지정된 색상으로 채웁니다.
				::FillRect((HDC)hDC, &Rect, NULL);
			}

			Brush = FColor(0, 0);
			Pen = FColor(1, 1);
			return true;
		}

		return false;
	}

	bool FGraphics::End() {
		if (Bitmap && hDC) {
			HWND hWnd = (HWND)Window->GetRawWindow();

			if (bFromWindow) {
				::BitBlt((HDC)hWndDC, 0, 0,
					Bitmap->GetSize().X, Bitmap->GetSize().Y,
					(HDC)hDC, 0, 0, SRCCOPY);
			}

			::SelectObject((HDC)hDC, hOldBitmap);
			::ReleaseDC(hWnd, (HDC)hDC);
			::DeleteDC((HDC)hWndDC);

			if (this->hBrush) {
				DeleteObject(this->hBrush);
			}

			if (this->hPen) {
				DeleteObject(this->hPen);
			}

			hDC = hWndDC = nullptr;
			hPen = hBrush = nullptr;
			hOldBitmap = nullptr;
			return true;
		}

		return false;
	}

	bool FGraphics::SetColor(const FColor& Brush, const FColor& Pen) {
		if (IsBegan()) {
			FByteColor PenColor = Pen.ToByteColor();
			FByteColor BrushColor = Brush.ToByteColor();

			HBRUSH hBrush = CreateSolidBrush(RGB(
				BrushColor.R, BrushColor.G, BrushColor.B
			));

			HPEN hPen = CreatePen(PS_SOLID, 1, RGB(
				BrushColor.R, BrushColor.G, BrushColor.B
			));

			if (this->hBrush) {
				DeleteObject(this->hBrush);
			}

			if (this->hPen) {
				DeleteObject(this->hPen);
			}

			SelectObject((HDC)hDC, this->hBrush = hBrush);
			SelectObject((HDC)hDC, this->hPen = hPen);
			return true;
		}

		return false;
	}

	bool FGraphics::DrawRectangle(const FRectangle& Rect, const FColor& Color /*= FColor()*/) {
		if (IsBegan()) {
			FIntVector2 TopLeft = Rect.GetTopLeft();
			FIntVector2 BottomRight = Rect.GetBottomRight();

			if (TopLeft.X < 0) TopLeft.X = 0;
			if (TopLeft.Y < 0) TopLeft.Y = 0;
			if (BottomRight.X < 0) BottomRight.X = 0;
			if (BottomRight.Y < 0) BottomRight.Y = 0;

			SetColor(Color, Pen);
			::Rectangle((HDC)hDC, TopLeft.X, 
				TopLeft.Y, BottomRight.X, BottomRight.Y);

			return true;
		}

		return false;
	}

	bool FGraphics::DrawLine(const FVector2& Starts, const FVector2& Ends, const FColor& Color /*= FColor()*/) {
		if (IsBegan()) {
			FIntVector2 IntStarts = Starts;
			FIntVector2 IntEnds = Ends;

			SetColor(Color, Pen);

			::MoveToEx((HDC)hDC, IntStarts.X, IntStarts.Y, NULL);
			::LineTo((HDC)hDC, IntEnds.X, IntEnds.Y);
			return true;
		}

		return false;
	}

	bool FGraphics::DrawDot(const FVector2& Point, const FColor& Color /*= FColor()*/) {
		if (IsBegan()) {
			FVector2 Pt1 = Point;
			FVector2 Pt2 = Point;

			return DrawRectangle(FRectangle(
				Pt1 -= FVector2(1, 1), Pt2 += FVector2(1, 1)
			), Color);
		}

		return false;
	}

	bool FGraphics::DrawString(const FVector2& Point, const FString& Text, const FColor& Color /*= FColor()*/) {
		if (IsBegan()) {
			RECT Rect = { 0, };

			Rect.left = (int32_t)Point.X;
			Rect.top = (int32_t)Point.Y;
			Rect.right = (int32_t)Window->GetSize().X;
			Rect.bottom = (int32_t)Window->GetSize().Y;

			::DrawTextA((HDC)hDC, Text.c_str(), Text.size(), &Rect, 0);
			return true;
		}

		return false;
	}

}