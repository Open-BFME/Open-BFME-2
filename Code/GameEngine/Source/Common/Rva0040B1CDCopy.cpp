// cl: /DNDEBUG /MD
// stlport
#include <vector>
// ?Rva0040B1CDCopy@@YAPAVRva0040AF66@@PAV1@00@Z @ 0x0040B1CD (38B). Uninitialized copy range of Rva0040AF66 via rowed Construct.
// Evidence: retail loops calling the verified STLport _Construct 0x0040B17B stride 0x68 comparing first to last returning result end; callers 0x0040B929 0x0040B974 in 0x0040B8E8; same 38B shape as rowed 0x0040B2FD and 0x003F29D2.
class Rva0040AF66
{
public:
	Rva0040AF66(const Rva0040AF66 &other);
private:
	char m_pad[0x68];
};

namespace _STL {
template <> void _Construct<Rva0040AF66, Rva0040AF66>(Rva0040AF66 *, const Rva0040AF66 &);
}

Rva0040AF66 *__cdecl Rva0040B1CDCopy(Rva0040AF66 *first, Rva0040AF66 *last, Rva0040AF66 *result)
{
	Rva0040AF66 *cur = result;
	for (; first != last; ++first, ++cur)
		_STL::_Construct(cur, *first);
	return cur;
}
