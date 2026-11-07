// cl: /Oy- /DNDEBUG /MD /GX-
// ?ParseINI@BuildingRestriction@ModuleData@LivingWorldRegion@@YAXPAVINI@@PAX@Z @0x003F2576 104B
// Renamed from placeholder Rva003F2576Parse: the retail INIException literal
// "Invalid data in LivingWorldRegion::ModuleData::BuildingRestriction::ParseINI"
// names this function and its class nesting (WorldBuilder string, score 1.0).
// The second parameter's real type is not yet proven; PAX follows the
// ParseEyeTowerPointData opaque-argument precedent. The +0x14 holder view is
// TU-local and claims nothing about the owner class.
// Body provenance: placeholder Rva003F2576Parse.cpp (matched), itself built from
// landed callees initFromINI 0x0002DE78, new 0x0002FDA0, Rva003F1FB6 ctor
// 0x003F1FB6, holder 0x003F255C, INIException 0x0002F681; table VA 0x00C36EE0.
typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
#include "../../../Include/Common/INI/FieldParse.h"

#include "../../../Include/Common/INI/INI.h"

class ModuleData;

class Rva003F1FB6
{
public:
	Rva003F1FB6();
private:
	char m_pad[0x10];
};

class Rva003F255C
{
public:
	void rva003F255C(const ModuleData *p);
};

struct Rva003F2576Outer
{
	char _pad[0x14];
	Rva003F255C m_holder;
};



extern const char *const LivingWorldBuildingTypeNames[];
void Rva00339D26Parse(INI *, void *, void *, const void *);
// The retail table at 0x00836EE0: 2 entries and the null terminator; every parser is rowed.
extern const FieldParse buildingRestrictionFieldParse[3] = {
	{ "Buildings", &Rva00339D26Parse, LivingWorldBuildingTypeNames, 0x0 },
	{ "NumberAllowed", (FieldParseProc)&INI::parseInt, 0, 0xC },
	{ 0, 0, 0, 0 }
};

#include "../../../Include/GameLogic/LivingWorldRegion.h"

void LivingWorldRegion::ModuleData::BuildingRestriction::ParseINI(INI *ini, void *outer)
{
	if (!ini || !outer)
	{
		throw INIException(3, "Invalid data in LivingWorldRegion::ModuleData::BuildingRestriction::ParseINI");
	}
	Rva003F255C *holder = &reinterpret_cast<Rva003F2576Outer *>(outer)->m_holder;
	Rva003F1FB6 *restriction = new Rva003F1FB6;
	ini->initFromINI(restriction, buildingRestrictionFieldParse);
	holder->rva003F255C((const ::ModuleData *)restriction);
}
