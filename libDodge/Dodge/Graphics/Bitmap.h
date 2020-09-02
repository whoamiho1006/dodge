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
		/* ∫Ò∆Æ∏  ≈©±‚∏¶ »πµÊ«’¥œ¥Ÿ. */
		inline const FIntVector2& GetSize() const { return Size; }

		/* ∑ŒøÏ ∫Ò∆Æ∏ ¿ª »πµÊ«’¥œ¥Ÿ. (HBITMAP) */
		inline void* GetRawBitmap() const { return hBitmap; }
	};
}