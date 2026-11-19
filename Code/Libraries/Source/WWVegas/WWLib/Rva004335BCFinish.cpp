// ??0Rva001DA2D5@@QAE@ABV0@@Z retail 0x004335BC 422B
// cl: /Ireference/shims/bfme2_ascii /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Copy ctor: installs vtable 0x00BDA270, copies two AsciiString members and
// 16+11 int members and four /O1 STLport vectors, and zeroes the 4-byte base
// member at +0x4. Evidence: vtable + every callee rowed; caller 0x00433762 is
// the derived ctor (installs 0x00C3CB1C at +0x0 and AsciiString at +0xC8).
// The +0x4 zero goes through the inlined base copy ctor: a derived member init
// emits a 4-byte read-modify-write `and [esi+4],0` after the EH state, but
// retail's is a 7-byte pure write `mov [esi+4],0` before it. A volatile base
// member reproduces that pure-write, pre-EH-state placement exactly; it is a
// compiler-shape hypothesis for the encoding, not a recovered declaration.
#include <vector>
#include "ascii_string.h"
// Suppress this TU's non-retail copy of ??0?$_Vector_base@VBfmeStringTailRecord156@@V?$allocator@VBfmeStringTailRecord156@@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class BfmeStringTailRecord156;
namespace _STL { template <> _Vector_base<BfmeStringTailRecord156,allocator<BfmeStringTailRecord156> >::_Vector_base(unsigned int,allocator<BfmeStringTailRecord156> const &); }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@VBfmeStringTailRecord156@@@_STL@@QBEPAVBfmeStringTailRecord156@@IPBX:
// Suppress this TU's non-retail copy of ??0?$vector@VBfmeStringTailRecord156@@V?$allocator@VBfmeStringTailRecord156@@@_STL@@@_STL@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> vector<BfmeStringTailRecord156,allocator<BfmeStringTailRecord156> >::vector(vector<BfmeStringTailRecord156,allocator<BfmeStringTailRecord156> > const &); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAVBfmeStringTailRecord156@@@_STL@@YAXPAVBfmeStringTailRecord156@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> BfmeStringTailRecord156 * allocator<BfmeStringTailRecord156>::allocate(unsigned int,void const *) const; }
// Suppress this TU's non-retail copy of ??$_Destroy@PAVBfmeStringTailRecord156@@@_STL@@YAXPAVBfmeStringTailRecord156@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _Destroy<BfmeStringTailRecord156 *>(BfmeStringTailRecord156 *,BfmeStringTailRecord156 *); }
// Suppress this TU's non-retail copy of ??$_Construct@VBfmeStringTailRecord156@@V1@@_STL@@YAXPAVBfmeStringTailRecord156@@ABV1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void _Construct<BfmeStringTailRecord156,BfmeStringTailRecord156>(BfmeStringTailRecord156 *,BfmeStringTailRecord156 const &); }

#include "TreeKey00242F5E.h"
// The native eight-byte range copy calls the rowed placement-copy helper.
void Rva001D9B0FConstruct(void *, const void *);
namespace _STL {
template <> inline TreeKey00242F5E *__uninitialized_copy<const TreeKey00242F5E *, TreeKey00242F5E *>(
    const TreeKey00242F5E *first, const TreeKey00242F5E *last,
    TreeKey00242F5E *result, const __false_type &)
{
    TreeKey00242F5E *cur = result;
    for (; first != last; ++first, ++cur)
        Rva001D9B0FConstruct(cur, first);
    return cur;
}
}

// Its range destroy is rowed with the TreeKey vector growth path
// (TreeKey00242F5EVectorOverflow); this unit's copy is not retail's.
namespace _STL { template <> void _Destroy<TreeKey00242F5E *>(TreeKey00242F5E *, TreeKey00242F5E *); }
class BfmeStringTailRecord156 { public: char m_pad[156]; };
struct BfmeE8 { int m_a; int m_b; };

class __declspec(novtable) Rva001DA2D5Base
{
public:
	virtual ~Rva001DA2D5Base();
	Rva001DA2D5Base() {}
	Rva001DA2D5Base(const Rva001DA2D5Base &other) : m_unk04(0) { (void)other; }
	volatile int m_unk04;
};

class Rva001DA2D5 : public Rva001DA2D5Base
{
public:
	virtual ~Rva001DA2D5();
	virtual const AsciiString &getAudioName() const;
	Rva001DA2D5(const Rva001DA2D5 &other);
private:
	AsciiString m_str08;
	AsciiString m_str0C;
	int m_unk10; int m_unk14; int m_unk18; int m_unk1C;
	int m_unk20; int m_unk24; int m_unk28; int m_unk2C;
	int m_unk30; int m_unk34; int m_unk38; int m_unk3C;
	int m_unk40; int m_unk44; int m_unk48; int m_unk4C;
	_STL::vector<TreeKey00242F5E> m_vec50;
	int m_unk5C;
	_STL::vector<TreeKey00242F5E> m_vec60;
	int m_unk6C;
	_STL::vector<TreeKey00242F5E> m_vec70;
	int m_unk7C;
	_STL::vector<BfmeStringTailRecord156> m_vec80;
	int m_unk8C; int m_unk90; int m_unk94; int m_unk98;
	int m_unk9C; int m_unkA0; int m_unkA4; int m_unkA8;
	int m_unkAC; int m_unkB0; int m_unkB4;
	_STL::vector<BfmeE8> m_vecB8;
};

Rva001DA2D5::Rva001DA2D5(const Rva001DA2D5 &other)
	: Rva001DA2D5Base(other)
	, m_str08(other.m_str08)
	, m_str0C(other.m_str0C)
	, m_unk10(other.m_unk10) , m_unk14(other.m_unk14) , m_unk18(other.m_unk18) , m_unk1C(other.m_unk1C)
	, m_unk20(other.m_unk20) , m_unk24(other.m_unk24) , m_unk28(other.m_unk28) , m_unk2C(other.m_unk2C)
	, m_unk30(other.m_unk30) , m_unk34(other.m_unk34) , m_unk38(other.m_unk38) , m_unk3C(other.m_unk3C)
	, m_unk40(other.m_unk40) , m_unk44(other.m_unk44) , m_unk48(other.m_unk48) , m_unk4C(other.m_unk4C)
	, m_vec50(other.m_vec50)
	, m_unk5C(other.m_unk5C)
	, m_vec60(other.m_vec60)
	, m_unk6C(other.m_unk6C)
	, m_vec70(other.m_vec70)
	, m_unk7C(other.m_unk7C)
	, m_vec80(other.m_vec80)
	, m_unk8C(other.m_unk8C) , m_unk90(other.m_unk90) , m_unk94(other.m_unk94) , m_unk98(other.m_unk98)
	, m_unk9C(other.m_unk9C) , m_unkA0(other.m_unkA0) , m_unkA4(other.m_unkA4) , m_unkA8(other.m_unkA8)
	, m_unkAC(other.m_unkAC) , m_unkB0(other.m_unkB0) , m_unkB4(other.m_unkB4)
	, m_vecB8(other.m_vecB8)
{
}
