// cl: /O1 /G7 /MD /EHsc
// Native comparator0017368A..001736A7 follows a RET4 at00173687.
// Both range flushers001748B3 and00174A57 pass this address to the owned
// STLport sort over32-byte rendering tasks. Only the mesh pointer at task0
// and its unsigned ordering word at meshC4 are read here. The names below
// describe an address-derived ABI view; the original record and method
// spelling are unknown. Native EAX is the complete zero/one result.
struct Rva0017368AMesh {
    char unknown[0xc4]; unsigned key;
    char unknownC8[0x310-0xc8]; unsigned *state310;
};
struct Rva0017368ATask { Rva0017368AMesh *mesh; char unknown[28]; };

unsigned Rva0017368ACompare(const Rva0017368ATask &lhs, const Rva0017368ATask &rhs)
{
    return lhs.mesh->key < rhs.mesh->key;
}

unsigned Rva0017368ACompare(const Rva0017368ATask &lhs, const Rva0017368ATask &rhs);

// Native001736A7..001736D6 follows the comparator above and returns the
// same full EAX zero/one value. Software-skinning flush001748E8 passes
// this address to the same sort. Equal meshC4 words select mesh310;
// both comparisons use unsigned carry. These are target offset facts,
// rather than recovered names for either mesh field. Owned cleanup174350
// also dereferences the word at310, establishing that it is a state pointer.
// This comparator orders its32-bit address rather than the pointed-to value.
unsigned Rva001736A7Compare(const Rva0017368ATask &lhs, const Rva0017368ATask &rhs)
{
    if(lhs.mesh->key==rhs.mesh->key)
        return (unsigned)lhs.mesh->state310 < (unsigned)rhs.mesh->state310;
    return lhs.mesh->key < rhs.mesh->key;
}

// Native001748B3..001748E8 is a RET0 range flusher, rather than the
// unrelated vector::resize suggested by the drift queue. Its three calls
// are sort00174870, rendering0017438B and erase00173FB6. The rendering
// worker's existing address-derived two-word declaration is retained;
// WB names that worker FXShaderRenderer::PerformRendering. No original
// name or complete renderer layout is claimed for this receiver view.
// 0x00174870 is rowed as the STLport sort over these 32-byte records with a
// function-pointer comparator; declared only, so the call keeps that name.
class FXShaderRenderer {public:void PerformRendering(int,int);};
struct BfmeAssignRecord32 {char unknown[32];};
namespace _STL {
template<class T>class allocator {};
template<class T,class A>class vector {public:T*erase(T*,T*);};
template<class It,class Cmp> void sort(It first,It last,Cmp comp);
}
typedef bool (*BfmeAssignRecord32Less)(const BfmeAssignRecord32 &,const BfmeAssignRecord32 &);
class Rva001748B3 {
public:void rva001748B3();
private:int start,finish,limit;
};

void Rva001748B3::rva001748B3()
{
    if(start==finish)return;
    _STL::sort((BfmeAssignRecord32*)start,(BfmeAssignRecord32*)finish,(BfmeAssignRecord32Less)&Rva0017368ACompare);
    ((FXShaderRenderer*)this)->PerformRendering(start,finish);
    ((_STL::vector<BfmeAssignRecord32,_STL::allocator<BfmeAssignRecord32> >*)this)->erase((BfmeAssignRecord32*)start,(BfmeAssignRecord32*)finish);
}
