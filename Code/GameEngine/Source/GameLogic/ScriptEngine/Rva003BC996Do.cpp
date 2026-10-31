// stlport
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// ?Rva003BC996Do@ScriptActions@@QAEXPAVParameter@@ABV?$StringBase@D@@M@Z @0x003BC996 63B: Script unit to Drawable anim via getUnitNamed getDrawable and slot10; neighbours Rva003BC96FDo Rva003BCA12Do; caller 0x003CD629.
#include "ascii_string.h"

class Parameter
{
};

class Drawable
{
public:
	void setEmoticon(const StringBase<char> &name, int val);
};

#include "../../Common/Thing/thing.h"

class Object : public Thing
{
};

#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;

class AIGroup;

extern int BfmeLogicFramesPerSecond;

// ?getUnitNamed@ScriptEngine@@QAEPAVObject@@PAVParameter@@@Z present-unmatched
// ?getDrawable@Thing@@QBEPAVDrawable@@XZ present-unmatched
// ?setEmoticon@Drawable@@QAEXABV?$StringBase@D@@H@Z present-unmatched
void ScriptActions::Rva003BC996Do(Parameter *param, const StringBase<char> &animName, float f)
{
	Object *obj = TheScriptEngine->getUnitNamed(param);
	if (obj == 0)
		return;
	Drawable *drawable = obj->getDrawable();
	if (drawable == 0)
		return;
	int v = (int)((float)BfmeLogicFramesPerSecond * f);
	drawable->setEmoticon(animName, v);
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
