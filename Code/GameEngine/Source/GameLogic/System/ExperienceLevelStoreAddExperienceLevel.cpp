// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /O1 /G7 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ExperienceLevelStore::AddExperienceLevel, retail 0x0028A1AA..0x0028A294.
// WB 0x00BE9FF0 names the operation and original ExperienceLevelSystem.cpp.
// Retail iterates the AsciiString vector at level+0x24, generates a NameKey,
// and appends a copied level to the hash-map entry or assigns a new one-item
// list. The temporary CreateAHero string survives in the retail release body.
// FieldParse 0x00BFBAC0 and the rowed ExperienceLevel constructor establish
// the 0x108-byte polymorphic payload and its names vector; other fields remain
// opaque here. BfmePod264 is the existing STL provider spelling, not a claim
// about the original ExperienceLevel type name.
// The map/list providers at 0x0028A104/0x00289F2C use that existing spelling.
// Retail calls list assignment at 0x00289FBC, whose ledger owner has a separate
// opaque element spelling. The casts bridge identical list headers and node
// links to that declaration-only provider; no element access or copy is emitted
// through the opaque type. Its native element-assignment and insert callees
// are the same experience-level payload operations at 0x00289902/0x00289F46.
// Full body, call targets, string, and three-state exception cleanup verified.
#include <list>
#include <vector>
#include <hash_map>
#include "ascii_string.h"
struct BfmePod264 {
    virtual ~BfmePod264();
    char unknown04[0x20];
    _STL::vector<AsciiString> targetNames24;
    char unknown30[0xd8];
};
struct Rva00289FBCRecord;
typedef _STL::list<BfmePod264> ExperienceList;
typedef _STL::hash_map<int,ExperienceList> ExperienceMap;
namespace _STL {
template<> void ExperienceList::push_back(const BfmePod264 &);
template<> ExperienceList &ExperienceMap::operator[](const int &);
template<> list<Rva00289FBCRecord> &list<Rva00289FBCRecord>::operator=(const list<Rva00289FBCRecord> &);
}
enum NameKeyType { NAMEKEY_UNKNOWN=0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const AsciiString &); };
extern NameKeyGenerator *TheNameKeyGenerator;
class ExperienceLevelStore { public: void rva0028A1AA(void *,const BfmePod264 *); };
void ExperienceLevelStore::rva0028A1AA(void *table,const BfmePod264 *level)
{
    ExperienceMap *map=(ExperienceMap *)table;
    for(unsigned i=0;i<level->targetNames24.size();++i) {
        AsciiString name(level->targetNames24[i]);
        AsciiString createAHero("CreateAHero");
        int key=TheNameKeyGenerator->nameToKey(name);
        ExperienceMap::iterator found=map->find(key);
        if(found==map->end()) {
            ExperienceList list;
            list.push_back(*level);
            reinterpret_cast<_STL::list<Rva00289FBCRecord> &>((*map)[key])=
                reinterpret_cast<const _STL::list<Rva00289FBCRecord> &>(list);
        } else {
            ExperienceList &existing=found->second;
            existing.push_back(*level);
        }
    }
}





