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
	virtual void s25(void *record, int milliseconds, int enabled,
		float a, float b, float c, int mode);
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
	virtual void s51(float value, int milliseconds, int mode, float a, float b);
	virtual void s52(unsigned int objectID, int a, int b, float c, float d, float e);
	virtual void s53(void *position, int milliseconds, float a, float b, int mode);
	virtual void s54();
	virtual void s55();
	virtual void s56();
	virtual void s57();
	virtual void s58();
	virtual void s59(float value, int milliseconds, float a, float b);
	virtual void s60(float value, int milliseconds, float a, float b);
	virtual void s61(float value, int milliseconds, float a, float b);
	virtual void s62(float angle, int milliseconds, float a, float b);
};

extern class View *TheTacticalView;
extern class TerrainLogic *TheTerrainLogic;

// A call-only view of the retail terrain interface: slot 34 returns the
// record whose embedded position starts at +0x0C. Its real method name
// and the complete record layout remain unresolved.
struct Rva003BB0C7Record
{
	unsigned char pad[0x60];
	int type;
};

class Rva003BB05FTerrain
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual void s12() = 0;
	virtual void s13() = 0;
	virtual void s14() = 0;
	virtual void s15() = 0;
	virtual void s16() = 0;
	virtual void s17() = 0;
	virtual void s18() = 0;
	virtual void s19() = 0;
	virtual void s20() = 0;
	virtual void s21() = 0;
	virtual void s22() = 0;
	virtual void s23() = 0;
	virtual void s24() = 0;
	virtual void s25() = 0;
	virtual void s26() = 0;
	virtual void s27() = 0;
	virtual void s28() = 0;
	virtual void s29() = 0;
	virtual void s30() = 0;
	virtual void s31() = 0;
	virtual void s32() = 0;
	virtual void s33() = 0;
	virtual char *s34(int index) = 0;
	virtual void s35() = 0;
	virtual void s36() = 0;
	virtual Rva003BB0C7Record *s37(int index) = 0;
};

class Parameter;
class Object;

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *);
};
extern ScriptEngine *TheScriptEngine;

// Only the ObjectID word read by the native caller is needed here.
struct Rva003BAFE8Object
{
	unsigned char pad[0x74];
	unsigned int objectID;
};

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

// Five sibling RET16 script wrappers. Each native body passes its first
// float unchanged, scales the other three by the retail 1000.0f literal,
// and truncates the second argument to an integer. Slots and the extra
// mode argument below are read separately from each bounded retail body.
// The original action and virtual-method names remain unresolved.
void __stdcall Rva003BAB7A(float a0, float a1, float a2, float a3)
{
	reinterpret_cast<TacticalView *>(TheTacticalView)->s59(
		a0, (int)(a1 * 1000.0f), a2 * 1000.0f, a3 * 1000.0f);
}

void __stdcall Rva003BABCB(float a0, float a1, float a2, float a3)
{
	reinterpret_cast<TacticalView *>(TheTacticalView)->s60(
		a0, (int)(a1 * 1000.0f), a2 * 1000.0f, a3 * 1000.0f);
}

void __stdcall Rva003BAC1C(float a0, float a1, float a2, float a3)
{
	reinterpret_cast<TacticalView *>(TheTacticalView)->s61(
		a0, (int)(a1 * 1000.0f), a2 * 1000.0f, a3 * 1000.0f);
}

void __stdcall Rva003BAECA(float a0, float a1, float a2, float a3)
{
	reinterpret_cast<TacticalView *>(TheTacticalView)->s51(
		a0, (int)(a1 * 1000.0f), 0, a2 * 1000.0f, a3 * 1000.0f);
}

void __stdcall Rva003BAF95(float a0, float a1, float a2, float a3)
{
	reinterpret_cast<TacticalView *>(TheTacticalView)->s51(
		a0, (int)(a1 * 1000.0f), 1, a2 * 1000.0f, a3 * 1000.0f);
}

// Retail 0x003BAFE8..0x003BB05F, RET24; script caller 0x003CAF53.
// The rowed Parameter lookup is 0x003588E7. A missing object returns;
// otherwise slot 52 receives Object+0x74, two truncated scaled floats,
// two scaled floats and the last input unchanged. Original names unknown.
void __stdcall Rva003BAFE8(Parameter *p, float a1, float a2,
	float a3, float a4, float a5)
{
	Object *object = TheScriptEngine->getUnitNamed(p);
	if (object)
	{
		reinterpret_cast<TacticalView *>(TheTacticalView)->s52(
			reinterpret_cast<Rva003BAFE8Object *>(object)->objectID,
			(int)(a1 * 1000.0f), (int)(a2 * 1000.0f),
			a3 * 1000.0f, a4 * 1000.0f, a5);
	}
}

// Retail 0x003BB05F..0x003BB0C7, RET20; dispatcher caller 0x003CAFAB.
// Slot 34 of the rowed TerrainLogic global supplies the record. View
// slot 53 receives record+12, scaled/truncated a2, two scaled floats and
// the final integer unchanged. The scale literal is retail 1000.0f.
void __stdcall Rva003BB05FSet(int a1, float a2, float a3, float a4, int a5)
{
	char *record = reinterpret_cast<Rva003BB05FTerrain *>(TheTerrainLogic)->s34(a1);
	if (record)
	{
		reinterpret_cast<TacticalView *>(TheTacticalView)->s53(
			record + 12, (int)(a2 * 1000.0f),
			a3 * 1000.0f, a4 * 1000.0f, a5);
	}
}

// Retail 0x003BB0C7..0x003BB141, RET28; dispatcher caller 0x003CADF5.
// Terrain slot 37 returns the record; only type 6 at +0x60 is accepted.
// View slot 25 takes that record, the scaled/truncated second argument,
// literal 1, three scaled floats and the final integer. Argument 3 is unused.
void __stdcall Rva003BB0C7Set(int a1, float a2, int a3,
	float a4, float a5, float a6, int a7)
{
	Rva003BB0C7Record *record =
		reinterpret_cast<Rva003BB05FTerrain *>(TheTerrainLogic)->s37(a1);
	if (record && record->type == 6)
	{
		reinterpret_cast<TacticalView *>(TheTacticalView)->s25(
			record, (int)(a2 * 1000.0f), 1,
			a4 * 1000.0f, a5 * 1000.0f, a6 * 1000.0f, a7);
	}
}
