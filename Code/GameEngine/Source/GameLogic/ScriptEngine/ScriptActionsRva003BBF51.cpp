// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?doNamedSetStoppingDistance@ScriptActions@@QAEXPAVParameter@@M@Z @0x003BBF51 62B gap caller 0x003CC4A7 globals 0xDFE16C float 0x7C26F0 offsets 0x258 0x1F0 0x3C
// Evidence: getUnitNamed then [eax+0x258] [eax+0x1F0] null checks then movss xmm0,[esp+8] comiss with g_Va007C26F0 jb skip movss [eax+0x3C],xmm0 ret 8.
class Object;
class Parameter;
#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;
extern float g_Va007C26F0;
void ScriptActions::doNamedSetStoppingDistance(Parameter *parameter, float f)
{
	Object *object = TheScriptEngine->getUnitNamed(parameter);
	if (!object)
		return;
	char *ai = *(char **)((char *)object + 0x258);
	if (!ai)
		return;
	char *sub = *(char **)(ai + 0x1F0);
	if (!sub)
		return;
	if (f >= g_Va007C26F0)
		*(float *)(sub + 0x3C) = f;
}
