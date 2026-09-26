// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// BFME2 record copy at0x63BE4: seven words, an AsciiString, two tail bytes.
// The original application class and field meanings are unknown.
// The36-byte layout and memberwise copy are read directly from the complete
// retail body. Its string member calls the established copy at0x365F0.
// The placement-copy caller at0x63C8F independently links the same value.
class AsciiString { public: AsciiString(const AsciiString &); __forceinline ~AsciiString() { releaseBuffer(); } protected: void releaseBuffer(); private: void *m_data; };
struct BfmeStringRecord00063BE4 {
    unsigned int word0, word1, word2, word3, word4, word5, word6;
    AsciiString text;
    unsigned char tail0, tail1;
    BfmeStringRecord00063BE4(const BfmeStringRecord00063BE4 &o)
      : word0(o.word0), word1(o.word1), word2(o.word2), word3(o.word3), word4(o.word4), word5(o.word5), word6(o.word6), text(o.text), tail0(o.tail0), tail1(o.tail1) {}
};
#include <memory>
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

// Retail copy 0x00404BF3: observed scalar fields and string member.
// Original application type and scalar meanings are unknown.
struct BfmeStringRecord00404BF3 {
    AsciiString text; unsigned int word0, word1, word2, word3, word4;
    BfmeStringRecord00404BF3(const BfmeStringRecord00404BF3 &o) : text(o.text), word0(o.word0), word1(o.word1), word2(o.word2), word3(o.word3), word4(o.word4) {}
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
    BfmeStringRecord00426A5B(const BfmeStringRecord00426A5B &o) : text(o.text), flag0(o.flag0), flag1(o.flag1), flag2(o.flag2) {}
};
template void _STL::_Construct<BfmeStringRecord00426A5B,BfmeStringRecord00426A5B>(BfmeStringRecord00426A5B*,const BfmeStringRecord00426A5B&);

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
template <typename T> class StringBase
{
public:
	~StringBase();
private:
	void *m_data;
};
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
