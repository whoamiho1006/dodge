#pragma once
#include "Dodge/Types.h"
#include "Dodge/Math/Vector.h"

namespace dodge {

	class DODGE_API FBitmap : public IObject {
	public:
		FBitmap(const FIntVector2& Size);
		~FBitmap();

	private:
		FIntVector2 Size;
		void* hBitmap;

	public:
		/* ��Ʈ�� ũ�⸦ ȹ���մϴ�. */
		inline const FIntVector2& GetSize() const { return Size; }

		/* �ο� ��Ʈ���� ȹ���մϴ�. (HBITMAP) */
		inline void* GetRawBitmap() const { return hBitmap; }
	};
}