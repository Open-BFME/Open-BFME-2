// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// InGameUI's superweapon timer bookkeeping: findSWInfo and the virtual
// add/remove/objectChangedTeam family of vftable 0x7FD410.
// Donor: ZH GameEngine/Source/GameClient/InGameUI.cpp (findSWInfo,
// addSuperweapon, objectChangedTeam), same control flow.
// Target evidence for the layout: findSWInfo (0x002A435D, ret 0x10) indexes
// this + (playerIndex + 0x84) * 12, so the per-player superweapon maps (12-byte
// STLport maps) start at +0x630; it calls the shared AsciiString-key tree find
// 0x001F8437, compares the result with the map header, walks the list held in
// the node at +0x14 and matches SuperweaponInfo::m_id at +0x18 (the 0x24-byte
// record built by the ctor 0x0029B74A, vftable 0x7FD028).
// addSuperweapon (0x002A70AE, slot 34): BFME 2 hides the timer when the
// template's required science list (by-value getter 0x0029FCB4) is non-empty
// and the owner has none of it (Player::hasAnyRequiredSciences 0x002AB7FD),
// where ZH tested one science. The record is a plain 0x24-byte new (0x0002FDA0)
// built with ten arguments (no evaReadyPlayed); font, point size and bold come
// from this+0x72C/+0x730/+0x734 and the color from the player's +0x280. The
// per-name list comes from the map subscript 0x002A6A2D and the append is the
// folded four-byte list push_back 0x0005548F. The local science vector carries
// unwind state -1 before its inline teardown because the game's free 0x00030830
// is C++-linkage and may throw: the _STL::free spelling (SidesList castle maps
// idiom) reproduces it; the extern "C" import would be nothrow.
#include <stdlib.h>
namespace _STL { void __cdecl free(void *block); }
#define free _STL::free
#include <list>
#include <map>
#include <vector>
#undef free
#include "ascii_string.h"

enum ObjectID { INVALID_ID = 0 };
enum ScienceType { SCIENCE_INVALID = -1 };
typedef _STL::vector<ScienceType> ScienceVec;

class SpecialPowerTemplate;

// Address-named by-value getter of the template's required sciences (rowed
// in Rva0029FCB4.cpp: final override +0x24).
class Rva0029FCB4
{
public:
	ScienceVec rva0029FCB4();
};

class Player
{
public:
	bool hasAnyRequiredSciences( const ScienceVec &sciences ) const;
	int getPlayerColor() const { return m_color; }
private:
	char m_opaque000[0x280];
	int m_color;							// +0x280
};

class PlayerList
{
public:
	Player *getNthPlayer( int i );
};

extern PlayerList *ThePlayerList;

// The SuperweaponInfo ctor as rowed (Rva0029B816Ctor.cpp, address-named).
class Rva0029B816
{
public:
	Rva0029B816( int id, int timestamp, bool hiddenByScript, bool hiddenByScience, bool ready, const AsciiString &font, int pointSize, bool bold, int color, int powerTemplate );
private:
	char m_data[0x24];
};

class SuperweaponInfo
{
public:
	virtual ~SuperweaponInfo();
	void *m_nameDisplayString;				// +0x04
	void *m_timeDisplayString;				// +0x08
	int m_color;							// +0x0C
	const SpecialPowerTemplate *m_powerTemplate;	// +0x10
	AsciiString m_powerName;				// +0x14
	ObjectID m_id;							// +0x18
};

typedef _STL::list<SuperweaponInfo *> SuperweaponList;
typedef _STL::map<AsciiString, SuperweaponList> SuperweaponMap;

class InGameUI
{
public:
	virtual ~InGameUI();
	virtual void addSuperweapon( int playerIndex, const AsciiString &powerName, ObjectID id, const SpecialPowerTemplate *powerTemplate );

protected:
	SuperweaponInfo *findSWInfo( int playerIndex, const AsciiString &powerName, ObjectID id, const SpecialPowerTemplate *powerTemplate );

	char m_opaque004[0x630 - 0x4];
	SuperweaponMap m_superweapons[(0x72C - 0x630) / 12];	// +0x630, one 12-byte map per player
	AsciiString m_superweaponNormalFont;	// +0x72C
	int m_superweaponNormalPointSize;		// +0x730
	bool m_superweaponNormalBold;			// +0x734
};

// ?findSWInfo@InGameUI@@IAEPAVSuperweaponInfo@@HABVAsciiString@@W4ObjectID@@PBVSpecialPowerTemplate@@@Z
SuperweaponInfo *InGameUI::findSWInfo( int playerIndex, const AsciiString &powerName, ObjectID id, const SpecialPowerTemplate *powerTemplate )
{
	SuperweaponMap::iterator mapIt = m_superweapons[playerIndex].find( powerName );
	if( mapIt != m_superweapons[playerIndex].end() )
	{
		for( SuperweaponList::iterator listIt = mapIt->second.begin(); listIt != mapIt->second.end(); ++listIt )
		{
			if( (*listIt)->m_id == id )
				return *listIt;
		}
	}
	return 0;
}

// ?addSuperweapon@InGameUI@@UAEXHABVAsciiString@@W4ObjectID@@PBVSpecialPowerTemplate@@@Z
void InGameUI::addSuperweapon( int playerIndex, const AsciiString &powerName, ObjectID id, const SpecialPowerTemplate *powerTemplate )
{
	if( powerTemplate == 0 )
		return;

	SuperweaponInfo *swInfo = findSWInfo( playerIndex, powerName, id, powerTemplate );
	if( swInfo != 0 )
		return;

	const Player *player = ThePlayerList->getNthPlayer( playerIndex );
	ScienceVec sciences = ((Rva0029FCB4 *)powerTemplate)->rva0029FCB4();
	bool hiddenByScience = !sciences.empty() && !player->hasAnyRequiredSciences( sciences );

	SuperweaponInfo *info = (SuperweaponInfo *)new Rva0029B816( id, -1, false, hiddenByScience, false,
		m_superweaponNormalFont, m_superweaponNormalPointSize, m_superweaponNormalBold,
		player->getPlayerColor(), (int)powerTemplate );

	m_superweapons[playerIndex][powerName].push_back( info );
}
