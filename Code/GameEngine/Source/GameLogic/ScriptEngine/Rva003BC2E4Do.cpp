// cl: /O1
// ?Rva003BC2E4Do@@YGXPAVParameter@@_N@Z @0x003BC2E4 34B: script helper that resolves Parameter* via ScriptEngine::getUnitNamed then forwards Object* plus flag to Rva002EFB20::helper. Evidence: push [esp+4] mov ecx,[0x009FE16C]=g_Va009FE16C call getUnitNamed test eax je then push [esp+8] push eax call helper pop pop ret 8; callees rowed; caller 0x003CCFA9; sibling Rva003BC306Do same stdcall Parameter* shape.
class Parameter
{
};
class Object
{
};
class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *);
};
extern ScriptEngine *g_Va009FE16C;
namespace Rva002EFB20
{
void __cdecl helper(void *, bool);
}
void __stdcall Rva003BC2E4Do(Parameter *param, bool flag)
{
	Object *obj = g_Va009FE16C->getUnitNamed(param);
	if (obj)
		Rva002EFB20::helper(obj, flag);
}
