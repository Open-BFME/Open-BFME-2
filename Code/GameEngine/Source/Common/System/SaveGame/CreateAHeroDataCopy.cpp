// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// CreateAHeroData is identified by retail typeName0x409353 and vtable0xC38D88.
// Its copy and destructor establish this0x140-byte Snapshot-derived layout.
// Container identities follow the independently recovered copy-call chains:
// int/int trees21CF2C; AsciiString payload tree40884B; bit-vector389413;
// int/vector<unsigned> tree21E146. Unknown application fields stay offset-named.
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#define _STLP_TRIVIAL_DESTRUCTOR_BUG // Declare pair destruction for explicit specialization.
#include <memory>
#include <vector>
#include <map>

#include "ascii_string.h"
#include "unicode_string.h"
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::_Rb_tree(_Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > > const &); }
namespace _STL { template <> _Rb_tree_node<pair<int const, int> > * _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::_M_copy(_Rb_tree_node<pair<int const, int> > *, _Rb_tree_node<pair<int const, int> > *); }
namespace _STL { template <> AsciiString * __uninitialized_copy<AsciiString const *, AsciiString *>(AsciiString const *, AsciiString const *, AsciiString *, __false_type const &); }
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> copy<_Bit_iter<bool, bool const *>, _Bit_iter<_Bit_reference, _Bit_reference *> >(_Bit_iter<bool, bool const *>, _Bit_iter<bool, bool const *>, _Bit_iter<_Bit_reference, _Bit_reference *>); }
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *>::_Bit_iter(); }
namespace _STL { template <> _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::~_Rb_tree(); }
namespace _STL { template <> _Rb_tree_node<pair<int const, vector<unsigned int, allocator<unsigned int> > > > * _Rb_tree<int, pair<int const, vector<unsigned int, allocator<unsigned int> > >, _Select1st<pair<int const, vector<unsigned int, allocator<unsigned int> > > >, less<int>, allocator<pair<int const, vector<unsigned int, allocator<unsigned int> > > > >::_M_copy(_Rb_tree_node<pair<int const, vector<unsigned int, allocator<unsigned int> > > > *, _Rb_tree_node<pair<int const, vector<unsigned int, allocator<unsigned int> > > > *); }
namespace _STL { template <> _Rb_tree_node<pair<int const, vector<unsigned int, allocator<unsigned int> > > > * _Rb_tree<int, pair<int const, vector<unsigned int, allocator<unsigned int> > >, _Select1st<pair<int const, vector<unsigned int, allocator<unsigned int> > > >, less<int>, allocator<pair<int const, vector<unsigned int, allocator<unsigned int> > > > >::_M_create_node(pair<int const, vector<unsigned int, allocator<unsigned int> > > const &); }
namespace _STL { template <> void _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::clear(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??1?$_Bvector_base@V?$allocator@_N@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Bvector_base<allocator<bool> >::~_Bvector_base(); }
// Suppress this TU's non-retail copy of ??0?$_Bvector_base@V?$allocator@_N@_STL@@@_STL@@QAE@ABV?$allocator@_N@1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Bvector_base<allocator<bool> >::_Bvector_base(const allocator<bool> &); }
namespace _STL { template <> vector<bool>::~vector(); }
class Xfer;
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
struct TreeHintPayload001F8ACB { unsigned int value; };
bool operator<(const AsciiString &, const AsciiString &);
namespace _STL { template <> pair<const AsciiString, TreeHintPayload001F8ACB>::~pair(); }
// Scalar-vector copy is supplied by the complete retail 0x002CFAB9 provider.
namespace _STL {
template <> vector<unsigned int>::vector(const vector<unsigned int> &);
}
// The copy below calls vector<AsciiString>'s copy constructor (REL32); its
// retail body (0x000BC07E, with EH frame) is supplied by
// stlport_vector_asciistring_copy_backward.cpp. This TU's /EHs copy is not
// retail's, and from this unit's link place (0x00069F75) it would be kept.
namespace _STL {
template <> vector<AsciiString>::vector(const vector<AsciiString> &);
}

typedef _STL::map<int,int> IntegerMap;
typedef _STL::map<AsciiString,TreeHintPayload001F8ACB> StringPayloadMap;
typedef _STL::map<int,_STL::vector<unsigned int> > IntegerVectorMap;

// Recovered separately: default5C39DE/13 and assignment406E22/37.
// The implicit destructor is the complete5-byte release tail at48BA39.
struct BfmeHeroElement005C39DE {
    AsciiString text;
    unsigned int word4, word8;
    BfmeHeroElement005C39DE();
    ~BfmeHeroElement005C39DE();
    BfmeHeroElement005C39DE &operator=(const BfmeHeroElement005C39DE &);
};
class CreateAHeroData;
// Retail searches the pointer registry atVA DFE358 and appends if absent.
void RegisterCreateAHeroAtRva0021D517(CreateAHeroData *);

class CreateAHeroData : public Snapshot {
    unsigned int word04;
    UnicodeString text08;
    unsigned int word0C, word10;
    IntegerMap map14, map20;
    unsigned int word2C, word30, word34, word38;
    _STL::vector<AsciiString> strings3C;
    unsigned char flag48;
    AsciiString text4C;
    StringPayloadMap map50;
    _STL::vector<bool> bits5C;
    unsigned char flag70, flag71;
    IntegerVectorMap map74;
    BfmeHeroElement005C39DE elements80[15];
    unsigned int word134, word138, word13C;
public:
    CreateAHeroData(const CreateAHeroData &createAHeroData)
        : Snapshot(createAHeroData), word04(createAHeroData.word04), text08(createAHeroData.text08),
          word0C(createAHeroData.word0C), word10(createAHeroData.word10), map14(createAHeroData.map14), map20(createAHeroData.map20),
          word2C(createAHeroData.word2C), word30(createAHeroData.word30), word34(createAHeroData.word34), word38(0x2FF),
          strings3C(createAHeroData.strings3C), flag48(createAHeroData.flag48), text4C(createAHeroData.text4C),
          map50(createAHeroData.map50), bits5C(createAHeroData.bits5C), flag70(0), flag71(createAHeroData.flag71),
          map74(createAHeroData.map74), elements80(), word134(createAHeroData.word134),
          word138(createAHeroData.word138), word13C(createAHeroData.word13C)
    {
        for (int i = 0; i < 15; ++i)
            elements80[i] = createAHeroData.elements80[i];
        RegisterCreateAHeroAtRva0021D517(this);
    }
    virtual ~CreateAHeroData();
    virtual void crc(Xfer *xfer);
    virtual void xfer(Xfer *xfer);
protected:
    virtual void loadPostProcess();
public:
};
template void _STL::_Construct<CreateAHeroData,CreateAHeroData>(CreateAHeroData *,const CreateAHeroData &);

// Retail's CreateAHeroData vftable (0x00C38D88) holds ??_G, the empty virtual 0x000B3FD0,
// GetSnapshotName 0x00409353 in slot 2 and the xfer 0x00408C11 in slot 3. Snapshot's crc stands
// in for slot 2 (see Snapshot.h), so bind the two placeholders to the rows at those addresses.
#pragma comment(linker, "/alternatename:?crc@CreateAHeroData@@UAEXPAVXfer@@@Z=?GetSnapshotName@CreateAHeroData@@UBEPBDXZ")
#pragma comment(linker, "/alternatename:?xfer@CreateAHeroData@@UAEXPAVXfer@@@Z=?DoXfer@CreateAHeroHero@@QAEXAAVXfer@@@Z")
