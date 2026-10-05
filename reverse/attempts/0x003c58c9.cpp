// ?Rva003C58C9Do@@YGXPAVParameter@@ABVAsciiString@@PAX@Z
// partial score=0.93 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
// ?Rva003C58C9Do@@YGXPAVParameter@@ABVAsciiString@@PAX@Z @0x003C58C9 161B: unit command-button with TerrainLogic Coord3D via getUnitNamed name lookup CommandSet loop 32 compare then rva00297149. Evidence: rowed getUnitNamed 0x3588E7 rva00290E67 0x290E67 rva0031D5F8 0x31D5F8 getCommandButton 0x409EE8 isEmpty 0x1E2F compare 0x69D6 pin rva00297149 0x297149 g_Va009FE16C g_bfmeWorldRV TheTerrainLogic slot 0x88; caller 0x003CCAD6; ret 0xC stdcall.
#include "ascii_string.h"

class Parameter;
class Object;
class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
};
extern ScriptEngine *g_Va009FE16C;

struct Coord3D { float x, y, z; };

struct TerrainPos
{
	char _pad[0x0C];
	Coord3D pos;
};

class TerrainLogic
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
	virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
	virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
	virtual TerrainPos *s34(void *p);
};
extern TerrainLogic *TheTerrainLogic;

class CommandButton
{
public:
	char m_pad00[0x10];
	AsciiString m_str10;
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(int i) const;
};

struct BfmeWorldRV;
extern BfmeWorldRV *g_bfmeWorldRV;

class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *s);
};

class Object
{
public:
	const AsciiString *rva00290E67() const;
	void rva00297149(const CommandButton *b, const Coord3D *pos, int a, int c);
};

// ?Rva003C58C9Do@@YGXPAVParameter@@ABVAsciiString@@PAX@Z present-unmatched
void __stdcall Rva003C58C9Do(Parameter *p, const AsciiString &name, void *arg3)
{
	Object *obj;
	TerrainPos *base;
	obj = g_Va009FE16C->getUnitNamed(p);
	base = TheTerrainLogic->s34(arg3);
	if (obj == 0 || base == 0)
		return;
	const AsciiString *s = obj->rva00290E67();
	const CommandSet *cmdSet = (const CommandSet *)((Rva0031D5F8 *)g_bfmeWorldRV)->rva0031D5F8(s);
	if (cmdSet == 0)
		return;
	for (int i = 0; i < 32; ++i)
	{
		const CommandButton *b = cmdSet->getCommandButton(i);
		if (b == 0)
			continue;
		const StringBase<char> &bs = (const StringBase<char> &)b->m_str10;
		if (bs.isEmpty())
			continue;
		int cmp = bs.compare((const StringBase<char> &)name);
		if (cmp != 0)
			continue;
		obj->rva00297149(b, &base->pos, 1, cmp);
	}
}
