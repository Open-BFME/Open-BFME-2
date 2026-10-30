// cl: /GX-
// Scattered global dword getters, each `mov eax,[mem]; ret` (6B), ported from
// Open-BFME-1 Code/GameEngine/Source/Common/GlobalDwordGetters.cpp.
// Unlike the adjacent runs (Rva000752BDGetters etc.), these stand alone with
// ret/pad on both sides; each lands as its own row in this shared TU
// (dedicated per run would be eight files for one shape).

// ?getPageSize@@YAHXZ @ 0x0001D1C0 (6B) over 0x00DA6CC8.

// STLport's protected ?_M_page_size@_Filebuf_base@_STL@@1IA (stlport_narrow_filebuf.cpp), read through a
// TU-scoped friend view (real decoration, no alias, no second datum).
int getPageSize(void);
namespace _STL
{
class _Filebuf_base
{
	friend int ::getPageSize(void);
protected:
	static unsigned int _M_page_size;	// size_t, as STLport declares it
};
}

int getPageSize(void)
{
	return (int)_STL::_Filebuf_base::_M_page_size;
}

// ?Rva00020E80Get@@YAHXZ @ 0x00020E80 (6B) over 0x00DA7188.

extern int g_Va00DA7188;
// g_Va00DA7188: matched references place it at VA 0xda7188 (retail .data initial value 12305416).
int g_Va00DA7188 = 12305416;

int Rva00020E80Get(void)
{
	return g_Va00DA7188;
}

// ?Rva00020E90Get@@YAHXZ @ 0x00020E90 (6B) over 0x00DA718C.

extern int g_Va00DA718C;
// g_Va00DA718C: matched references place it at VA 0xda718c (retail .data initial value 12305424).
int g_Va00DA718C = 12305424;

int Rva00020E90Get(void)
{
	return g_Va00DA718C;
}

// ?getBlockParseList@@YAHXZ @ 0x0002BACF (6B) over 0x00DDF578.

struct BlockParse; extern BlockParse *theBlockParseList;
// g_Va00DDF578: matched references place it at VA 0xddf578 (zero-filled .bss).
struct BlockParse; extern BlockParse *theBlockParseList;

int getBlockParseList(void)
{
	return (*(int *)&theBlockParseList);
}

// ?getLODTextureReduction@@YAHXZ @ 0x0006E16F (6B) over 0x00DB5FA0.

extern int LODTextureReduction;
// LODTextureReduction: matched references place it at VA 0xdb5fa0 (retail .data initial value 2).
int LODTextureReduction = 2;

int getLODTextureReduction(void)
{
	return LODTextureReduction;
}

// ?Rva00117C10Get@@YAXPAH@Z @ 0x00117C10 (13B) and ?Rva00117C20Get@@YAXPAH@Z
// @ 0x00117C20 (13B): copy the dwords at 0x00DB5FA4 / 0x00DB5FA8, the two
// words after LODTextureReduction (retail .data 0x0010581B and 0x0011401B),
// to the caller's slot. They sit in the int3-padded ww3d.cpp run before
// Rva00117C30Get; no direct caller reaches them. Address-derived names.

extern int g_Va00DB5FA4;
// g_Va00DB5FA4: matched references place it at VA 0xdb5fa4 (retail .data initial value 1071131).
int g_Va00DB5FA4 = 0x0010581B;
extern int g_Va00DB5FA8;
// g_Va00DB5FA8: matched references place it at VA 0xdb5fa8 (retail .data initial value 1130523).
int g_Va00DB5FA8 = 0x0011401B;

void Rva00117C10Get(int *out)
{
	*out = g_Va00DB5FA4;
}

void Rva00117C20Get(int *out)
{
	*out = g_Va00DB5FA8;
}

// ?Rva000A8F36Get@@YAHXZ @ 0x000A8F36 (6B) over 0x00DB5FC8.

extern int g_Va00DB5FC8;
// g_Va00DB5FC8: matched references place it at VA 0xdb5fc8 (retail .data initial value 10568192).
int g_Va00DB5FC8 = 10568192;

int Rva000A8F36Get(void)
{
	return g_Va00DB5FC8;
}

// ?Rva000EDF40Get@@YAHXZ @ 0x000EDF40 (6B) over 0x00DEDA24.

// dx8wrapper.cpp's protected ?FogColor@DX8Wrapper@@1KA through a friend view.
class DX8Wrapper
{
	friend int Rva000EDF40Get(void);
	friend void Rva00149570Set(int value);
protected:
	static unsigned long FogColor;
};

int Rva000EDF40Get(void)
{
	return (int)DX8Wrapper::FogColor;
}

// ?Rva00149570Set@@YAXH@Z @ 0x00149570 (10B): the matching dword setter over
// the same 0x00DEDA24 (mov eax,[esp+4]; mov [mem],eax; ret); CC padding on
// both sides, no direct callers. Address-derived name.
void Rva00149570Set(int value)
{
	DX8Wrapper::FogColor = value;
}

// ?Rva00171660Get@@YAHXZ @ 0x00171660 (6B) over 0x00DB5F90.

// ww3d.cpp defines this datum (initial NPATCHES_GAP_FILLING_ENABLED, 1) as the
// private ?NPatchesGapFillingMode@WW3D@@0W4NPatchesGapFillingModeEnum@1@A.
class WW3D
{
public:
	static int Get_Texture_Reduction(void);	// 0x00117C00
private:
	friend int Rva00171660Get(void);
	enum NPatchesGapFillingModeEnum {};
	static NPatchesGapFillingModeEnum NPatchesGapFillingMode;
};

int Rva00171660Get(void)
{
	return WW3D::NPatchesGapFillingMode;
}

// ?Rva000B29C3Get@@YAHXZ @ 0x000B29C3 (6B) over 0x00DE1B40.

extern int g_bfmeDisplayAnimationSyncClock;
// Neutral semantic name, not an assertion of the original symbol spelling.
// Native scripted-model constructor, sync wrapper and processAnimations plus
// WB W3DDisplay::GetCurSyncTime assert identify this DWORD animation/display clock.
// Sole existing provider is renamed; no second address owner is introduced.
int g_bfmeDisplayAnimationSyncClock;

int Rva000B29C3Get(void)
{
	return g_bfmeDisplayAnimationSyncClock;
}

// ?Rva000B29C9Set@@YAXH@Z @ 0x000B29C9 (10B): global dword setter over
// 0x00DB3BDC (mov eax,[esp+4]; mov [mem],eax; ret 4). Same honest
// address-derived naming as the getters above.

extern int g_Va00DB3BDC;
// g_Va00DB3BDC: matched references place it at VA 0xdb3bdc (retail .data initial value -1).
int g_Va00DB3BDC = -1;

void Rva000B29C9Set(int value)
{
	g_Va00DB3BDC = value;
}

// ?Rva006CD220Get@@YAHXZ @ 0x006CD220 (6B) over 0x00E17724.

extern int g_Va00E17724;

int Rva006CD220Get(void)
{
	return g_Va00E17724;
}

// ?Rva0058AEB6Get@@YAHXZ @ 0x0058AEB6 (6B) over 0x00E063A4.

extern int g_Va00E063A4;
// g_Va00E063A4: matched references place it at VA 0xe063a4 (zero-filled .bss).
int g_Va00E063A4;

int Rva0058AEB6Get(void)
{
	return g_Va00E063A4;
}

// ?Rva00658200Get@@YAHXZ @ 0x00658200 (6B) over 0x00E09FA4.

class T_007ea120;
extern T_007ea120 *g_Va0130A588;

int Rva00658200Get(void)
{
	return reinterpret_cast<int>(g_Va0130A588);
}

// ?Rva0043C969Get@@YAHXZ @ 0x0043C969 (6B) over 0x00E03314.

struct GlobalA03314;
extern GlobalA03314 *g_Va00A03314;

int Rva0043C969Get(void)
{
	return reinterpret_cast<int>(g_Va00A03314);
}

// ?Rva00062AC4Get@@YAHXZ @ 0x00062AC4 (6B) over 0x00DFEC54.

// Waypoint's constructors/destructor maintain this list at VA 0x00DFEC54.
// Its single zero-initialized definition lives with those bodies.
class Waypoint;
extern Waypoint *g_waypointListHead;

int Rva00062AC4Get(void)
{
	return reinterpret_cast<int>(g_waypointListHead);
}

// ?Rva00452D86Get@@YAHXZ @ 0x00452D86 (6B) over 0x00DC908C.

extern int g_Va00DC908C;
// g_Va00DC908C: matched references place it at VA 0xdc908c (retail .data initial value 16777214).
int g_Va00DC908C = 16777214;

int Rva00452D86Get(void)
{
	return g_Va00DC908C;
}

// ?Rva0051E2B7Get@@YAHXZ @ 0x0051E2B7 (6B) over 0x00E048DC.

extern int g_Va00E048DC;
// g_Va00E048DC: matched references place it at VA 0xe048dc (zero-filled .bss).
int g_Va00E048DC;

int Rva0051E2B7Get(void)
{
	return g_Va00E048DC;
}

// ?Get_Texture_Reduction@WW3D@@SAHXZ @ 0x00117C00 (6B) over 0x00DEC40C.

extern int g_Va00DEC40C;
// g_Va00DEC40C: matched references place it at VA 0xdec40c (zero-filled .bss).
int g_Va00DEC40C;

int WW3D::Get_Texture_Reduction(void)
{
	return g_Va00DEC40C;
}

// ?Rva0011F1B0Get@@YAHXZ @ 0x0011F1B0 (6B) over 0x00DED5C0.

extern int g_Va00DED5C0;
// g_Va00DED5C0: matched references place it at VA 0xded5c0 (zero-filled .bss).
int g_Va00DED5C0;

int Rva0011F1B0Get(void)
{
	return g_Va00DED5C0;
}

// ?Rva00129590Get@@YAHXZ @ 0x00129590 (6B) over 0x00DEE8E4.

extern int g_last4;

int Rva00129590Get(void)
{
	return g_last4;
}

// ?Rva00129660Get@@YAHXZ @ 0x00129660 (6B) over 0x00DEE894.

extern int g_stat10;

int Rva00129660Get(void)
{
	return g_stat10;
}

// ?Rva00129680Get@@YAHXZ @ 0x00129680 (6B) over 0x00DEE8A0.

extern int g_last9;

int Rva00129680Get(void)
{
	return g_last9;
}
