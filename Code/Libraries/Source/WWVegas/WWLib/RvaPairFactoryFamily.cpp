// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// BFME1 donor 9cbfb551fe20dae985f91f2319d8997287b6a705 clean make_pair
// instantiations provide the aggregate-return algorithm. Their AsciiString / FXList
// types are not target facts: native callees instead prove the existing entry
// unsigned/tree constructor owner. Ghidra entry604251 spans
// 27 bytes and invokes603FD2; RET0 hidden output slot.
// Holder's 4-byte ownership and nontrivial destructor come from its existing
// stlport_sort_rva0040cb11entry.cpp provider. No new type name or callee pin.
// Constructor definitions remain with their independently verified home units.
#include <map>
typedef _STL::pair<const unsigned,void*> PairIntPtr00603FD2;
typedef _STL::_Rb_tree<unsigned,PairIntPtr00603FD2,_STL::_Select1st<PairIntPtr00603FD2>,_STL::less<unsigned>,_STL::allocator<PairIntPtr00603FD2> > TreeIntPtr00603FD2;
class Rva00603FD2 {public:Rva00603FD2(const unsigned*,const TreeIntPtr00603FD2&);private:unsigned key;TreeIntPtr00603FD2 value;};
Rva00603FD2 Rva00604251(const unsigned&key,const TreeIntPtr00603FD2&value) {return Rva00603FD2(&key,value);}
