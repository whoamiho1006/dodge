#pragma once
#include <stdint.h>
#include <string>
#include <type_traits>

#ifdef __DODGE_INTERNALS__
#	define DODGE_API __declspec(dllexport)
#else
#	define DODGE_API __declspec(dllimport)
#endif

#pragma warning(disable: 4251)
#pragma warning(disable: 4275)

namespace dodge {
	using ::int8_t;
	using ::int16_t;
	using ::int32_t;
	using ::int64_t;

	using ::uint8_t;
	using ::uint16_t;
	using ::uint32_t;
	using ::uint64_t;

	using ::size_t;
	using nullptr_t = decltype(nullptr);

	using FString = std::string;

	template<typename T>
	class TObjectPtr;

	/* 모든 객체의 기본 클래스입니다. */
	class IObject {
		template<typename>
		friend class TObjectPtr;

	private:
		int32_t Reference;

	public:
		IObject() : Reference(0) { }

	protected:
		virtual ~IObject() { }

	protected:
		void Grab() { ++Reference; }
		virtual bool Drop() {
			if (!(--Reference)) {
				delete this;
				return true;
			}

			return false;
		}
	};

	
	template<typename T>
	class TObjectPtr {
		/*static_assert(std::is_base_of<IObject, T>::value,
			"TObjectPtr<T> is only for `IObject`s.");*/
		template<typename> friend class TObjectPtr;

	public:
		TObjectPtr(nullptr_t = nullptr) : Object(nullptr) { }
		TObjectPtr(T* InPtr) : Object(InPtr) { if (InPtr) { InPtr->Grab(); } }
		TObjectPtr(const TObjectPtr<T>& Other) : TObjectPtr(Other.Object) { }
		TObjectPtr(TObjectPtr<T>&& Other) : Object(Other.Object) { Other.Object = nullptr; }
		~TObjectPtr() { if (Object) { Object->Drop(); } }

		template<typename U, typename = std::enable_if_t<std::is_base_of<T, U>::value>>
		TObjectPtr(const TObjectPtr<U>& Other) : TObjectPtr(Other.Object) { }

	public:
		inline TObjectPtr<T>& operator =(const TObjectPtr<T>& Other) {
			if (&Other != this) {
				if (Object) {
					Object->Drop();
				}

				Object = nullptr;
				if (Other.Object) {
					(Object = Other.Object)->Grab();
				}
			}

			return *this;
		}

		inline TObjectPtr<T>& operator =(TObjectPtr<T>&& Other) {
			if (&Other != this) {
				auto* Ptr = Object;
				Object = Other.Object;
				Other.Object = Ptr;
			}

			return *this;
		}

	protected:
		T* Object;

	public:
		inline operator bool() const { return Object != nullptr; }
		inline bool operator !() const { return Object == nullptr; }
		inline T* operator ->() const { return Object; }

	public:
		inline bool operator == (const TObjectPtr<T>& Other) const {
			return this == &Other || Object == Other.Object;
		}

		inline bool operator != (const TObjectPtr<T>& Other) const {
			return this != &Other && Object != Other.Object;
		}
	};
}
