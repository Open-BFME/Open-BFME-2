// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BACCA@@YGXPAVParameter@@@Z @0x003BACCA 75B: free stdcall Parameter* (unused) doing two TacticalView slot 0x5c calls with 2-float structs from g_00BBB9B0/g_00BBB9B4.
// Evidence: ret 4 unused arg; movss xmm0 [0xBBB9B0]/[0xBBB9B4]; mov ecx [0xDFEA3C TheTacticalView]; lea edx [ebp-8]; movss [ebp-8]/[ebp-4] xmm0; mov eax [ecx]; push edx; call [eax+0x5c] twice; caller 0x003CAD58 in ScriptActions dispatch.

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class AsciiString;
struct CameraMarker;

// Retail .rdata floats at VA 0x00BBB9B0/0x00BBB9B4 (+/-0.0001f, exact bytes
// 0x38D1B717/0xB8D1B717): defined here, the sole reader TU.
float g_00BBB9B0 = 0.0001f;
float g_00BBB9B4 = -0.0001f;

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
	virtual void s21(const Coord3D *p);
	virtual void s22();
	virtual void s023(const Rva003BACCAPoint &p);
	virtual void s24(const Coord3D *position, CameraMarker *marker,
		int milliseconds, int enabled, float a, float b);
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
	virtual void s39(const Coord3D *p);
	virtual void s40();
	virtual void s41();
	virtual void s42();
	virtual void s43();
	virtual void s44();
	virtual bool s45(int mode);
	virtual void s46(const Coord3D *p, int mode);
	virtual bool s47(int filter);
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
    virtual void s97(unsigned int objectID);
    virtual void s98();
    virtual void s99(int mode, float value);
    virtual void s100(float value);
    virtual void s101();
    virtual void s102();
    virtual void s103(int drawableID);

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

template <class Arg>
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
	virtual char *s34(Arg argument) = 0;
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

// Existing descriptive owner of the rowed 0x0025F385 lookup. Its original
// EA class name is unresolved; the emitted ABI uses struct CameraMarker.
class CameraMarkerList
{
public:
	CameraMarker *find(const AsciiString &name) const;
};

struct Rva003BAAE4TerrainPosition
{
	unsigned char pad[12];
	Coord3D position;
};

struct Rva003BAAE4MarkerPosition
{
	unsigned char pad[8];
	Coord3D position;
};

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
	char *record = reinterpret_cast<Rva003BB05FTerrain<int> *>(TheTerrainLogic)->s34(a1);
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
		reinterpret_cast<Rva003BB05FTerrain<int> *>(TheTerrainLogic)->s37(a1);
	if (record && record->type == 6)
	{
		reinterpret_cast<TacticalView *>(TheTacticalView)->s25(
			record, (int)(a2 * 1000.0f), 1,
			a4 * 1000.0f, a5 * 1000.0f, a6 * 1000.0f, a7);
	}
}

// Retail 0x003BAAE4..0x003BAB7A, RET20. Caller 0x003CAB7A passes the
// Parameter's string at +0x10. Terrain slot 34 and the rowed marker lookup
// resolve that same name. A marker's +8 position overrides terrain's +12
// position; View slot 24 takes the copy, marker and scaled arguments.
// Argument a2 is unused. Original action and virtual-method names unknown.
void __stdcall Rva003BAAE4(const AsciiString &name,
	float a1, float a2, float a3, float a4)
{
	char *terrain =
		reinterpret_cast<Rva003BB05FTerrain<const AsciiString &> *>(TheTerrainLogic)->s34(name);
	CameraMarker *marker = reinterpret_cast<CameraMarkerList *>(TheTacticalView)->find(name);
	if (!terrain && !marker)
		return;
	Coord3D position;
	if (terrain)
		position = reinterpret_cast<Rva003BAAE4TerrainPosition *>(terrain)->position;
	if (marker)
		position = reinterpret_cast<Rva003BAAE4MarkerPosition *>(marker)->position;
	reinterpret_cast<TacticalView *>(TheTacticalView)->s24(
		&position, marker, (int)(a1 * 1000.0f), 1,
		a3 * 1000.0f, a4 * 1000.0f);
}

// Zero Hour ScriptActions::doModCameraMoveToSelection supplies the selected
// drawable centroid algorithm. Target 0x003BAE04/198B and dispatcher 0x003CAFFF
// independently establish the free ABI, selection byte +0x43C, next +0x104,
// first-drawable slot 17 and final-move slot 39. Original BFME2 name unresolved.
// BFMERopeDrawable does not override getPosition: the 0x002763E6 body is
// owned by Drawable (rowed under that name from BFMERopeDrawableGetPosition),
// so this view inherits it instead of declaring a same-named method.
class Drawable
{
public:
    const Coord3D *getPosition() const;
};
class BFMERopeDrawable : public Drawable
{
};
struct Rva003BAE04Drawable
{
    unsigned char pad[0x104];
    BFMERopeDrawable *next;
    unsigned char pad108[0x43C - 0x108];
    bool selected;
};
class Rva003BAE04Client
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
    virtual BFMERopeDrawable *firstDrawable();
};
extern class GameClient *TheGameClient;

void Rva003BAE04()
{
    int count = 0;
    Coord3D destination;
    destination.x = destination.y = destination.z = 0.0f;
    for (BFMERopeDrawable *d = reinterpret_cast<Rva003BAE04Client *>(TheGameClient)->firstDrawable();
        d; d = reinterpret_cast<Rva003BAE04Drawable *>(d)->next)
    {
        if (reinterpret_cast<Rva003BAE04Drawable *>(d)->selected)
        {
            const Coord3D *position = d->getPosition();
            Coord3D pos;
            pos.x = position->x;
            pos.y = position->y;
            pos.z = position->z;
            destination.x += pos.x;
            destination.y += pos.y;
            destination.z += pos.z;
            ++count;
        }
    }
    if (count)
    {
        float scale = 1.0f / count;
        destination.z *= scale;
        destination.x *= scale;
        destination.y *= scale;
        reinterpret_cast<TacticalView *>(TheTacticalView)->s39(&destination);
    }
}

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
// ZH doCameraTetherNamed supplies the lock/snap/tether workflow. Native
// 0x003BAA46 adds Drawable-ID slot103 before snap and uses slots97/98/100/99;
// dispatcher0x003CAD35 and RET12 prove Parameter*, bool, float free ABI.
void __stdcall Rva003BAA46(Parameter *p, bool snap, float play)
{
    Object *object = TheScriptEngine->getUnitNamed(p);
    if (object)
    {
        reinterpret_cast<TacticalView *>(TheTacticalView)->s97(
            reinterpret_cast<Rva003BAFE8Object *>(object)->objectID);
        reinterpret_cast<TacticalView *>(TheTacticalView)->s103(
            reinterpret_cast<Rva0055A88BDwordField *>(
                reinterpret_cast<Thing *>(object)->getDrawable())->get());
        if (snap)
            reinterpret_cast<TacticalView *>(TheTacticalView)->s98();
        reinterpret_cast<TacticalView *>(TheTacticalView)->s100(play);
        reinterpret_cast<TacticalView *>(TheTacticalView)->s99(0, 0.0f);
    }
}

// ZH doCameraMotionBlurJump is the semantic/control-flow guide. Native
// 0x003BB7FE..0x003BB898/RET8 separately proves slot34 lookup and slots
// 47/45/46/21 with filter2, saturate8 or alpha7, and fallback filter0.
void __stdcall Rva003BB7FESet(int waypoint, bool saturate)
{
    char *way = reinterpret_cast<Rva003BB05FTerrain<int> *>(TheTerrainLogic)->s34(waypoint);
    if (!way)
        return;
    bool passed = false;
    Coord3D pos;
    pos.x = reinterpret_cast<Rva003BAAE4TerrainPosition *>(way)->position.x;
    pos.y = reinterpret_cast<Rva003BAAE4TerrainPosition *>(way)->position.y;
    pos.z = reinterpret_cast<Rva003BAAE4TerrainPosition *>(way)->position.z;
    if (reinterpret_cast<TacticalView *>(TheTacticalView)->s47(2))
    {
        passed = true;
        if (saturate)
        {
            if (!reinterpret_cast<TacticalView *>(TheTacticalView)->s45(8))
            {
                reinterpret_cast<TacticalView *>(TheTacticalView)->s47(0);
                passed = false;
            }
        }
        else
        {
            if (!reinterpret_cast<TacticalView *>(TheTacticalView)->s45(7))
            {
                reinterpret_cast<TacticalView *>(TheTacticalView)->s47(0);
                passed = false;
            }
        }
        if (passed)
            reinterpret_cast<TacticalView *>(TheTacticalView)->s46(&pos, 0);
    }
    if (!passed)
        reinterpret_cast<TacticalView *>(TheTacticalView)->s21(&pos);
}
