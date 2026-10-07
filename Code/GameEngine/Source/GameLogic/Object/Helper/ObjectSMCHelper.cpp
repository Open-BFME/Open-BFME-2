// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfmelist /ICode/GameEngine/Source/Common
// stlport
//
// ObjectSMCHelper (Zero Hour GameLogic/Object/Helper/ObjectSMCHelper.cpp) with
// BFME's timed special-model-condition list:
//   0x004DE7C2 157B update (UpdateModuleInterface entry, this at +0x10)
//   0x004DE85F 167B setModelConditionState(condition, frames)
//
// Target evidence: the timer list at +0x20 is the one the rowed destructor
// 0x004DE767 clears and the rowed xfer 0x004DE906 saves as (model condition,
// frame) pairs, appending each through the rowed push_back 0x004DE74D. Both
// bodies end by asking the rowed framesUntilNext 0x004DE700 for the next wake:
// update returns it, setModelConditionState hands it to
// UpdateModule::setWakeFrame. setModelConditionState range-checks the
// condition against 0x24F (the model condition count), raises an existing
// timer to the later frame or queues a new one and sets the condition on the
// owner (flag words at Object +0x10C, then the change notifier 0x0028AE6D).
// update clears and drops each expired timer through the list's out-of-line
// erase, then refreshes the owner's drawable (0x00274176).
// Donor-carried: the names and the shape of BFME 1's
// ObjectSMCHelperUpdate / ObjectSMCHelperSetModelConditionState (Open-BFME-1
// 6d943426), whose list holds the same two words.

#include <list>
#include "BfmeSpecialPowerTimer8.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

enum ModelConditionFlagType
{
	MODELCONDITION_FIRST = 0,
	MODELCONDITION_COUNT = 0x24F
};

class Drawable
{
public:
	void rva00274176(Bool force);
};

class ModelConditionFlags
{
public:
	UnsignedInt testMask(UnsignedInt bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(UnsignedInt bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(UnsignedInt bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}

private:
	UnsignedInt m_words[19];
};

class Thing
{
public:
	Drawable *getDrawable() const;

private:
	unsigned char m_unmodelled00[0x48];
};

class Object : public Thing
{
public:
	void rva0028AE6D();

	__forceinline void clearModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.testMask(mc))
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}

	__forceinline void setModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.testMask(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			rva0028AE6D();
		}
	}

private:
	unsigned char m_unmodelled48[0x10C - 0x48];
	ModelConditionFlags m_modelConditionFlags;																///< 0x10C
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	unsigned char m_unmodelled00[0x40];
	UnsignedInt m_frame;																											///< 0x40
};

extern GameLogic *TheGameLogic;

class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class ObjectModule
{
public:
	virtual ~ObjectModule();

protected:
	Object *getObject() const { return m_object; }

private:
	const void *m_moduleData;
	Object *m_object;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;
};

class ObjectHelper : public UpdateModule
{
public:
	virtual ~ObjectHelper();
};

class ObjectSMCHelper : public ObjectHelper
{
public:
	virtual UpdateSleepTime update();
	void setModelConditionState(ModelConditionFlagType condition, UnsignedInt frames);

private:
	Int framesUntilNext();

	typedef _STL::list<BfmeSpecialPowerTimer8> TimerList;

	TimerList m_timers;																												///< 0x20
};

//-------------------------------------------------------------------------------------------------
UpdateSleepTime ObjectSMCHelper::update()
{
	UnsignedInt now = TheGameLogic->getFrame();

	for (TimerList::iterator it = m_timers.begin(); it != m_timers.end(); )
	{
		BfmeSpecialPowerTimer8 timer = *it;
		TimerList::iterator cur = it++;
		if (now >= timer.m_readyFrame)
		{
			getObject()->clearModelConditionState((ModelConditionFlagType)timer.m_templateID);
			m_timers.erase(cur);
		}
	}

	Object *obj = getObject();
	if (obj)
	{
		Drawable *draw = obj->getDrawable();
		if (draw)
			draw->rva00274176(true);
	}

	return (UpdateSleepTime)framesUntilNext();
}

//-------------------------------------------------------------------------------------------------
void ObjectSMCHelper::setModelConditionState(ModelConditionFlagType condition, UnsignedInt frames)
{
	if (condition < 0 || condition >= MODELCONDITION_COUNT)
		return;

	UnsignedInt now = TheGameLogic->getFrame();
	Bool found = false;
	for (TimerList::iterator it = m_timers.begin(); it != m_timers.end(); ++it)
	{
		if (it->m_templateID == condition)
		{
			UnsignedInt endFrame = frames + now;
			it->m_readyFrame = *(it->m_readyFrame > endFrame ? &it->m_readyFrame : &endFrame);
			found = true;
			break;
		}
	}

	if (!found)
	{
		BfmeSpecialPowerTimer8 timer;
		timer.m_templateID = condition;
		timer.m_readyFrame = now + frames;
		m_timers.push_back(timer);
		getObject()->setModelConditionState(condition);
	}

	UpdateSleepTime sleep = (UpdateSleepTime)framesUntilNext();
	setWakeFrame(getObject(), sleep);
}
