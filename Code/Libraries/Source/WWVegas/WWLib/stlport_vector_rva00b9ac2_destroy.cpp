// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$_Destroy@PAURva00B9AC2@@@_STL@@YAXPAURva00B9AC2@@0@Z, retail 0x000BD28D, 25 bytes.
// Range destroy for 0x18 holder stride 0x18 calling pinned dtor 0xB9AC2.
// Same 25B loop shape as rowed Rva0048130E _Destroy at 0x00481595 (53B QAE
// dtor at 0x48130E non-virtual no vptr store). The existing UAE pin at
// 0xB9AC2 carries the wrong virtualness (body stores no vptr); the QAE twin
// pin added beside this TU corrects it per the ICF-twin plus call site
// (BD28D calls B9AC2 as 481595 calls 48130E). Emitted via explicit _Destroy
// instantiation over an opaque 0x18 view declaring the twin dtor; callers at
// 0xC1C20/0xC2085/0xC218F unblock C2085 and C1C20.
#include <vector>

struct Rva00B9AC2
{
	~Rva00B9AC2();
	unsigned char m_data[0x18];
};

template void _STL::_Destroy<Rva00B9AC2 *>(Rva00B9AC2 *, Rva00B9AC2 *);

// vector dtor (retail 0x000C1C20): byte-identical explicit member
// instantiation calling the _Destroy above and _free.
template _STL::vector<Rva00B9AC2>::~vector();
