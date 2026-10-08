// ??1Gen_0035B960@@QAE@XZ
// partial score=0.9 date=2026-10-08
// cl: /O1 /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// stlport
#include <vector>
struct Rva003B7057Record { char opaque[0x14]; };
namespace _STL {
template<> vector<Rva003B7057Record>::~vector();
}
struct Rva003B678ARange { void *first,*last; };
void destroyRva003B678ARange(Rva003B678ARange*);
struct Gen_0035B960 : public _STL::_Vector_base<unsigned char, _STL::allocator<unsigned char> > {
 _STL::vector<Rva003B7057Record> records;
 int first,second;
 ~Gen_0035B960();
};
Gen_0035B960::~Gen_0035B960() { destroyRva003B678ARange((Rva003B678ARange*)&records); }
