// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// BFME 1 semantic donor: 9cbfb551fe20dae985f91f2319d8997287b6a705,
// game/GameEngine/Source/GameLogic/AI/AIAttackState_xfer.cpp.
// Target identity: slot 3 of C13B78, whose name getter identifies AIAttackState;
// WB E22D80 has the same transfer string and WB E22F0A names its catch context
// AIAttackState::DoXfer (AIStates.cpp:12445). The xfer spelling follows the
// existing Snapshot/state slot-3 convention; DoXfer is not a separate body.
// Complete retail extent 34B3C0..34B502 includes the catch at34B489..34B4B1
// and its continuation, ending in RET4. No standalone funclet row.
// Target access deltas: machine18/owner14; attackMachine24; position30;
// ObjectID44; two flag bytes48/49; kind4C. Flag meanings remain unproven.
// Consumed declaration-only Xfer slots include the BFME2 boolean slot90.
// All direct callees have existing owners; no instantiated local vtables.

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct XferVersion
{
	XferVersion(UnsignedByte version, UnsignedByte currentVersion) :
		m_version(version), m_currentVersion(currentVersion)
	{
	}

	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Object;

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;
#include "../../../Include/Common/BfmeXfer.h"

#include "../../../Include/Common/StateMachineClass.h"

class AttackStateMachine
{
};

class AIAttackState
{
protected:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void xfer(Xfer *xfer);
	void createAttackMachine(Object *owner);

	char m_stateFieldsPrefix[0x14];
	StateMachine *m_machine;
	char m_stateFieldsSuffix[0x08];
	AttackStateMachine *m_attackMachine;
	char m_attackStateFields[0x08];
	Coord3D m_originalVictimPos;
	char m_lockedWeaponOnEnter[0x08];
	ObjectID m_objectID44;
	Bool m_flag48;
	Bool m_flag49;
	char m_unrecovered4A[2];
	UnsignedInt m_attackMachineType;
};

void XferObjectID(Xfer *, ObjectID *);

// ?xfer@AIAttackState@@MAEXPAVXfer@@@Z
void AIAttackState::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	XferVersion version(1, 3);
	*xfer == (Xfer::Version &)version;

	Bool hasMachine = m_attackMachine != 0;
	*xfer == hasMachine;
	*xfer == (Coord3DBase &)m_originalVictimPos;
	xfer->XferRawBytes(&m_attackMachineType, sizeof(m_attackMachineType));

	if (hasMachine && m_attackMachine == 0)
	{
		Object *owner = m_machine->m_owner;
		createAttackMachine(owner);
	}

	if (hasMachine)
	{
		if (version.m_currentVersion >= 3)
		{
			if (xfer->IsStoring())
			{
				xfer->BeginBlock("AIAttackState_attackMachine");
				*xfer == *(Snapshot *)m_attackMachine;
				xfer->EndBlock();
			}
			else
			{
				int block;
				try
				{
					block = xfer->BeginBlock("AIAttackState_attackMachine");
					*xfer == *(Snapshot *)m_attackMachine;
					xfer->EndBlock();
				}
				catch (...)
				{
					xfer->SkipBadBlock(*(Snapshot *)m_attackMachine, block);
					m_attackMachine = 0;
					Object *owner = m_machine->m_owner;
					createAttackMachine(owner);
				}
			}
		}
		else
		{
			*xfer == *(Snapshot *)m_attackMachine;
		}
	}

	XferObjectID(xfer, &m_objectID44);
	*xfer == m_flag48;
	if (version.m_currentVersion > 1)
		*xfer == m_flag49;
}
