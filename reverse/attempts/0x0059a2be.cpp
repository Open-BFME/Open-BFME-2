// ?defineUnitsNormal_old@Rva0059AC4D@@QAE_NPAVTeamPrototype@@@Z
// partial score=0.94 date=2026-10-08
// cl: /O1 /MD /EHsc /arch:SSE /G7 /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
#include <stdlib.h>
namespace _STL { void __cdecl free(void *); }
#define free _STL::free
#include <vector>
#undef free
#include "ascii_string.h"
#include "../../../Common/GameLogicObjectLookupView.h"
enum ObjectStatusTypes {};
class ThingTemplate { public: char prefix[0x64]; AsciiString name; char pad[0x108-0x68]; unsigned char kind0; char pad109[0xa]; unsigned char kind1; };
class Object { public: char prefix[4]; ThingTemplate *m_template; char pad08[0x304-8]; int player; bool testStatus(ObjectStatusTypes) const; int getIndex() const { return player; } ThingTemplate *getTemplate() const {return m_template;} };
class Player { public: char prefix[0x2ec]; int index; int getIndex() const { return index; } };
class Rva002A8F24 { public: void *rva002A8F24(Player *); };
class Rva005C4AD1LeaField { public: void *get() const; };
class Rva0039D761DwordClearer { public: void clear(); };
class Rva0039D5A9 { public: int rva0039D5A9(); };
namespace _STL {
template <class T> struct hash;
template <class T> struct equal_to;
template <class A,class B> struct pair;
template <class K,class V,class H,class E,class A> class hash_map { public: unsigned bucket_count() const; };
template<> vector<ObjectID>::vector(const vector<ObjectID> &);
}
typedef _STL::hash_map<int,int,_STL::hash<int>,_STL::equal_to<int>,_STL::allocator<_STL::pair<const int,int> > > CountView;
class Rva0039EA9C {
public:
 Rva0039EA9C(); ~Rva0039EA9C();
 int count,other,flag; AsciiString name0c,name10; int id;
};
class Rva0039D769;
class TeamPrototype {
public:
 void addUnitInfo(const Rva0039D769 &);
 char pad00[0x1d8]; int number;
 char pad1dc[0x2d0-0x1dc]; unsigned max;
};
extern Rva002A8F24 *g_00DFEEF8;
extern GameLogic *TheGameLogic;
class Rva0059AC4D { char prefix[0x14]; Player *owner; public: bool defineUnitsNormal_old(TeamPrototype *); };
bool Rva0059AC4D::defineUnitsNormal_old(TeamPrototype *prototype)
{
 ((Rva0039D761DwordClearer *)prototype)->clear();
 void *stats=g_00DFEEF8->rva002A8F24(owner);
 void *units=*(void **)stats;
 if (((CountView *)units)->bucket_count() > 0) {
  const _STL::vector<ObjectID> ids=*(const _STL::vector<ObjectID> *)((Rva005C4AD1LeaField *)units)->get();
  Rva0039D5A9 *requirements=(Rva0039D5A9 *)((char *)prototype+0x12c);
  for (_STL::vector<ObjectID>::const_iterator it=ids.begin(); it!=ids.end() && (unsigned)requirements->rva0039D5A9() < prototype->max; ++it) {
   Object *object=TheGameLogic->findObjectByID(*it);
   if (object && object->getIndex()==owner->getIndex() &&
       ((object->m_template->kind0 & 8) || (object->m_template->kind1 & 4)) &&
       !object->testStatus((ObjectStatusTypes)0x5a)) {
    Rva0039EA9C info;
    info.count=1;
    info.other=1;
    info.name10=object->getTemplate()->name;
    info.id=-1;
    prototype->addUnitInfo((const Rva0039D769 &)info);
   }
  }
  if (prototype->number > 0) return true;
 }
 return false;
}
