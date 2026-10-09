// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
// stlport
// AptOnlineCustomMatch.cpp -- AptOnlineCustomMatch members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// function and asserts TheGameSpyInfo and the current game exist; retail
// supplies the bytes and skips both instead.
//
// The game owner's name is slot 0's name (+0x30, a UnicodeString). The
// current game comes from GameSpyInfo's virtual at +0xD4 (Zero Hour's
// getCurrentStagingRoom; the name is carried from that donor).
#include "ascii_string.h"
#include "unicode_string.h"
#include <map>

// Keep STLport4.5.3's integer comparison inline without a competing copy.
namespace _STL {
template<> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int& a,const int& b) const
{ return a < b; }
}

typedef int Int;

class GameSpyStagingRoom;
typedef std::map<Int, GameSpyStagingRoom *> StagingRoomMap;

class GameSlot
{
public:
	unsigned char m_pad00[0x30];
	UnicodeString m_name;				// +0x30
};

class GameInfo
{
public:
	GameSlot *getSlot(Int slotNum);			// 0x003FF29F
};

#define GSI_SLOT(n) virtual void slot##n();

class GameSpyInfoInterface
{
public:
	GSI_SLOT(00) GSI_SLOT(01) GSI_SLOT(02) GSI_SLOT(03) GSI_SLOT(04) GSI_SLOT(05) GSI_SLOT(06) GSI_SLOT(07)
	GSI_SLOT(08) GSI_SLOT(09) GSI_SLOT(10) GSI_SLOT(11) GSI_SLOT(12) GSI_SLOT(13) GSI_SLOT(14) GSI_SLOT(15)
	GSI_SLOT(16) GSI_SLOT(17) GSI_SLOT(18) GSI_SLOT(19) GSI_SLOT(20) GSI_SLOT(21) GSI_SLOT(22) GSI_SLOT(23)
	GSI_SLOT(24) GSI_SLOT(25) GSI_SLOT(26) GSI_SLOT(27) GSI_SLOT(28) GSI_SLOT(29) GSI_SLOT(30) GSI_SLOT(31)
	GSI_SLOT(32) GSI_SLOT(33) GSI_SLOT(34) GSI_SLOT(35) GSI_SLOT(36) GSI_SLOT(37) GSI_SLOT(38) GSI_SLOT(39)
	GSI_SLOT(40)
	virtual StagingRoomMap *getStagingRoomList();	// +0xA4
	GSI_SLOT(42) GSI_SLOT(43) GSI_SLOT(44) GSI_SLOT(45) GSI_SLOT(46) GSI_SLOT(47)
	GSI_SLOT(48) GSI_SLOT(49) GSI_SLOT(50) GSI_SLOT(51) GSI_SLOT(52)
	virtual GameInfo *getCurrentStagingRoom();	// +0xD4
};

#undef GSI_SLOT

extern GameSpyInfoInterface *TheGameSpyInfo;		// 0x00E02320

class AptOnlineCustomMatch
{
public:
	void MpOwnerGetLocalPlayerName(UnicodeString &name);
	GameSpyStagingRoom *GetGameToJoin();

private:
	unsigned char m_pad000[0x4b8];
	Int m_gameToJoinID;				// +0x4B8
};

// AptOnlineCustomMatch::MpOwnerGetLocalPlayerName, retail 0x0059EBAF.
void AptOnlineCustomMatch::MpOwnerGetLocalPlayerName(UnicodeString &name)
{
	if (!TheGameSpyInfo)
		return;
	GameInfo *myGame = TheGameSpyInfo->getCurrentStagingRoom();
	if (!myGame)
		return;
	name.set(myGame->getSlot(0)->m_name);
}

// AptOnlineCustomMatch::GetGameToJoin, retail 0x005A0808: the staging room
// for the remembered game id (+0x4B8), or NULL (Zero Hour's staging room
// map lookup; the list comes from GameSpyInfo's virtual at +0xA4).
GameSpyStagingRoom *AptOnlineCustomMatch::GetGameToJoin()
{
	StagingRoomMap *srm = TheGameSpyInfo->getStagingRoomList();
	if (!srm)
		return 0;
	StagingRoomMap::iterator it = srm->find(m_gameToJoinID);
	if (it == srm->end())
		return 0;
	return it->second;
}
