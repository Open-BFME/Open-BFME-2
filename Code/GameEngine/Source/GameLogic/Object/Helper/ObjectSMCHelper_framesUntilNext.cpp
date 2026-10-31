// ?framesUntilNext@ObjectSMCHelper@@AAEHXZ
// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfmelist /ICode/GameEngine/Source/Common
// stlport
//
// ?framesUntilNext@ObjectSMCHelper@@AAEHXZ, retail 0x004DE700, 77 bytes.
// Private timer helper behind ObjectSMCHelper::update (0x004DE85F caller
// tail-jumps here): 0x3fffffff for an empty timer list, else the smallest
// queued wake frame minus the current frame, clamped to at least 1.
// The separate empty()/begin()/end() list calls keep retail's two m_node
// loads and its duplicate empty check; the min is a cmovb, which needs
// /arch:SSE (the P6 instruction set) on top of the TU's /O1. Donor:
// BFME1 ObjectSMCHelperFramesUntilNext.cpp with ObjectSMCHelperUpdate.cpp.

#include <list>
#include "BfmeSpecialPowerTimer8.h"
#include "../../../Common/GameLogicObjectLookupView.h"

// Inline comparisons avoid the base-class operator!= COMDAT, whose byte
// shape depends on TU flags; this overload emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

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

#include "../../../../Include/Common/ObjectModule.h"

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
	virtual ~ObjectSMCHelper();
	virtual UpdateSleepTime update();
	void setModelConditionState(ModelConditionFlagType condition, UnsignedInt frames);

protected:
	virtual void xfer(Xfer *xfer);

private:
	Int framesUntilNext();

	typedef _STL::list<BfmeSpecialPowerTimer8> TimerList;

	TimerList m_timers;																												///< 0x20
};

int ObjectSMCHelper::framesUntilNext()
{
	if (m_timers.empty())
		return 0x3fffffff;

	unsigned int frame = TheGameLogic->getFrame();
	unsigned int best = 99999999;
	TimerList::iterator node = m_timers.begin();
	if (node != m_timers.end())
	{
		do
		{
			BfmeSpecialPowerTimer8 value = *node;
			unsigned int expirationFrame = value.m_readyFrame;
			++node;
			if (expirationFrame < best)
				best = expirationFrame;
		} while (node != m_timers.end());
	}
	int delta = best - frame;
	if (delta > 0)
		return delta;
	return 1;
}
