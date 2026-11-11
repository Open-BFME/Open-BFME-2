// stlport
// Native [41EC73,41ED84): AI base-definition registry parser.
// Table names/offsets and the independently owned constructors, destructor,
// name-key and registry operations establish behavior. Existing typed STL
// providers are ABI call views; original parser and element names stay unknown.
// The owned50B ctor only clears fields and zero-vector headers; throw() here
// expresses that verified behavior and avoids allocation EH absent in retail.
// Inline contains reproduces the native ADD-this before PUSH-key scheduling.
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
#define private public

#include <vector>
#undef private
#include "ascii_string.h"
enum NameKeyType {NAMEKEY_INVALID=0};
#include "../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator*TheNameKeyGenerator;
class INI;
#include "../../../Include/Common/INI/FieldParse.h"
#include "../../../Include/Common/INI/INI.h"
// Native table is exactly five entries at C3AF18..C3AF68; the following
// bytes are unrelated code pointers and the Unnamed string, not a zero
// terminator. Preserve that observed extent instead of adding a sentinel.
static const FieldParse fields[]={
 {"Side",INI::parseAsciiString,0,0},{"Map",INI::parseAsciiString,0,4},{"GameMapToUseOn",INI::parseAsciiString,0,8},{"PlayerPositions",INI::Rva004E8EFF_ParseDisabledSlots,0,12},{"AllowsArbirtaryRotation",INI::parseBool,0,24}};
enum ScienceType {SCIENCE_NONE=0};
// Native scalar-vector cleanup uses the rowed game-memory free wrapper.
// Keep the first compatible ScienceType destructor's allocator identity.
void __cdecl Rva00030830GameFree(void *);
namespace _STL {
template <> inline _Vector_base<ScienceType, allocator<ScienceType> >::~_Vector_base()
{ if (_M_start) Rva00030830GameFree(_M_start); }
}

#include "../../../../Libraries/Source/WWVegas/WWLib/Rva0021C21BElement.h"
void parseAIBaseDefinition(INI*);
class ModuleData;
class Rva0041E912Template;
// TheBaseTemplateLibrary's class: retail's only caller (AIBase 0x005AE29B)
// loads ECX from the global before the call, so the side lookup is a member.
class Rva0022BD9ASubsystem {public:bool rva0041E912(const AsciiString &side,_STL::vector<Rva0041E912Template*> &out);};
namespace _STL {
template<class T>struct hash {};template<class T>struct equal_to {};
template<class K,class V,class H=hash<K>,class E=equal_to<K>,class A=allocator<pair<const K,V> > >class hash_map {public:V&operator[](const K&);char body[20];};
template<class V>struct _Select1st {};template<class V>struct _Hashtable_node {};
template<class V,class K,class H,class S,class E,class A>class hashtable {friend void ::parseAIBaseDefinition(INI*);friend class ::Rva0022BD9ASubsystem;public:__forceinline bool contains(const K &key) const {return _M_find(key)!=0;} private:template<class KT>_Hashtable_node<V>*_M_find(const KT&)const;};
template<>void vector<ScienceType>::push_back(const ScienceType&);
template<>void vector<const ModuleData*>::push_back(const ModuleData*const&);
template<>vector<Rva0021C21BElement>&vector<Rva0021C21BElement>::operator=(const vector<Rva0021C21BElement>&);
template<>vector<ScienceType>&hash_map<int,vector<ScienceType> >::operator[](const int&);
}
#include "../../../Include/GameLogic/Armor.h"
namespace rts {template<class T>struct hash {};template<class T>struct equal_to {};}
typedef _STL::hashtable<_STL::pair<const NameKeyType,ArmorTemplate>,NameKeyType,rts::hash<NameKeyType>,_STL::_Select1st<_STL::pair<const NameKeyType,ArmorTemplate> >,rts::equal_to<NameKeyType>,_STL::allocator<_STL::pair<const NameKeyType,ArmorTemplate> > > ArmorHashtable;
class Object;class ObjectLookupMap {public:Object**findSlot(int*);};
extern Rva0022BD9ASubsystem*TheBaseTemplateLibrary;
struct Rva0041EC73View {char prefix[12];char map0C[20];_STL::hash_map<int,_STL::vector<ScienceType> >map20;};


// Native [41E912,41E96F) RET8 (thiscall, this unused): the side's base definitions. The side name's
// key selects the +0x20 entry (its vector of definition keys); each key's
// definition slot in the +0x0C map is appended to the output through the
// rowed ModuleData-pointer push_back 0x004DFCB0. False when the side has no
// entry. Original name unknown; the output element view is the push owner's.
struct Rva0041E912Entry {void*next;int key;int*begin;int*end;};
bool Rva0022BD9ASubsystem::rva0041E912(const AsciiString &side,_STL::vector<Rva0041E912Template*> &templates){
 // Retail reads TheBaseTemplateLibrary, not this, and appends through the
 // rowed ModuleData-pointer push_back 0x004DFCB0 (one pointer-vector body).
 _STL::vector<const ModuleData*> *out=reinterpret_cast<_STL::vector<const ModuleData*>*>(&templates);
 NameKeyType key=TheNameKeyGenerator->nameToKey(side);
 Rva0041E912Entry*entry=reinterpret_cast<Rva0041E912Entry*>(reinterpret_cast<ArmorHashtable*>(&reinterpret_cast<Rva0041EC73View*>(TheBaseTemplateLibrary)->map20)->_M_find(key));
 if(!entry) return false;
 for(int*it=entry->begin;it!=entry->end;++it)
  out->push_back(*(const ModuleData**)(reinterpret_cast<ObjectLookupMap*>(&reinterpret_cast<Rva0041EC73View*>(TheBaseTemplateLibrary)->map0C)->findSlot(it)));
 return true;
}
