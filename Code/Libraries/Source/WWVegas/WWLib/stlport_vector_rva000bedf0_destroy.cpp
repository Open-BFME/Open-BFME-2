// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$_Destroy@PAURva000BEDF0Record@@@_STL@@YAXPAURva000BEDF0Record@@0@Z @0x000C37E6 25B: range destroy stride 0x14 via rowed dtor 0x000BEDF0; callers 0x000C68C2 0x000C690C 0x000C695D; same loop as rowed 0x000C37CD.
#include <vector>
struct Rva000BEDF0Record
{
	~Rva000BEDF0Record();
	unsigned char m_data[0x14];
};
template void _STL::_Destroy<Rva000BEDF0Record *>(Rva000BEDF0Record *, Rva000BEDF0Record *);
