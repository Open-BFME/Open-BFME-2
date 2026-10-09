// ?Rva00524CC6@@YAXH@Z
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Target524CC6..524D01: find a slot for a preserved integer key, return on
// null value, clear value+C and low two flags at+24, then erase the key.
// Existing global E04938 and findSlot41F4E5 establish the lookup-table view.
// The native erase call54883B is the existing key-only hashtable provider:
// its pointer-valued instantiation has identical20B header and ignores value
// type during erase. This cast is a storage view, not an Object/order identity
// claim for the unknown pointee. Value offsets and native RET0 are target facts.
#include <hash_map>
class Object;
class ObjectLookupMap {public:Object**findSlot(int*);};
class Rva00548984;
typedef _STL::hashtable<_STL::pair<const int,Rva00548984*>,int,_STL::hash<int>,_STL::_Select1st<_STL::pair<const int,Rva00548984*> >,_STL::equal_to<int>,_STL::allocator<_STL::pair<const int,Rva00548984*> > > EraseView;
namespace _STL {template<> unsigned EraseView::erase(const int&);}
extern unsigned g_Va00E04938;
struct Rva00524CC6Value {char prefix[0xc];int clearC;char unknown10[0x14];unsigned char flags24;};
void Rva00524CC6(int key){
 int copy=key;
 ObjectLookupMap *map=(ObjectLookupMap*)&g_Va00E04938;
 Rva00524CC6Value *value=(Rva00524CC6Value*)*map->findSlot(&copy);
 if(!value)return;
 value->clearC=0;value->flags24&=0xfc;
 copy=key;((EraseView*)map)->erase(copy);
}
