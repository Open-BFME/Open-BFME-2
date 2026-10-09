// cl: /MD
// stlport
// STLport 4.5.3 lower_bound over counted ushort adjacency entries.
// Target 0x0053249D..0x005324D8: native caller 0x00532DF6 pushes
// first, last, key reference, empty comparator and distance-type pointer.
// The prior three-argument address view omitted the two unused template args.
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
struct Rva00532DF6Entry {unsigned short id,count;};
struct Rva00532DF6Less {bool operator()(const Rva00532DF6Entry&a,unsigned short b)const{return a.id<b;}};
typedef Rva00532DF6Entry *(__cdecl *BoundFunction)(Rva00532DF6Entry*,Rva00532DF6Entry*,const unsigned short&,Rva00532DF6Less,int*);
BoundFunction Rva0053249DInstantiate=&_STL::__lower_bound<Rva00532DF6Entry*,unsigned short,Rva00532DF6Less,int>;
