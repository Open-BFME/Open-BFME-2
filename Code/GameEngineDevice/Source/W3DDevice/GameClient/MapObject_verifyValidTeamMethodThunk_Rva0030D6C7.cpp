// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/stringinline -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient
//
// ?verifyValidTeam@MapObject@@QAEXXZ
// retail 0x0030D6C7, 129 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngineDevice/Source/W3DDevice/GameClient/MapObject_verifyValidTeamMethodThunk.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /Os it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here.
// MapObject::verifyValidTeam, donor retail RVA 0x000889A0, 157 bytes.
// The BFME dictionary and StringBase ABI are distinct from the Zero Hour
// headers used by WorldHeightMap.cpp; StringInline.h supplies the existing
// one-pointer by-value string model and its proven StringBase forwarding
// constructors without redeclaring a covered string type here.

#include "StringInline.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

// StaticNameKey::key is rowed as Rva00148F5ECache::get.
class StaticNameKey;
class Rva00148F5ECache
{
public:
	NameKeyType get();
};

extern const StaticNameKey TheKey_originalOwner;

class Dict
{
public:
	AsciiString getAsciiString(int key, bool *exists = 0) const;
	bool remove(int key);
};

class MapObject
{
public:
	Dict *getProperties()
	{
		return &m_properties;
	}

	void verifyValidTeam();

private:
	char m_prefix[0x24];
	Dict m_properties;
};

class Rva0019C520Owner
{
public:
	int forward(AsciiString name, int extra);
};

// Canonical retail type of the 0x012EF428 singleton; pointee only, so a forward
// declaration is enough.  The definition lives in
// game/GameEngine/Source/Common/System/game_engine_subsystems.h.
class SidesList;

// Retail global at 0x012EF428, ?TheSidesList@@3PAVSidesList@@A.  The member
// call shape is taken through the TU-local ABI view below.
extern SidesList *TheSidesList;

void MapObject::verifyValidTeam()
{
	bool exists;
	AsciiString teamName = getProperties()->getAsciiString(
		((Rva00148F5ECache *)&TheKey_originalOwner)->get(), &exists);
	if (exists)
	{
		if (!((Rva0019C520Owner *)TheSidesList)->forward(teamName, 0))
			getProperties()->remove(((Rva00148F5ECache *)&TheKey_originalOwner)->get());
	}
}
