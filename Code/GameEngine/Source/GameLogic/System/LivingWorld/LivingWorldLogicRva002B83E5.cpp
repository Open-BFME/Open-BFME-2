// cl: /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// ?rva002B83E5@LivingWorldLogic@@QAEXXZ
// retail 0x002B83E5..0x002B84C8 (227 bytes), thiscall, EH frame.
//
// A LivingWorldLogic reset member, pinned as the callee of the rowed
// LivingWorldLogic::rva002B84CD.  WorldBuilder twin 0xD7D850 (unnamed; its
// first call is LivingWorldLogic::processArmyDestroyList) gives the order:
// the rowed cleanup members 0x002B7BBB 0x002B7B25 0x002B7B71 0x002B7D91,
// the region manager at +0xB0 cleared through rowed 0x0020F795, rowed
// 0x002B7C74, the 12-byte element vector at +0x148 cleared (rowed
// vector<Gen_p12pod>::erase 0x002A133B), rowed 0x002B6900, the flag at
// +0xE9 dropped, rowed 0x002B296F, TheLivingWorldManager reset through rowed
// 0x002129B4, rowed 0x002B753B and the flag at +0xB4 raised.  With a GameSpy
// staging room it reports buddy status 5 with the game name (rowed getter
// 0x0022C4DF and WideCharStringToMultiByte 0x003289AC into rowed
// updateBuddyStatus 0x003896E7) and ends with rowed 0x00211570 on
// TheLivingWorldManager.  The class views here mirror the neighbouring
// LivingWorldLogic destructor unit (LivingWorldLogicDtorRva002B964F.cpp).

#include <string>
#include <vector>
#include "unicode_string.h"

struct Gen_p12pod { int a[3]; };

class Rva0020EE29 { public: void rva0020F795(); };
class Rva002B7C74 { public: void rva002B7C74(); };
class Rva002B4CED { public: void rva002B753B(); };
class Rva002B7B25 { public: void rva002B7B25(); };
class Rva002B6900 { public: void rva002B6900(); };
class Rva002B7B71 { public: void rva002B7B71(); };
class Rva002B296F { public: void rva002B296F(); };
class Glo012F1028Type { public: void rva002B7D91(); };
class Rva00211589 { public: void rva002129B4(); };
class Rva00211570 { public: void rva00211570(); };

class Rva0022C4DF
{
public:
	UnicodeString rva0022C4DF(void) const;
};

class LivingWorldManager;
class GameSpyStagingRoom;
extern LivingWorldManager *TheLivingWorldManager;
extern GameSpyStagingRoom *TheGameSpyGame;

enum GameSpyBuddyStatus
{
	GAMESPY_BUDDY_STATUS_5 = 5
};

_STL::string WideCharStringToMultiByte(const unsigned short *orig);
void updateBuddyStatus(GameSpyBuddyStatus status, int sleepTime, _STL::string mapName);

class LivingWorldLogic
{
public:
	void processArmyDestroyList();
	void rva002B83E5();
	void rva002B84C8();

	unsigned char m_pad00[0xb0];
	Rva0020EE29 *m_regions;					// +0xB0
	bool m_b4;						// +0xB4
	unsigned char m_padB5[0xe9 - 0xb5];
	bool m_e9;						// +0xE9
	unsigned char m_padEA[0x148 - 0xea];
	_STL::vector<Gen_p12pod> m_vector148;			// +0x148
};

void LivingWorldLogic::rva002B83E5()
{
	processArmyDestroyList();
	((Rva002B7B25 *)this)->rva002B7B25();
	((Rva002B7B71 *)this)->rva002B7B71();
	((Glo012F1028Type *)this)->rva002B7D91();
	m_regions->rva0020F795();
	((Rva002B7C74 *)this)->rva002B7C74();
	m_vector148.clear();
	((Rva002B6900 *)this)->rva002B6900();
	m_e9 = false;
	((Rva002B296F *)this)->rva002B296F();
	((Rva00211589 *)TheLivingWorldManager)->rva002129B4();
	((Rva002B4CED *)this)->rva002B753B();
	m_b4 = true;
	if (TheGameSpyGame)
		updateBuddyStatus(GAMESPY_BUDDY_STATUS_5, 0,
			WideCharStringToMultiByte(((Rva0022C4DF *)TheGameSpyGame)->rva0022C4DF().str()));
	((Rva00211570 *)TheLivingWorldManager)->rva00211570();
}

// 0x002B84C8 (5B), directly after the body it enters: a tail jump into the rowed
// 0x002B83E5 with its arguments unchanged. No referencing site found in this pass;
// address-named.
void LivingWorldLogic::rva002B84C8()
{
	rva002B83E5();
}
