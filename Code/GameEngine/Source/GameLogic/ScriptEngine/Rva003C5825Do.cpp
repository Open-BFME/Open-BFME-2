// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
// ?Rva003C5825Do@@YGXPAVParameter@@ABVAsciiString@@1@Z @0x003C5825 164B: unit command-button with two-object lookup via getUnitNamed plus by-value lookupUnitByValue then CommandSet loop 32 compare then rva00297000. Evidence: rowed getUnitNamed 0x3588E7 StringBase copy 0x365F0 lookupUnitByValue 0x358752 rva00290E67 0x290E67 rva0031D5F8 0x31D5F8 getCommandButton 0x409EE8 isEmpty 0x1E2F compare 0x69D6 pin rva00297000 0x297000 g_Va009FE16C g_bfmeWorldRV; caller 0x003CCAA7; ret 0xC stdcall.
#include "ascii_string.h"

class Parameter;
class Object;
class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
};
extern class ScriptEngine *TheScriptEngine;

class Rva00358752Opaque
{
public:
	Object *lookupUnitByValue(AsciiString name);
};

struct Coord3D { float x, y, z; };

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
extern class ControlBar *TheControlBar;

class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *s);
};

class Object
{
public:
	const AsciiString *rva00290E67() const;
	void rva00297000(const CommandButton *b, Object *o, int a, int c);
};

void __stdcall Rva003C5825Do(Parameter *p, const AsciiString &name, const AsciiString &lookupName)
{
	Object *obj = TheScriptEngine->getUnitNamed(p);
	Object *obj2 = ((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue(lookupName);
	if (obj == 0 || obj2 == 0)
		return;
	const AsciiString *s = obj->rva00290E67();
	const CommandSet *cmdSet = (const CommandSet *)((Rva0031D5F8 *)(*(BfmeWorldRV **)&TheControlBar))->rva0031D5F8(s);
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
		obj->rva00297000(b, obj2, 1, cmp);
	}
}
