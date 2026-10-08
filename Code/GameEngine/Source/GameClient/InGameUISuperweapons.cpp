// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfme2_ascii
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
#include <list>
#include <map>
#include "ascii_string.h"

enum ObjectID { INVALID_ID = 0 };

class SpecialPowerTemplate;

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

protected:
	SuperweaponInfo *findSWInfo( int playerIndex, const AsciiString &powerName, ObjectID id, const SpecialPowerTemplate *powerTemplate );

	char m_opaque004[0x630 - 0x4];
	SuperweaponMap m_superweapons[1];		// +0x630, one 12-byte map per player
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
