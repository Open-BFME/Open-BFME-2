// cl: /Ireference/shims/bfme2_ascii /GX /DNDEBUG /MD
//
// Thin FieldParse procs built with unwinding (AsciiString temporaries);
// original names unproven, so address names:
//   0x004E8E57 79B Unit (0x00BFD804, beside the rowed parseAIKindOfList
//       TargetTypes row): stores getAIKindOfFromName (rowed 0x004E8DE7) of the
//       next AsciiString token into the int at the store.
//   0x0029B919 78B TerrainResourceClaimDecal (0x00BFC788): parses an
//       AsciiString through INI::parseAsciiString into a local and hands it to
//       the resource-entry holder at instance + 0x58C (rowed 0x004E7D16).
//   0x005096FF 33B WeaponLaunchBoneSlotOverride (0x00C64670): weapon slot index
//       (member scanIndexList over the VA 0x00DBC284 names) into the store.

#include "ascii_string.h"

#define NULL 0

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	AsciiString getNextAsciiString();
	int scanIndexList(const char *token, const char *const *names);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004E8E57_ParseAIKindOf(INI *ini, void *instance, void *store, const void *userData);
	static void Rva0029B919_ParseResourceClaimDecal(INI *ini, void *instance, void *store, const void *userData);
	static void Rva005096FF_ParseWeaponSlot(INI *ini, void *instance, void *store, const void *userData);
};

int getAIKindOfFromName(const char *name);

class Rva004E7B0CHolder
{
public:
	void rva004E7D16(const AsciiString &value);
private:
	void *m_owner;
};

const char *TheWeaponSlotTypeNames[] = {
	"PRIMARY",
	"SECONDARY",
	"TERTIARY",
	"QUATERNARY",
	"QUINARY",
	0,
};

// ?Rva004E8E57_ParseAIKindOf@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva004E8E57_ParseAIKindOf(INI *ini, void *, void *store, const void *)
{
	*(int *)store = getAIKindOfFromName(ini->getNextAsciiString().str());
}

// ?Rva0029B919_ParseResourceClaimDecal@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva0029B919_ParseResourceClaimDecal(INI *ini, void *instance, void *, const void *)
{
	AsciiString name;
	INI::parseAsciiString(ini, NULL, &name, NULL);
	((Rva004E7B0CHolder *)((char *)instance + 0x58C))->rva004E7D16(name);
}

// ?Rva005096FF_ParseWeaponSlot@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva005096FF_ParseWeaponSlot(INI *ini, void *, void *store, const void *)
{
	*(int *)store = ini->scanIndexList(ini->getNextToken(NULL), TheWeaponSlotTypeNames);
}
