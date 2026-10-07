// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/BfmeConv642.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: BfmeThingCSG::bfmeGoCSG 0x00264A4E (56B). Callee addresses
// are read off retail's call sites (reverse/symbols.csv). Only the placed
// bodies are carried; the donor's other definitions are omitted.
#include "PreRTS.h"
#include "GameLogic/AIStateMachine.h"

class BfmeOutCSG
{
public:
	virtual void bfmeSpareCSG_0();
	virtual void bfmeSpareCSG_1();
	virtual void bfmeSpareCSG_2();
	virtual void bfmeSpareCSG_3();
	virtual void bfmeSpareCSG_4();
	virtual void bfmeBeginCSG();
	virtual void bfmeSpareCSG_6();
	virtual void bfmeSpareCSG_7();
	virtual void bfmeSendCSG(int code);
	virtual void bfmeSpareCSG_9();
	virtual void bfmeSpareCSG_10();
	virtual void bfmeSpareCSG_11();
	virtual void bfmeSpareCSG_12();
	virtual void bfmeSpareCSG_13();
	virtual void bfmeSpareCSG_14();
};

// Native Object+8 owner call reaches the verified mobility body 0x002907A1.
// Reuse its Object thiscall bool() identity; keep the caller layout unchanged.
class Object
{
public:
	bool rva002907A1();
};

class BfmeThingCSG
{
public:
	unsigned char m_bfmeHead[8];
	Object *m_bfmeSub;
	unsigned char m_bfmeGap[0x24];
	BfmeOutCSG *m_bfmeOut;
	unsigned char m_bfmeGap2[0x14];
	void *m_bfmeVal;
	void bfmeGoCSG(void *one, void *two);
};

void BfmeThingCSG::bfmeGoCSG(void *one, void *two)
{
	if (m_bfmeSub->rva002907A1())
	{
		m_bfmeOut->bfmeBeginCSG();
		m_bfmeVal = two;
		// ILT 0x00036192 resolves to AIStateMachine::setGoalWaypoint at 0x0016AEB0.
		reinterpret_cast<AIStateMachine *>(m_bfmeOut)->setGoalWaypoint(static_cast<const Waypoint *>(one));
		m_bfmeOut->bfmeSendCSG(0x12);
	}
}
