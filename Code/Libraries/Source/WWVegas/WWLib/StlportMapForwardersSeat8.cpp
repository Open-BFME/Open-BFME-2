// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// Five-byte STLport container forwarders from unrowed .text gaps: each is a
// bare tail jump from the container's inline member to the rowed tree or
// vector member it forwards to (map/set::clear -> _Rb_tree::clear,
// map::swap -> _Rb_tree::swap, vector::insert(pos, n, x) ->
// _M_fill_insert). The callees are only declared so the calls stay out of
// line; element and key types are the ledger's spellings for those rows.
#include <hash_map>
#include <map>
#include <set>
#include <stack>
#include <vector>
#include "ascii_string.h"

class NamedTimerInfo;
struct TreeHintPayload001F8ACB;
struct Coord3D;
struct BfmeStringRecord002CF550;
struct BfmeVectorRecord0002154F3;
enum ScienceType { SCIENCE_INVALID = -1 };

typedef _STL::map<AsciiString, NamedTimerInfo *> MapA;                       // 0x002A3F56
typedef _STL::map<AsciiString, TreeHintPayload001F8ACB> MapB;          // 0x002C6C8E
typedef _STL::map<AsciiString, Coord3D> MapC;                          // 0x00301EC2
typedef _STL::map<_STL::pair<AsciiString, AsciiString>, int> MapD;     // 0x0032C366
typedef _STL::set<BfmeStringRecord002CF550> SetE;                     // 0x0033D000
typedef _STL::map<int, int> MapF;                                      // 0x0032B4AD
typedef _STL::vector<BfmeVectorRecord0002154F3> VecG;                  // 0x00215A88
typedef _STL::vector<float> VecH;                                      // 0x0030E90B
typedef _STL::vector<_STL::vector<ScienceType> > VecI;                 // 0x0033A271

namespace _STL {
template <> void MapA::_Rep_type::clear();   // 0x002A1B9D
template <> void MapB::_Rep_type::clear();   // 0x001F8927
template <> void MapC::_Rep_type::clear();   // 0x0022D160
template <> void MapD::_Rep_type::clear();   // 0x0032BEBF
template <> void SetE::_Rep_type::clear();   // 0x002572AE
template <> void MapF::_Rep_type::swap(MapF::_Rep_type &);   // 0x0032AC92
template <> void VecG::_M_fill_insert(VecG::iterator, VecG::size_type, const VecG::value_type &);   // 0x00215949
template <> void VecH::_M_fill_insert(VecH::iterator, VecH::size_type, const VecH::value_type &);   // 0x0030E7FE
template <> void VecI::_M_fill_insert(VecI::iterator, VecI::size_type, const VecI::value_type &);   // 0x0033A05E
}

template void MapA::clear();
template void MapB::clear();
template void MapC::clear();
template void MapD::clear();
template void SetE::clear();
template void MapF::swap(MapF &);
template void VecG::insert(VecG::iterator, VecG::size_type, const VecG::value_type &);
template void VecH::insert(VecH::iterator, VecH::size_type, const VecH::value_type &);
template void VecI::insert(VecI::iterator, VecI::size_type, const VecI::value_type &);

// holder destructors (5B each), tail jumps to the rowed _Rb_tree destructors:
//   0x002F1C55 -> 0x002F0B8A, 0x002F1C5A -> 0x002F0BB5, 0x0032C62D -> 0x0032C36B
struct Rva002F0B8AElement;
struct Rva002F0BB5Element;
typedef _STL::map<int, Rva002F0B8AElement> MapJ;
typedef _STL::map<int, Rva002F0BB5Element> MapK;
typedef _STL::pair<const int, Rva002F0B8AElement> ValJ;
typedef _STL::pair<const int, Rva002F0BB5Element> ValK;
typedef _STL::pair<AsciiString, AsciiString> KeyD;
typedef _STL::pair<const KeyD, int> ValD;
namespace _STL {
template <> _Rb_tree<int, ValJ, _Select1st<ValJ>, less<int>, allocator<ValJ> >::~_Rb_tree();
template <> _Rb_tree<int, ValK, _Select1st<ValK>, less<int>, allocator<ValK> >::~_Rb_tree();
template <> _Rb_tree<KeyD, ValD, _Select1st<ValD>, less<KeyD>, allocator<ValD> >::~_Rb_tree();
}
// The owners holding each map as their only member are not recovered, so
// the destructors are spelled on address-named holders.
class Rva002F1C55 { public: ~Rva002F1C55(); private: MapJ m_map; };
Rva002F1C55::~Rva002F1C55() {}
class Rva002F1C5A { public: ~Rva002F1C5A(); private: MapK m_map; };
Rva002F1C5A::~Rva002F1C5A() {}
class Rva0032C62D { public: ~Rva0032C62D(); private: MapD m_map; };
Rva0032C62D::~Rva0032C62D() {}

// 0x002BC5C4 (5B): vector<Rva002BC47DElement>::insert(pos, n, x) -> rowed
// _M_fill_insert 0x002BC47D (StlSweepW4Rva002BC47D.cpp stand-in).
struct Rva002BC47DElement { Rva002BC47DElement();Rva002BC47DElement(const Rva002BC47DElement&);~Rva002BC47DElement();Rva002BC47DElement&operator=(const Rva002BC47DElement&);char bytes[52]; bool operator<(const Rva002BC47DElement&)const; bool operator==(const Rva002BC47DElement&)const; };
typedef _STL::vector<Rva002BC47DElement> VecL;
namespace _STL {
template <> void VecL::_M_fill_insert(VecL::iterator, VecL::size_type, const VecL::value_type &);
}
template void VecL::insert(VecL::iterator, VecL::size_type, const VecL::value_type &);

// Additional 5-byte STLport container and holder forwarders:
struct Rva00051B89Keyed;
struct Rva00051B89Hash { unsigned int operator()(Rva00051B89Keyed *const &) const; };
typedef _STL::hashtable<Rva00051B89Keyed *, Rva00051B89Keyed *, Rva00051B89Hash, _STL::_Identity<Rva00051B89Keyed *>, _STL::equal_to<Rva00051B89Keyed *>, _STL::allocator<Rva00051B89Keyed *> > HTableA;
struct EvaMessageInfo { ~EvaMessageInfo(); };
enum NameKeyType { NAMEKEY_INVALID = 0 };
class Rva001E2747;
namespace rts { template <class T> struct hash { unsigned int operator()(const T &) const; }; }
class Rva00548984;
struct BfmeE8 { int a[2]; };
struct TreeOpaqueMapped00372FF4;
struct Rva0021A917Element { short words[1]; bool operator<(const Rva0021A917Element &b) const { return words[0] < b.words[0]; } };
struct TreeHintOpaque0043671B;
enum ObjectID { INVALID_ID = 0 };
struct Rva004D751DElement { short words[1]; bool operator<(const Rva004D751DElement &b) const { return words[0] < b.words[0]; } };
#include "../../../../GameEngine/Include/Common/Rva00064640Record.h"
template <int N> class BitFlags {};
class WeaponTemplateSet;
template <class T, class F> class SparseMatchFinder {
public:
	struct MapHelper { bool operator()(const F &, const F &) const; };
	~SparseMatchFinder() {}
private:
	_STL::map<const F, const T *, MapHelper> m_bestMatches;
};

typedef _STL::hash_map<NameKeyType, Rva001E2747 *, rts::hash<NameKeyType>, _STL::equal_to<NameKeyType> > HMapA;                 // 0x002418DD
typedef _STL::hash_map<int, Rva00548984 *> HMapB;                                                                               // 0x002BF338
typedef _STL::map<int, _STL::vector<_STL::vector<BfmeE8> > > MapN;                                                              // 0x0032EC21
typedef _STL::map<float, TreeOpaqueMapped00372FF4> MapO;                                                                        // 0x00372F7F
typedef _STL::map<unsigned int, void *> MapP;                                                                                   // 0x0039C023
typedef _STL::stack<void *, _STL::deque<void *> > StackA;                                                                       // 0x003B55FE
typedef _STL::map<Rva0021A917Element, int> MapQ;                                                                                // 0x004075A3
typedef _STL::map<AsciiString, TreeHintOpaque0043671B> MapR;                                                                    // 0x00435AFB
typedef _STL::map<ObjectID, int> MapS;                                                                                // 0x0046AAD9
typedef _STL::map<Rva004D751DElement, int> MapT;                                                                                // 0x004D755A
typedef _STL::multimap<int, void *> MapU;                                                                                       // 0x004FFBD2
typedef _STL::set<Rva00064640Record> SetV;                                                                                      // 0x00504491
typedef _STL::map<const BitFlags<17>, const WeaponTemplateSet *, SparseMatchFinder<WeaponTemplateSet, BitFlags<17> >::MapHelper> MapW; // 0x00604460

typedef _STL::pair<const NameKeyType, Rva001E2747 *> ValHMapA;
typedef _STL::hashtable<ValHMapA, NameKeyType, rts::hash<NameKeyType>, _STL::_Select1st<ValHMapA>, _STL::equal_to<NameKeyType>, _STL::allocator<ValHMapA> > HTableHMapA;
typedef _STL::pair<const int, Rva00548984 *> ValHMapB;
typedef _STL::hashtable<ValHMapB, int, _STL::hash<int>, _STL::_Select1st<ValHMapB>, _STL::equal_to<int>, _STL::allocator<ValHMapB> > HTableHMapB;

typedef _STL::pair<const BitFlags<17>, const WeaponTemplateSet *> ValW;

namespace _STL {
template <> HTableA::size_type HTableA::_M_bkt_num_key(const HTableA::key_type &) const;   // 0x00053EA8
template <> vector<EvaMessageInfo>::~vector();                                              // 0x000B0254
template <> void HTableHMapA::resize(HTableHMapA::size_type);                               // 0x0053F1EC
template <> HTableHMapB::size_type HTableHMapB::erase(const HTableHMapB::key_type &);       // 0x0054883B
template <> void MapN::_Rep_type::clear();                                                  // 0x0032EB5E
template <> void MapO::_Rep_type::clear();                                                  // 0x00372F2D
template <> void MapP::_Rep_type::clear();                                                  // 0x00357416
template <> void deque<void *>::pop_back();                                                 // 0x003B445C
template <> void MapQ::_Rep_type::clear();                                                  // 0x0021A917
template <> void MapR::_Rep_type::clear();                                                  // 0x0043534F
template <> void MapS::_Rep_type::clear();                                                  // 0x00286656
template <> void MapT::_Rep_type::clear();                                                  // 0x004D751D
template <> MapU::size_type MapU::_Rep_type::count(const int &) const;                      // 0x004FF8B1
template <> void SetV::_Rep_type::clear();                                                  // 0x002B70B3
template <> _Rb_tree<const BitFlags<17>, ValW, _Select1st<ValW>, SparseMatchFinder<WeaponTemplateSet, BitFlags<17> >::MapHelper, allocator<ValW> >::~_Rb_tree(); // 0x00604396
}

template HTableA::size_type HTableA::_M_bkt_num(const HTableA::value_type &) const;
template void HMapA::resize(HMapA::size_type);
template HMapB::size_type HMapB::erase(const HMapB::key_type &);
template void MapN::clear();
template void MapO::clear();
template void MapP::clear();
template void StackA::pop();
template void MapQ::clear();
template void MapR::clear();
template void MapS::clear();
template void MapT::clear();
template MapU::size_type MapU::count(const int &) const;
template void SetV::clear();
template SparseMatchFinder<WeaponTemplateSet, BitFlags<17> >::~SparseMatchFinder();

class Rva000B0560 { public: ~Rva000B0560(); private: _STL::vector<EvaMessageInfo> m_vec; };
Rva000B0560::~Rva000B0560() {}

class AnimationSoundTree { public: ~AnimationSoundTree(); private: int m_0; int m_4; };
class Rva004CA6D5 { public: ~Rva004CA6D5(); private: AnimationSoundTree m_tree; };
Rva004CA6D5::~Rva004CA6D5() {}

