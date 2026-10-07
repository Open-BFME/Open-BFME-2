// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /ICode/Libraries/Include
//
// DynamicShroudClearingRangeUpdate::update (BFME 2), from the Generals Zero
// Hour DynamicShroudClearingRangeUpdate.cpp.
//
// Target facts. update is slot 0 of the UpdateModuleInterface vftable at
// 0x0084BEB0. The fields follow the ZH order from +0x20 (state, the state
// countdown, total frames, the grow/sustain/shrink deadlines, the done-forever
// frame, the change-interval countdown, the decals-created flag at +0x40 and
// the native and current clearing ranges at +0x48/+0x4C), as the rowed ctor
// 0x0048B067, xfer 0x0048B505 and animateGridDecals 0x0048B256 use them. The
// module data holds ShrinkTime +0xC, GrowTime +0x14, FinalVision +0x18,
// ChangeInterval +0x1C, GrowInterval +0x20 and the grid decal template +0x28.
#include "Lib/Coord3D.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#define TRUE 1

class Thing;
class ModuleData;

template <class T> inline const T &max(const T &a, const T &b)
{
	return a > b ? a : b;
}

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class Thing
{
public:
	const Coord3D *getPosition() const { return &m_position; }

private:
	char m_unknown00[0x38];
	Coord3D m_position; // +0x38
};

class Object : public Thing
{
public:
	void setShroudClearingRange(Real range);
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	char m_unknown00[0x40];
	UnsignedInt m_frame; // +0x40
};

extern GameLogic *TheGameLogic;

class RadiusDecalTemplate
{
};

class RadiusDecal
{
	const void *m_template;
	void *m_decal;
	Bool m_empty;
	Real m_unknown0C;
};

class DynamicShroudClearingRangeUpdateModuleData
{
public:
	char m_unknown00[0x08];
	UnsignedInt m_shrinkDelay; // +0x08
	UnsignedInt m_shrinkTime; // +0x0C
	UnsignedInt m_growDelay; // +0x10
	UnsignedInt m_growTime; // +0x14
	Real m_finalVision; // +0x18
	UnsignedInt m_changeInterval; // +0x1C
	UnsignedInt m_growInterval; // +0x20
	char m_unknown24[0x04];
	RadiusDecalTemplate m_gridDecalTemplate; // +0x28
};

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	Object *getObject() const { return m_object; }
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

enum { GRID_FX_DECAL_COUNT = 30 };

class DynamicShroudClearingRangeUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();

	void createGridDecals( const RadiusDecalTemplate& tmpl, Real radius, const Coord3D& pos );
	void killGridDecals( void );
	void rva0048B256( void ); // animateGridDecals

protected:
	const DynamicShroudClearingRangeUpdateModuleData *getDynamicShroudClearingRangeUpdateModuleData() const
	{
		return (const DynamicShroudClearingRangeUpdateModuleData *)m_moduleData;
	}

	enum DSCRU_STATE
	{
		DSCRU_NOT_STARTED_YET,
		DSCRU_GROWING,
		DSCRU_SUSTAINING,
		DSCRU_SHRINKING,
		DSCRU_DONE_FOREVER,
		DSCRU_SLEEPING
	};

	DSCRU_STATE m_state; // +0x20
	Int m_stateCountDown; // +0x24
	Int m_totalFrames; // +0x28
	UnsignedInt m_growStartDeadline; // +0x2C
	UnsignedInt m_sustainDeadline; // +0x30
	UnsignedInt m_shrinkStartDeadline; // +0x34
	UnsignedInt m_doneForeverFrame; // +0x38
	UnsignedInt m_changeIntervalCountdown; // +0x3C
	Bool m_decalsCreated; // +0x40
	Real m_visionChangePerInterval; // +0x44
	Real m_nativeClearingRange; // +0x48
	Real m_currentClearingRange; // +0x4C
	RadiusDecal m_gridDecal[GRID_FX_DECAL_COUNT]; // +0x50
};

// ?update@DynamicShroudClearingRangeUpdate@@UAE?AW4UpdateSleepTime@@XZ @0x0048B33F 454B
UpdateSleepTime DynamicShroudClearingRangeUpdate::update( void )
{
	if (m_state == DSCRU_SLEEPING) {
		return UPDATE_SLEEP_NONE;
	}
	//Housekeeping-----------------------------------------
	Object *me = getObject();
	const DynamicShroudClearingRangeUpdateModuleData *md = getDynamicShroudClearingRangeUpdateModuleData();
	UnsignedInt currentFrame = TheGameLogic->getFrame();

	if ( ! m_decalsCreated )
	{
		createGridDecals(md->m_gridDecalTemplate, 100, *(me->getPosition()));
		m_decalsCreated = TRUE;
	}
	//-----------------------------------------------------


	if( m_stateCountDown <= 0 || currentFrame > m_doneForeverFrame )
		m_state = DSCRU_DONE_FOREVER;
	else if ( m_stateCountDown <= m_shrinkStartDeadline  )
		m_state = DSCRU_SHRINKING;
	else if ( m_stateCountDown <= m_sustainDeadline )
		m_state = DSCRU_SUSTAINING;
	else if ( m_stateCountDown <= m_growStartDeadline )
		m_state = DSCRU_GROWING;


	switch (m_state)
	{

		case DSCRU_NOT_STARTED_YET :
		{
			rva0048B256();

			break;
		}
		case DSCRU_GROWING :
		{
			rva0048B256();

			m_currentClearingRange += m_nativeClearingRange / max(1.0f, (Real)md->m_growTime);
			if (m_currentClearingRange >= m_nativeClearingRange)
				m_state = DSCRU_SUSTAINING;
			break;
		}
		case DSCRU_SUSTAINING :
		{
			m_currentClearingRange = m_nativeClearingRange;
			killGridDecals();
			break;
		}
		case DSCRU_SHRINKING :
		{
			m_currentClearingRange -= (m_nativeClearingRange-md->m_finalVision) / max(1.0f, (Real)md->m_shrinkTime);
			break;
		}
		case DSCRU_DONE_FOREVER :
		{
			killGridDecals();
			m_currentClearingRange = md->m_finalVision;
			break;
		}

	}

	if ( m_stateCountDown > 0 ) m_stateCountDown --;// it is important that this gets called every frame without sleeping
	//beacuse it handles animation and may need to respond to changing vision range from scripts & stuff


	if( m_changeIntervalCountdown > 0 )
		m_changeIntervalCountdown--;
	else
	{// reset per change timer
		m_changeIntervalCountdown = ( m_state == DSCRU_GROWING ? md->m_growInterval : md->m_changeInterval);
		me->setShroudClearingRange( m_currentClearingRange );
		if (m_state == DSCRU_DONE_FOREVER) { // We are done forever, and have done the final update, so sleep.+
			m_state = DSCRU_SLEEPING;
		}
	}

	return UPDATE_SLEEP_NONE;
}
