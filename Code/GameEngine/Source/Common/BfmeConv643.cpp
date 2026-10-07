// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/BfmeConv643.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: BfmeThingCSH::bfmeGoCSH 0x00264ADE (56B). Callee addresses
// are read off retail's call sites (reverse/symbols.csv). Only the placed
// bodies are carried; the donor's other definitions are omitted.
#include "PreRTS.h"
#include "GameLogic/AIStateMachine.h"

class BfmeOutCSH
{
public:
	virtual void bfmeSpareCSH_0();
	virtual void bfmeSpareCSH_1();
	virtual void bfmeSpareCSH_2();
	virtual void bfmeSpareCSH_3();
	virtual void bfmeSpareCSH_4();
	virtual void bfmeBeginCSH();
	virtual void bfmeSpareCSH_6();
	virtual void bfmeSpareCSH_7();
	virtual void bfmeSendCSH(int code);
	virtual void bfmeSpareCSH_9();
	virtual void bfmeSpareCSH_10();
	virtual void bfmeSpareCSH_11();
	virtual void bfmeSpareCSH_12();
	virtual void bfmeSpareCSH_13();
	virtual void bfmeSpareCSH_14();
};

// Native Object+8 owner call reaches the verified mobility body 0x002907A1.
// Reuse its Object thiscall bool() identity; keep the caller layout unchanged.
class Object
{
public:
	bool rva002907A1();
};

class BfmeThingCSH
{
public:
	unsigned char m_bfmeHead[8];
	Object *m_bfmeSub;
	unsigned char m_bfmeGap[0x24];
	BfmeOutCSH *m_bfmeOut;
	unsigned char m_bfmeGap2[0x14];
	void *m_bfmeVal;
	void bfmeGoCSH(void *one, void *two);
};

void BfmeThingCSH::bfmeGoCSH(void *one, void *two)
{
	if (m_bfmeSub->rva002907A1())
	{
		m_bfmeOut->bfmeBeginCSH();
		m_bfmeVal = two;
		// ILT 0x00036192 resolves to AIStateMachine::setGoalWaypoint at 0x0016AEB0.
		reinterpret_cast<AIStateMachine *>(m_bfmeOut)->setGoalWaypoint(static_cast<const Waypoint *>(one));
		m_bfmeOut->bfmeSendCSH(0x13);
	}
}
