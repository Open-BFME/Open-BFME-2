// cl: /MD
// ?rva0037F551@Rva0037F551@@QAEAAV1@ABV1@@Z retail 0x0037F551 45B
// Evidence: chain from 0x0037F51A; copies two 0x20 blocks at +0 and +0x20 via that row then int at +0x40 and bool at +0x44; caller 0x0037F71F
#include "../GameLogic/System/ArmyPlacerCopyRecord.h"

Rva0037F551 &Rva0037F551::rva0037F551(const Rva0037F551 &src)
{
	m_a.rva0037F51A(src.m_a);
	m_b.rva0037F51A(src.m_b);
	m_40 = src.m_40;
	m_44 = src.m_44;
	return *this;
}
// ?Rva0037F71FCopy@@YAXPAVRva0037F551@@ABV1@@Z retail 0x0037F71F 18B
// Evidence: chain from 0x0037F551; null-checked forward to rva0037F551; callers 0x0037F731 0x0037F757 0x0037FF20 0x0037FFDD
void Rva0037F71FCopy(Rva0037F551 *dst, const Rva0037F551 &src)
{
	if (dst)
		dst->rva0037F551(src);
}
// ?Rva0037F757Fill@@YAPAVRva0037F551@@PAV1@IABV1@PAX@Z retail 0x0037F757 37B
// Evidence: chain from 0x0037F71F; fill loop over Rva0037F551 stride 0x48; caller 0x0037FF20
Rva0037F551 *Rva0037F757Fill(Rva0037F551 *dst, unsigned int count, const Rva0037F551 &src, void *unused)
{
	Rva0037F551 *cur = dst;
	while (count > 0) {
		Rva0037F71FCopy(cur, src);
		++cur;
		--count;
	}
	return cur;
}
// ?Rva0037F731Copy@@YAPAVRva0037F551@@PAV1@00PAX@Z retail 0x0037F731 38B
// Evidence: chain from 0x0037F71F; copy range stride 0x48; callers 0x0037F77C 0x0037FF20
Rva0037F551 *Rva0037F731Copy(Rva0037F551 *first, Rva0037F551 *last, Rva0037F551 *dst, void *unused)
{
	Rva0037F551 *cur = dst;
	while (first != last) {
		Rva0037F71FCopy(cur, *first);
		++first;
		++cur;
	}
	return cur;
}
// ?rva0037F77C@Rva0037F77C@@QAEPAVRva0037F551@@IPAV2@0@Z retail 0x0037F77C 45B
// Evidence: chain from 0x0037F731; allocate n via allocator at this+8 then copy range via that row; caller 0x0037FEDD
struct BfmePod72 { int a[18]; };
namespace _STL { template <typename T> struct allocator { T *allocate(unsigned int n, const void *hint) const; }; }
class Rva0037F77C
{
public:
	Rva0037F551 *rva0037F77C(unsigned int n, Rva0037F551 *first, Rva0037F551 *last);
private:
	char m_pad[8];
	_STL::allocator<BfmePod72> m_alloc;
};
#pragma optimize("y", off)
Rva0037F551 *Rva0037F77C::rva0037F77C(unsigned int n, Rva0037F551 *first, Rva0037F551 *last)
{
	BfmePod72 *buf = m_alloc.allocate(n, 0);
	Rva0037F731Copy(first, last, (Rva0037F551 *)buf, (void *)((char *)&n + 3));
	return (Rva0037F551 *)buf;
}
#pragma optimize("", on)
