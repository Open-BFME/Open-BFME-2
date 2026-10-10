// cl: /O1 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?clear@TeamFactory@@QAEXXZ -- retail 0x003A2F4C..0x003A2FD4 (136 bytes).
// Target identity: WorldBuilder 0x00EED0E0 and the TeamFactory caller family;
// retail copies the 12-byte tree at +0xB0 using 0x003A299C; clears the
// original at 0x0039F56E; destroys each +0x18 prototype through virtual slot
// zero with deleting flag zero before global delete; then zeros +0x10..+0xAF.
// Donor purpose: ZH Team.cpp TeamFactory::clear copies its prototype map
// before destruction because each prototype can remove itself from the map.
// BFME 1 donor revision: 575ba2b04743f190f069805fbdc59936123c45da.
// Structural inference: the existing CopyTree/BfmePod8 ABI names describe
// the owned copy constructor, not proof that retail's semantic key is int.
// The second payload word holds the prototype; the first remains opaque.
#include <map>
#include <string.h>
struct BfmePod8 { int words[2]; };
typedef _STL::_Rb_tree<int,_STL::pair<const int,BfmePod8>,_STL::_Select1st<_STL::pair<const int,BfmePod8> >,_STL::less<int>,_STL::allocator<_STL::pair<const int,BfmePod8> > > CopyTree;
class Rva0039F56E:public CopyTree{public:void rva0039F56E();~Rva0039F56E();};
class TeamPrototype{public:virtual ~TeamPrototype();};
class TeamFactory{public:void clear();private:char unknown00[0x10];TeamPrototype*m_dummyTeams[40];Rva0039F56E m_prototypes;};
void TeamFactory::clear(){
 Rva0039F56E copy(m_prototypes);m_prototypes.rva0039F56E();
 for(CopyTree::iterator i=copy.begin();i!=copy.end();++i){
  ::delete reinterpret_cast<TeamPrototype*>(i->second.words[1]);
 }
 memset(m_dummyTeams,0,sizeof(m_dummyTeams));
}
