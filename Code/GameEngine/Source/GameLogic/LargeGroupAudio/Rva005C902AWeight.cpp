// stlport
// cl: /O1 /G7 /arch:SSE /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// Retail 0x005C902A..0x005C9069, 63B; WB 0x01568CB0.
// Caller 0x005C9311 supplies a float weight to an audio grid cell. The native
// float-key tree at +0x2C stores a count at node+0x14; its first reference calls
// the independently owned 0x005C8D6B. Names remain address derived.
// The map wrapper below is the exact owned 35B provider at 0x005C8F9A.
// Visible, non-inlined provider code proves the returned iterator cannot be
// changed by the counter store, matching retail's single node load. Its full
// bytes and relocations were independently checked, not inferred from 63B.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
struct TreeOpaqueMapped00372FF4{unsigned m_bits;};
typedef _STL::pair<const float,TreeOpaqueMapped00372FF4> TreeValue00372FF4;
typedef _STL::_Rb_tree<float,TreeValue00372FF4,_STL::_Select1st<TreeValue00372FF4>,_STL::less<float>,_STL::allocator<TreeValue00372FF4> > Tree00372FF4;
class Rva005C8F9A{public:_STL::pair<Tree00372FF4::iterator,bool>rva005C8F9A(const TreeValue00372FF4&);private:Tree00372FF4 m_tree;};
class TargetObj005C8DBF{public:void method_005C902A(float);void method_005C8D6B();char unknown[0x2c];};
void TargetObj005C8DBF::method_005C902A(float value){
 const TreeOpaqueMapped00372FF4 count={0};const TreeValue00372FF4 key(value,count);
 const _STL::pair<Tree00372FF4::iterator,bool>r=((Rva005C8F9A*)((char*)this+0x2c))->rva005C8F9A(key);
 ++r.first->second.m_bits;
 if(r.first->second.m_bits==1)method_005C8D6B();
}

inline __declspec(noinline) _STL::pair<Tree00372FF4::iterator,bool> Rva005C8F9A::rva005C8F9A(const TreeValue00372FF4&v){_STL::pair<Tree00372FF4::iterator,bool>tmp=m_tree.insert_unique(v);return tmp;}
