#pragma once
#include "Dodge/Types.h"
#include <math.h>

namespace dodge {
	template<typename ElemType = float>
	struct TVector2	{
		ElemType X, Y;

		constexpr TVector2() : X(0), Y(0) { }
		constexpr TVector2(ElemType Value) : X(Value), Y(Value) { }
		constexpr TVector2(ElemType X, ElemType Y) : X(X), Y(Y) { }

		TVector2(const TVector2<ElemType>& Other)
			: X(Other.X), Y(Other.Y)
		{
		}

		template<typename OtherType>
		TVector2(const TVector2<OtherType>& Other) 
			: X((ElemType)Other.X), Y((ElemType)Other.Y)
		{
		}

		inline static TVector2<ElemType> MaxVector(const TVector2<ElemType>& A, const TVector2<ElemType>& B) {
			return TVector2<ElemType>(A.X < B.X ? B.X : A.X, A.Y < B.Y ? B.Y : A.Y);
		}

		inline static TVector2<ElemType> MinVector(const TVector2<ElemType>& A, const TVector2<ElemType>& B) {
			return TVector2<ElemType>(A.X > B.X ? B.X : A.X, A.Y > B.Y ? B.Y : A.Y);
		}

		inline static TVector2<ElemType> Rand() {
			return TVector2<ElemType>(
				(rand() % 10000), (rand() % 10000)
			).Normalize();
		}

		/*
		TVector2(const TVector2<ElemType>&) = default;
		TVector2(TVector2<ElemType>&&) = default;

		TVector2<ElemType>& operator =(const TVector2<ElemType>&) = default;
		TVector2<ElemType>& operator =(TVector2<ElemType>&&) = default;
		*/
		inline bool operator ==(const TVector2<ElemType>& Other) const { return this == &Other || ((int64_t)(X * 10000) == (int64_t)(Other.X * 10000) && (int64_t)(Y * 10000) == (int64_t)(Other.Y * 10000)); }
		inline bool operator !=(const TVector2<ElemType>& Other) const { return this != &Other && (int64_t)(X * 10000) != (int64_t)(Other.X * 10000) || (int64_t)(Y * 10000) != (int64_t)(Other.Y * 10000); }

		inline bool operator <(const TVector2<ElemType>& Other) const { return GetSizeSquad() < Other.GetSizeSquad(); }
		inline bool operator >(const TVector2<ElemType>& Other) const { return GetSizeSquad() > Other.GetSizeSquad(); }
		inline bool operator <=(const TVector2<ElemType>& Other) const { return GetSizeSquad() <= Other.GetSizeSquad(); }
		inline bool operator >=(const TVector2<ElemType>& Other) const { return GetSizeSquad() >= Other.GetSizeSquad(); }

		inline double GetSize() const { return ::sqrt(GetSizeSquad()); }
		inline double GetSizeSquad() const { return (double)(X * X + Y * Y); }
		inline bool Normalize(TVector2<ElemType>& Out) const {
			double SizeSquad = GetSizeSquad();

			if ((int64_t)(SizeSquad * 10000.0) != 0) {
				(Out = *this) /= sqrt(SizeSquad);
			}

			return true;
		}

		inline TVector2<ElemType> Normalize() const {
			TVector2<ElemType> Vec;

			if (Normalize(Vec)) {
				return Vec;
			}

			return 0;
		}

		inline double Cross(const TVector2<ElemType>& Other) const { return X * Other.Y - Y * Other.X; }

		inline TVector2<ElemType>& operator +=(const TVector2<ElemType>& Other) { X += Other.X; Y += Other.Y; return *this; }
		inline TVector2<ElemType>& operator -=(const TVector2<ElemType>& Other) { X -= Other.X; Y -= Other.Y; return *this; }
		inline TVector2<ElemType>& operator *=(const TVector2<ElemType>& Other) { X *= Other.X; Y *= Other.Y; return *this; }
		inline TVector2<ElemType>& operator /=(const TVector2<ElemType>& Other) { X /= Other.X; Y /= Other.Y; return *this; }
		inline TVector2<ElemType>& operator *=(double Scalar) { X = (ElemType)(X * Scalar); Y = (ElemType)(Y * Scalar); return *this; }
		inline TVector2<ElemType>& operator /=(double Scalar) { X = (ElemType)(X / Scalar); Y = (ElemType)(Y / Scalar); return *this; }

		inline TVector2<ElemType> operator +(const TVector2<ElemType>& Other) { return TVector2<ElemType>(X + Other.X, Y + Other.Y); }
		inline TVector2<ElemType> operator -(const TVector2<ElemType>& Other) { return TVector2<ElemType>(X - Other.X, Y - Other.Y); }
		inline TVector2<ElemType> operator *(const TVector2<ElemType>& Other) { return TVector2<ElemType>(X * Other.X, Y * Other.Y); }
		inline TVector2<ElemType> operator /(const TVector2<ElemType>& Other) { return TVector2<ElemType>(X / Other.X, Y / Other.Y); }
		inline TVector2<ElemType> operator *(double Scalar) { return TVector2<ElemType>((ElemType)(X * Scalar), (ElemType)(Y * Scalar)); }
		inline TVector2<ElemType> operator /(double Scalar) { return TVector2<ElemType>((ElemType)(X / Scalar), (ElemType)(Y / Scalar)); }
	};

	using FVector2 = TVector2<float>;
	using FIntVector2 = TVector2<int32_t>;
}