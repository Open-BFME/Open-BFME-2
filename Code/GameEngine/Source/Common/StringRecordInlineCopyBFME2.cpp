// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// BFME2 record copies with verified StringBase member operations.
// Layouts are read from the complete retail constructors and their STLport
// placement-copy callers. Application names and scalar meanings are unknown.
// String semantics follow BFME1 AsciiString/UnicodeString: the inline derived
// copies call StringBase<char>0x365F0 or StringBase<unsigned short>0x37050.
#include <memory>
#include <utility>
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
};
class UnicodeString : private StringBase<unsigned short> {
public:
    __forceinline UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
    __forceinline ~UnicodeString() {}
};

// Complete retail record copy at0x00054F57.
struct BfmeStringRecord00054F57 {
    AsciiString ansi; UnicodeString wide;
    BfmeStringRecord00054F57(const BfmeStringRecord00054F57 &o);
};
BfmeStringRecord00054F57::BfmeStringRecord00054F57(const BfmeStringRecord00054F57 &o) : ansi(o.ansi), wide(o.wide) {}
template void _STL::_Construct<BfmeStringRecord00054F57,BfmeStringRecord00054F57>(BfmeStringRecord00054F57*,const BfmeStringRecord00054F57&);

// Complete retail record copy at0x00204A30.
struct BfmeStringRecord00204A30 {
    unsigned int word0; AsciiString text0; unsigned int word1; AsciiString text1; unsigned int word2;
    BfmeStringRecord00204A30(const BfmeStringRecord00204A30 &o);
};
BfmeStringRecord00204A30::BfmeStringRecord00204A30(const BfmeStringRecord00204A30 &o) : word0(o.word0), text0(o.text0), word1(o.word1), text1(o.text1), word2(o.word2) {}
template void _STL::_Construct<BfmeStringRecord00204A30,BfmeStringRecord00204A30>(BfmeStringRecord00204A30*,const BfmeStringRecord00204A30&);

// Complete retail record copy at0x002199C8.
struct BfmeStringRecord002199C8 {
    AsciiString text0, text1, text2; unsigned int word;
    BfmeStringRecord002199C8(const BfmeStringRecord002199C8 &o);
};
BfmeStringRecord002199C8::BfmeStringRecord002199C8(const BfmeStringRecord002199C8 &o) : text0(o.text0), text1(o.text1), text2(o.text2), word(o.word) {}
template void _STL::_Construct<BfmeStringRecord002199C8,BfmeStringRecord002199C8>(BfmeStringRecord002199C8*,const BfmeStringRecord002199C8&);

// Complete retail record copy at0x00219A68.
struct BfmeStringRecord00219A68 {
    unsigned int word0; AsciiString text0, text1; unsigned int word1, word2;
    BfmeStringRecord00219A68(const BfmeStringRecord00219A68 &o);
    BfmeStringRecord00219A68(unsigned int w0, const AsciiString &t0, const AsciiString &t1, unsigned int w1, unsigned int w2);
};
BfmeStringRecord00219A68::BfmeStringRecord00219A68(const BfmeStringRecord00219A68 &o) : word0(o.word0), text0(o.text0), text1(o.text1), word1(o.word1), word2(o.word2) {}
// Retail 0x00219A1B is the 5-arg ctor of the same record: word0 + two AsciiString copies via 0x365F0 + word1/word2.
// Same EH scope as the copy (mov eax 0xb6e568); sole placed caller 0x0021ECB2 pushes (0, "None", "None", -1, 2).
BfmeStringRecord00219A68::BfmeStringRecord00219A68(unsigned int w0, const AsciiString &t0, const AsciiString &t1, unsigned int w1, unsigned int w2) : word0(w0), text0(t0), text1(t1), word1(w1), word2(w2) {}
template void _STL::_Construct<BfmeStringRecord00219A68,BfmeStringRecord00219A68>(BfmeStringRecord00219A68*,const BfmeStringRecord00219A68&);

// Complete retail record copy at0x0022074B.
struct BfmeStringRecord0022074B {
    AsciiString text0, text1; unsigned int word;
    BfmeStringRecord0022074B(const BfmeStringRecord0022074B &o);
};
BfmeStringRecord0022074B::BfmeStringRecord0022074B(const BfmeStringRecord0022074B &o) : text0(o.text0), text1(o.text1), word(o.word) {}
template void _STL::_Construct<BfmeStringRecord0022074B,BfmeStringRecord0022074B>(BfmeStringRecord0022074B*,const BfmeStringRecord0022074B&);

// Complete retail record copy at0x005BC576.
struct BfmeStringRecord005BC576 {
    AsciiString text0, text1, text2, text3, text4, text5; unsigned char flag;
    BfmeStringRecord005BC576(const BfmeStringRecord005BC576 &o);
};
BfmeStringRecord005BC576::BfmeStringRecord005BC576(const BfmeStringRecord005BC576 &o) : text0(o.text0), text1(o.text1), text2(o.text2), text3(o.text3), text4(o.text4), text5(o.text5), flag(o.flag) {}
template void _STL::_Construct<BfmeStringRecord005BC576,BfmeStringRecord005BC576>(BfmeStringRecord005BC576*,const BfmeStringRecord005BC576&);

// Complete retail record copy at0x005D511F.
struct BfmeStringRecord005D511F {
    UnicodeString text0; unsigned int word0, word1; UnicodeString text1; unsigned int word2;
    BfmeStringRecord005D511F(const BfmeStringRecord005D511F &o);
};
BfmeStringRecord005D511F::BfmeStringRecord005D511F(const BfmeStringRecord005D511F &o) : text0(o.text0), word0(o.word0), word1(o.word1), text1(o.text1), word2(o.word2) {}
template void _STL::_Construct<BfmeStringRecord005D511F,BfmeStringRecord005D511F>(BfmeStringRecord005D511F*,const BfmeStringRecord005D511F&);

// Retail 0x00111ACF copies strings at +0 and +0x18, a word at +4,
// then the four-float subobject at +8 through its observed x87 loop.
struct BfmeStringRecord00111ACF {
    AsciiString first; unsigned int word4; struct FloatStorage { float values[4]; } middle; AsciiString second;
    BfmeStringRecord00111ACF(const BfmeStringRecord00111ACF &o) : first(o.first), word4(o.word4), second(o.second) { for (int i=0;i<4;++i) middle.values[i]=o.middle.values[i]; }
};
template void _STL::_Construct<BfmeStringRecord00111ACF, BfmeStringRecord00111ACF>(BfmeStringRecord00111ACF *, const BfmeStringRecord00111ACF &);

// Complete retail record copy at0x005EC43C.
struct BfmeStringRecord005EC43C {
    UnicodeString text; unsigned int word0, word1, word2, word3, word4;
    BfmeStringRecord005EC43C(const BfmeStringRecord005EC43C &o);
};
BfmeStringRecord005EC43C::BfmeStringRecord005EC43C(const BfmeStringRecord005EC43C &o) : text(o.text), word0(o.word0), word1(o.word1), word2(o.word2), word3(o.word3), word4(o.word4) {}
template void _STL::_Construct<BfmeStringRecord005EC43C,BfmeStringRecord005EC43C>(BfmeStringRecord005EC43C*,const BfmeStringRecord005EC43C&);

// Complete retail record copy at0x005F93E3.
struct BfmeStringRecord005F93E3 {
    unsigned int word0, word1; UnicodeString text;
    BfmeStringRecord005F93E3(const BfmeStringRecord005F93E3 &o);
};
BfmeStringRecord005F93E3::BfmeStringRecord005F93E3(const BfmeStringRecord005F93E3 &o) : word0(o.word0), word1(o.word1), text(o.text) {}
template void _STL::_Construct<BfmeStringRecord005F93E3,BfmeStringRecord005F93E3>(BfmeStringRecord005F93E3*,const BfmeStringRecord005F93E3&);

// Complete retail record copy at0x005ED5F3.
struct BfmeStringRecord005ED5F3 {
    UnicodeString text; unsigned int word0, word1, word2, word3;
    BfmeStringRecord005ED5F3(const BfmeStringRecord005ED5F3 &o);
};
BfmeStringRecord005ED5F3::BfmeStringRecord005ED5F3(const BfmeStringRecord005ED5F3 &o) : text(o.text), word0(o.word0), word1(o.word1), word2(o.word2), word3(o.word3) {}
template void _STL::_Construct<BfmeStringRecord005ED5F3,BfmeStringRecord005ED5F3>(BfmeStringRecord005ED5F3*,const BfmeStringRecord005ED5F3&);

// Upstream LanguageFilter.cpp identifies the former opaque record at0x387D03
// as pair<const UnicodeString,bool>. Reuse that claim and keep only this
// independently verified placement-copy caller at0x387E7C.
typedef _STL::pair<const UnicodeString,bool> UnicodeFlagPair;
template void _STL::_Construct<UnicodeFlagPair,UnicodeFlagPair>(UnicodeFlagPair*,const UnicodeFlagPair&);

// Complete retail record copy at0x002B4DC1.
struct BfmeStringRecord002B4DC1 {
    UnicodeString text; unsigned int word0, word1;
    BfmeStringRecord002B4DC1(const BfmeStringRecord002B4DC1 &o);
};
BfmeStringRecord002B4DC1::BfmeStringRecord002B4DC1(const BfmeStringRecord002B4DC1 &o) : text(o.text), word0(o.word0), word1(o.word1) {}
template void _STL::_Construct<BfmeStringRecord002B4DC1,BfmeStringRecord002B4DC1>(BfmeStringRecord002B4DC1*,const BfmeStringRecord002B4DC1&);

// Complete retail record copy at0x005DDD40.
struct BfmeStringRecord005DDD40 {
    UnicodeString text; unsigned int word;
    BfmeStringRecord005DDD40(const BfmeStringRecord005DDD40 &o);
};
BfmeStringRecord005DDD40::BfmeStringRecord005DDD40(const BfmeStringRecord005DDD40 &o) : text(o.text), word(o.word) {}
template void _STL::_Construct<BfmeStringRecord005DDD40,BfmeStringRecord005DDD40>(BfmeStringRecord005DDD40*,const BfmeStringRecord005DDD40&);

// Complete retail record copy at0x00415F34.
struct BfmeStringRecord00415F34 {
    unsigned int word0, word1; AsciiString text0; unsigned int word2; AsciiString text1; UnicodeString text2;
    BfmeStringRecord00415F34(const BfmeStringRecord00415F34 &o);
};
BfmeStringRecord00415F34::BfmeStringRecord00415F34(const BfmeStringRecord00415F34 &o) : word0(o.word0), word1(o.word1), text0(o.text0), word2(o.word2), text1(o.text1), text2(o.text2) {}
template void _STL::_Construct<BfmeStringRecord00415F34,BfmeStringRecord00415F34>(BfmeStringRecord00415F34*,const BfmeStringRecord00415F34&);

// Complete retail record copy at0x00448113.
struct BfmeStringRecord00448113 {
    UnicodeString text0, text1;
    BfmeStringRecord00448113(const BfmeStringRecord00448113 &o);
};
BfmeStringRecord00448113::BfmeStringRecord00448113(const BfmeStringRecord00448113 &o) : text0(o.text0), text1(o.text1) {}
template void _STL::_Construct<BfmeStringRecord00448113,BfmeStringRecord00448113>(BfmeStringRecord00448113*,const BfmeStringRecord00448113&);

struct BfmeStringRecord002049D6 {
    _STL::pair<AsciiString,AsciiString> pair;
    AsciiString third;
    BfmeStringRecord002049D6(const BfmeStringRecord002049D6 &o);
};
BfmeStringRecord002049D6::BfmeStringRecord002049D6(const BfmeStringRecord002049D6 &o) : pair(o.pair), third(o.third) {}
template void _STL::_Construct<BfmeStringRecord002049D6,BfmeStringRecord002049D6>(BfmeStringRecord002049D6*,const BfmeStringRecord002049D6&);


struct Rva00468520Obj { int m_00; int m_04; };
class Rva00468520 {
    Rva00468520Obj *m_00; int m_04;
public:
    __declspec(nothrow) Rva00468520 *set(const Rva00468520 *src);
    ~Rva00468520();
    __declspec(nothrow) __forceinline Rva00468520(const Rva00468520 &other) { set(&other); }
};
struct BfmeStringRecord00222E08 {
    AsciiString text;
    Rva00468520 ref;
    BfmeStringRecord00222E08(const BfmeStringRecord00222E08 &o);
};
BfmeStringRecord00222E08::BfmeStringRecord00222E08(const BfmeStringRecord00222E08 &o) : text(o.text), ref(o.ref) {}
template void _STL::_Construct<BfmeStringRecord00222E08,BfmeStringRecord00222E08>(BfmeStringRecord00222E08*,const BfmeStringRecord00222E08&);


class Rva0036CA00Str { void *m_item; public: __declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &); ~Rva0036CA00Str(); };
class Rva002390CB {
    void *m_00; Rva0036CA00Str m_04;
public:
    __declspec(nothrow) Rva002390CB(const Rva002390CB &);
    ~Rva002390CB();
};
struct BfmeStringRecord002CF550 {
    AsciiString text;
    Rva002390CB ref;
    BfmeStringRecord002CF550(const BfmeStringRecord002CF550 &o);
};
BfmeStringRecord002CF550::BfmeStringRecord002CF550(const BfmeStringRecord002CF550 &o) : text(o.text), ref(o.ref) {}
template void _STL::_Construct<BfmeStringRecord002CF550,BfmeStringRecord002CF550>(BfmeStringRecord002CF550*,const BfmeStringRecord002CF550&);
