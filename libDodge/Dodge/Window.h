#pragma once
#include "Dodge/Types.h"
#include "Dodge/Math/Vector.h"
#include "Dodge/Math/Rectangle.h"

namespace dodge {
	class FEngine;
	class FGraphics;
	class FWindowClass;

	/* â �ν��Ͻ��� ǥ���մϴ�. */
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
		/* â ũ�⸦ ȹ���մϴ�. */
		inline const FIntVector2& GetSize() const { return Size; }

		/* â ������ ȹ���մϴ�. */
		inline const FString& GetTitle() const { return Title; }

		/* â ������ �����մϴ�.*/
		void SetTitle(const FString&);

		/* �� â�� �ݽ��ϴ�. (���� â�� ������ ������ ����˴ϴ�) */
		void Close();

		inline float GetAspectRatio() const { return Size.X / Size.Y; }
	};
}