#include "Bitmap.h"
#include <Windows.h>

namespace dodge {

	FBitmap::FBitmap(const FIntVector2& Size)
		: Size(Size)
	{
		hBitmap = CreateBitmap(Size.X, Size.Y, 1, 32, nullptr);
	}

	FBitmap::~FBitmap() {
		if (hBitmap) {
			DeleteObject((HGDIOBJ) hBitmap);
		}
	}

}