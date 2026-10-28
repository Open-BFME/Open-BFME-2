// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport46
// BFME2 record copies with verified StringBase member operations.
// Layouts are read from the complete retail constructors and their STLport
// placement-copy callers. Application names and scalar meanings are unknown.
// String semantics follow BFME1 AsciiString/UnicodeString: the inline derived
// copies call StringBase<char>0x365F0 or StringBase<unsigned short>0x37050.
#include <memory>
#include "ascii_string.h"
#include "unicode_string.h"

// Existing WeaponTemplateSetHeadCopyCtor.cpp proves a nonthrowing 0x4C-byte
// memcpy constructor at 0x45455. Preserve the out-of-line helper call.
class WeaponTemplateSetHead {
    char m_bytes[0x4C];
public:
    __declspec(nothrow) WeaponTemplateSetHead(const WeaponTemplateSetHead &);
};

// Complete retail record copy at 0x00048139.
struct BfmeContainerRecord00048139 {
    AsciiString text0, text1; WeaponTemplateSetHead head; unsigned int word54, word58;
    BfmeContainerRecord00048139(const BfmeContainerRecord00048139 &other);
    BfmeContainerRecord00048139 &operator=(const BfmeContainerRecord00048139 &other);
};
BfmeContainerRecord00048139::BfmeContainerRecord00048139(const BfmeContainerRecord00048139 &other) : text0(other.text0), text1(other.text1), head(other.head), word54(other.word54), word58(other.word58) {}
BfmeContainerRecord00048139 &BfmeContainerRecord00048139::operator=(const BfmeContainerRecord00048139 &other) { text0 = other.text0; text1 = other.text1; head = other.head; word54 = other.word54; word58 = other.word58; return *this; }
template void _STL::_Construct<BfmeContainerRecord00048139,BfmeContainerRecord00048139>(BfmeContainerRecord00048139*,const BfmeContainerRecord00048139&);

// Complete retail record copy at 0x003A451B.
struct BfmeContainerRecord003A451B {
    AsciiString text; unsigned int word4; WeaponTemplateSetHead head0, head1;
    BfmeContainerRecord003A451B(const BfmeContainerRecord003A451B &other);
};
BfmeContainerRecord003A451B::BfmeContainerRecord003A451B(const BfmeContainerRecord003A451B &other) : text(other.text), word4(other.word4), head0(other.head0), head1(other.head1) {}
template void _STL::_Construct<BfmeContainerRecord003A451B,BfmeContainerRecord003A451B>(BfmeContainerRecord003A451B*,const BfmeContainerRecord003A451B&);

// Retail helper 0x0004543D copies exactly 28 bytes and cannot throw.
class BfmeFixedStorage0004543D {
    char m_bytes[28];
public:
    __declspec(nothrow) BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &);
};

// Complete memberwise constructor at 0x00462D62.
struct BfmeContainerRecord00462D62 {
    BfmeFixedStorage0004543D storage; AsciiString text;
    BfmeContainerRecord00462D62(const BfmeContainerRecord00462D62 &other);
};
BfmeContainerRecord00462D62::BfmeContainerRecord00462D62(const BfmeContainerRecord00462D62 &other) : storage(other.storage), text(other.text) {}
template void _STL::_Construct<BfmeContainerRecord00462D62,BfmeContainerRecord00462D62>(BfmeContainerRecord00462D62*,const BfmeContainerRecord00462D62&);

// Retail helper 0x002CF0F0 copies exactly 4 bytes and cannot throw.
class BfmeFixedStorage002CF0F0 {
    char m_bytes[4];
public:
    __declspec(nothrow) BfmeFixedStorage002CF0F0(const BfmeFixedStorage002CF0F0 &);
};

// Complete memberwise constructor at 0x002CF46E.
struct BfmeContainerRecord002CF46E {
    BfmeFixedStorage002CF0F0 storage; AsciiString text; unsigned int word8;
    BfmeContainerRecord002CF46E(const BfmeContainerRecord002CF46E &other);
};
BfmeContainerRecord002CF46E::BfmeContainerRecord002CF46E(const BfmeContainerRecord002CF46E &other) : storage(other.storage), text(other.text), word8(other.word8) {}
template void _STL::_Construct<BfmeContainerRecord002CF46E,BfmeContainerRecord002CF46E>(BfmeContainerRecord002CF46E*,const BfmeContainerRecord002CF46E&);

#include <vector>

// __node_alloc<1,0>:: otherwise emits a per-TU COMDAT that loses to another
// unit's copy in link order; this declaration-only specialization suppresses
// this unit's copy and binds the calls to the kept one (bodies unchanged).
namespace _STL {
template <> void __node_alloc<true, 0>::deallocate(void *, size_t);
}

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t);
template <> vector<AsciiString, allocator<AsciiString> >::vector(const vector<AsciiString, allocator<AsciiString> >&);
template <> _Vector_base<AsciiString, allocator<AsciiString> >::_Vector_base(size_t, const allocator<AsciiString>&);
template <> AsciiString *__uninitialized_copy(const AsciiString*, const AsciiString*, AsciiString*, const __false_type&);
}
struct BfmeAsciiScalarValue8 {
    AsciiString text; unsigned int value;
    BfmeAsciiScalarValue8(const BfmeAsciiScalarValue8 &other) : text(other.text), value(other.value) {}
    // Out of line: retail's copy is the 5-byte releaseBuffer tail jump (CastleBehavior's
    // unwind funclets reach it at 0x0048BA39). This unit declares ~AsciiString only, so its
    // own copy would tail-jump to ~AsciiString instead; use the units that inline it.
    ~BfmeAsciiScalarValue8();
};
namespace _STL {
template<> vector<BfmeAsciiScalarValue8>::vector(const vector<BfmeAsciiScalarValue8> &);
}

// Complete retail copy has three scalars before the owning eight-byte-element
// vector, then two established WeaponTemplateSetHead storage members.
struct BfmeContainerRecord000C0B85 {
    AsciiString text;
    unsigned int word04, word08, word0C;
    _STL::vector<BfmeAsciiScalarValue8> values10;
    WeaponTemplateSetHead head1C, head68;
    BfmeContainerRecord000C0B85(const BfmeContainerRecord000C0B85 &other);
};
BfmeContainerRecord000C0B85::BfmeContainerRecord000C0B85(const BfmeContainerRecord000C0B85 &other)
    : text(other.text), word04(other.word04), word08(other.word08), word0C(other.word0C),
      values10(other.values10), head1C(other.head1C), head68(other.head68) {}
template void _STL::_Construct<BfmeContainerRecord000C0B85,BfmeContainerRecord000C0B85>(BfmeContainerRecord000C0B85*,const BfmeContainerRecord000C0B85&);

// Shared string member copy at 0xA8C7C retains the pointed reference count.
// Its nontrivial destructor participates in constructor exception cleanup.
class Rva0036CA00Str {
    void *data;
public:
    __declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &);
    ~Rva0036CA00Str();
};
struct BfmeRecord001ECAF9{AsciiString a0,a4,a8,aC;Rva0036CA00Str s10;unsigned int w14;_STL::vector<AsciiString> v18;BfmeRecord001ECAF9(const BfmeRecord001ECAF9&other):a0(other.a0),a4(other.a4),a8(other.a8),aC(other.aC),s10(other.s10),w14(other.w14),v18(other.v18){}};template void _STL::_Construct<BfmeRecord001ECAF9,BfmeRecord001ECAF9>(BfmeRecord001ECAF9*,const BfmeRecord001ECAF9&);

struct BfmeRecord001DD3BC{AsciiString a0;Rva0036CA00Str a4;BfmeRecord001DD3BC(const BfmeRecord001DD3BC&other):a0(other.a0),a4(other.a4){}};template void _STL::_Construct<BfmeRecord001DD3BC,BfmeRecord001DD3BC>(BfmeRecord001DD3BC*,const BfmeRecord001DD3BC&);

// Raw range copy at 0x0004687B: assignment-loop over the byte span, count by
// stride, trailing scratch pair observed dead in the body (callers push a
// caller-local address plus zero; retail never reads them, frameless and no
// EH funclet, so no exception-path use either).
BfmeContainerRecord00048139 *copyRecordRange(const char *first, const char *last, BfmeContainerRecord00048139 *dest, void *scratchBuffer, int scratchSize)
{
	int count = (int)(last - first) / (int)sizeof(BfmeContainerRecord00048139);
	if (count > 0) {
		for (int left = count; left != 0; --left) {
			*dest = *(const BfmeContainerRecord00048139 *)first;
			first += sizeof(BfmeContainerRecord00048139);
			++dest;
		}
	}
	return dest;
}

// Checked range copy at 0x0004811C: own scratch byte plus zero size threaded
// into copyRecordRange; the caller-context slot is observed dead like the
// scratch pair below (single forwarder, no EH, straight-line).
BfmeContainerRecord00048139 *copyRecordRangeWithScratch(const char *first, const char *last, BfmeContainerRecord00048139 *dest, void *outerCtx)
{
	char scratch;
	return copyRecordRange(first, last, dest, &scratch, 0);
}
