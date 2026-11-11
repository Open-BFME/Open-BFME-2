// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??4CreateAHeroSubClass@CreateAHeroManager@@QAEAAV01@ABV01@@Z 0x0021E5B3 192B.
// CreateAHeroManager::CreateAHeroSubClass copy assignment, beside its rowed
// destructor 0x0021E50F (BfmePod216Dtor.cpp, whose member order this follows):
// a self check, then the strings +0x00..+0x0C through StringBase<char>::set
// (0x000366F0), the ints +0x10..+0x1C, the string +0x20, the int-vector map
// +0x24 (tree operator= 0x0021DD0E), the vectors +0x30/+0x3C (operator=
// 0x0021C21B), the map +0x48 (tree operator= 0x0021C33F), the set +0x54 (tree
// operator= 0x0021D842), the bool +0x60, the ints +0x64/+0x68 and a 27-dword
// block at +0x6C copied whole (rep movsd), which fills the 216-byte layout.
// The container element types use the spellings their rowed operations carry.
#include <vector>
#include <map>
#include <set>
#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree_node<pair<int const, vector<unsigned int, allocator<unsigned int> > > > * _Rb_tree<int, pair<int const, vector<unsigned int, allocator<unsigned int> > >, _Select1st<pair<int const, vector<unsigned int, allocator<unsigned int> > > >, less<int>, allocator<pair<int const, vector<unsigned int, allocator<unsigned int> > > > >::_M_copy(_Rb_tree_node<pair<int const, vector<unsigned int, allocator<unsigned int> > > > *, _Rb_tree_node<pair<int const, vector<unsigned int, allocator<unsigned int> > > > *); }
namespace _STL { template <> _Rb_tree_node<pair<int const, vector<unsigned int, allocator<unsigned int> > > > * _Rb_tree<int, pair<int const, vector<unsigned int, allocator<unsigned int> > >, _Select1st<pair<int const, vector<unsigned int, allocator<unsigned int> > > >, less<int>, allocator<pair<int const, vector<unsigned int, allocator<unsigned int> > > > >::_M_create_node(pair<int const, vector<unsigned int, allocator<unsigned int> > > const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$_Destroy@UBfmeStringRecord0021A940@@@_STL@@YAXPAUBfmeStringRecord0021A940@@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeStringRecord0021A940;
namespace _STL { template <> void _Destroy<BfmeStringRecord0021A940>(BfmeStringRecord0021A940 *); }
// Suppress this TU's non-retail copy of ?_M_copy@?$_Rb_tree@UBfmeStringRecord0021A940@@U1@U?$_Identity@UBfmeStringRecord0021A940@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeStringRecord0021A940;
namespace _STL { template <> _Rb_tree_node<BfmeStringRecord0021A940> * _Rb_tree<BfmeStringRecord0021A940,BfmeStringRecord0021A940,_Identity<BfmeStringRecord0021A940>,less<BfmeStringRecord0021A940>,allocator<BfmeStringRecord0021A940> >::_M_copy(_Rb_tree_node<BfmeStringRecord0021A940> *,_Rb_tree_node<BfmeStringRecord0021A940> *); }
// Suppress this TU's non-retail copy of ?_M_erase@?$_Rb_tree@UBfmeStringRecord0021A940@@U1@U?$_Identity@UBfmeStringRecord0021A940@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeStringRecord0021A940;
namespace _STL { template <> void _Rb_tree<BfmeStringRecord0021A940,BfmeStringRecord0021A940,_Identity<BfmeStringRecord0021A940>,less<BfmeStringRecord0021A940>,allocator<BfmeStringRecord0021A940> >::_M_erase(_Rb_tree_node<BfmeStringRecord0021A940> *); }
// Suppress this TU's non-retail copy of ??4?$vector@URva0021C21BElement@@V?$allocator@URva0021C21BElement@@@_STL@@@_STL@@QAEAAV01@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0021C21BElement;
namespace _STL { template <> vector<Rva0021C21BElement,allocator<Rva0021C21BElement> > & vector<Rva0021C21BElement,allocator<Rva0021C21BElement> >::operator=(vector<Rva0021C21BElement,allocator<Rva0021C21BElement> > const &); }

#include "../../../../../Libraries/Source/WWVegas/WWLib/Rva0021C21BElement.h"
struct Rva0021C33FElement
{
    int words[1];
    bool operator<(const Rva0021C33FElement &b) const { return words[0] < b.words[0]; }
};
struct BfmeStringRecord0021A940 { unsigned char m_data[20]; };
bool operator<(const BfmeStringRecord0021A940 &a, const BfmeStringRecord0021A940 &b);

struct Rva0021E5B3Block { int words[27]; };

#include "../../../../Include/GameLogic/CreateAHeroManager.h"

class CreateAHeroManager::CreateAHeroSubClass
{
public:
    CreateAHeroSubClass &operator=(const CreateAHeroSubClass &that);
private:
    AsciiString m_00;
    AsciiString m_04;
    AsciiString m_08;
    AsciiString m_0c;
    int m_10;
    int m_14;
    int m_18;
    int m_1c;
    AsciiString m_20;
    _STL::map<int, _STL::vector<unsigned int> > m_24;
    _STL::vector<Rva0021C21BElement> m_30;
    _STL::vector<Rva0021C21BElement> m_3c;
    _STL::map<Rva0021C33FElement, int> m_48;
    _STL::set<BfmeStringRecord0021A940> m_54;
    bool m_60;
    int m_64;
    int m_68;
    Rva0021E5B3Block m_6c;
};

CreateAHeroManager::CreateAHeroSubClass &CreateAHeroManager::CreateAHeroSubClass::operator=(const CreateAHeroSubClass &that)
{
    if (this != &that) {
        m_00 = that.m_00;
        m_04 = that.m_04;
        m_08 = that.m_08;
        m_0c = that.m_0c;
        m_10 = that.m_10;
        m_14 = that.m_14;
        m_18 = that.m_18;
        m_1c = that.m_1c;
        m_20 = that.m_20;
        m_24 = that.m_24;
        m_30 = that.m_30;
        m_3c = that.m_3c;
        m_48 = that.m_48;
        m_54 = that.m_54;
        m_60 = that.m_60;
        m_64 = that.m_64;
        m_68 = that.m_68;
        m_6c = that.m_6c;
    }
    return *this;
}
