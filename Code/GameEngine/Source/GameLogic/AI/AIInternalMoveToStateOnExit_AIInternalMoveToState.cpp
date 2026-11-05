// cl: /DNDEBUG /MD
// Split from AIInternalMoveToStateOnExit.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// AIInternalMoveToState::onExit, retail 0x003473A4 (188 bytes).
// Identity (target evidence): slot 5 of vtable 0x00C10DE8, whose slot 4 is the
// pinned AIInternalMoveToState::onEnter 0x0034C146; the 28 direct callers are
// derived states chaining to the base onExit (as the 27 onEnter callers do),
// and vtable 0x00C124D8 inherits it unchanged. The body follows the Zero Hour
// AIStates.cpp onExit: TheAudio->removeAudioEvent(m_ambientPlayingHandle) and
// the AI ending-move call when the owner has an AI.
// BFME2 deltas: the owner's model conditions 1*32+29 (unless object status
// 0x4B is set), 4*32+28, 3*32+7 and 3*32+9 are cleared first (Object+0x10C
// words, notifier 0x0028AE6D on change); the handle is reset to 1 after the
// removal (as the FiringTracker dtor does); the ending-move call is the rowed
// AIUpdateInterface::rva00262AEA, and when the +0x4B flag is set the AI float
// +0x1A0 is reset to FLT_MAX; +0x4B is cleared last. The state machine owner
// sits at machine+0x14. ZH supplies the labels only.
// AIInternalMoveToState::AIInternalMoveToState, retail 0x0033F279 (94 bytes):
// the ZH inline ctor, out of line in BFME2 (16 derived-state ctors call it
// with their name hash): State base (rowed hash ctor 0x004D73FC), vftable
// 0x00C10DE8, goal and path-goal positions zeroed, the +0x2C float, goal
// layer and path timestamp cleared, the three flag bytes +0x49..+0x4B
// cleared, the audio handle set to 1 (as onExit leaves it) and
// adjustDestinations true. Layout per the rowed xfer 0x0033FF76.
// AIInternalMoveToState::getAdjustsDestination, retail 0x00344138 (191
// bytes): the ZH body (parachuting status 7 -> false; AI present and its
// isAllowedToAdjustDestination, vslot 107 at +0x1AC, false -> false; else
// m_adjustDestinations at +0x48) with BFME2's CritterDesync log lines
// (flag g_00E03745, log file theLogicRandomLogFile; strings from retail .rdata).
typedef int AudioHandle;
enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0,
	OBJECT_STATUS_PARACHUTING = 7
};
#include "../../../Include/Common/GameAudio.h"
extern AudioManager *TheAudio;
#include "../../../Include/GameClient/ModelConditionFlags.h"
typedef bool Bool;
// Coord3D: shared header/view; no private copy.
#include "../../../../Libraries/Include/Lib/Coord3DInline.h"
enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};
template <int N> class AIUpdateSlots : public AIUpdateSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIUpdateSlots<0>
{
};
#include "../../../Include/GameLogic/Module/AIUpdate.h"
class Object
{
public:
	void rva0028AE6D();
	bool testStatus(ObjectStatusTypes bit) const;
	AIUpdateInterface *getAI() const { return m_ai; }
	__forceinline void clearModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}
	__forceinline void setModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.test(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			rva0028AE6D();
		}
	}
	void clearAndSetModelConditionState(unsigned int clr, unsigned int set);
private:
	unsigned char m_pad000[0x10C];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x258 - 0x158];
	AIUpdateInterface *m_ai; // +0x258
};
#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/Common/StateMachineClass.h"
class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
protected:
	Bool getAdjustsDestination() const;
	virtual Bool computePath();
private:
	Coord3D m_goalPosition; // +0x20
	float m_2C; // +0x2C
	PathfindLayerEnum m_goalLayer; // +0x30
	Coord3D m_pathGoalPosition; // +0x34
	AudioHandle m_ambientPlayingHandle; // +0x40
	unsigned int m_pathTimestamp; // +0x44
	Bool m_adjustDestinations; // +0x48
	bool m_waitingForPath; // +0x49
	Bool m_tryOneMoreRepath; // +0x4A
	bool m_4B; // +0x4B
protected:
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
public:
	// retail vftable slot: the rowed override
	virtual StateReturnType update();
};
AIInternalMoveToState::AIInternalMoveToState(StateMachine *machine, unsigned int hash)
	: State(machine, hash)
{
	m_goalPosition.zero();
	m_goalLayer = LAYER_INVALID;
	m_2C = 0.0f;
	m_pathGoalPosition.zero();
	m_pathTimestamp = 0;
	m_waitingForPath = false;
	m_tryOneMoreRepath = false;
	m_4B = false;
	m_ambientPlayingHandle = 1;
	m_adjustDestinations = true;
}
struct FprintfTarget
{
	char m_pad[4];
};
extern "C" void fprintf(FprintfTarget *target, const char *format, ...);
extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;






// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?slot07@State@@UAEXXZ=?disable@Rva0033F2D7ByteSetter@@QAEXXZ")
#pragma comment(linker, "/alternatename:?slot09@State@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?slot10@State@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?slot11@State@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?slot12@State@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?slot13@State@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?slot14@State@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?slot15@State@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?slot16@State@@UAEXXZ=??1Region2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?update@State@@UAE?AW4StateReturnType@@XZ=?update@AIInternalMoveToState@@UAE?AW4StateReturnType@@XZ")
