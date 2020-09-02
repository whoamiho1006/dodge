#include "Window.h"
#include "Engine.h"
#include <Windows.h>

namespace dodge {
	class FWindowClass {
	private:
		WNDCLASSEXA WndCX;
		TObjectPtr<FInputManager> Inputs;

	public:
		FWindowClass() {
			ZeroMemory(&WndCX, sizeof(WndCX));
			WndCX.cbSize = sizeof(WndCX);

			WndCX.style = CS_HREDRAW | CS_VREDRAW;
			WndCX.cbClsExtra = 0;
			WndCX.cbWndExtra = 0;
			WndCX.hInstance = GetModuleHandle(NULL);
			WndCX.hIcon = LoadIcon(WndCX.hInstance, IDI_APPLICATION);
			WndCX.hCursor = LoadCursor(nullptr, IDC_ARROW);
			WndCX.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
			WndCX.hIconSm = WndCX.hIcon;
			WndCX.lpszClassName = "DODGE";
			WndCX.lpfnWndProc = WndProc;

			RegisterClassExA(&WndCX);
		}

	public:
		static FWindowClass& Get() {
			static FWindowClass WindowClass;
			return WindowClass;
		}

	private:
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
			switch (message) {
			case WM_CLOSE:
			case WM_DESTROY:
				PostQuitMessage(0);
				return 1;
			}

			return Get().OnWndProc(hWnd, message, wParam, lParam);
		}

		inline LRESULT OnWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
			switch(message) {
			case WM_KEYDOWN:
				if (!Inputs) {
					Inputs = FEngine::Get().GetInputs();
				}

				if (Inputs) {
					Inputs->Update(wParam, true);
				}
				return 1;

			case WM_KEYUP:
				if (!Inputs) {
					Inputs = FEngine::Get().GetInputs();
				}

				if (Inputs) {
					Inputs->Update(wParam, false);
				}
				return 1;
			}

			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	};

	FWindow::FWindow(const FIntVector2& Resolution)
		: Size(Resolution)
	{
		FWindowClass& Windows = FWindowClass::Get();
		HINSTANCE hInst = GetModuleHandle(NULL);

		hWnd = CreateWindowA("DODGE", "Dodge", 
			WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
			CW_USEDEFAULT, CW_USEDEFAULT, Resolution.X, Resolution.Y,
			nullptr, nullptr, hInst, nullptr);

		if (hWnd) {
			ShowWindow((HWND) hWnd, 1);
			UpdateWindow((HWND)hWnd);
		}
	}

	FWindow::~FWindow()
	{
		if (hWnd) {
			DestroyWindow((HWND) hWnd);
		}
	}

	bool FWindow::DoEvents(bool& bOutExit) {
		MSG Message = { 0, };
		bOutExit = false;

		if (PeekMessageA(&Message, nullptr, 0, 0, PM_REMOVE)) {
			if (Message.message == WM_QUIT) {
				bOutExit = true;
			}

			TranslateMessage(&Message);
			DispatchMessage(&Message);
			return true;
		}

		::Sleep(10);
		return false;
	}

	void FWindow::Close() {
		if (hWnd) {
			DestroyWindow((HWND)hWnd);
		}
	}

	void FWindow::SetTitle(const FString& Title) {
		SetWindowTextA((HWND)hWnd, Title.c_str());
	}

}