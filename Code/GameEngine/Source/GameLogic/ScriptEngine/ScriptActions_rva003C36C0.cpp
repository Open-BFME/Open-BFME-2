// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
// ?Rva003C36C0Do@@YGXPAVParameter@@_N@Z @0x003C36C0 62B: lookup unit by value then drawable flag. Evidence: rowed lookupUnitByValue 0x358752 getDrawable 0x5508E2 rva00270FAC 0x270FAC StringBase copy 0x365F0 globals g_Va009FE16C; caller 0x003CE8C2; ret 0x8 stdcall.
#include "ascii_string.h"

class Object;
class Drawable
{
public:
	void rva00270FAC(bool flag);
};
class Thing
{
public:
	Drawable *getDrawable() const;
};
class Parameter
{
public:
	unsigned char m_beforeInt[8];
	int m_int;
	float m_real;
	AsciiString m_string;
};
class Rva00358752Opaque
{
public:
	Object *lookupUnitByValue(AsciiString name);
};
class ScriptEngine;
extern class ScriptEngine *TheScriptEngine;

void __stdcall Rva003C36C0Do(Parameter *parm, bool flag)
{
	Object *obj = ((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue((AsciiString &)parm->m_string);
	if (obj == 0)
		return;
	Drawable *draw = ((Thing *)obj)->getDrawable();
	if (draw == 0)
		return;
	draw->rva00270FAC(flag);
}
