#include "toeInput.h"
#include "toeWorld.h"

using namespace TinyOpenEngine;

void TouchContext::Init(uint32 tid)
{
	touchID = tid;
}

//Constructor
CtoeInputFilter::CtoeInputFilter()
{
	world = 0;
}
//Desctructor
CtoeInputFilter::~CtoeInputFilter()
{
}

void CtoeInputFilter::KeyboardKeyEvent(s3eKeyboardEvent*e)
{
	if (!world) return;
	KeyContext kc;
	kc.key = e->m_Key;
	kc.pressed = e->m_Pressed!=0;
	world->UnhandledKeyEvent(&kc);
}
int32 CtoeInputFilter::FindTouchContext(uint32 touchId) const
{
	for (uint32 i=0; i<activePointers.size(); ++i)
	{
		TouchContext& item = activePointers[i];
		if (item.touchID == touchId)
			return (int32)i;
	}
	return -1;
}
int32 CtoeInputFilter::GetTouchContext(uint32 touchId)
{
	int32 i = FindTouchContext(touchId);
	if (i >= 0) return i;
	i = (int32)activePointers.size();
	activePointers.push_back();
	TouchContext& item = activePointers[i];
	item.Init(touchId);
	return i;
}
void CtoeInputFilter::ReleaseTouchContext(int32 touchIndex)
{
	activePointers.erase_fast(touchIndex);
}

void CtoeInputFilter::PointerTouchEvent(s3ePointerTouchEvent*e)
{
	if (!world) return;
	int32 index = GetTouchContext(e->m_TouchID);
	TouchContext& item = activePointers[index];
	if (e->m_Pressed)
	{
		TouchEvent(item,e->m_x,e->m_y);
	}
	else
	{
		TouchReleaseEvent(item,e->m_x,e->m_y);
		ReleaseTouchContext(index);
	}

}

void CtoeInputFilter::PointerTouchMotionEvent(s3ePointerTouchMotionEvent*e)
{
	if (!world) return;
	int32 index = FindTouchContext(e->m_TouchID);
	if (index < 0) return;
	TouchContext& item = activePointers[index];
	TouchMotionEvent(item,e->m_x,e->m_y);
}
void CtoeInputFilter::PointerButtonEvent(s3ePointerEvent*e)
{
	if (!world) return;

	if (e->m_Button != S3E_POINTER_BUTTON_SELECT)
		return;

	int32 index = GetTouchContext(0);
	TouchContext& item = activePointers[index];
	if (e->m_Pressed)
	{
		TouchEvent(item,e->m_x,e->m_y);
	}
	else
	{
		TouchReleaseEvent(item,e->m_x,e->m_y);
		ReleaseTouchContext(index);
	}
}

void CtoeInputFilter::PointerMotionEvent(s3ePointerMotionEvent*e)
{
	if (!world) return;
	int32 index = FindTouchContext(0);
	if (index < 0) return;
	TouchContext& item = activePointers[index];
	TouchMotionEvent(item,e->m_x,e->m_y);
}
void CtoeInputFilter::TouchEvent(TouchContext& touchContext,int32 x,int32 y)
{
	touchContext.firstKnownPoistion.x = touchContext.lastKnownPoistion.x = touchContext.currentPoistion.x = x;
	touchContext.firstKnownPoistion.y = touchContext.lastKnownPoistion.y = touchContext.currentPoistion.y = y;

	context.screenSpacePoint.x = x;
	context.screenSpacePoint.y = y;
	context.filter = this;
	context.touch = &touchContext;
	context.callback =TouchEventCallback;
	world->PointerHitTest(&context);
	if (!touchContext.entityInFocus.HasEntity())
	{
		world->UnhandledTouchEvent(&touchContext);
	}
}
bool CtoeInputFilter::TouchEventCallback(HitTestContext * context, const CtoeEntityWeakPointer & e)
{
	CtoeEntity* entityInFocus = e.Get(context->filter->world);
	if (entityInFocus)
	{
		CtoePointerFoucusRecievedMessageArgs fr_args;
		entityInFocus->SendMessage(PointerFoucusRecieved,&fr_args);

		CtoePointerTouchMessageArgs args;
		entityInFocus->SendMessage(PointerTouch,&args);

		if (args.IsHandled())
		{
			context->touch->entityInFocus = entityInFocus;
			return true;
		}
		else
		{
			CtoePointerFoucusLostMessageArgs fl_args;
			entityInFocus->SendMessage(PointerFoucusLost,&fl_args);
		}
	}
	return false;
}
void CtoeInputFilter::TouchReleaseEvent(TouchContext& touchContext,int32 x,int32 y)
{
	touchContext.currentPoistion.x = x;
	touchContext.currentPoistion.y = y;
	CtoeEntity* entityInFocus = touchContext.entityInFocus.Get(world);
	if (entityInFocus)
	{
		CtoePointerTouchReleaseMessageArgs args;
		entityInFocus->SendMessage(PointerTouchRelease,&args);
		CtoePointerFoucusLostMessageArgs fl_args;
		entityInFocus->SendMessage(PointerFoucusLost,&fl_args);
		touchContext.entityInFocus = (CtoeEntity*)0;
	}
	else
	{
		world->UnhandledTouchReleaseEvent(&touchContext);
	}
}
void CtoeInputFilter::TouchMotionEvent(TouchContext& touchContext,int32 x,int32 y)
{
	touchContext.currentPoistion.x = x;
	touchContext.currentPoistion.y = y;
	if (touchContext.currentPoistion == touchContext.lastKnownPoistion)
		return;
	CtoeEntity* entityInFocus = touchContext.entityInFocus.Get(world);
	CtoePointerTouchMotionMessageArgs args;
	if (entityInFocus)
	{
		entityInFocus->SendMessage(PointerTouchMotion,&args);
		if (args.IsHandled())
		{
			goto eventProcessed;
		}
	}
	else
	{
		world->UnhandledTouchMotionEvent(&touchContext);
	}
	eventProcessed:
	touchContext.lastKnownPoistion = touchContext.currentPoistion;
}
bool CtoeInputFilter::TouchMotionEventCallback(HitTestContext * context, const CtoeEntityWeakPointer & e)
{
	if (e == context->touch->entityInFocus)
		return false;

	/*CtoeEntity* entityInFocus = e.Get(context->filter->world);
	CtoePointerTouchMotionMessageArgs args;
	if (entityInFocus)
	{
		CtoePointerFoucusRecievedMessageArgs fr_args;
		entityInFocus->SendMessage(PointerFoucusRecieved,&fr_args);
		entityInFocus->SendMessage(PointerTouchMotion,&args);
		if (args.IsHandled())
		{
			CtoeEntity* old = context->touch->entityInFocus.Get(context->filter->world);
			if (old)
			{
				CtoePointerFoucusLostMessageArgs fl_args;
				entityInFocus->SendMessage(PointerFoucusLost,&fl_args);

			}
			context->touch->entityInFocus = entityInFocus;
			return true;
		}
		else
		{
			entityInFocus->SendMessage(PointerFoucusLost,&args);
		}
	}*/
	return false;
}
void CtoeInputFilter::SetCurrentWorld(CtoeWorld* w)
{
	world = w;
}