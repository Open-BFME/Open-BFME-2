// ?Rva003BAA46@@YGXPAVParameter@@_NM@Z
// partial score=0.9 date=2026-10-05
// cl: /O1
// ?Rva003BAA46@@YGXPAVParameter@@_NM@Z @0x003BAA46 144B: free stdcall Parameter* bool float driving TacticalView slots via Object+0x74 Drawable field.
// Evidence: ret 12 three args; push [esp+8] call ScriptEngine::getUnitNamed row je; push [esi+0x74] call [eax+0x184]; Thing::getDrawable row plus Rva0055A88BDwordField::get row; push eax call [edi+0x19c]; cmp byte [esp+0x10]; call [eax+0x188]; fld [esp+0x10] call [eax+0x190]; fldz push 0 call [eax+0x18c]; caller 0x003CAD35.
class Parameter;
class Drawable;
class Thing
{
public:
	Drawable *getDrawable() const;
};
class Rva0055A88BDwordField
{
public:
	int get() const;
};
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
	virtual void s52();
	virtual void s53();
	virtual void s54();
	virtual void s55();
	virtual void s56();
	virtual void s57();
	virtual void s58();
	virtual void s59();
	virtual void s60();
	virtual void s61();
	virtual void s62();
	virtual void s63();
	virtual void s64();
	virtual void s65();
	virtual void s66();
	virtual void s67();
	virtual void s68();
	virtual void s69();
	virtual void s70();
	virtual void s71();
	virtual void s72();
	virtual void s73();
	virtual void s74();
	virtual void s75();
	virtual void s76();
	virtual void s77();
	virtual void s78();
	virtual void s79();
	virtual void s80();
	virtual void s81();
	virtual void s82();
	virtual void s83();
	virtual void s84();
	virtual void s85();
	virtual void s86();
	virtual void s87();
	virtual void s88();
	virtual void s89();
	virtual void s90();
	virtual void s91();
	virtual void s92();
	virtual void s93();
	virtual void s94();
	virtual void s95();
	virtual void s96();
	virtual void s97(int v);
	virtual void s98();
	virtual void s99(int v, float f);
	virtual void s100(float f);
	virtual void s101();
	virtual void s102();
	virtual void s103(int v);
};
extern TacticalView *TheTacticalView;

// ?Rva003BAA46@@YGXPAVParameter@@_NM@Z present-unmatched
void __stdcall Rva003BAA46(Parameter *p, bool b, float f)
{
	Object *o = g_Va009FE16C->getUnitNamed(p);
	if (!o)
		return;
	TheTacticalView->s97(o->m_74);
	Drawable *d = ((Thing *)o)->getDrawable();
	int v = ((Rva0055A88BDwordField *)d)->get();
	TheTacticalView->s103(v);
	if (b)
		TheTacticalView->s98();
	TheTacticalView->s100(f);
	TheTacticalView->s99(0, 0.0f);
}
