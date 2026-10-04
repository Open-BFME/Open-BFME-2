// cl: /O1 /arch:SSE
// ?Rva003BC903Do@@YGXPAVParameter@@H@Z @0x003BC903 57B: script getUnitNamed then ExperienceTracker at Object+0x264 add with int as float. Evidence: push [esp+4] mov ecx,[0x00DFE16C]=g_Va009FE16C call getUnitNamed test eax je then mov ecx,[eax+0x264] test je then cvtsi2ss xmm0,[esp+8] push 0 push 1 push 1 push 1 push ecx movss [esp],xmm0 call rva0039B315 ret 8; callee pin ExperienceTracker float bool bool bool int; caller 0x003CDBFC; sibling Rva003BC96FDo same +0x264 Parameter int shape.
class Parameter
{
};
class ExperienceTracker
{
public:
	void rva0039B315(float amount, bool a, bool b, bool c, int d);
};
class Object
{
public:
	char m_pad[0x264];
	ExperienceTracker *m_264;
};
class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
};
extern ScriptEngine *g_Va009FE16C;
void __stdcall Rva003BC903Do(Parameter *param, int val)
{
	Object *obj = g_Va009FE16C->getUnitNamed(param);
	if (obj == 0)
		return;
	ExperienceTracker *tracker = obj->m_264;
	if (tracker == 0)
		return;
	tracker->rva0039B315((float)val, true, true, true, 0);
}
