// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// BFME2 record copies with verified StringBase member operations.
// Layouts are read from the complete retail constructors and their STLport
// placement-copy callers. Application names and scalar meanings are unknown.
// String semantics follow BFME1 AsciiString/UnicodeString: the inline derived
// copies call StringBase<char>0x365F0 or StringBase<unsigned short>0x37050.
#include <memory>
#include <utility>
#include "ascii_string.h"
#include "unicode_string.h"
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
    BfmeStringRecord00204A30 &operator=(const BfmeStringRecord00204A30 &o);
};
BfmeStringRecord00204A30::BfmeStringRecord00204A30(const BfmeStringRecord00204A30 &o) : word0(o.word0), text0(o.text0), word1(o.word1), text1(o.text1), word2(o.word2) {}
template void _STL::_Construct<BfmeStringRecord00204A30,BfmeStringRecord00204A30>(BfmeStringRecord00204A30*,const BfmeStringRecord00204A30&);

// ??4BfmeStringRecord00204A30@@QAEAAU0@ABU0@@Z retail 0x00203DDA 55B.
// Same layout as the 0x00204A30 copy ctor above (word AsciiString word AsciiString word = 0x14).
// Callees are the AsciiString copy-assign fold at 0x000366F0 (existing pins).
// Sole placed caller 0x00204170 is the 0x14-stride array copy loop.
// ?Rva00203DDA assignment via memberwise copy in declaration order.
BfmeStringRecord00204A30 &BfmeStringRecord00204A30::operator=(const BfmeStringRecord00204A30 &o)
{
    word0 = o.word0;
    text0 = o.text0;
    word1 = o.word1;
    text1 = o.text1;
    word2 = o.word2;
    return *this;
}

// Complete retail record copy at0x002199C8.
struct BfmeStringRecord002199C8 {
    AsciiString text0, text1, text2; unsigned int word;
    BfmeStringRecord002199C8(const BfmeStringRecord002199C8 &o);
    BfmeStringRecord002199C8(unsigned int w, const AsciiString &a, const AsciiString &b, const AsciiString &c);
};
BfmeStringRecord002199C8::BfmeStringRecord002199C8(const BfmeStringRecord002199C8 &o) : text0(o.text0), text1(o.text1), text2(o.text2), word(o.word) {}
// ??0BfmeStringRecord002199C8@@QAE@IABVAsciiString@@00@Z @0x0021997A 78B
// 4-arg ctor of the same 0x10 record: word + three AsciiString copies via 0x365F0.
// Same EH scope as the copy; callers 0x0021E9D8 0x0021EAD3 forward (w,a,b,c) and
// destroy the temp via rowed dtor 0x0021A0C2; init permuted to retail push order.
// ?rva0021997A ctor via declaration-order emission text0(b) text1(c) text2(a) word(w).
BfmeStringRecord002199C8::BfmeStringRecord002199C8(unsigned int w, const AsciiString &a, const AsciiString &b, const AsciiString &c) : text0(b), text1(c), text2(a), word(w) {}
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

// Native5BC576 copies six AsciiString fields and the resume byte at24.
// WB MainMenuUtils and ZH DownloadManager.h establish QueuedDownload identity.
// Rename the existing owner rather than adding another name at its address.
class QueuedDownload { public: AsciiString server,userName,password,file,localFile,regKey; bool tryResume; QueuedDownload(const QueuedDownload &); ~QueuedDownload(); };
QueuedDownload::QueuedDownload(const QueuedDownload &o) : server(o.server), userName(o.userName), password(o.password), file(o.file), localFile(o.localFile), regKey(o.regKey), tryResume(o.tryResume) {}
template void _STL::_Construct<QueuedDownload,QueuedDownload>(QueuedDownload*,const QueuedDownload&);

// Complete retail record copy at0x005D511F.
struct BfmeStringRecord005D511F {
    UnicodeString text0; unsigned int word0, word1; UnicodeString text1; unsigned int word2;
    BfmeStringRecord005D511F(const BfmeStringRecord005D511F &o);
    BfmeStringRecord005D511F(const UnicodeString &t0, unsigned int w0, unsigned int w1, const UnicodeString &t1, unsigned int w2);
    ~BfmeStringRecord005D511F();
};
BfmeStringRecord005D511F::BfmeStringRecord005D511F(const BfmeStringRecord005D511F &o) : text0(o.text0), word0(o.word0), word1(o.word1), text1(o.text1), word2(o.word2) {}
// ??0BfmeStringRecord005D511F@@QAE@ABVUnicodeString@@II0I@Z retail 0x005D516E 75B.
// 5-arg ctor of the same 0x14 record: text0 via 0x37050 + word0/word1 + text1 via 0x37050 + word2.
// Same EH scope as the copy (first StringBase before state 0, second after); callers 0x005D5604 0x005D5692.
BfmeStringRecord005D511F::BfmeStringRecord005D511F(const UnicodeString &t0, unsigned int w0, unsigned int w1, const UnicodeString &t1, unsigned int w2) : text0(t0), word0(w0), word1(w1), text1(t1), word2(w2) {}
// ??1BfmeStringRecord005D511F@@QAE@XZ retail 0x005D51B9 53B.
// Layout from the 0x005D511F copy ctor in this TU (UnicodeString +0 and +0xC with words at +4 +8 +0x10 = 0x14).
// Retail destroys text1 (+0xC) then text0 (+0) via StringBase<ushort>::releaseBuffer 0x00036E70 with EH states 0 then -1.
// Callers are the deleting dtor 0x005D5266 and the 0x14-stride destroy range 0x005D541B.
BfmeStringRecord005D511F::~BfmeStringRecord005D511F() {}
template void _STL::_Construct<BfmeStringRecord005D511F,BfmeStringRecord005D511F>(BfmeStringRecord005D511F*,const BfmeStringRecord005D511F&);
// ??$_Destroy@PAUBfmeStringRecord005D511F@@@_STL@@YAXPAUBfmeStringRecord005D511F@@0@Z retail 0x005D541B 25B.
// Range destroy over 0x14-byte record via rowed dtor 0x005D51B9 in this TU. Callers 0x005D5434 and 0x005D5473.
template void _STL::_Destroy<BfmeStringRecord005D511F *>(BfmeStringRecord005D511F *, BfmeStringRecord005D511F *);

extern "C" void free(void *ptr);

// ??1BfmeRecordRange005D5473@@QAE@XZ retail 0x005D5473 30B.
// Owning two-pointer range over BfmeStringRecord005D511F: destroy via rowed _Destroy 0x005D541B then free via 0x00030830.
// Same frameless shape as BfmeRecordRange004B205 at 0x0004B205. Caller 0x005D5491.
struct BfmeRecordRange005D5473 {
    BfmeStringRecord005D511F *m_begin;
    BfmeStringRecord005D511F *m_end;
    ~BfmeRecordRange005D5473();
};
BfmeRecordRange005D5473::~BfmeRecordRange005D5473()
{
    _STL::_Destroy(m_begin, m_end);
    if (m_begin != 0) {
        free(m_begin);
    }
}

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
    BfmeStringRecord005ED5F3 &operator=(const BfmeStringRecord005ED5F3 &o);
};
BfmeStringRecord005ED5F3::BfmeStringRecord005ED5F3(const BfmeStringRecord005ED5F3 &o) : text(o.text), word0(o.word0), word1(o.word1), word2(o.word2), word3(o.word3) {}
inline BfmeStringRecord005ED5F3 &BfmeStringRecord005ED5F3::operator=(const BfmeStringRecord005ED5F3 &o)
{
    text.set(o.text);
    word0 = o.word0;
    word1 = o.word1;
    word2 = o.word2;
    word3 = o.word3;
    return *this;
}
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
    BfmeStringRecord005DDD40 &operator=(const BfmeStringRecord005DDD40 &o);
};
inline BfmeStringRecord005DDD40::BfmeStringRecord005DDD40(const BfmeStringRecord005DDD40 &o) : text(o.text), word(o.word) {}
// ??4BfmeStringRecord005DDD40@@QAEAAU0@ABU0@@Z retail 0x005DD6B6 31B.
// Same layout as the 0x005DDD40 copy above (UnicodeString text + word).
// Callee is StringBase<ushort>::set at 0x00037150 (pin-only); self-check plus word copy.
// Callers 0x005DD704/0x005DD72D/0x005DD764/0x005DDB86 unblock 0x005DD743/0x005DDD5B chain.
BfmeStringRecord005DDD40 &BfmeStringRecord005DDD40::operator=(const BfmeStringRecord005DDD40 &o)
{
    if (this != &o) {
        text.set(o.text);
        word = o.word;
    }
    return *this;
}
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
inline BfmeStringRecord002CF550::BfmeStringRecord002CF550(const BfmeStringRecord002CF550 &o) : text(o.text), ref(o.ref) {}
template void _STL::_Construct<BfmeStringRecord002CF550,BfmeStringRecord002CF550>(BfmeStringRecord002CF550*,const BfmeStringRecord002CF550&);

// ??4BfmeStringRecord002602A6@@QAEAAU0@ABU0@@Z retail 0x002602A6 27B.
// Same 8-byte layout as 005DDD40 (UnicodeString text + word) without self-check.
// Callee StringBase<ushort>::set at 0x00037150 (pin-only); 47B __copy caller
// at 0x002605EB uses sar 3 stride 8.
struct BfmeStringRecord002602A6 {
    UnicodeString text; unsigned int word;
    BfmeStringRecord002602A6 &operator=(const BfmeStringRecord002602A6 &o);
};
BfmeStringRecord002602A6 &BfmeStringRecord002602A6::operator=(const BfmeStringRecord002602A6 &o)
{
    text.set(o.text);
    word = o.word;
    return *this;
}
#include <vector>
// Retail __copy 0x002605EB 47B: forward copy of 8-byte BfmeStringRecord002602A6 via operator= at 0x002602A6; sar 3 stride 8; caller at 0x0026065A; same shape as 47B __copy at 0x00426A82.
template BfmeStringRecord002602A6* _STL::__copy<BfmeStringRecord002602A6*, BfmeStringRecord002602A6*, int>(BfmeStringRecord002602A6*, BfmeStringRecord002602A6*, BfmeStringRecord002602A6*, const _STL::random_access_iterator_tag&, int*);

// Retail __copy_ptrs 0x00260647 29B: ptrs wrapper via rowed __copy 0x002605EB; same shape as 29B wrapper 0x00426B29; caller at 0x002606CA.
// Manual wrapper with identical pushes: tag local plus null distance.
BfmeStringRecord002602A6 *Rva00260647Copy(BfmeStringRecord002602A6 *first, BfmeStringRecord002602A6 *last, BfmeStringRecord002602A6 *result)
{
    const _STL::random_access_iterator_tag tag;
    return _STL::__copy(first, last, result, tag, (int *)0);
}
template void _STL::fill<BfmeStringRecord005ED5F3 *, BfmeStringRecord005ED5F3>(BfmeStringRecord005ED5F3 *, BfmeStringRecord005ED5F3 *, const BfmeStringRecord005ED5F3 &);
template BfmeStringRecord005ED5F3* _STL::__copy_backward<BfmeStringRecord005ED5F3*, BfmeStringRecord005ED5F3*, int>(BfmeStringRecord005ED5F3*, BfmeStringRecord005ED5F3*, BfmeStringRecord005ED5F3*, const _STL::random_access_iterator_tag&, int*);
template BfmeStringRecord005ED5F3* _STL::__copy_backward_ptrs<BfmeStringRecord005ED5F3*, BfmeStringRecord005ED5F3*>(BfmeStringRecord005ED5F3*, BfmeStringRecord005ED5F3*, BfmeStringRecord005ED5F3*, const _STL::__false_type&);
template BfmeStringRecord005ED5F3* _STL::__copy<BfmeStringRecord005ED5F3*, BfmeStringRecord005ED5F3*, int>(BfmeStringRecord005ED5F3*, BfmeStringRecord005ED5F3*, BfmeStringRecord005ED5F3*, const _STL::random_access_iterator_tag&, int*);

// Complete retail record copy at0x00219B0B.
struct BfmeStringRecord00219B0B {
    unsigned int word0; AsciiString text0, text1, text2;
    BfmeStringRecord00219B0B(const BfmeStringRecord00219B0B &o);
    BfmeStringRecord00219B0B(unsigned int w0, const AsciiString &t0, const AsciiString &t1, const AsciiString &t2);
    ~BfmeStringRecord00219B0B();
};
BfmeStringRecord00219B0B::BfmeStringRecord00219B0B(const BfmeStringRecord00219B0B &o) : word0(o.word0), text0(o.text0), text1(o.text1), text2(o.text2) {}
// ??0BfmeStringRecord00219B0B@@QAE@IABVAsciiString@@00@Z @0x00219ABB 80B
// 4-arg ctor of the same 0x10 record: word0 + three AsciiString copies via 0x365F0.
// Same EH scope as the copy; caller 0x0021DEF9 forwards (w,t0,t1,t2) in order.
BfmeStringRecord00219B0B::BfmeStringRecord00219B0B(unsigned int w0, const AsciiString &t0, const AsciiString &t1, const AsciiString &t2) : word0(w0), text0(t0), text1(t1), text2(t2) {}
BfmeStringRecord00219B0B::~BfmeStringRecord00219B0B() {}
template void _STL::_Construct<BfmeStringRecord00219B0B,BfmeStringRecord00219B0B>(BfmeStringRecord00219B0B*,const BfmeStringRecord00219B0B&);

// Complete retail 2-arg ctor at0x0021A940.
struct BfmeStringRecord0021A940 {
    unsigned int word0; BfmeStringRecord00219B0B rec;
    BfmeStringRecord0021A940(const unsigned int *p, const BfmeStringRecord00219B0B &o);
    BfmeStringRecord0021A940(const BfmeStringRecord0021A940 &o);
    ~BfmeStringRecord0021A940();
};
BfmeStringRecord0021A940::BfmeStringRecord0021A940(const unsigned int *p, const BfmeStringRecord00219B0B &o) : word0(*p), rec(o) {}
BfmeStringRecord0021A940::BfmeStringRecord0021A940(const BfmeStringRecord0021A940 &o) : word0(o.word0), rec(o.rec) {}
BfmeStringRecord0021A940::~BfmeStringRecord0021A940() {}
template void _STL::_Construct<BfmeStringRecord0021A940,BfmeStringRecord0021A940>(BfmeStringRecord0021A940*,const BfmeStringRecord0021A940&);

#pragma inline_depth(0)
// ?bfmeEmitStringRecordInlineCopyBFME2@@YAXPAUBfmeStringRecord002CF550@@PBU1@PAUBfmeStringRecord005ED5F3@@PBU2@@Z present-unmatched
void bfmeEmitStringRecordInlineCopyBFME2(BfmeStringRecord002CF550 *p0, const BfmeStringRecord002CF550 *q0, BfmeStringRecord005ED5F3 *p1, const BfmeStringRecord005ED5F3 *q1)
{
	p0->BfmeStringRecord002CF550::BfmeStringRecord002CF550(*q0);
	p1->BfmeStringRecord005ED5F3::operator=(*q1);
}
#pragma inline_depth()

// BfmeStringRecord005DDD40 copy is a header inline elsewhere: other units emit
// select-any copies, so a strong definition here was a duplicate in the linked
// build. This anchor only makes this unit emit its copy for the ledger row; it
// is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitStringRecord005DDD40Copy@@YAXPAUBfmeStringRecord005DDD40@@PBU1@@Z present-unmatched
void bfmeEmitStringRecord005DDD40Copy(BfmeStringRecord005DDD40 *p, const BfmeStringRecord005DDD40 *q)
{
	p->BfmeStringRecord005DDD40::BfmeStringRecord005DDD40(*q);
}
#pragma inline_depth()

// Target strings/xrefs at 0x007E5E28 and 0x007E5E60 name AwardSystemManager
// validation; data xrefs identify its manager at 0x00A02F74. The exact method
// names are not established, so retain address-derived callback names.
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class INI;
class Rva0014921EVector;
void __cdecl rva00149002(int ini, int instance, Rva0014921EVector *store, int userData);

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;

struct BfmePod40;
class Rva0040BAD0
{
public:
	int rva0040AAF8(int key);
};
class Rva0040AAD5 : public Rva0040BAD0
{
public:
	BfmePod40 *rva0040AAD5(int key);
};
extern Rva0040AAD5 *g_00E02F74;

struct _s__ThrowInfo;
struct INIException
{
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
};
extern "C" void __stdcall _CxxThrowException(void *exceptionObject, const _s__ThrowInfo *throwInfo);
extern "C" const _s__ThrowInfo __identifier("_TI1?AVINIException@@");

// Standalone callbacks at 0x0021A7A3 and 0x0021A859 share the same checked
// NameKey vector walk. The target strings and method calls distinguish Award
// from Stat; all other layout details below are read from the retail bodies.
void rva0021A7A3(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	bool parsed = true;
	rva00149002((int)ini, 0, (Rva0014921EVector *)store, (int)&parsed);
	std::vector<NameKeyType> *keys = (std::vector<NameKeyType> *)store;
	for (unsigned int i = 0; i < keys->size(); ++i)
	{
		if (g_00E02F74->rva0040AAD5(keys->begin()[i]) == 0)
		{
			AsciiString name(TheNameKeyGenerator->keyToName(keys->begin()[i]));
			INIException e(3, "The Award %s does not exist in the AwardSystemManager.", name.str());
			_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
			__assume(0);
		}
	}
}

void rva0021A859(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	bool parsed = true;
	rva00149002((int)ini, 0, (Rva0014921EVector *)store, (int)&parsed);
	std::vector<NameKeyType> *keys = (std::vector<NameKeyType> *)store;
	for (unsigned int i = 0; i < keys->size(); ++i)
	{
		if (g_00E02F74->rva0040AAF8(keys->begin()[i]) == 0)
		{
			AsciiString name(TheNameKeyGenerator->keyToName(keys->begin()[i]));
			INIException e(3, "The Stat %s does not exist in the AwardSystemManager.", name.str());
			_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
			__assume(0);
		}
	}
}
