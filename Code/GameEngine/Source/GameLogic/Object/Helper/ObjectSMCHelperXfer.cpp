// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfmelist /ICode/GameEngine/Source/Common
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


// ObjectSMCHelper::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/
// Object/Helper/ObjectSMCHelper.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference), with the timer list that BFME 1
// added (reference/open-bfme-1/game/GameEngine/Source/GameLogic/Object/
// Helper/ObjectSMCHelperXfer.cpp, retail BFME 1 0x00257390). It is slot 3 of
// the vftable whose name getter (0x0029288E) returns "ObjectSMCHelper".
//
// BFME 2 order: the helper base xfer (Rva004DF81B, ZH's ObjectHelper) first,
// then the light-CRC gate and Version1, then the timer count and the
// (model condition, frame) pairs. Loading appends each pair through the list's
// out-of-line push_back (0x004DE74D). The list sits at +0x20, as the matched
// destructor 0x004DE767 shows.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};


typedef int Int;
typedef unsigned int UnsignedInt;

void XferModelConditionFlagType( Xfer *xfer, Int *value );

// The rowed push_back at 0x004DE74D (SpecialPowerTimerList.cpp) takes the
// eight-byte condition/frame element; its definition lives in the row owner.
// Rowed 8-byte list element at 0x004DE74D (SpecialPowerTimerList.cpp), holding
// condition and frame; the retail xfer
// calls it directly, so this TU calls the row name via cast. Declaration
// only: the definition lives in the row owner.
#include "../../../Common/BfmeSpecialPowerTimer8.h"

#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> list<BfmeSpecialPowerTimer8, allocator<BfmeSpecialPowerTimer8> >::iterator list<BfmeSpecialPowerTimer8, allocator<BfmeSpecialPowerTimer8> >::insert(list<BfmeSpecialPowerTimer8, allocator<BfmeSpecialPowerTimer8> >::iterator, const BfmeSpecialPowerTimer8 &);
}

// Inline comparisons avoid the base-class operator!= COMDAT, whose byte
// shape depends on TU flags; this overload emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

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

class Rva004DF81B
{
public:
	void xfer(Xfer *xfer);
};

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

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void ObjectSMCHelper::xfer( Xfer *xfer )
{

	// object helper base class
	((Rva004DF81B *)this)->xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	xfer->Version1();

	BfmeSpecialPowerTimer8 timer;
	Int count = m_timers.size();
	*xfer == count;

	if( xfer->IsStoring() )
	{
		for( TimerList::iterator it = m_timers.begin(); it != m_timers.end(); )
		{
			timer = *it;
			++it;
			XferModelConditionFlagType( xfer, (Int *)&timer.m_templateID );
			*xfer == timer.m_readyFrame;
		}
	}
	else
	{
		for( Int i = 0; i < count; ++i )
		{
			XferModelConditionFlagType( xfer, (Int *)&timer.m_templateID );
			*xfer == timer.m_readyFrame;
			m_timers.push_back(timer);
		}
	}

}  // end xfer
