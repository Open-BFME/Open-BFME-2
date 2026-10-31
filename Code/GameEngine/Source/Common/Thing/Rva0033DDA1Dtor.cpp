// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHs /MD
// ??1ThingTemplate@@UAE@XZ @0x0033DDA1 713B.
// Virtual scalar destructor of the large ThingTemplate-side record holder:
// vptr store, 20 member-dtor calls in reverse order, three ehvec array
// teardowns, inline free-holder tails, then the rowed base dtor 0x001E3624.
// All member dtors are declared-only TU-local spellings so each call site
// resolves to its rowed body or symbols.csv pin; only the PtrHolder tails
// inline (free 0x00030830). Member order and sizes mirror the banked 0.99
// layout (+0x364 is the Rva0033BD50 holder, not a CD02Vec).

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "ascii_string.h"

// The member containers are STLport instantiations whose out-of-line
// destructors are rowed (vector<Rva002DFC30> 0x0033D4AB,
// vector<BfmeStringRecord002CF4C6> 0x0033CD02, vector<ProductionPrerequisite>
// 0x0033CA81, the BfmeStringRecord002CF550 set tree 0x0025742C and the
// no-case AsciiString map tree 0x0033D00A). Declaration-only views of those
// templates keep each call a direct call to its rowed body.
namespace _STL
{
template <class T> class allocator;
template <class T> struct less;
template <class T> struct _Identity;
template <class P> struct _Select1st;
template <class A, class B> struct pair;
template <class T, class A = allocator<T> > class vector
{
public:
	~vector();
private:
	void *m_v[3];
};
template <class K, class V, class KoV, class C, class A> class _Rb_tree
{
public:
	~_Rb_tree();
private:
	void *m_t[3];
};
}
class Rva002DFC30;
class ProductionPrerequisite;
struct BfmeStringRecord002CF4C6;
struct BfmeStringRecord002CF550;
// The four module-info members (+0x2e4..+0x308): ModuleInfo holds the
// record vector. Its destructor is the 5-byte thunk 0x0033CF2F
// (ThingTemplateCleanupForwards.cpp) that the unwind funclets jump to; the
// normal path expands it into the vector destructor call 0x0033CD02.
struct ModuleInfo { _STL::vector<BfmeStringRecord002CF4C6> records; };
struct NoCaseTreeValue4;
struct BfmeStringNoCaseLess;
typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NoCasePair4;

struct PtrHolder
{
	void *m_p;
	~PtrHolder()
	{
		if (m_p != 0)
			free(m_p);
	}
};

class Rva0033B84ETok
{
public:
	~Rva0033B84ETok();

private:
	void *m_data;
};

class Rva0033B352Record
{
public:
	~Rva0033B352Record();

private:
	char m_wide_narrow[8];
};

// The +0x124 field is the existing 56-record array holder: its cleanup
// calls the verified 16-byte destructor at 0x00254B72. Use that owner and
// its 8-byte record callback (0x004C9F38), rather than a private nested name.
class OpaqueRefCounted;
class Rva002390CB
{
public:
	~Rva002390CB();
private:
	void *unknown00;
	OpaqueRefCounted *owner04;
};

class Rva00254B72
{
	Rva002390CB records[56];
};

class AssetList
{
public:
	~AssetList();

private:
	char m[0x14];
};

class GeometryInfo
{
public:
	virtual ~GeometryInfo();
}; // 4B: vptr only; the +0xa4..0xfc span is dtor-silent POD

struct Rva0033C3F3
{
	void *m_a;
	void *m_b;
	~Rva0033C3F3();
};

class RvaVecAscii
{
public:
	~RvaVecAscii();

private:
	void *m_v[3];
};

struct Rva0033BD50
{
	void *m_begin;
	void *m_end;
	~Rva0033BD50();
};

struct Rva0033BD88
{
	void *m_begin;
	void *m_end;
	~Rva0033BD88();
};

struct Rva0033BDC0
{
	void *m_begin;
	void *m_end;
	~Rva0033BDC0();
};

class Rva0026E1A6
{
public:
	~Rva0026E1A6();

private:
	char m_pad[12];
};

class Overridable
{
public:
	virtual ~Overridable();

private:
	char m_pad[0x14 - 4];
};

// Empty visible wrapper destructors preserve direct member calls in the parent,
// while its unwind funclets use the native enclosing-finder destructor thunks.
struct ArmorSetFinderView { Rva0033BD50 tree; unsigned int comparator; };
struct WeaponSetFinderView { Rva0033BD88 tree; unsigned int comparator; };
struct TemplateNameMapView { Rva0033BDC0 tree; unsigned int comparator; };

class ThingTemplate : public Overridable
{
public:
	virtual ~ThingTemplate();

private:
	Rva0033B84ETok m_s14; // +0x14
	char m_pad18[8];
	Rva0033B84ETok m_s20; // +0x20
	char m_pad24[8];
	Rva0033B352Record m_r2c; // +0x2c
	Rva0033B352Record m_r34; // +0x34
	Rva0033B352Record m_r3c; // +0x3c
	Rva0033B352Record m_r44; // +0x44
	Rva0033B352Record m_r4c; // +0x4c
	Rva0033B352Record m_r54; // +0x54
	Rva0033B84ETok m_s5c; // +0x5c
	Rva0033B84ETok m_s60; // +0x60
	Rva0033B84ETok m_s64; // +0x64
	Rva0033B84ETok m_s68; // +0x68
	Rva0033B84ETok m_s6c; // +0x6c
	Rva0033B84ETok m_s70; // +0x70
	Rva0033B84ETok m_s74; // +0x74
	Rva0033B84ETok m_s78; // +0x78
	AsciiString m_e7c[5]; // +0x7c
	Rva0033B84ETok m_s90; // +0x90
	Rva0033B84ETok m_s94; // +0x94
	Rva0033B84ETok m_s98; // +0x98
	Rva0033B84ETok m_s9c; // +0x9c
	GeometryInfo m_gA0; // +0xa0
	char m_padA4[0xfc - 0xa4];
	Rva0033C3F3 m_cFC; // +0xfc
	char m_pad104[0x124 - 0x104];
	Rva00254B72 m_e124; // +0x124, 56 records of 8 bytes
	ModuleInfo m_v2e4; // +0x2e4
	ModuleInfo m_v2f0; // +0x2f0
	ModuleInfo m_v2fc; // +0x2fc
	ModuleInfo m_v308; // +0x308
	char m_pad314[0x324 - 0x314];
	_STL::vector<ProductionPrerequisite> m_v324; // +0x324
	RvaVecAscii m_a330; // +0x330
	RvaVecAscii m_a33c; // +0x33c
	RvaVecAscii m_a348; // +0x348
	char m_pad354[0x358 - 0x354];
	PtrHolder m_h358; // +0x358
	char m_pad35C[0x364 - 0x35c];
	ArmorSetFinderView m_d364; // +0x364
	_STL::vector<Rva002DFC30> m_v370; // +0x370
	WeaponSetFinderView m_d37c; // +0x37c
	_STL::_Rb_tree<BfmeStringRecord002CF550, BfmeStringRecord002CF550, _STL::_Identity<BfmeStringRecord002CF550>, _STL::less<BfmeStringRecord002CF550>, _STL::allocator<BfmeStringRecord002CF550> > m_t388; // +0x388
	_STL::_Rb_tree<AsciiString, NoCasePair4, _STL::_Select1st<NoCasePair4>, BfmeStringNoCaseLess, _STL::allocator<NoCasePair4> > m_t394; // +0x394
	TemplateNameMapView m_d3a0; // +0x3a0
	Rva0026E1A6 m_m3ac; // +0x3ac
	PtrHolder m_h3b8; // +0x3b8
	char m_pad3BC[0x3c4 - 0x3bc];
	AssetList m_e3c4[2]; // +0x3c4
	PtrHolder m_h3ec; // +0x3ec
	char m_pad3F0[0x3f8 - 0x3f0];
	PtrHolder m_h3f8; // +0x3f8
};

ThingTemplate::~ThingTemplate()
{
}
