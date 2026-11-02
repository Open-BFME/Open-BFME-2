// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /ICode/Libraries/Include/Lib /DNDEBUG /MD /I.
// ?aiDoCommand@Rva00368344@@UAEXPBUAICommandParms@@@Z, retail
// 0x0036BC79..0x0036BDF2 (377B): a Ghidra-unlisted aiDoCommand override
// reached through the AIUpdateInterface table of a class whose primary part
// (0x20 bytes, the receiver of the ledger's rowed 0x00368344 family) precedes
// the interface. Zero Hour's JetAIUpdate::aiDoCommand shape: unless the
// primary part's slot 148 allows the command nothing happens; while +0x538 is
// set the command is only stored (rowed 0x00351570); otherwise the stored
// command is cleared and the command type picks one of the rowed movement
// helpers, with everything else falling back (after clearing bit 0 of the
// +0x4B8 flags) to the rowed AIUpdateInterface::aiDoCommand. Parameter
// fields follow the sibling AIUpdateInterfaceAiDoCommand.cpp view.
#include "Coord3D.h"
#include "GameLogic/BfmeStoredAICommandView.h"
#include "reference/open-bfme-1/game/GameEngine/Source/GameLogic/command_source_type.h"
class Object;
class Waypoint;
#include "../../../Include/GameLogic/AICommandParms.h"

class AIUpdateInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms);	// 0x002673F6
};

class Rva003683EA
{
public:
	void rva003683EA(const Coord3D *pos, int cmdSource);	// 0x003683EA
};

class Rva00368542
{
public:
	void rva00368542(int value, const Waypoint *waypoint);	// 0x00368542
};

#define SLOTS10(n) virtual void s##n##0(); virtual void s##n##1(); virtual void s##n##2(); virtual void s##n##3(); virtual void s##n##4(); \
	virtual void s##n##5(); virtual void s##n##6(); virtual void s##n##7(); virtual void s##n##8(); virtual void s##n##9();

class Rva00368344Primary
{
public:
	SLOTS10(0) SLOTS10(1) SLOTS10(2) SLOTS10(3)
	virtual void s40(); virtual void s41(); virtual void s42();
	virtual void s43(int cmdSource);
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
	SLOTS10(5) SLOTS10(6) SLOTS10(7) SLOTS10(8) SLOTS10(9) SLOTS10(10) SLOTS10(11) SLOTS10(12) SLOTS10(13)
	virtual void s140(); virtual void s141(); virtual void s142(); virtual void s143(); virtual void s144();
	virtual void s145(); virtual void s146(); virtual void s147(); virtual bool isAllowedToRespondToAiCommands(const AICommandParms *parms); virtual void s149();
	virtual void s150(); virtual void s151(); virtual void s152(); virtual void s153(); virtual void s154();
	virtual void s155(); virtual void s156(); virtual void s157(); virtual void s158(); virtual void s159();
	virtual void s160(); virtual void s161(); virtual void s162(); virtual void s163(); virtual void s164();
	virtual void s165(); virtual void s166(); virtual void s167(); virtual void s168(); virtual void s169();
	char m_pad04[0x20 - 4];
};

class Rva00368344 : public Rva00368344Primary, public AIUpdateInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms);
	void rva00368344(const Coord3D *pos, int cmdSource);	// 0x00368344
	void rva00368397(const Coord3D *pos, int cmdSource);	// 0x00368397
	void rva00368433(const Coord3D *pos, int cmdSource);	// 0x00368433
	void rva00368486(const Coord3D *pos, const Waypoint *waypoint, bool flag);	// 0x00368486
	void rva0036BB2F(const Waypoint *waypoint, bool flag, int cmdSource);	// 0x0036BB2F
private:
	void clearFlag0() { m_flags &= ~1; }
	char m_pad024[0x3F0 - 0x24];
	Rva00351570 m_storedCommand;							// +0x3F0 (+0x3D0 of the interface)
	char m_pad4B4[0x4B8 - 0x3F0 - sizeof(Rva00351570)];
	unsigned int m_flags;									// +0x4B8
	char m_pad4BC[0x558 - 0x4BC];
	bool m_commandPending;									// +0x558 (+0x538 of the interface)
};

void Rva00368344::aiDoCommand(const AICommandParms *parms)
{
	if (!isAllowedToRespondToAiCommands(parms))
		return;
	if (m_commandPending)
	{
		m_storedCommand.rva00351570(*reinterpret_cast<const Rva00351570Src *>(parms));
		return;
	}
	m_storedCommand.m_00 = -1;
	switch (parms->m_cmd)
	{
	case 0x3F:
		rva00368486((const Coord3D *)parms->m_obj, (const Waypoint *)parms->m_cmdSource, true);
		break;
	case 0x0B:
	case 0x0C:
	case 0x39:
		rva00368486((const Coord3D *)parms->m_obj, (const Waypoint *)parms->m_cmdSource, false);
		break;
	case 0x23:
		((Rva00368542 *)this)->rva00368542((int)parms->m_polygon, (const Waypoint *)parms->m_cmdSource);
		break;
	case 0x12:
		s43(parms->m_cmdSource);
		break;
	case 0x0F:
		((Rva003683EA *)this)->rva003683EA(&parms->m_pos, parms->m_cmdSource);
		break;
	case 6:
	case 0x32:
		rva0036BB2F((const Waypoint *)parms->m_waypoint, false, parms->m_cmdSource);
		break;
	case 7:
	case 0x33:
		rva0036BB2F((const Waypoint *)parms->m_waypoint, true, parms->m_cmdSource);
		break;
	case 0x41:
		rva00368433(&parms->m_pos, parms->m_cmdSource);
		break;
	case 0x0E:
	case 0x40:
		break;
	default:
		clearFlag0();
		AIUpdateInterface::aiDoCommand(parms);
		break;
	case 0:
	case 0x4E:
		rva00368344(&parms->m_pos, parms->m_cmdSource);
		break;
	case 0x48:
		rva00368397((const Coord3D *)((const char *)parms->m_obj + 0x38), parms->m_cmdSource);
		break;
	case 0x47:
		rva00368397(&parms->m_pos, parms->m_cmdSource);
		break;
	}
}
