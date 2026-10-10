// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// BFME1 reference9cbfb551fe20dae985f91f2319d8997287b6a705:
// ThingTemplateLocomotorBinding.cpp and stock STLport map::operator[].
// The donor algorithm is reused; its Locomotor element name is NOT a target fact.
// Target4FA168..4FA1F3 proves signed key at node10 and12-byte value at14.
// Native pair constructor4F7DDC..4F7DF9 copies key0 and delegates value4 to
// canonical vector-copy provider4F69D6; parent4FA1A8 proves its entry/RET8.
// Empty header211E58 and destruction4F7D7F are existing canonical providers.
// Storage is an owning callable ABI view of their three pointer words. Element
// identity stays unknown; no type/name pins or object-symbol aliases are added.

#include <vector>
#include <map>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}
struct BfmeE16 {float x,y,z,w;};
struct Rva004F69D6Record {char bytes[4];~Rva004F69D6Record();};
struct Rva004F7D7FRecord {char bytes[4];~Rva004F7D7FRecord();};
typedef _STL::vector<Rva004F69D6Record> CopyProvider;
typedef _STL::vector<Rva004F7D7FRecord> DestroyProvider;
namespace _STL {
template<> CopyProvider::vector(const CopyProvider&);
template<> DestroyProvider::~vector();
}
class Rva004FA168Storage {
 unsigned int start,finish,capacity;
public:
 __forceinline Rva004FA168Storage() {
  typedef _STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> > HeaderProvider;
  ((HeaderProvider*)this)->HeaderProvider::_Vector_base(_STL::allocator<BfmeE16>());
 }
 __forceinline Rva004FA168Storage(const Rva004FA168Storage &source) {
  ((CopyProvider*)this)->CopyProvider::vector(*(const CopyProvider*)&source);
 }
 __forceinline ~Rva004FA168Storage(){((DestroyProvider*)this)->DestroyProvider::~DestroyProvider();}
};
struct Rva004F90FFMapped {int a;};
typedef _STL::map<int,int> BoundProvider;
typedef _STL::map<int,Rva004F90FFMapped> InsertProvider;
namespace _STL {
template<> InsertProvider::iterator InsertProvider::insert(InsertProvider::iterator,const InsertProvider::value_type&);
}
struct Rva004FA168Node {int color;Rva004FA168Node *parent,*left,*right;int key;};
class Rva004FA168Map {
public:Rva004FA168Storage &subscript(const int &);
private:Rva004FA168Node *header;
};
typedef _STL::pair<const int,Rva004FA168Storage> StoragePair;
__forceinline const InsertProvider::value_type &insertView(const StoragePair &v){return *(const InsertProvider::value_type*)&v;}
Rva004FA168Storage &Rva004FA168Map::subscript(const int &key)
{
 BoundProvider::iterator position=((BoundProvider*)this)->lower_bound(key);
 if(position._M_node==(_STL::_Rb_tree_node_base*)header || key<((Rva004FA168Node*)position._M_node)->key) {
  Rva004FA168Storage value;
  InsertProvider::iterator hint;hint._M_node=position._M_node;
  position._M_node=((InsertProvider*)this)->insert(hint,insertView(StoragePair(key,value)))._M_node;
 }
 return *(Rva004FA168Storage*)((char*)position._M_node+0x14);
}
