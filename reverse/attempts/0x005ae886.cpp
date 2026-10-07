// ?rva005AE886@AptMessenger@@QAEXXZ
// partial score=0.96 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?rva005AE886@AptMessenger@@QAEXXZ @0x005AE886 137B. Caller selects the first tab; retail walks its player IDs and compares GameSpy slots +0x7c/+0x128.
// stlport
#include <vector>

struct PlayerAITypeEntry { int playerId; };
typedef _STL::_Vector_base<PlayerAITypeEntry, _STL::allocator<PlayerAITypeEntry> > PlayerAITypeVectorBase;
class PlayerAITypeEntries : public PlayerAITypeVectorBase
{
public:
	PlayerAITypeEntries() : PlayerAITypeVectorBase(_STL::allocator<PlayerAITypeEntry>()) {}
	~PlayerAITypeEntries() {}
	PlayerAITypeEntry *begin() { return this->_M_start; }
	PlayerAITypeEntry *end() { return this->_M_finish; }
};

class GameSpyInfoInterface
{
public:
#define GS_SLOT(n) virtual void slot##n();
GS_SLOT(00) GS_SLOT(01) GS_SLOT(02) GS_SLOT(03) GS_SLOT(04) GS_SLOT(05) GS_SLOT(06) GS_SLOT(07)
GS_SLOT(08) GS_SLOT(09) GS_SLOT(10) GS_SLOT(11) GS_SLOT(12) GS_SLOT(13) GS_SLOT(14) GS_SLOT(15)
GS_SLOT(16) GS_SLOT(17) GS_SLOT(18) GS_SLOT(19) GS_SLOT(20) GS_SLOT(21) GS_SLOT(22) GS_SLOT(23)
GS_SLOT(24) GS_SLOT(25) GS_SLOT(26) GS_SLOT(27) GS_SLOT(28) GS_SLOT(29) GS_SLOT(30)
	virtual int playerStatus();
GS_SLOT(32) GS_SLOT(33) GS_SLOT(34) GS_SLOT(35) GS_SLOT(36) GS_SLOT(37) GS_SLOT(38) GS_SLOT(39)
GS_SLOT(40) GS_SLOT(41) GS_SLOT(42) GS_SLOT(43) GS_SLOT(44) GS_SLOT(45) GS_SLOT(46) GS_SLOT(47)
GS_SLOT(48) GS_SLOT(49) GS_SLOT(50) GS_SLOT(51) GS_SLOT(52) GS_SLOT(53) GS_SLOT(54) GS_SLOT(55)
GS_SLOT(56) GS_SLOT(57) GS_SLOT(58) GS_SLOT(59) GS_SLOT(60) GS_SLOT(61) GS_SLOT(62) GS_SLOT(63)
GS_SLOT(64) GS_SLOT(65) GS_SLOT(66) GS_SLOT(67) GS_SLOT(68) GS_SLOT(69) GS_SLOT(70) GS_SLOT(71)
GS_SLOT(72) GS_SLOT(73)
#undef GS_SLOT
	virtual void updatePlayer(int playerId);
};

extern GameSpyInfoInterface *TheGameSpyInfo;

class AptMessenger
{
public:
	void GetSelectedPlayers(int a, int buffer, int c);
	void rva005AE886();
};

void AptMessenger::rva005AE886()
{
	if (!TheGameSpyInfo)
		return;

	{
		PlayerAITypeEntries selected;
		GetSelectedPlayers(0, (int)&selected, 0);
		for (PlayerAITypeEntry *entry = selected.begin(); entry != selected.end(); ++entry)
		{
			int playerId = entry->playerId;
			if (playerId != TheGameSpyInfo->playerStatus())
				TheGameSpyInfo->updatePlayer(playerId);
		}
	}
}
