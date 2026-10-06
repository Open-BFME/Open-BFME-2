// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$_Destroy@PAURva00079554Record@@@_STL@@YAXPAURva00079554Record@@0@Z, retail 0x000BD2A6, 25 bytes.
// Range destroy for 0x2C record (three int vectors at +0x00/+0x0C/+0x18 plus
// 8-byte tail) stride 0x2C calling rowed dtor 0x79554. Same 25B loop shape as
// rowed Rva0048130E _Destroy at 0x00481595. Emitted via explicit _Destroy
// instantiation over the rowed record plus tail pad; callers at
// 0xC1C6A/0xC20A3/0xC4D89 unblock C20A3 and C1C6A.
#include <vector>

struct Rva00079554Record
{
	~Rva00079554Record();
	_STL::vector<int> m_00;
	_STL::vector<int> m_0C;
	_STL::vector<int> m_18;
	unsigned char m_tail24[8];
};

template void _STL::_Destroy<Rva00079554Record *>(Rva00079554Record *, Rva00079554Record *);

// vector dtor (retail 0x000C1C6A): byte-identical explicit member
// instantiation calling the _Destroy above and _free.
template _STL::vector<Rva00079554Record>::~vector();
