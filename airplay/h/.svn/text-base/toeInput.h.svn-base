#pragma once

#include "toeEntity.h"
#include "s3eKeyboard.h"
#include "s3ePointer.h"

namespace TinyOpenEngine
{
	class CtoeWorld;
	class CtoeInputFilter;

	enum toeInputMessages
	{
		PointerTouch=0xcb08c849,
		PointerTouchRelease=0x5a1fbbce,
		PointerTouchMotion=0x6a3670df,
		PointerFoucusRecieved=0xe9f912e2,
		PointerFoucusLost=0x102ba09d,
	};
	struct KeyContext
	{
		// Key that was pressed or released.
		s3eKey key;
		// Whether the key was pressed (1) or released (0).
		bool pressed;
	};
	struct TouchContext
	{
		uint32 touchID;
		CIwVec2 firstKnownPoistion;
		CIwVec2 lastKnownPoistion;
		CIwVec2 currentPoistion;
		CtoeEntityWeakPointer entityInFocus;
		void Init(uint32 tid);
	};
	struct HitTestContext
	{
		CtoeInputFilter* filter;
		TouchContext*touch;
		CIwVec2 screenSpacePoint;
		bool (*callback)(HitTestContext * context, const CtoeEntityWeakPointer &);
	};

	class CtoePointerTouchMessageArgs: public CtoeEventArgs
	{
	};
	class CtoePointerTouchReleaseMessageArgs: public CtoeEventArgs
	{
	};
	class CtoePointerTouchMotionMessageArgs: public CtoeEventArgs
	{
	};
	class CtoePointerFoucusRecievedMessageArgs: public CtoeEventArgs
	{
	};
	class CtoePointerFoucusLostMessageArgs: public CtoeEventArgs
	{
	};
	class CtoeInputFilter
	{
		HitTestContext context;
		CtoeWorld* world;
		CIwArray<TouchContext> activePointers;
	public:
		//Constructor
		CtoeInputFilter();
		//Desctructor
		~CtoeInputFilter();

		int32 GetTouchContext(uint32 touchId);
		int32 FindTouchContext(uint32 touchId) const;
		void ReleaseTouchContext(int32 touchIndex);

		void KeyboardKeyEvent(s3eKeyboardEvent*e);
		void PointerTouchEvent(s3ePointerTouchEvent*e);
		void PointerTouchMotionEvent(s3ePointerTouchMotionEvent*e);
		void PointerButtonEvent(s3ePointerEvent*e);
		void PointerMotionEvent(s3ePointerMotionEvent*e);

		void SetCurrentWorld(CtoeWorld* world);
		CtoeWorld* GetCurrentWorld() const {return world;}
		void TouchEvent(TouchContext&,int32,int32);
		void TouchReleaseEvent(TouchContext&,int32,int32);
		void TouchMotionEvent(TouchContext&,int32,int32);
		static bool TouchEventCallback(HitTestContext * context, const CtoeEntityWeakPointer &);
		static bool TouchMotionEventCallback(HitTestContext * context, const CtoeEntityWeakPointer &);
	};
}