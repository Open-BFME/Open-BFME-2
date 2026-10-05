// cl: /O1 /arch:SSE
// ?Rva003BACCA@@YGXPAVParameter@@@Z @0x003BACCA 75B: free stdcall Parameter* (unused) doing two TacticalView slot 0x5c calls with 2-float structs from g_00BBB9B0/g_00BBB9B4.
// Evidence: ret 4 unused arg; movss xmm0 [0xBBB9B0]/[0xBBB9B4]; mov ecx [0xDFEA3C TheTacticalView]; lea edx [ebp-8]; movss [ebp-8]/[ebp-4] xmm0; mov eax [ecx]; push edx; call [eax+0x5c] twice; caller 0x003CAD58 in ScriptActions dispatch.

extern float g_00BBB9B0;
extern float g_00BBB9B4;

struct Rva003BACCAPoint
{
	float x;
	float y;
};

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
	virtual void s023(const Rva003BACCAPoint &p);
};

extern TacticalView *TheTacticalView;

class Parameter;

void __stdcall Rva003BACCA(Parameter *p)
{
	Rva003BACCAPoint v;
	v.x = g_00BBB9B0;
	v.y = g_00BBB9B0;
	TheTacticalView->s023(v);
	v.x = g_00BBB9B4;
	v.y = g_00BBB9B4;
	TheTacticalView->s023(v);
}
