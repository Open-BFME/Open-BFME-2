// cl: /O1 /DNDEBUG /MD
//
// TurretAI::updateTurretAI, retail 0x004D8DEA (194 bytes), ported from Zero
// Hour's GameEngine/Source/GameLogic/AI/TurretAI.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference). Zero Hour's body on
// BFME 2's layout (target evidence): turret state machine +0x14 (its
// updateStateMachine is vslot 4; current state +0x04 with its id at +0x04),
// m_enableSweepUntil +0x24, m_continuousFireExpirationFrame +0x30,
// m_sleepUntil +0x34, m_playRotSound / m_playPitchSound +0x38 / +0x39,
// m_didFire +0x3B, m_enabled +0x3C, m_firesWhileTurning +0x3D.
// startRotOrPitchSound is 0x004D8B50 and stopRotOrPitchSound the rowed
// 0x004D82F6. BFME 2 addition: when the state machine is gone after its
// update the function returns UPDATE_SLEEP_NONE without re-arming.
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
#define NULL 0

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
#define IS_STATE_SLEEP(r) ((r) > 0)
#define GET_STATE_SLEEP_FRAMES(r) ((Int)(r))

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
#define UPDATE_SLEEP(x) ((UpdateSleepTime)(x))

typedef UnsignedInt StateID;
enum
{
	INVALID_STATE_ID = 999999
};
enum TurretStateType
{
	TURRETAI_IDLE = 0,
	TURRETAI_IDLESCAN = 1,
	TURRETAI_AIM = 2,
	TURRETAI_FIRE = 3,
	TURRETAI_RECENTER = 4,
	TURRETAI_HOLD = 5
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

class State
{
public:
	StateID getID() const { return m_ID; }
private:
	void *m_vtbl;
	StateID m_ID; // +0x04
};

class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType updateStateMachine();
	StateID getCurrentStateID() const { return m_currentState ? m_currentState->getID() : (StateID)INVALID_STATE_ID; }
private:
	State *m_currentState; // +0x04
};

class TurretAI
{
public:
	UpdateSleepTime updateTurretAI();
	void rva004D82F6(); // stopRotOrPitchSound
private:
	void startRotOrPitchSound();
	void stopRotOrPitchSound() { rva004D82F6(); }
	unsigned char m_pad00[0x14];
	StateMachine *m_turretStateMachine; // +0x14
	unsigned char m_pad18[0x24 - 0x18];
	UnsignedInt m_enableSweepUntil; // +0x24
	unsigned char m_pad28[0x30 - 0x28];
	UnsignedInt m_continuousFireExpirationFrame; // +0x30
	UnsignedInt m_sleepUntil; // +0x34
	Bool m_playRotSound; // +0x38
	Bool m_playPitchSound; // +0x39
	Bool m_pad3A;
	Bool m_didFire; // +0x3B
	Bool m_enabled; // +0x3C
	Bool m_firesWhileTurning; // +0x3D
};

//-------------------------------------------------------------------------------------------------
UpdateSleepTime TurretAI::updateTurretAI()
{
	UnsignedInt now = TheGameLogic->getFrame();
	if (m_sleepUntil != 0 && now < m_sleepUntil)
	{
		return UPDATE_SLEEP(m_sleepUntil - now);
	}

	UpdateSleepTime subMachineSleep = UPDATE_SLEEP_FOREVER;	// assume the best!

	// either we don't care about continuous fire stuff, or we care, but time has elapsed
	if ((!m_firesWhileTurning) || (m_continuousFireExpirationFrame <= now))
	{
		m_playRotSound = false;
		m_playPitchSound = false;
	}

	if (m_enabled || m_turretStateMachine->getCurrentStateID() == TURRETAI_RECENTER)
	{
		m_didFire = false;

		// run the behavior state machine BEFORE doing sound check
		StateReturnType stRet = m_turretStateMachine->updateStateMachine();
		if (m_turretStateMachine == NULL)
			return UPDATE_SLEEP_NONE;

		if (m_didFire)
		{
			// if we fired, enable sweeping for a few frames.
			const Int ENABLE_SWEEP_FRAME_COUNT = 3;
			m_enableSweepUntil = now + ENABLE_SWEEP_FRAME_COUNT;
			m_continuousFireExpirationFrame = now + ENABLE_SWEEP_FRAME_COUNT;// so the recent firing will not interrupt the moving sound
		}

		if (m_playRotSound || m_playPitchSound)
			startRotOrPitchSound();
		else
			stopRotOrPitchSound();

		if (IS_STATE_SLEEP(stRet))
		{
			Int frames = GET_STATE_SLEEP_FRAMES(stRet);
			if (frames < subMachineSleep)
				subMachineSleep = UPDATE_SLEEP(frames);
		}
		else
		{
			// it's STATE_CONTINUE, STATE_SUCCESS, or STATE_FAILURE,
			// any of which will probably require next frame
			subMachineSleep = UPDATE_SLEEP_NONE;
		}

	}	// if enabled or recentering

	m_sleepUntil = now + subMachineSleep;

	return subMachineSleep;
}
