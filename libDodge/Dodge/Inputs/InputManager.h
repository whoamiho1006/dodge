#pragma once
#include "Dodge/Types.h"
#include "Dodge/Inputs/InputKeys.h"

namespace dodge {
	class FWindowClass;



	class DODGE_API FInputManager : public IObject {
		friend class FEngine;
		friend class FWindowClass;

	protected:
		FInputManager() { Reset(); }

	public:
		~FInputManager() { }

	private:
		bool CurrentStates[256];
		bool LatestStates[256];

	protected:
		/* 키 상태를 갱신합니다. */
		inline void Update(char Key, bool State) {
			LatestStates[Key] = CurrentStates[Key];
			CurrentStates[Key] = State;
		}

		/* 프레임 갱신 이벤트입니다. */
		inline void Update() {
			::memcpy(LatestStates, CurrentStates, sizeof(CurrentStates));
		}

	public:
		inline void Reset() {
			for (int32_t i = 0; i < 256; i++) {
				CurrentStates[i] = false;
				LatestStates[i] = false;
			}
		}

	public:
		inline bool IsKeyDown(char Key) { return CurrentStates[Key]; }
		inline bool IsKeyUp(char Key) { return !CurrentStates[Key]; }

		inline bool IsKeyDownNow(char Key) { return CurrentStates[Key] && !LatestStates[Key]; }
		inline bool IsKeyUpNow(char Key) { return !CurrentStates[Key] && LatestStates[Key]; }
	};
}