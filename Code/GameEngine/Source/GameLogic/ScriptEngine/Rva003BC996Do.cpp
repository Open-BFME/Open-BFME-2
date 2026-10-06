// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE
// ?Rva003BC996Do@@YGXPAVParameter@@ABV?$StringBase@D@@M@Z @0x003BC996 63B: Script unit to Drawable anim via getUnitNamed getDrawable and slot10; neighbours Rva003BC96FDo Rva003BCA12Do; caller 0x003CD629.
#include "ascii_string.h"

class Parameter
{
};

class Drawable
{
public:
	void setEmoticon(const StringBase<char> &name, int val);
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class Object : public Thing
{
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
};
extern class ScriptEngine *TheScriptEngine;

class AIGroup;

extern int g_Va00DBA4E4;

// ?getUnitNamed@ScriptEngine@@QAEPAVObject@@PAVParameter@@@Z present-unmatched
// ?getDrawable@Thing@@QBEPAVDrawable@@XZ present-unmatched
// ?setEmoticon@Drawable@@QAEXABV?$StringBase@D@@H@Z present-unmatched
void __stdcall Rva003BC996Do(Parameter *param, const StringBase<char> &animName, float f)
{
	Object *obj = TheScriptEngine->getUnitNamed(param);
	if (obj == 0)
		return;
	Drawable *d = obj->getDrawable();
	if (d == 0)
		return;
	int v = (int)((float)g_Va00DBA4E4 * f);
	d->setEmoticon(animName, v);
}
