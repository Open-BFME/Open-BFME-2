// cl: /O1 /DNDEBUG /MD
//
// Static-initializer strip: clear a file-scope bit mask through memset.
// Each is one translation unit's dynamic initializer of the same shape the
// four-byte copies in Rva007AD295ZeroInits.cpp recover, memset(&mask, 0,
// sizeof mask): a header-level BitFlags-style object whose default
// constructor resets its words. Unlike those copies these globals are read
// elsewhere in .text, so each keeps the name the ledger already uses for it
// (the kind-of mask KINDOFMASK_NONE) or an address-named extern sized from
// the memset length. The owning TUs are unrecovered, so each initializer
// keeps an honest address name. /O1 is retail's: its memset stays a call
// (under /O2 it is an intrinsic store); these rows lie in no voting flag
// region, so the line sets it. DISABLEDMASK_NONE/ALL (0x007B00F1,
// 0x007B0103) moved to BitFlags11Any.cpp, which defines them.

#include <string.h>

template <int N>
class BitFlags;

extern unsigned char g_00DFE794[16];
extern unsigned char g_00DFEA50[76];
// Owned here (retail BSS zeros): cleared by the inits below.
unsigned char g_00DFE794[16] = { 0 };
unsigned char g_00DFEA50[76] = { 0 };
extern BitFlags<116> KINDOFMASK_NONE;
extern unsigned char g_00E01EC0[4];
extern unsigned char g_00E01EC4[4];
extern unsigned char g_00E01EC8[4];
extern unsigned char g_00E01ECC[4];
extern unsigned char g_00E01ED0[4];
extern unsigned char g_00E0284C[28];
extern unsigned char g_00E02868[28];
extern unsigned char g_00E02884[28];
extern unsigned char g_00E028A0[28];
// Owned here (retail BSS zeros, 28B each): scoring/building masks cleared by
// the inits below. Defined (not merely declared) so the TU links.
unsigned char g_00E0284C[28] = { 0 };
unsigned char g_00E02868[28] = { 0 };
unsigned char g_00E02884[28] = { 0 };
unsigned char g_00E028A0[28] = { 0 };

struct Rva007ADC9CMaskInits
{
	static void rva007ADC9C();
	static void rva007ADE4C();
	static void rva007AE26A();
	static void rva007AEDE7();
	static void rva007AEDF9();
	static void rva007AEE0B();
	static void rva007AEE1D();
	static void rva007AEE2F();
	static void rva007AF2C2();
	static void rva007AF2D4();
	static void rva007AF2E6();
	static void rva007AF2F8();
};

// 0x007ADC9C (18B): memset(VA 0x00DFE794, 0, 16); read only by the rowed address getter 0x002856FD
void Rva007ADC9CMaskInits::rva007ADC9C()
{
	memset( &g_00DFE794, 0, 16 );
}

// 0x007ADE4C (18B): memset(VA 0x00DFEA50, 0, 76); read only by the rowed address getter 0x002856F7
void Rva007ADC9CMaskInits::rva007ADE4C()
{
	memset( &g_00DFEA50, 0, 76 );
}

// 0x007AE26A (18B): memset(VA 0x00DFEFA4, 0, 28); KINDOFMASK_NONE, the 28-byte empty kind-of mask
void Rva007ADC9CMaskInits::rva007AE26A()
{
	memset( &KINDOFMASK_NONE, 0, 28 );
}

// 0x007AEDE7 (18B): memset(VA 0x00E01EC0, 0, 4); read around 0x0036877F
void Rva007ADC9CMaskInits::rva007AEDE7()
{
	memset( &g_00E01EC0, 0, 4 );
}

// 0x007AEDF9 (18B): memset(VA 0x00E01EC4, 0, 4); read around 0x00368CD2
void Rva007ADC9CMaskInits::rva007AEDF9()
{
	memset( &g_00E01EC4, 0, 4 );
}

// 0x007AEE0B (18B): memset(VA 0x00E01EC8, 0, 4); read around 0x0036B805
void Rva007ADC9CMaskInits::rva007AEE0B()
{
	memset( &g_00E01EC8, 0, 4 );
}

// 0x007AEE1D (18B): memset(VA 0x00E01ECC, 0, 4); read around 0x0036B7F9
void Rva007ADC9CMaskInits::rva007AEE1D()
{
	memset( &g_00E01ECC, 0, 4 );
}

// 0x007AEE2F (18B): memset(VA 0x00E01ED0, 0, 4); read around 0x0036B825
void Rva007ADC9CMaskInits::rva007AEE2F()
{
	memset( &g_00E01ED0, 0, 4 );
}

// 0x007AF2C2 (18B): memset(VA 0x00E0284C, 0, 28); read around 0x0039C624
void Rva007ADC9CMaskInits::rva007AF2C2()
{
	memset( &g_00E0284C, 0, 28 );
}

// 0x007AF2D4 (18B): memset(VA 0x00E02868, 0, 28); read around 0x0039C636
void Rva007ADC9CMaskInits::rva007AF2D4()
{
	memset( &g_00E02868, 0, 28 );
}

// 0x007AF2E6 (18B): memset(VA 0x00E02884, 0, 28); read around 0x0039C630
void Rva007ADC9CMaskInits::rva007AF2E6()
{
	memset( &g_00E02884, 0, 28 );
}

// 0x007AF2F8 (18B): memset(VA 0x00E028A0, 0, 28); read around 0x0039CD78
void Rva007ADC9CMaskInits::rva007AF2F8()
{
	memset( &g_00E028A0, 0, 28 );
}
