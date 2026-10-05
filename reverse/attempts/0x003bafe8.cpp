// ?Rva003BAFE8@@YGXPAVParameter@@MMMMM@Z
// partial score=0.88 date=2026-10-05
// cl: /O1 /arch:SSE
// ?Rva003BAFE8@@YGXPAVParameter@@MMMMM@Z @0x003BAFE8 119B: free stdcall Parameter* plus five floats scaling four and forwarding Object+0x74 plus two ints plus three floats to TacticalView slot 0xd0.
// Evidence: ret 24 six args; push [ebp+8] call ScriptEngine::getUnitNamed row; test eax je; movss xmm0 [0xBBE358]; fld [ebp+0x1c] fstp [esp+8]; three movss+mulss scales plus two cvttss2si ints; push [eax+0x74]; call [edx+0xd0]; caller 0x003CAF53.
extern float g_00BBE358;

class Parameter;
class Object
{
public:
	char m_pad[0x74];
	int m_74;
};
class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *);
};
extern ScriptEngine *g_Va009FE16C;

class TacticalView
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
	virtual void s39();
	virtual void s40();
	virtual void s41();
	virtual void s42();
	virtual void s43();
	virtual void s44();
	virtual void s45();
	virtual void s46();
	virtual void s47();
	virtual void s48();
	virtual void s49();
	virtual void s50();
	virtual void s51();
	virtual void s52(int f, int i1, int i2, float f1, float f2, float f3);
};
extern TacticalView *TheTacticalView;

// ?Rva003BAFE8@@YGXPAVParameter@@MMMMM@Z present-unmatched
void __stdcall Rva003BAFE8(Parameter *p, float a1, float a2, float a3, float a4, float a5)
{
	Object *o = g_Va009FE16C->getUnitNamed(p);
	if (!o)
		return;
	float t5 = a5;
	float t4 = a4 * g_00BBE358;
	TacticalView *tv = TheTacticalView;
	float t3 = a3 * g_00BBE358;
	int t2 = (int)(a2 * g_00BBE358);
	int t1 = (int)(a1 * g_00BBE358);
	tv->s52(o->m_74, t1, t2, t3, t4, t5);
}
