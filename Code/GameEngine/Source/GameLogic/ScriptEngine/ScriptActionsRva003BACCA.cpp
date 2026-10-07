// flags: region default (reverse/retail_inventory/flag_regions.csv)
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
	virtual void s62(float angle, int milliseconds, float a, float b);
};

extern class View *TheTacticalView;

class Parameter;

void __stdcall Rva003BACCA(Parameter *p)
{
	Rva003BACCAPoint v;
	v.x = g_00BBB9B0;
	v.y = g_00BBB9B0;
	reinterpret_cast<TacticalView *>(TheTacticalView)->s023(v);
	v.x = g_00BBB9B4;
	v.y = g_00BBB9B4;
	reinterpret_cast<TacticalView *>(TheTacticalView)->s023(v);
}

// Retail 0x003BAC6D..0x003BACCA, RET16; called by script dispatch at
// 0x003CACEB. The global is the rowed View*; slot 62 accepts a radians
// value, one truncated integer and two floats. Retail constants at
// 0x00BBE358 and 0x00BBB8D0 are 1000.0f and float bits 0x3C8EFA35.
// The original action and virtual-method names remain unresolved.
void __stdcall Rva003BAC6D(float a0, float a1, float a2, float a3)
{
	reinterpret_cast<TacticalView *>(TheTacticalView)->s62(
		a0 * 0.01745329238474369f, (int)(a1 * 1000.0f),
		a2 * 1000.0f, a3 * 1000.0f);
}
