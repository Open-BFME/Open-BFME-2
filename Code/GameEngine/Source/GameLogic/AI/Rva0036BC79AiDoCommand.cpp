// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /ICode/Libraries/Include/Lib /DNDEBUG /MD /I.
// ?aiDoCommand@Rva00368344@@UAEXPBUAICommandParms@@@Z, retail
// 0x0036BC79..0x0036BDF2 (377B): a Ghidra-unlisted aiDoCommand override
// reached through the +0x20 command table of an AIUpdateInterface subclass
// (the receiver of the ledger's rowed 0x00368344 family). Zero Hour's
// JetAIUpdate::aiDoCommand shape: unless the primary slot 148 allows the
// command nothing happens; while +0x538 is
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

#include "../../../Include/GameLogic/Module/AIUpdate.h"

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

class Rva00368344 : public AIUpdateInterface
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
	char m_pad3E4[0x3F0 - sizeof(AIUpdateInterface)];
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
		privateHunt(parms->m_cmdSource);
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
