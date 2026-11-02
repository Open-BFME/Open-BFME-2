// cl: /DNDEBUG /MD /GX-
// ?rva0041330C@Rva0041330C@@QAEXPAVINI@@@Z, retail 0x0041330C, 18 bytes.
// INI table forward: ini->initFromINI(this) through table 0x00839968 (rowed
// 0x0002DE78). Same recipe as sibling Rva00413D46Parse. Evidence: unlock lane;
// retail push-imm plus push-ecx plus mov-ecx-[esp+0xc] plus call plus ret-4;
// caller 0x00413586.
typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
#include "../../Include/Common/INI/FieldParse.h"
#include "../../Include/Common/INI/INI.h"
// The retail table at 0x00839968: 4 entries and the null terminator; every parser is rowed.
extern const FieldParse g_00C39968[5] = {
	{ "GUIDisplayedLevel", (FieldParseProc)&INI::parseInt, 0, 0x0 },
	{ "WeaponMultiplier", (FieldParseProc)&INI::parseReal, 0, 0x4 },
	{ "ArmorMultiplier", (FieldParseProc)&INI::parseReal, 0, 0x8 },
	{ "ExperienceMultiplier", (FieldParseProc)&INI::parseReal, 0, 0xC },
	{ 0, 0, 0, 0 }
};
class Rva0041330C
{
public:
  void rva0041330C(INI *ini);
};

void Rva0041330C::rva0041330C(INI *ini)
{
  ini->initFromINI(this, g_00C39968);
}
