// stlport
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BC903Do@ScriptActions@@QAEXPAVParameter@@H@Z @0x003BC903 57B: script getUnitNamed then ExperienceTracker at Object+0x264 add with int as float. Evidence: push [esp+4] mov ecx,[0x00DFE16C]=g_Va009FE16C call getUnitNamed test eax je then mov ecx,[eax+0x264] test je then cvtsi2ss xmm0,[esp+8] push 0 push 1 push 1 push 1 push ecx movss [esp],xmm0 call rva0039B315 ret 8; callee pin ExperienceTracker float bool bool bool int; caller 0x003CDBFC; sibling Rva003BC96FDo same +0x264 Parameter int shape.
class Parameter
{
};
class ExperienceTracker
{
public:
	void rva0039B315(float amount, bool a, bool b, bool c, bool d);
};
class Object
{
public:
	char m_pad[0x264];
	ExperienceTracker *m_264;
};
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;
void ScriptActions::Rva003BC903Do(Parameter *param, int val)
{
	Object *obj = TheScriptEngine->getUnitNamed(param);
	if (obj == 0)
		return;
	ExperienceTracker *tracker = obj->m_264;
	if (tracker == 0)
		return;
	tracker->rva0039B315((float)val, true, true, true, false);
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
