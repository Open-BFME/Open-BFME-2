// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// BFME2 record copy at0x63BE4: seven words, an AsciiString, two tail bytes.
// The original application class and field meanings are unknown.
// The36-byte layout and memberwise copy are read directly from the complete
// retail body. Its string member calls the established copy at0x365F0.
// The placement-copy caller at0x63C8F independently links the same value.
struct BfmeStringRecord00404BF3;
template <typename T> class StringBase
{
public:
	~StringBase();
	void set(const StringBase<T> &that);
private:
	StringBase(const StringBase<T> &);
	friend class AsciiString;
	friend struct BfmeStringRecord00404BF3;
	friend struct S4Name;
	void *m_data;
};
class AsciiString
{
public:
	__forceinline AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
	}
	AsciiString &operator=(const AsciiString &);
	~AsciiString();
	static const AsciiString TheEmptyString;
protected:
	void releaseBuffer();
private:
	void *m_data;
};
struct BfmeStringRecord00063BE4 {
    unsigned int word0, word1, word2, word3, word4, word5, word6;
    AsciiString text;
    unsigned char tail0, tail1;
    BfmeStringRecord00063BE4(const BfmeStringRecord00063BE4 &o)
      : word0(o.word0), word1(o.word1), word2(o.word2), word3(o.word3), word4(o.word4), word5(o.word5), word6(o.word6), text(o.text), tail0(o.tail0), tail1(o.tail1) {}
};
#include <memory>
// Codegen view of BFME2 AsciiString's one-pointer StringBase<char> base. Its
// copy operation calls retail 0x000365F0 without changing other record views.
template void _STL::_Construct<BfmeStringRecord00063BE4,BfmeStringRecord00063BE4>(BfmeStringRecord00063BE4*,const BfmeStringRecord00063BE4&);


// Retail copy 0x000B757D: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord000B757D {
    unsigned int word0, word1; AsciiString text; unsigned int word2; unsigned char tail;
    BfmeStringRecord000B757D(const BfmeStringRecord000B757D &o) : word0(o.word0), word1(o.word1), text(o.text), word2(o.word2), tail(o.tail) {}
};
template void _STL::_Construct<BfmeStringRecord000B757D,BfmeStringRecord000B757D>(BfmeStringRecord000B757D*,const BfmeStringRecord000B757D&);

// Retail copy 0x000B950F: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord000B950F {
    unsigned int word0; AsciiString text; unsigned int word1;
    BfmeStringRecord000B950F(const BfmeStringRecord000B950F &o) : word0(o.word0), text(o.text), word1(o.word1) {}
};
template void _STL::_Construct<BfmeStringRecord000B950F,BfmeStringRecord000B950F>(BfmeStringRecord000B950F*,const BfmeStringRecord000B950F&);

// Retail copy 0x000B9534: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord000B9534 {
    AsciiString text; unsigned char flag; unsigned int word0, word1, word2, word3;
    BfmeStringRecord000B9534(const BfmeStringRecord000B9534 &o) : text(o.text), flag(o.flag), word0(o.word0), word1(o.word1), word2(o.word2), word3(o.word3) {}
};
template void _STL::_Construct<BfmeStringRecord000B9534,BfmeStringRecord000B9534>(BfmeStringRecord000B9534*,const BfmeStringRecord000B9534&);

// Retail copy 0x002CF4C6: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord002CF4C6 {
    AsciiString text0, text1; unsigned int word0, word1; unsigned char flag0, flag1;
    BfmeStringRecord002CF4C6(const BfmeStringRecord002CF4C6 &o) : text0(o.text0), text1(o.text1), word0(o.word0), word1(o.word1), flag0(o.flag0), flag1(o.flag1) {}
};
template void _STL::_Construct<BfmeStringRecord002CF4C6,BfmeStringRecord002CF4C6>(BfmeStringRecord002CF4C6*,const BfmeStringRecord002CF4C6&);

// Retail copy 0x002CF5B1: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord002CF5B1 {
    unsigned int word0, word1; AsciiString text;
    BfmeStringRecord002CF5B1(const BfmeStringRecord002CF5B1 &o) : word0(o.word0), word1(o.word1), text(o.text) {}
};
template void _STL::_Construct<BfmeStringRecord002CF5B1,BfmeStringRecord002CF5B1>(BfmeStringRecord002CF5B1*,const BfmeStringRecord002CF5B1&);

// Retail copy 0x00395E75: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord00395E75 {
    AsciiString text0, text1; unsigned int word;
    BfmeStringRecord00395E75(const BfmeStringRecord00395E75 &o) : text0(o.text0), text1(o.text1), word(o.word) {}
};
template void _STL::_Construct<BfmeStringRecord00395E75,BfmeStringRecord00395E75>(BfmeStringRecord00395E75*,const BfmeStringRecord00395E75&);

// Retail copy 0x00568CE0: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord00568CE0 {
    AsciiString text0, text1; unsigned int word0, word1; unsigned char flag;
    BfmeStringRecord00568CE0(const BfmeStringRecord00568CE0 &o) : text0(o.text0), text1(o.text1), word0(o.word0), word1(o.word1), flag(o.flag) {}
};
template void _STL::_Construct<BfmeStringRecord00568CE0,BfmeStringRecord00568CE0>(BfmeStringRecord00568CE0*,const BfmeStringRecord00568CE0&);

// Retail copy 0x000B75AE: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord000B75AE {
    AsciiString text; unsigned int word0, word1, word2, word3, word4, word5; unsigned char flag0, flag1, flag2, flag3;
    BfmeStringRecord000B75AE(const BfmeStringRecord000B75AE &o) : text(o.text), word0(o.word0), word1(o.word1), word2(o.word2), word3(o.word3), word4(o.word4), word5(o.word5), flag0(o.flag0), flag1(o.flag1), flag2(o.flag2), flag3(o.flag3) {}
};
template void _STL::_Construct<BfmeStringRecord000B75AE,BfmeStringRecord000B75AE>(BfmeStringRecord000B75AE*,const BfmeStringRecord000B75AE&);

// Retail copy 0x003B3F78: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord003B3F78 {
    unsigned int word0, word1; AsciiString text; unsigned char flag; unsigned short short0; unsigned int word2;
    BfmeStringRecord003B3F78(const BfmeStringRecord003B3F78 &o) : word0(o.word0), word1(o.word1), text(o.text), flag(o.flag), short0(o.short0), word2(o.word2) {}
};
template void _STL::_Construct<BfmeStringRecord003B3F78,BfmeStringRecord003B3F78>(BfmeStringRecord003B3F78*,const BfmeStringRecord003B3F78&);

// Retail copy 0x0040360E: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord0040360E {
    unsigned int word0; AsciiString text; unsigned int word1, word2;
    BfmeStringRecord0040360E(const BfmeStringRecord0040360E &o) : word0(o.word0), text(o.text), word1(o.word1), word2(o.word2) {}
};
template void _STL::_Construct<BfmeStringRecord0040360E,BfmeStringRecord0040360E>(BfmeStringRecord0040360E*,const BfmeStringRecord0040360E&);

// Retail copy 0x00404BF3: the 0x00404BC5 sibling ctor establishes an
// AsciiString at +0 and five floats at +4..+0x14; their meanings are unknown.
// StringBase<char> below is the layout-equivalent codegen view for the copy.
struct BfmeStringRecord00404BF3 {
    StringBase<char> text; float f0, f1, f2, f3, f4;
    BfmeStringRecord00404BF3(const BfmeStringRecord00404BF3 &o) : text(o.text), f0(o.f0), f1(o.f1), f2(o.f2), f3(o.f3), f4(o.f4) {}
};
template void _STL::_Construct<BfmeStringRecord00404BF3,BfmeStringRecord00404BF3>(BfmeStringRecord00404BF3*,const BfmeStringRecord00404BF3&);

// Retail copy 0x001EA478: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord001EA478 {
    AsciiString text0, text1;
    BfmeStringRecord001EA478(const BfmeStringRecord001EA478 &o) : text0(o.text0), text1(o.text1) {}
};
template void _STL::_Construct<BfmeStringRecord001EA478,BfmeStringRecord001EA478>(BfmeStringRecord001EA478*,const BfmeStringRecord001EA478&);

// Retail copy 0x00426A5B: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord00426A5B {
    AsciiString text; unsigned char flag0, flag1, flag2;
    BfmeStringRecord00426A5B();
    BfmeStringRecord00426A5B(const BfmeStringRecord00426A5B &o) : text(o.text), flag0(o.flag0), flag1(o.flag1), flag2(o.flag2) {}
    BfmeStringRecord00426A5B &operator=(const BfmeStringRecord00426A5B &o);
};
BfmeStringRecord00426A5B::BfmeStringRecord00426A5B() : text(AsciiString::TheEmptyString), flag0(0), flag1(1), flag2(0) {}
inline BfmeStringRecord00426A5B &BfmeStringRecord00426A5B::operator=(const BfmeStringRecord00426A5B &o) {
    ((StringBase<char> &)text).set((const StringBase<char> &)o.text);
    flag0 = o.flag0;
    flag1 = o.flag1;
    flag2 = o.flag2;
    return *this;
}
template void _STL::_Construct<BfmeStringRecord00426A5B,BfmeStringRecord00426A5B>(BfmeStringRecord00426A5B*,const BfmeStringRecord00426A5B&);
#include <vector>
// Retail __copy 0x00426A82 47B: forward copy of 8-byte BfmeStringRecord00426A5B via operator= at 0x004267A5; sar 3 stride 8; caller at 0x00426B29; same shape as 47B __copy at 0x00215696 and 0x001737C0.
template BfmeStringRecord00426A5B* _STL::__copy<BfmeStringRecord00426A5B*, BfmeStringRecord00426A5B*, int>(BfmeStringRecord00426A5B*, BfmeStringRecord00426A5B*, BfmeStringRecord00426A5B*, const _STL::random_access_iterator_tag&, int*);

// Retail copy 0x004071F7: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord004071F7 {
    AsciiString text; unsigned int word0, word1;
    BfmeStringRecord004071F7(const BfmeStringRecord004071F7 &o) : text(o.text), word0(o.word0), word1(o.word1) {}
};
template void _STL::_Construct<BfmeStringRecord004071F7,BfmeStringRecord004071F7>(BfmeStringRecord004071F7*,const BfmeStringRecord004071F7&);

// Retail copy 0x004D05B8: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord004D05B8 {
    unsigned short short0; AsciiString text;
    BfmeStringRecord004D05B8(const BfmeStringRecord004D05B8 &o) : short0(o.short0), text(o.text) {}
};
template void _STL::_Construct<BfmeStringRecord004D05B8,BfmeStringRecord004D05B8>(BfmeStringRecord004D05B8*,const BfmeStringRecord004D05B8&);

// Retail copy 0x00331962: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord00331962 {
    unsigned int word; AsciiString text; unsigned char flag;
    BfmeStringRecord00331962(const BfmeStringRecord00331962 &o) : word(o.word), text(o.text), flag(o.flag) {}
};
template void _STL::_Construct<BfmeStringRecord00331962,BfmeStringRecord00331962>(BfmeStringRecord00331962*,const BfmeStringRecord00331962&);

// Retail copy 0x000B94D2: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord000B94D2 {
    AsciiString text0, text1;
    BfmeStringRecord000B94D2(const BfmeStringRecord000B94D2 &o) : text0(o.text0), text1(o.text1) {}
};
template void _STL::_Construct<BfmeStringRecord000B94D2,BfmeStringRecord000B94D2>(BfmeStringRecord000B94D2*,const BfmeStringRecord000B94D2&);

// Retail copy 0x00466E64: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord00466E64 {
    AsciiString text0, text1; unsigned int word;
    BfmeStringRecord00466E64(const BfmeStringRecord00466E64 &o) : text0(o.text0), text1(o.text1), word(o.word) {}
};
template void _STL::_Construct<BfmeStringRecord00466E64,BfmeStringRecord00466E64>(BfmeStringRecord00466E64*,const BfmeStringRecord00466E64&);

// Retail copy 0x00239B46: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord00239B46 {
    AsciiString text; unsigned short short0;
    BfmeStringRecord00239B46(const BfmeStringRecord00239B46 &o) : text(o.text), short0(o.short0) {}
};
template void _STL::_Construct<BfmeStringRecord00239B46,BfmeStringRecord00239B46>(BfmeStringRecord00239B46*,const BfmeStringRecord00239B46&);

// Retail dtor 0x001EA443 (53B) and deleting dtor 0x001EA4B5 (28B): two
// narrow-string members at +0/+4 destroyed in reverse order through the
// pinned StringBase dtor at 0x36410, with /EHsc states. Identity unproven
// beyond the string-pair layout shared with BfmeStringRecord001EA478, so
// both land under an honest Rva address name in this TU (same flags).
class Rva001EA443
{
public:
	~Rva001EA443();
private:
	StringBase<char> m_text0;
	StringBase<char> m_text1;
};
Rva001EA443::~Rva001EA443() {}
void famgenDelete001EA443(Rva001EA443 *p) { delete p; }

// Retail dtor 0x00395D77 (53B): two narrow-string members at +0/+4 destroyed
// in reverse order through the pinned StringBase dtor at 0x36410 with /EHsc
// states. Same 53B shape as 0x001EA443 in this TU (mov eax scope-table reloc
// plus EH prolog plus two releaseBuffer calls). Callers at 0x3962CE 0x396EF2
// 0x396F22 0x39933F 0x39A618 plus jmp tail at 0x39698F prove dtor role.
// Next copy 0x395E75 (BfmeStringRecord00395E75 text0 text1 word) shares the
// string-pair layout. Honest Rva address name; same flags.
class Rva00395D77
{
public:
	~Rva00395D77();
private:
	StringBase<char> m_text0;
	StringBase<char> m_text1;
};
Rva00395D77::~Rva00395D77() {}

// Retail dtor 0x00568C4E (53B): two narrow-string members at +0/+4 destroyed
// in reverse order through the pinned StringBase dtor at 0x36410 with /EHsc
// states. Same 53B shape as 0x001EA443 and 0x00395D77 in this TU (mov eax
// scope-table reloc plus EH prolog plus two releaseBuffer calls). Destroy loop
// at 0x569A5B steps 0x14 (20-byte BfmeStringRecord00568CE0) plus deleting-dtor
// caller at 0x568E17 and parse caller at 0x56A96F prove dtor role.
// Honest Rva address name; same flags.
class Rva00568C4E
{
public:
	~Rva00568C4E();
private:
	StringBase<char> m_text0;
	StringBase<char> m_text1;
};
Rva00568C4E::~Rva00568C4E() {}
void famgenDelete00568C4E(Rva00568C4E *p) { delete p; }

// Retail _Construct 0x000BB993 45B: placement copy of Rva000BB491 via the
// rowed copy ctor at 0x000BB491; same 45B EH shape as 0x000BB9ED in this TU;
// callers at 0x000BBAD5 0x000BBB00 0x000C3543 0x000C46A0.
class Rva000BB491
{
public:
	Rva000BB491(const Rva000BB491 &o);
};
template void _STL::_Construct<Rva000BB491, Rva000BB491>(Rva000BB491 *, const Rva000BB491 &);

// Retail _Construct 0x000BB9C0 45B: placement copy of Rva000BB4AC via the
// rowed copy ctor at 0x000BB4AC; same 45B EH shape as neighbours in this TU;
// callers at 0x000BBB20 0x000BBB4B 0x000C35FA 0x000C46D7.
class Rva000BB4AC
{
public:
	Rva000BB4AC(const Rva000BB4AC &o);
};
template void _STL::_Construct<Rva000BB4AC, Rva000BB4AC>(Rva000BB4AC *, const Rva000BB4AC &);

// Retail _Construct 0x00568C83 18B: placement copy of Rva00568A20 via the
// rowed copy ctor at 0x00568A20; null-checked; callers at 0x00568CA3 0x00568CCE
// 0x0056A23A 0x0056A33D; step 0xC matches 12-byte Rva00568A20.
class Rva00568A20
{
public:
	Rva00568A20(const Rva00568A20 &o) throw();
};
template void _STL::_Construct<Rva00568A20, Rva00568A20>(Rva00568A20 *, const Rva00568A20 &);

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??$_Construct@VRva00297360Element@@V1@@_STL@@YAXPAVRva00297360Element@@ABV1@@Z=??$_Construct@UBfmeStringRecord0040360E@@U1@@_STL@@YAXPAUBfmeStringRecord0040360E@@ABU1@@Z")
#pragma inline_depth(0)
// ?bfmeEmitBfmeStringRecord00426A5BAssign@@YAXPAUBfmeStringRecord00426A5B@@ABU1@@Z present-unmatched
void bfmeEmitBfmeStringRecord00426A5BAssign(BfmeStringRecord00426A5B *p, const BfmeStringRecord00426A5B &o)
{
	p->operator=(o);
}
#pragma inline_depth()


// BFME 1 donor compiled with BFME 2 /O1 settings from revision 968ca36c3265b295297e6aed45a6bd89ffe59c40.
// The retail insertion-sort caller at 0x00331BD7 names this specialization; donor_sweep placed its 75-byte body at 0x00331A46.
struct S4Name
{
    S4Name(const S4Name &other) : m_base(other.m_base) {}
    ~S4Name(void) {}
    S4Name &operator=(const S4Name &other)
    {
        m_base.set(other.m_base);
        return *this;
    }
    StringBase<char> m_base;
};

struct S4SortElem12
{
    int m_bfmeA;
    S4Name m_bfmeName;
    char m_bfmeC;
    S4SortElem12 &operator=(const S4SortElem12 &);
};

struct S4Cmp002E1690
{
    int m_bfmeSlot;
    bool operator()(const S4SortElem12 &left, const S4SortElem12 &right) const
    {
        return left.m_bfmeA < right.m_bfmeA;
    }
};

namespace _STL
{

template <class RandomAccessIter, class Tp, class Compare>
void __unguarded_linear_insert(RandomAccessIter last, Tp val, Compare comp)
{
    RandomAccessIter next = last;
    --next;
    while (comp(val, *next))
    {
        *last = *next;
        last = next;
        --next;
    }
    *last = val;
}

template void __unguarded_linear_insert<S4SortElem12 *, S4SortElem12, S4Cmp002E1690>(
    S4SortElem12 *, S4SortElem12, S4Cmp002E1690);

}
