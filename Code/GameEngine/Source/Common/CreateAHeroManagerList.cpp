// cl: /MD /O1 /arch:SSE /G7
// ?rva0021F797@CreateAHeroManager@@QAEPAVRva0040A3F9@@XZ @0x0021F797 16 bytes.
// Target evidence: calls the CRC routine with the incoming this, then returns
// this + 0x174. Caller declarations identify the manager and return type;
// the CRC routine's same-this call supports its zero-offset base relationship.

class Rva0040A3F9
{
};

class CreateAHeroCRC
{
public:
	void rva0021F47E();
};

class CreateAHeroManager : public CreateAHeroCRC
{
public:
	Rva0040A3F9 *rva0021F797();
	int rva002192C0();

private:
	char m_pad001[0x174];
	Rva0040A3F9 m_entries;
};

Rva0040A3F9 *CreateAHeroManager::rva0021F797()
{
	rva0021F47E();
	return &m_entries;
}

#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;
class GameSpyStagingRoom;
extern GameSpyStagingRoom *TheGameSpyGame;

// Target 0x002192C0..0x00219309, ending RET. Two pinned manager callers
// establish the thiscall ABI. The receiver is unused; target reads the
// global GameLogic words +0x114/+0x110 and, in one mode, the pointer-valued
// TheGameSpyGame pointer at VA 0x00E02324 followed by its flag at +0xFF4.
// The pointer's canonical data-ledger name is used; the flag remains unnamed.
int CreateAHeroManager::rva002192C0()
{
    GameLogic *logic = TheGameLogic;
    int mode114 = *reinterpret_cast<const int *>(
        reinterpret_cast<const unsigned char *>(logic) + 0x114);
    if (mode114 == 2)
        return 1;
    if (mode114 == 0)
        return 2;
    int mode110 = *reinterpret_cast<const int *>(
        reinterpret_cast<const unsigned char *>(logic) + 0x110);
    if (mode110 == 5)
    {
        if (TheGameSpyGame &&
            !*(reinterpret_cast<const unsigned char *>(TheGameSpyGame) + 0xFF4))
            return 0;
    }
    else if (mode110 == 2)
        return 3;
    return 4;
}
