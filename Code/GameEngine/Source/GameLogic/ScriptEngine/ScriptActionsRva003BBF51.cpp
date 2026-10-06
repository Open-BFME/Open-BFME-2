// cl: /O1 /arch:SSE
// ?Rva003BBF51Set@@YGXPAVParameter@@M@Z @0x003BBF51 62B gap caller 0x003CC4A7 globals 0xDFE16C float 0x7C26F0 offsets 0x258 0x1F0 0x3C
// Evidence: getUnitNamed then [eax+0x258] [eax+0x1F0] null checks then movss xmm0,[esp+8] comiss with g_Va007C26F0 jb skip movss [eax+0x3C],xmm0 ret 8.
class Object;
class Parameter;
class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *);
};
extern class ScriptEngine *TheScriptEngine;
extern float g_Va007C26F0;
void __stdcall Rva003BBF51Set(Parameter *p, float f)
{
	Object *o = TheScriptEngine->getUnitNamed(p);
	if (!o)
		return;
	char *ai = *(char **)((char *)o + 0x258);
	if (!ai)
		return;
	char *sub = *(char **)(ai + 0x1F0);
	if (!sub)
		return;
	if (f >= g_Va007C26F0)
		*(float *)(sub + 0x3C) = f;
}
