// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/iniexception
// Native 0x0021376B..0x0021386C, 257B, cdecl INI block callback.
// Registration VA 0x00DB9A20 names LivingWorldObject; WB 0x00B63BA0
// confirms singleton lookup, override clone/new, field parsing and insertion.
// BFME1 donor cee35b7d8c game/GameEngine/Source/GameLogic/LivingWorld/
// LivingWorldObjectParser00614F50.cpp guides override semantics. Target
// independently proves load type +8, override +4/+8, object 0x1C and map +2B4.
// Existing address-derived providers retain their unknown original names;
// the clone and field-table getter use the method ABI witnessed by this caller.
#include "../../../Include/Common/INI/FieldParse.h"
class INI;
class INI {
public:
 const char *getNextToken(const char *seps);
 void initFromINI(void *, const FieldParse *);
 static void parseIndexList(INI *, void *, void *, const void *);
 static void parseReal(INI *, void *, void *, const void *);
 char pad[8]; int loadType;
};
enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
#include "../../../Include/Common/Overridable.h"
// Retail inlines markAsOverride here (the outline is 0x00248D08).
__forceinline void Overridable::markAsOverride()
{
 m_isOverride = true;
}
class Rva00210F3D : public Overridable { public: int b,c,d; };
class Rva003FA776 : public Rva00210F3D { public: Rva003FA776(); const FieldParse *rva003FA6FF(); };
class Rva002122D4 { public: int rva002122D4(int); };
void Rva0021376BParse(INI *);
template<class T> class StringBase {
 friend void Rva0021376BParse(INI *);
 void validate() const;
};
namespace _STL {
template<class A, class B> struct pair;
template<class A> struct less;
template<class A> class allocator;
template<class A, class B, class C, class D> class map { public: B &operator[](const A &); };
}
// Native C378F0..C37930: three 16-byte records followed by the null sentinel.
// The constructor and parser independently witness object offsets 10/14/18;
// the existing emissive-template name array is the ObjectType index list.
extern const char *EmissiveTemplateNames[];
extern const FieldParse LivingWorldObjectFields[] = {
 {"ObjectType", INI::parseIndexList, EmissiveTemplateNames, 0x10},
 {"DefaultFlashValue", INI::parseReal, 0, 0x14},
 {"FlashVariation", INI::parseReal, 0, 0x18},
 {0, 0, 0, 0}
};
typedef _STL::map<int,int,_STL::less<int>,_STL::allocator<_STL::pair<const int,int> > > NameMap;
class LivingWorldManager { public: Rva00210F3D *rva00211142(Rva00210F3D *); char pad[0x2b4]; NameMap names; };
extern LivingWorldManager *TheLivingWorldManager;
void Rva0021376BParse(INI *ini) {
 if (!TheLivingWorldManager) throw INIException(3, "TheLivingWorldManager==NULL");
 bool existed = false;
 int key = TheNameKeyGenerator->nameToKey(ini->getNextToken(0));
 LivingWorldManager *manager = TheLivingWorldManager;
 Rva003FA776 *object = (Rva003FA776 *)((Rva002122D4 *)manager)->rva002122D4(key);
 if (object) {
  if (ini->loadType == 2)
   object = (Rva003FA776 *)manager->rva00211142((Rva00210F3D *)(object->friend_getNextOverride() ? object->friend_getNextOverride()->friend_getFinalOverride() : object));
  existed = true;
 } else {
  object = new Rva003FA776;
  if (ini->loadType == 2) object->markAsOverride();
 }
 ini->initFromINI(object, object->rva003FA6FF());
 // The unidentified object hook calls the shared empty validation body.
 ((StringBase<char> *)object)->validate();
 if (!existed) TheLivingWorldManager->names[key] = (int)object;
}
