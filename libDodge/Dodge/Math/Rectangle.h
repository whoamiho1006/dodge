#pragma once
#include "Dodge/Types.h"
#include "Dodge/Math/Vector.h"

namespace dodge {
	template<typename ElemType>
	struct TRectangle {
		using VectorType = TVector2<ElemType>;

		VectorType TopLeft, BottomRight;

		constexpr TRectangle() : TopLeft(0), BottomRight(0) { }
		constexpr TRectangle(VectorType Value) : TopLeft(Value), BottomRight(Value) { }
		constexpr TRectangle(VectorType A, VectorType B) : TopLeft(A), BottomRight(B) { }

		inline bool operator ==(const VectorType& Other) const { return this == &Other || (TopLeft == Other.TopLeft && BottomRight == Other.BottomRight); }
		inline bool operator !=(const VectorType& Other) const { return this != &Other && (TopLeft != Other.TopLeft || BottomRight != Other.BottomRight); }

		inline TRectangle<ElemType> Normalize() {
			return TRectangle<ElemType>(
				VectorType::MinVector(TopLeft, BottomRight),
				VectorType::MaxVector(TopLeft, BottomRight)
			);
		}

		inline double GetSize() const { return sqrt(TopLeft.GetSize() * BottomRight.GetSize()); }
		inline double GetSizeSquad() const { return TopLeft.GetSize() * BottomRight.GetSize(); }

		inline VectorType GetTopLeft() const { return TopLeft; }
		inline VectorType GetBottomRight() const { return BottomRight; }

		inline VectorType GetTopRight() const { return VectorType(BottomRight.X, TopLeft.Y); }
		inline VectorType GetBottomLeft() const { return VectorType(TopLeft.X, BottomRight.Y); }

		inline TRectangle<ElemType>& operator +=(const VectorType& Other) { TopLeft += Other; BottomRight += Other; return *this; }
		inline TRectangle<ElemType>& operator -=(const VectorType& Other) { TopLeft -= Other; BottomRight -= Other; return *this; }

		inline TRectangle<ElemType> operator +(const VectorType& Other) { return TRectangle<ElemType>(TopLeft + Other, BottomRight + Other); }
		inline TRectangle<ElemType> operator -(const VectorType& Other) { return TRectangle<ElemType>(TopLeft - Other, BottomRight - Other); }
	};

	using FRectangle = TRectangle<float>;
	using FIntRectangle = TRectangle<int32_t>;
}