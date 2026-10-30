// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -GX -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003C36C0Do@ScriptActions@@QAEXPAVParameter@@_N@Z @0x003C36C0 62B: lookup unit by value then drawable flag. Evidence: rowed lookupUnitByValue 0x358752 getDrawable 0x5508E2 rva00270FAC 0x270FAC StringBase copy 0x365F0 globals g_Va009FE16C; caller 0x003CE8C2; ret 0x8 stdcall.
#include "ascii_string.h"

class Object;
#include "../../../Include/GameClient/DrawableBFME2.h"
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

void ScriptActions::Rva003C36C0Do(Parameter *parm, bool flag)
{
	Object *obj = ((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue((AsciiString &)parm->m_string);
	if (obj == 0)
		return;
	Drawable *draw = ((Thing *)obj)->getDrawable();
	if (draw == 0)
		return;
	draw->rva00270FAC(flag);
}
