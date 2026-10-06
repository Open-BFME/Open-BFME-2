// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$_Destroy@PAURva00153729@@@_STL@@YAXPAURva00153729@@0@Z, retail 0x00153BB6, 25 bytes.
// Range destroy for 0x4C holder (int at +0 plus array[6] of vector<Rva005F8F96> at +4) stride 0x4C calling rowed dtor 0x153729.
// Evidence: push esi mov esi [esp+8] loop call 0x153729 add esi 0x4C cmp jne; same 25B shape as rowed Rva005F8F96 _Destroy at 0x153470; callers at 0x153BD7 0x153C07 0x153C4B.
#include <vector>
struct Rva00153729
{
	~Rva00153729();
	unsigned char m_data[0x4C];
};
template void _STL::_Destroy<Rva00153729 *>(Rva00153729 *, Rva00153729 *);
