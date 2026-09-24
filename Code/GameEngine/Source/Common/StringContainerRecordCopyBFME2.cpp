// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// BFME2 record copies with verified StringBase member operations.
// Layouts are read from the complete retail constructors and their STLport
// placement-copy callers. Application names and scalar meanings are unknown.
// String semantics follow BFME1 AsciiString/UnicodeString: the inline derived
// copies call StringBase<char>0x365F0 or StringBase<unsigned short>0x37050.
#include <memory>
template <typename T> class StringBase {
    friend class AsciiString;
    friend class UnicodeString;
    StringBase(const StringBase &);
    __forceinline ~StringBase() { releaseBuffer(); }
    void releaseBuffer();
    void *m_data;
};
class AsciiString : private StringBase<char> {
public:
    __forceinline AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    __forceinline ~AsciiString() {}
    AsciiString &operator=(const AsciiString &other);
};
class UnicodeString : private StringBase<unsigned short> {
public:
    __forceinline UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
    __forceinline ~UnicodeString() {}
};

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
    BfmeContainerRecord00048139(const BfmeContainerRecord00048139 &o);
    BfmeContainerRecord00048139 &operator=(const BfmeContainerRecord00048139 &o);
};
BfmeContainerRecord00048139::BfmeContainerRecord00048139(const BfmeContainerRecord00048139 &o) : text0(o.text0), text1(o.text1), head(o.head), word54(o.word54), word58(o.word58) {}
BfmeContainerRecord00048139 &BfmeContainerRecord00048139::operator=(const BfmeContainerRecord00048139 &o) { text0 = o.text0; text1 = o.text1; head = o.head; word54 = o.word54; word58 = o.word58; return *this; }
template void _STL::_Construct<BfmeContainerRecord00048139,BfmeContainerRecord00048139>(BfmeContainerRecord00048139*,const BfmeContainerRecord00048139&);

// Complete retail record copy at 0x003A451B.
struct BfmeContainerRecord003A451B {
    AsciiString text; unsigned int word4; WeaponTemplateSetHead head0, head1;
    BfmeContainerRecord003A451B(const BfmeContainerRecord003A451B &o);
};
BfmeContainerRecord003A451B::BfmeContainerRecord003A451B(const BfmeContainerRecord003A451B &o) : text(o.text), word4(o.word4), head0(o.head0), head1(o.head1) {}
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
    BfmeContainerRecord00462D62(const BfmeContainerRecord00462D62 &o);
};
BfmeContainerRecord00462D62::BfmeContainerRecord00462D62(const BfmeContainerRecord00462D62 &o) : storage(o.storage), text(o.text) {}
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
    BfmeContainerRecord002CF46E(const BfmeContainerRecord002CF46E &o);
};
BfmeContainerRecord002CF46E::BfmeContainerRecord002CF46E(const BfmeContainerRecord002CF46E &o) : storage(o.storage), text(o.text), word8(o.word8) {}
template void _STL::_Construct<BfmeContainerRecord002CF46E,BfmeContainerRecord002CF46E>(BfmeContainerRecord002CF46E*,const BfmeContainerRecord002CF46E&);

#include <vector>
struct BfmeAsciiScalarValue8 {
    AsciiString text; unsigned int value;
    BfmeAsciiScalarValue8(const BfmeAsciiScalarValue8 &o) : text(o.text), value(o.value) {}
};
// Complete retail copy has three scalars before the owning eight-byte-element
// vector, then two established WeaponTemplateSetHead storage members.
struct BfmeContainerRecord000C0B85 {
    AsciiString text;
    unsigned int word04, word08, word0C;
    _STL::vector<BfmeAsciiScalarValue8> values10;
    WeaponTemplateSetHead head1C, head68;
    BfmeContainerRecord000C0B85(const BfmeContainerRecord000C0B85 &o);
};
BfmeContainerRecord000C0B85::BfmeContainerRecord000C0B85(const BfmeContainerRecord000C0B85 &o)
    : text(o.text), word04(o.word04), word08(o.word08), word0C(o.word0C),
      values10(o.values10), head1C(o.head1C), head68(o.head68) {}
template void _STL::_Construct<BfmeContainerRecord000C0B85,BfmeContainerRecord000C0B85>(BfmeContainerRecord000C0B85*,const BfmeContainerRecord000C0B85&);

// Shared string member copy at 0xA8C7C retains the pointed reference count.
// Its nontrivial destructor participates in constructor exception cleanup.
class Rva0036CA00Str {
    void *data;
public:
    __declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &);
    ~Rva0036CA00Str();
};
struct BfmeRecord001ECAF9{AsciiString a0,a4,a8,aC;Rva0036CA00Str s10;unsigned int w14;_STL::vector<AsciiString> v18;BfmeRecord001ECAF9(const BfmeRecord001ECAF9&o):a0(o.a0),a4(o.a4),a8(o.a8),aC(o.aC),s10(o.s10),w14(o.w14),v18(o.v18){}};template void _STL::_Construct<BfmeRecord001ECAF9,BfmeRecord001ECAF9>(BfmeRecord001ECAF9*,const BfmeRecord001ECAF9&);

struct BfmeRecord001DD3BC{AsciiString a0;Rva0036CA00Str a4;BfmeRecord001DD3BC(const BfmeRecord001DD3BC&o):a0(o.a0),a4(o.a4){}};template void _STL::_Construct<BfmeRecord001DD3BC,BfmeRecord001DD3BC>(BfmeRecord001DD3BC*,const BfmeRecord001DD3BC&);
