// cl: /Ireference/shims/bfme2_ascii /arch:SSE /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1BfmePod248@@QAE@XZ, retail 0x000C6D44 214B.
// Provisional ordinary thiscall dtor spelling (QAE): direct callers + EH shape
// support ECX=this with no stack args; virtualness unproven (virtual bodies
// can be direct-called; vtables may point to deleting wrappers). No UAE flip.
// REL32 pin from rowed aux 0xC872C; scalar-deleting wrapper 0xC79AD calls here.
// BfmePod248 is a size-derived opaque identifier (248-byte stride via aux
// 0xC872C advancing 0xF8), not an original name; uncertainty preserved.
// Boundary [0xC6D44,0xC6E1A): final C3 at 0xC6E19, FS-restore epilogue from
// 0xC6E0B; next Ghidra body 0xC6E1A abuts. Exact bytes are proof, pins
// candidates only.
//
// Independently established anchors (read from game.dat + primary ledger):
// - List +0x74 is NOT AsciiString. Native ctor 0xC6A4D leas ecx=[esi+0x74] and
//   calls 0xB92D2; primary row 14601 proves 0xB92D2 is
//   ??0?$_List_base@UBfmePod32@@... (List_base<Pod32> 41B, node 0x28 = 8B links
//   + 32B payload). Native copy 0xC6B17 leas ecx=[esi+0x74] and calls 0xBDA52;
//   primary row 38377 proves 0xBDA52 is list<Pod32> copy 88B. A 4B AsciiString
//   node would be 12B, not 40B. Retail dtor calls 0x239D49 (E8 at 0xC6D61) and
//   0x2FECBC (E8 at 0xC6DE3); those rowed AsciiString clear/dtor bodies are a
//   compatible opaque-proxy ABI (node-front cleanup + header free), not proof
//   of consumer payload 4. Modelled below as explicit opaque 4B proxy with
//   address-derived ABI pins; original payload 32B per B92D2/BDA52.
// - Array +0xAC is NOT basic_string. Native copy 0xC6B17 builds six 12B slots
//   (ehvec ctor 0x629512 size 0xC count 6 ctor-cb 0x656646 dtor-cb 0x47FAB3)
//   then loops 6 times: ecx=current slot (ebx from esi+0xAC step 0xC),
//   arg=corresponding source slot (edi+ebx), calls 0xBC3C4, dec 6. Primary row
//   16894 proves 0xBC3C4 is vector<BfmeFixedObject60>::operator= 209B (divides
//   ranges/capacity by 0x3C). Each 12B slot is therefore a three-pointer
//   vector-like object, original element name unknown. Retail dtor ehvec
//   0x629110 (size 0xC count 6 callback VA 0x47FAB3) is modelled as six opaque
//   12B three-pointer slots with address-derived dtor pin to 0x7FAB3; 0x7FAB3
//   row 666 is a generic free-first-pointer ICF body (compatible bytes, not
//   string-type proof).
// - Erase/dtor double-calls share this-pointers (edi=+0x78 via 0xC1CAE then
//   0xC1BE1; ebx=+0x90 via 0xC059B then 0xC0417) with compatible 12B/0x18
//   vector views sharing Destroy 0xBDD08/0x331FF1 (strides 24/12). Kept as
//   native-compatible ABI views; original payload names unknown.
//
// Layout is BFME2-observed from retail offsets, never donor-ported. Sizes:
// AsciiString 4B (shim; copy 0x365F0 at +0x00/+0x6C in C6B17, release 0x36410
// at +0x00/+0x6C in C6D44), vector 12B (3 ptrs), opaque list proxy 4B
// (STLport _list.h:193 single-header-ptr base, so +0x74 ends at +0x78 with NO
// overlap), tree Rva000B646B 8B, opaque slots 6x12B. Total 0xF8, preserving
// Pod248-family rows 14655/14658/14660/14664/14669/15058 +
// 43540/48465/48475/48481/54187.
//
// Teardown: explicit body clears (proxy clear 0x239D49 via opaque pin, vector
// erases 0xC1CAE/0xC059B via reinterpreted ABI views, flag zero) run under EH
// state 8; implicit reverse-declaration teardown states 7..0 (array ehvec
// 0x629110, tree 0xBB65C, vectors 0xC0417/0xC1C20/0xC1BE1, proxy dtor 0x2FECBC
// via opaque pin, strings 0x36410, vector 0xC6878) then -1 for final string.
#include <stdlib.h>
namespace _STL { void __cdecl free(void *block) throw(...); }
#define free _STL::free
#include "ascii_string.h"
#include <vector>
#undef free

struct BfmeVectorRecord000BDF17;
struct Rva00B9AC2 { char _pad[0x18]; };
struct Rva000C1CAEElement;
struct Rva000B435F;
struct Rva002DFC30;
struct Rva000B9AAA;

struct Rva000C1BE1 { void *m_p[3]; ~Rva000C1BE1(); };
struct Rva000C0417 { void *m_p[3]; ~Rva000C0417(); };

// Opaque 4B list proxy at +0x74. STLport _List_base single-header-ptr ABI.
// clear() pinned to 0x239D49 (retail E8 at 0xC6D61); dtor pinned to 0x2FECBC
// (retail E8 at 0xC6DE3). Payload 32B per B92D2/BDA52; NOT AsciiString.
struct Rva000C6D44ListProxy74
{
	void *m_header;
	void clear();
	~Rva000C6D44ListProxy74();
};

// Opaque 12B three-pointer slot at +0xAC. Per-slot copy via 0xBC3C4
// (vector<FixedObject60>::operator=) proves vector-like shape; original
// element name unknown. Dtor pinned to 0x7FAB3 (retail ehvec callback VA
// 0x47FAB3); generic free-first-pointer ICF bytes, NOT basic_string identity.
struct Rva000C6D44Slot12
{
	void *m_p[3];
	~Rva000C6D44Slot12();
};

struct RvaTreeFamilyHolder { void *m_ptr; };
class Rva000B646B
{
public:
	RvaTreeFamilyHolder m_header;
	int m_flag;
	void rva000B92FB();
	~Rva000B646B();
};

namespace _STL
{
template <> class vector<BfmeVectorRecord000BDF17, allocator<BfmeVectorRecord000BDF17> >
{
public:
	~vector();
private:
	BfmeVectorRecord000BDF17 *m_begin;
	BfmeVectorRecord000BDF17 *m_finish;
	BfmeVectorRecord000BDF17 *m_end;
};

template <> class vector<Rva00B9AC2, allocator<Rva00B9AC2> >
{
public:
	~vector();
private:
	Rva00B9AC2 *m_begin;
	Rva00B9AC2 *m_finish;
	Rva00B9AC2 *m_end;
};

template <> class vector<Rva000C1CAEElement, allocator<Rva000C1CAEElement> >
{
public:
	typedef Rva000C1CAEElement *iterator;
	__forceinline iterator begin() { return m_start; }
	__forceinline iterator end() { return m_finish; }
	iterator erase(iterator first, iterator last);
private:
	iterator m_start;
	iterator m_finish;
	iterator m_end;
};

template <> class vector<Rva000B435F, allocator<Rva000B435F> >
{
public:
	typedef Rva000B435F *iterator;
	__forceinline iterator begin() { return m_start; }
	__forceinline iterator end() { return m_finish; }
	iterator erase(iterator first, iterator last);
private:
	iterator m_start;
	iterator m_finish;
	iterator m_end;
};
}

class BfmePod248
{
public:
	~BfmePod248();
private:
	AsciiString m_s00; // +0x00 -> 0x36410 (copy 0x365F0 in C6B17)
	char m_pad04[0x4C]; // +0x04..+0x50
	_STL::vector<BfmeVectorRecord000BDF17, _STL::allocator<BfmeVectorRecord000BDF17> > m_v50; // +0x50 -> 0xC6878
	char m_pad5C[0xC]; // +0x5C..+0x68
	int m_f68; // +0x68 (and [esi+0x68],0)
	AsciiString m_s6C; // +0x6C -> 0x36410 (copy 0x365F0 in C6B17)
	int m_pad70; // +0x70
	Rva000C6D44ListProxy74 m_list74; // +0x74 (4B opaque) -> clear 0x239D49 + dtor 0x2FECBC via pins
	Rva000C1BE1 m_v78; // +0x78 (12B) -> dtor 0xC1BE1; erase view via reinterpret ABI cast
	_STL::vector<Rva00B9AC2, _STL::allocator<Rva00B9AC2> > m_v84; // +0x84 -> 0xC1C20
	Rva000C0417 m_v90; // +0x90 (12B) -> dtor 0xC0417; erase view via reinterpret ABI cast
	int m_pad9C; // +0x9C
	Rva000B646B m_tA0; // +0xA0 (8B) -> 0xBB65C
	int m_padA8; // +0xA8
	Rva000C6D44Slot12 m_arrAC[6]; // +0xAC 6x12B opaque -> ehvec 0x629110 dtor 0x7FAB3 via pin
	int m_padF4; // +0xF4
};
typedef char VerifyPod248Size[(sizeof(BfmePod248) == 0xF8) ? 1 : -1];

// ??1BfmePod248@@QAE@XZ @0x000C6D44 214B. Explicit pre-destroy range clears
// share this-pointers with their later dtors (edi=+0x78, ebx=+0x90), so they
// are written out; everything else is implicit reverse member teardown.
BfmePod248::~BfmePod248()
{
	m_list74.clear();
	_STL::vector<Rva000C1CAEElement, _STL::allocator<Rva000C1CAEElement> > &ev78 =
		reinterpret_cast<_STL::vector<Rva000C1CAEElement, _STL::allocator<Rva000C1CAEElement> > &>(m_v78);
	ev78.erase(ev78.begin(), ev78.end());
	_STL::vector<Rva000B435F, _STL::allocator<Rva000B435F> > &ev90 =
		reinterpret_cast<_STL::vector<Rva000B435F, _STL::allocator<Rva000B435F> > &>(m_v90);
	ev90.erase(ev90.begin(), ev90.end());
	m_f68 = 0;
}
