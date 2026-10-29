// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport46
// BFME2 records containing AsciiString and STLport vector<AsciiString>.
// The vector copy is the established 93-byte constructor at 0xBC07E.
// Layouts are read from the complete retail constructors and their STLport
// placement-copy callers. Application names and scalar meanings are unknown.
// String semantics follow BFME1 AsciiString/UnicodeString: the inline derived
// copies call StringBase<char>0x365F0 or StringBase<unsigned short>0x37050.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <memory>
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> vector<unsigned int,allocator<unsigned int> >::~vector(); }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> _Vector_base<unsigned int,allocator<unsigned int> >::~_Vector_base(); }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> _Vector_base<unsigned int,allocator<unsigned int> >::_Vector_base(unsigned int,allocator<unsigned int> const &); }
// bfme link decl-only begin
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
// bfme link decl-only end

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
template <> vector<AsciiString, allocator<AsciiString> > &vector<AsciiString, allocator<AsciiString> >::operator=(const vector<AsciiString, allocator<AsciiString> >&);
}

// Complete retail record copy at 0x000BDF17.
struct BfmeVectorRecord000BDF17 {
    _STL::vector<AsciiString> names; AsciiString text0, text1; unsigned int word14, word18, word1C, word20, word24, word28; unsigned char flag2C, flag2D; unsigned int word30, word34, word38; unsigned char flag3C;
    BfmeVectorRecord000BDF17(const BfmeVectorRecord000BDF17 &other);
};
BfmeVectorRecord000BDF17::BfmeVectorRecord000BDF17(const BfmeVectorRecord000BDF17 &other) : names(other.names), text0(other.text0), text1(other.text1), word14(other.word14), word18(other.word18), word1C(other.word1C), word20(other.word20), word24(other.word24), word28(other.word28), flag2C(other.flag2C), flag2D(other.flag2D), word30(other.word30), word34(other.word34), word38(other.word38), flag3C(other.flag3C) {}
template void _STL::_Construct<BfmeVectorRecord000BDF17,BfmeVectorRecord000BDF17>(BfmeVectorRecord000BDF17*,const BfmeVectorRecord000BDF17&);

// Complete retail record copy at 0x001B4A39.
struct BfmeVectorRecord001B4A39 {
    AsciiString text0; _STL::vector<AsciiString> names0, names1, names2, names3, names4; unsigned int word40; AsciiString text1;
    BfmeVectorRecord001B4A39(const BfmeVectorRecord001B4A39 &other);
    ~BfmeVectorRecord001B4A39();
};
BfmeVectorRecord001B4A39::BfmeVectorRecord001B4A39(const BfmeVectorRecord001B4A39 &other) : text0(other.text0), names0(other.names0), names1(other.names1), names2(other.names2), names3(other.names3), names4(other.names4), word40(other.word40), text1(other.text1) {}
BfmeVectorRecord001B4A39::~BfmeVectorRecord001B4A39() {}
template void _STL::_Construct<BfmeVectorRecord001B4A39,BfmeVectorRecord001B4A39>(BfmeVectorRecord001B4A39*,const BfmeVectorRecord001B4A39&);

// Complete retail record copy at 0x000C0BEC.
struct BfmeVectorRecord000C0BEC {
    AsciiString text; _STL::vector<AsciiString> names; unsigned int word10;
    BfmeVectorRecord000C0BEC(const BfmeVectorRecord000C0BEC &other);
};
BfmeVectorRecord000C0BEC::BfmeVectorRecord000C0BEC(const BfmeVectorRecord000C0BEC &other) : text(other.text), names(other.names), word10(other.word10) {}
template void _STL::_Construct<BfmeVectorRecord000C0BEC,BfmeVectorRecord000C0BEC>(BfmeVectorRecord000C0BEC*,const BfmeVectorRecord000C0BEC&);

// Complete retail record copy at 0x002154F3 and assignment at 0x00215530:
// text via pinned AsciiString assign 0x366F0, names via rowed vector assign
// 0xBDB46. Callers in 0x00215572 0x0021566B 0x00215696 dup.
struct BfmeVectorRecord0002154F3 {
    AsciiString text; _STL::vector<AsciiString> names;
    BfmeVectorRecord0002154F3(const BfmeVectorRecord0002154F3 &other);
    BfmeVectorRecord0002154F3 &operator=(const BfmeVectorRecord0002154F3 &other);
};
BfmeVectorRecord0002154F3::BfmeVectorRecord0002154F3(const BfmeVectorRecord0002154F3 &other) : text(other.text), names(other.names) {}
template void _STL::_Construct<BfmeVectorRecord0002154F3,BfmeVectorRecord0002154F3>(BfmeVectorRecord0002154F3*,const BfmeVectorRecord0002154F3&);
BfmeVectorRecord0002154F3 &BfmeVectorRecord0002154F3::operator=(const BfmeVectorRecord0002154F3 &other)
{
    text = other.text;
    names = other.names;
    return *this;
}

// Retail0x2AF478: a string and two owning vectors with verified element copies.
struct BfmeVectorRecord002AF478 {
    AsciiString text; unsigned int word04;
    _STL::vector<unsigned int> values08;
    _STL::vector<AsciiString> names14;
    unsigned int word20;
    BfmeVectorRecord002AF478(const BfmeVectorRecord002AF478 &other);
};
BfmeVectorRecord002AF478::BfmeVectorRecord002AF478(const BfmeVectorRecord002AF478 &other)
    : text(other.text), word04(other.word04), values08(other.values08),
      names14(other.names14), word20(other.word20) {}
template void _STL::_Construct<BfmeVectorRecord002AF478,BfmeVectorRecord002AF478>(BfmeVectorRecord002AF478*,const BfmeVectorRecord002AF478&);

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
 for(SubsystemLegendNode *subsystemLegendNode=head->next;subsystemLegendNode!=head;subsystemLegendNode=subsystemLegendNode->next) {
  AsciiString current=subsystemLegendNode->value.name;
  if(reinterpret_cast<const StringBase<char>*>(&current)->compare(*reinterpret_cast<const StringBase<char>*>(&name))==0) return &subsystemLegendNode->value;
 }
 return 0;
}
