// cl: /Ireference/shims/bfmelist /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva00438FC5@@QAE@XZ, retail 0x00438FC5, 47 bytes.
// Non-virtual dtor of a class with list<int> at +0 that explicitly clears it:
// EH prolog, clear via rowed 0x0023DAA5 then List_base dtor via rowed
// 0x004EC395. No vtable, this==member so no offset. Callers 0x439CD2 etc.
// /EHs for list-dtor state stores per 4.6. Honest address name.
#include <list>
class Rva00438FC5
{
public:
	~Rva00438FC5();
private:
	_STL::list<int, _STL::allocator<int> > m_list;
};
Rva00438FC5::~Rva00438FC5()
{
	m_list.clear();
}
