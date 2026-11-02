// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BCD1BDo@ScriptActions@@QAEXPAVParameter@@@Z @0x003BCD1B 42B: script fire special power slot 0x44.
// Evidence: push [esp+4] mov ecx,[0xDFE16C]=g_Va009FE16C call rowed getUnitNamed 0x003588E7 test je; push 0x2d mov ecx,eax call rowed findSpecialPowerModuleInterface 0x00290E22 test je; mov edx,[eax] mov ecx,eax call [edx+0x44] ret 4; caller 0x003CDCD0; sibling Rva003BCCC6Do same 0x2d pattern.
class Parameter;
class Object;

#include "../../../Include/GameLogic/Module/SpecialPowerModule.h"

enum SpecialPowerType
{
	SPECIAL_INVALID = 0
};

#include "../Object/object.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;

void ScriptActions::Rva003BCD1BDo(Parameter *param)
{
	Object *obj = TheScriptEngine->getUnitNamed(param);
	if (obj == 0)
		return;
	SpecialPowerModuleInterface *sp = obj->findSpecialPowerModuleInterface((SpecialPowerType)0x2d);
	if (sp == 0)
		return;
	sp->slot17();
}
