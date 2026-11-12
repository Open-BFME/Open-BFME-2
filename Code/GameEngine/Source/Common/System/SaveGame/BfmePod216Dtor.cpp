// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1CreateAHeroSubClass@CreateAHeroManager@@QAE@XZ 0x0021E50F 164B.
// CreateAHeroManager::CreateAHeroSubClass destructor. Identity: retail
// parseCreateAHeroSubClass (WB 0x00B80730) builds its local at ebp-0x104 with
// the rowed subclass ctor 0x0021E793 then push_backs it (0x0021FAAE) and
// destroys it here at 0x0021FD9D (unwind funclet 0x0076EB87 too); WB's twin
// call 0x00B80E56 lands on sub_B76770 which destroys the same members in the
// same order. Members follow the ctor's 216-byte layout: tree +0x54 via
// 0x0021D61F, int map +0x48 via 0x0021B775, vectors +0x3C/+0x30 via free
// 0x00030830, int-vector map +0x24 via 0x0021E0FC, strings +0x20/+0x0C/+0x08/
// +0x04/+0x00 via releaseBuffer 0x00036410. Other callers: ??_G 0x0021E77A,
// __destroy_aux 0x0021F188, _Destroy 0x0021F0F4.
#include <vector>
#include <map>
#include <set>
#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::~_Rb_tree(); }
namespace _STL { template <> void _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::clear(); }
// bfme link decl-only end

enum ScienceType
{
    SCIENCE_INVALID = 0
};

#include "../../../../Include/Common/BfmeStringRecord0021A940.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void _Rb_tree<BfmeStringRecord0021A940,BfmeStringRecord0021A940,_Identity<BfmeStringRecord0021A940>,less<BfmeStringRecord0021A940>,allocator<BfmeStringRecord0021A940> >::_M_erase(_Rb_tree_node<BfmeStringRecord0021A940> *); }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void _Destroy<BfmeStringRecord0021A940>(BfmeStringRecord0021A940 *); }

typedef _STL::map<int, _STL::vector<unsigned int> > IntegerVectorMap;
typedef _STL::map<int, int> IntegerMap;
typedef _STL::set<BfmeStringRecord0021A940> BfmeStringSet;

#include "../../../../Include/GameLogic/CreateAHeroManager.h"

class CreateAHeroManager::CreateAHeroSubClass
{
    AsciiString m_00;
    AsciiString m_04;
    AsciiString m_08;
    AsciiString m_0c;
    int m_10;
    int m_14;
    int m_18;
    int m_1c;
    AsciiString m_20;
    IntegerVectorMap m_24;
    _STL::vector<ScienceType> m_30;
    _STL::vector<ScienceType> m_3c;
    IntegerMap m_48;
    BfmeStringSet m_54;
public:
    ~CreateAHeroSubClass();
};

CreateAHeroManager::CreateAHeroSubClass::~CreateAHeroSubClass()
{
}
