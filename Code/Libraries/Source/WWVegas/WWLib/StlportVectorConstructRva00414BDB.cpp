// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ??$_Construct@URva00414BDBElement@@U1@@_STL@@YAXPAURva00414BDBElement@@ABU1@@Z, retail 0x00414A76, 45 bytes.
// True _Construct for 48-byte vector element: null-tests dest then copy-constructs
// via rowed Rva004147CF 0x004147CF. Same 45B EH shape as Rva0048130E precedent.
// Called by uninitialized-copy workers in StlportVectorInsertOverflowRva00414BDB.cpp.
#include <vector>

struct Rva00414BDBElement
{
	char opaque[48];
};

class Rva004147CF
{
public:
	Rva004147CF(const Rva004147CF &other);
};

namespace _STL {
template <>
void _Construct<Rva00414BDBElement, Rva00414BDBElement>(Rva00414BDBElement *p, const Rva00414BDBElement &val)
{
	new ((void *)p) Rva004147CF(*(const Rva004147CF *)&val);
}
}
