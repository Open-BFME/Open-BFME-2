// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// Constructor-only ABI view of BfmeVectorRecord000C0BEC.
// BFME1 donor: 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/Common/Containers/Rva007701C0Vector.cpp.
// Whole donor compiled and placed constructor 0x000BDD48 before this import.
// Target facts: C8492 news 20 bytes, scans names at +0 with 20-byte stride,
// calls BDD48, then set366F0/pushC8255/dtorBEDF0/delete2FD60. CopyC0BEC
// independently copies text+0/vector+4/word+10. Original owner/word names unknown.
#include "ascii_string.h"

// The rowed _Vector_base<AsciiString, allocator<AsciiString>> initializer
// 0x00211E58 stores three null pointers in twelve bytes. Its allocator
// argument is an empty stateless object; the native 11-byte proxy ctor
// 0x0014F3C4 ignores that argument and stores the supplied pointer.
// This external ABI view calls that provider, without emitting a second
// implementation of STLport's unrelated assignment or cleanup helpers.
struct BfmeAsciiStringAllocator000BDD48
{
    __forceinline BfmeAsciiStringAllocator000BDD48() {}
};
class BfmeAsciiStringStorage000BDD48
{
public:
    __declspec(nothrow) BfmeAsciiStringStorage000BDD48(const BfmeAsciiStringAllocator000BDD48 &);
private:
    AsciiString *first;
    AsciiString *last;
    AsciiString *limit;
};
class BfmeAsciiStringVector000BDD48 : public BfmeAsciiStringStorage000BDD48
{
public:
    __forceinline BfmeAsciiStringVector000BDD48()
        : BfmeAsciiStringStorage000BDD48(BfmeAsciiStringAllocator000BDD48()) {}
};
struct BfmeVectorRecord000C0BEC
{
    AsciiString text;
    BfmeAsciiStringVector000BDD48 names;
    unsigned int word10;
    BfmeVectorRecord000C0BEC();
    BfmeVectorRecord000C0BEC(const BfmeVectorRecord000C0BEC &);
    ~BfmeVectorRecord000C0BEC();
    BfmeVectorRecord000C0BEC &operator=(const BfmeVectorRecord000C0BEC &);
};
typedef char BfmeRecordExtent000BDD48[sizeof(BfmeVectorRecord000C0BEC)==20 ? 1 : -1];

// ??0BfmeVectorRecord000C0BEC@@QAE@XZ at 0x000BDD48 (36B).
BfmeVectorRecord000C0BEC::BfmeVectorRecord000C0BEC()
    : text(""), word10(0)
{
}

#pragma comment(linker, "/alternatename:??0BfmeAsciiStringStorage000BDD48@@QAE@ABUBfmeAsciiStringAllocator000BDD48@@@Z=??0?$_Vector_base@UBfmeE16@@V?$allocator@UBfmeE16@@@_STL@@@_STL@@QAE@ABV?$allocator@UBfmeE16@@@1@@Z")
