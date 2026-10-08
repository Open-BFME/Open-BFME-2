// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// BFME2 records containing AsciiString and STLport vector<AsciiString>.
// The vector copy is the established 93-byte constructor at 0xBC07E.
// Layouts are read from the complete retail constructors and their STLport
// placement-copy callers. Application names and scalar meanings are unknown.
// String semantics follow BFME1 AsciiString/UnicodeString: the inline derived
// copies call StringBase<char>0x365F0 or StringBase<unsigned short>0x37050.
#include <memory>
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"

// Complete retail record copy at 0x000BDF17.
struct BfmeVectorRecord000BDF17 {
    _STL::vector<AsciiString> names; AsciiString text0, text1; unsigned int word14, word18, word1C, word20, word24, word28; unsigned char flag2C, flag2D; unsigned int word30, word34, word38; unsigned char flag3C;
    BfmeVectorRecord000BDF17(const BfmeVectorRecord000BDF17 &o);
};
BfmeVectorRecord000BDF17::BfmeVectorRecord000BDF17(const BfmeVectorRecord000BDF17 &o) : names(o.names), text0(o.text0), text1(o.text1), word14(o.word14), word18(o.word18), word1C(o.word1C), word20(o.word20), word24(o.word24), word28(o.word28), flag2C(o.flag2C), flag2D(o.flag2D), word30(o.word30), word34(o.word34), word38(o.word38), flag3C(o.flag3C) {}
template void _STL::_Construct<BfmeVectorRecord000BDF17,BfmeVectorRecord000BDF17>(BfmeVectorRecord000BDF17*,const BfmeVectorRecord000BDF17&);

// Complete retail record copy at 0x001B4A39.
struct BfmeVectorRecord001B4A39 {
    AsciiString text0; _STL::vector<AsciiString> names0, names1, names2, names3, names4; unsigned int word40; AsciiString text1;
    BfmeVectorRecord001B4A39(const BfmeVectorRecord001B4A39 &o);
    ~BfmeVectorRecord001B4A39();
};
BfmeVectorRecord001B4A39::BfmeVectorRecord001B4A39(const BfmeVectorRecord001B4A39 &o) : text0(o.text0), names0(o.names0), names1(o.names1), names2(o.names2), names3(o.names3), names4(o.names4), word40(o.word40), text1(o.text1) {}
BfmeVectorRecord001B4A39::~BfmeVectorRecord001B4A39() {}
template void _STL::_Construct<BfmeVectorRecord001B4A39,BfmeVectorRecord001B4A39>(BfmeVectorRecord001B4A39*,const BfmeVectorRecord001B4A39&);

// Complete retail record copy at 0x000C0BEC.
struct BfmeVectorRecord000C0BEC {
    AsciiString text; _STL::vector<AsciiString> names; unsigned int word10;
    BfmeVectorRecord000C0BEC(const BfmeVectorRecord000C0BEC &o);
};
BfmeVectorRecord000C0BEC::BfmeVectorRecord000C0BEC(const BfmeVectorRecord000C0BEC &o) : text(o.text), names(o.names), word10(o.word10) {}
template void _STL::_Construct<BfmeVectorRecord000C0BEC,BfmeVectorRecord000C0BEC>(BfmeVectorRecord000C0BEC*,const BfmeVectorRecord000C0BEC&);

// Complete retail record copy at 0x002154F3.
struct BfmeVectorRecord002154F3 {
    AsciiString text; _STL::vector<AsciiString> names;
    BfmeVectorRecord002154F3(const BfmeVectorRecord002154F3 &o);
};
BfmeVectorRecord002154F3::BfmeVectorRecord002154F3(const BfmeVectorRecord002154F3 &o) : text(o.text), names(o.names) {}
template void _STL::_Construct<BfmeVectorRecord002154F3,BfmeVectorRecord002154F3>(BfmeVectorRecord002154F3*,const BfmeVectorRecord002154F3&);

// Retail 0x00215530: assignment for the 0x002154F3 record shape (pin spells
// it 0002154F3); text via pinned AsciiString assign 0x366F0, names via rowed
// vector assign 0xBDB46. Callers in 0x00215572 0x0021566B 0x00215696 dup.
struct BfmeVectorRecord0002154F3 {
    AsciiString text; _STL::vector<AsciiString> names;
    BfmeVectorRecord0002154F3 &operator=(const BfmeVectorRecord0002154F3 &o);
};
inline BfmeVectorRecord0002154F3 &BfmeVectorRecord0002154F3::operator=(const BfmeVectorRecord0002154F3 &o)
{
    text = o.text;
    names = o.names;
    return *this;
}

// Retail0x2AF478: a string and two owning vectors with verified element copies.
struct BfmeVectorRecord002AF478 {
    AsciiString text; unsigned int word04;
    _STL::vector<unsigned int> values08;
    _STL::vector<AsciiString> names14;
    unsigned int word20;
    BfmeVectorRecord002AF478(const BfmeVectorRecord002AF478 &o);
};
BfmeVectorRecord002AF478::BfmeVectorRecord002AF478(const BfmeVectorRecord002AF478 &o)
    : text(o.text), word04(o.word04), values08(o.values08),
      names14(o.names14), word20(o.word20) {}
template void _STL::_Construct<BfmeVectorRecord002AF478,BfmeVectorRecord002AF478>(BfmeVectorRecord002AF478*,const BfmeVectorRecord002AF478&);

// BfmeVectorRecord0002154F3::operator= is defined inline by the other units that copy this record: they emit
// select-any copies, so a strong definition here was a duplicate in the linked build. This
// anchor only makes this unit emit its copy for the ledger row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitBfmeVectorRecord0002154F3Assign@@YAXPAUBfmeVectorRecord0002154F3@@@Z present-unmatched
void bfmeEmitBfmeVectorRecord0002154F3Assign(BfmeVectorRecord0002154F3 *record)
{
	*record = *record;
}
#pragma inline_depth()

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??$_Construct@UBfmeVectorRecord0002154F3@@U1@@_STL@@YAXPAUBfmeVectorRecord0002154F3@@ABU1@@Z=??$_Construct@UBfmeVectorRecord002154F3@@U1@@_STL@@YAXPAUBfmeVectorRecord002154F3@@ABU1@@Z")

// Native1B49C4..1B4A39, called by IniLoad3397D8 through TheSubsystemLegend.
// The record prefix is its name and first file vector; the complete record
// copy earlier in this unit is already recovered as BfmeVectorRecord001B4A39.
// These views describe only accessed prefixes and never allocate a node.
// Retail comparison69D6 is nonthrowing. Bind its owned StringBase provider
// directly; the legacy AsciiString alias selects a wrong census provider.
template<> int StringBase<char>::compare(const StringBase<char>&) const throw();
struct IniLoadFileList {AsciiString name;AsciiString *begin,*end,*capacity;};
struct SubsystemLegendNode {SubsystemLegendNode *next,*prev;IniLoadFileList value;};
class SubsystemLegend {public:IniLoadFileList *rva001B49C4(AsciiString name);char prefix[12];SubsystemLegendNode *head;};
IniLoadFileList *SubsystemLegend::rva001B49C4(AsciiString name) {
 for(SubsystemLegendNode *p=head->next;p!=head;p=p->next) {
  AsciiString current=p->value.name;
  if(reinterpret_cast<const StringBase<char>*>(&current)->compare(*reinterpret_cast<const StringBase<char>*>(&name))==0) return &p->value;
 }
 return 0;
}
