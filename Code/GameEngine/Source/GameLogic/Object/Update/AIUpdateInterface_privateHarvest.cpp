// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/BfmeConv644.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: BfmeThingCTA::bfmeGoCTA 0x00264853 (56B). Callee addresses
// are read off retail's call sites (reverse/symbols.csv). Only the placed
// bodies are carried; the donor's other definitions are omitted.
//
// Identity (target evidence, not donor): WorldBuilder's AIUpdate.cpp:6981
// defines AIUpdateInterface::privateHarvest(pos, cmdSource) with this body
// (Object +8 mobility test 0x002907A1; state machine +0x30 clear at slot 5,
// setGoalPosition, last command source +0x48, setState 0x2F at slot 8), and
// retail's AIUpdate vtables hold 0x00264853 next to slot 133
// setLocomotorGoalPositionExplicitSmart, so it is a virtual member. The donor's
// Bfme* names were placeholders; the members are named here for that role.
#include "PreRTS.h"
#include "Common/StateMachine.h"

class BfmeOutCTA
{
public:
	virtual void bfmeSpareCTA_0();
	virtual void bfmeSpareCTA_1();
	virtual void bfmeSpareCTA_2();
	virtual void bfmeSpareCTA_3();
	virtual void bfmeSpareCTA_4();
	virtual void bfmeBeginCTA();
	virtual void bfmeSpareCTA_6();
	virtual void bfmeSpareCTA_7();
	virtual void bfmeSendCTA(int code);
	virtual void bfmeSpareCTA_9();
	virtual void bfmeSpareCTA_10();
	virtual void bfmeSpareCTA_11();
	virtual void bfmeSpareCTA_12();
	virtual void bfmeSpareCTA_13();
	virtual void bfmeWriteVCTA(void *what);
};

class Object;

class AIUpdateInterface
{
protected:
	virtual void privateHarvest(const Coord3D *pos, CommandSourceType cmdSource);
public:
	unsigned char m_bfmeHead[8 - 4];
	Object *m_object;
	unsigned char m_bfmeGap[0x24];
	BfmeOutCTA *m_stateMachine;
	unsigned char m_bfmeGap2[0x14];
	CommandSourceType m_lastCommandSource;
};

// Native Object+8 owner call reaches the verified mobility body 0x002907A1.
// Reuse its Object thiscall bool() identity; keep the caller layout unchanged.
class Object
{
public:
	bool rva002907A1();
};

void AIUpdateInterface::privateHarvest(const Coord3D *pos, CommandSourceType cmdSource)
{
	if (m_object->rva002907A1())
	{
		m_stateMachine->bfmeBeginCTA();
		// ILT 0x0000314D resolves to StateMachine::setGoalPosition at 0x000A0880.
		reinterpret_cast<StateMachine *>(m_stateMachine)->setGoalPosition(pos);
		m_lastCommandSource = cmdSource;
		m_stateMachine->bfmeSendCTA(0x2f);
	}
}
