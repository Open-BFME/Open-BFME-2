// ?onEnter@TurretAIHoldTurretState@@UAE?AW4StateReturnType@@XZ
// partial score=0.85 date=2026-10-04
// cl: /O1 /G7 /DNDEBUG /MD /arch:SSE
//
// TurretAI idle and hold-turret states with their file-static
// frameToSleepTime, ported from Zero Hour's GameEngine/Source/GameLogic/AI/
// TurretAI.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference):
//  - frameToSleepTime, retail 0x004D7CB9 (45 bytes): Zero Hour's static.
//    Retail passes its first frame in EAX (the value the preceding
//    friend_getNextIdleMoodTargetFrame call returns) and the other three on
//    the stack, caller-popped. That is the convention cl 7.1 gives an
//    internal-linkage function whose every call site is in the unit: it is
//    reproduced here by compiling the static together with its four
//    callers, no /GL or __fastcall needed.
//  - TurretAIIdleState::onEnter, retail 0x004D83D1 (88 bytes), and update,
//    retail 0x004D88F6 (63 bytes); TurretAIHoldTurretState::onEnter, retail
//    0x004D84D2 (53 bytes), and update, retail 0x004D8935 (63 bytes): Zero
//    Hour's bodies. resetIdleScan (0x004D839A), the turret's
//    friend_getNextIdleMoodTargetFrame (0x004D837D) and
//    friend_checkForIdleMoodTarget (0x004D88AC) are out of line.
// BFME 2 layout (target evidence): the state machine's turret +0x3C; the
// turret's which-turret +0x0C and data +0x08 (recenter time +0x60); the AI's
// turret sync +0x210 (resetNextMoodCheckTime is the rowed 0x00263025); the
// states' m_nextIdleScan / m_timestamp at +0x20.
typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
#define STATE_SLEEP(x) ((StateReturnType)(x))
#define FOREVER 0x3fffffff

enum WhichTurretType
{
	TURRET_INVALID = -1
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
private:
	unsigned char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

class AIUpdateInterface
{
public:
	void rva00263025(); // resetNextMoodCheckTime
	void resetNextMoodCheckTime() { rva00263025(); }
	WhichTurretType friend_getTurretSync() const { return m_turretSyncFlag; }
	void friend_setTurretSync(WhichTurretType t) { m_turretSyncFlag = t; }
private:
	unsigned char m_pad00[0x210];
	WhichTurretType m_turretSyncFlag; // +0x210
};

class Object
{
public:
	unsigned char m_pad00[0x258];
	AIUpdateInterface *m_ai; // +0x258
};

struct TurretAIData
{
	unsigned char m_pad00[0x60];
	UnsignedInt m_recenterTime; // +0x60
};

class TurretAI
{
public:
	UnsignedInt friend_getNextIdleMoodTargetFrame();
	void friend_checkForIdleMoodTarget();
	WhichTurretType friend_getWhichTurret() const { return m_whichTurret; }
	UnsignedInt getRecenterTime() const { return m_data->m_recenterTime; }
private:
	unsigned char m_pad00[0x08];
	const TurretAIData *m_data; // +0x08
	WhichTurretType m_whichTurret; // +0x0C
};

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
};

class TurretStateMachine : public StateMachine
{
public:
	TurretAI *getTurretAI() const { return m_turretAI; }
private:
	unsigned char m_pad18[0x3C - 0x18];
	TurretAI *m_turretAI; // +0x3C
};

class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit(Int status);
	virtual StateReturnType update();
protected:
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class TurretState : public State
{
protected:
	TurretAI *getTurretAI() const { return ((TurretStateMachine *)getMachine())->getTurretAI(); }
};

class TurretAIIdleState : public TurretState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
	void resetIdleScan();
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	UnsignedInt m_nextIdleScan; // +0x20
};

class TurretAIHoldTurretState : public TurretState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	UnsignedInt m_timestamp; // +0x20
};

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
static StateReturnType frameToSleepTime(
	UnsignedInt frame1,
	UnsignedInt frame2 = FOREVER,
	UnsignedInt frame3 = FOREVER,
	UnsignedInt frame4 = FOREVER
)
{
	if (frame1 > frame2) frame1 = frame2;
	if (frame1 > frame3) frame1 = frame3;
	if (frame1 > frame4) frame1 = frame4;
	UnsignedInt now = TheGameLogic->getFrame();
	if (frame1 > now)
	{
		return STATE_SLEEP(frame1 - now);
	}
	else
	{
		// ignore times that are in the past, since this can frequently happen
		return STATE_CONTINUE;
	}
}

//----------------------------------------------------------------------------------------------------------
StateReturnType TurretAIIdleState::onEnter()
{
	AIUpdateInterface *ai = getMachineOwner()->m_ai;
	if (ai)
	{
		ai->resetNextMoodCheckTime();
		if (ai->friend_getTurretSync() == getTurretAI()->friend_getWhichTurret())
			ai->friend_setTurretSync(TURRET_INVALID);
	} // ai doesn't exist if the object was just created this frame.

	resetIdleScan();

	return frameToSleepTime(getTurretAI()->friend_getNextIdleMoodTargetFrame(), m_nextIdleScan);
}

//----------------------------------------------------------------------------------------------------------
StateReturnType TurretAIIdleState::update()
{
	UnsignedInt now = TheGameLogic->getFrame();
	if (now >= m_nextIdleScan)
	{
		return STATE_FAILURE;
	}

	TurretAI* turret = getTurretAI();
	turret->friend_checkForIdleMoodTarget();

	return frameToSleepTime(turret->friend_getNextIdleMoodTargetFrame(), m_nextIdleScan);
}

//----------------------------------------------------------------------------------------------------------
StateReturnType TurretAIHoldTurretState::onEnter()
{
	m_timestamp = TheGameLogic->getFrame() + getTurretAI()->getRecenterTime();

	return frameToSleepTime(getTurretAI()->friend_getNextIdleMoodTargetFrame(), m_timestamp);
}

//----------------------------------------------------------------------------------------------------------
StateReturnType TurretAIHoldTurretState::update()
{
	if (TheGameLogic->getFrame() >= m_timestamp)
		return STATE_SUCCESS;

	TurretAI* turret = getTurretAI();
	turret->friend_checkForIdleMoodTarget();

	return frameToSleepTime(turret->friend_getNextIdleMoodTargetFrame(), m_timestamp);
}
