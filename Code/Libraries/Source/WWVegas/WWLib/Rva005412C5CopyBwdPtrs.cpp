// ??$__copy_backward_ptrs@PAVRva0054103E@@PAV1@@_STL@@YAPAVRva0054103E@@PAV1@00ABU__false_type@0@@Z
// partial score=0.95 date=2026-10-02
// cl: /DNDEBUG /MD
// stlport
//
// ??$__copy_backward_ptrs@PAVRva0054103E@@PAV1@@_STL@@YAPAVRva0054103E@@PAV1@00ABU__false_type@0@@Z @0x005412C5 (29B).
// _STL::__copy_backward_ptrs<Rva0054103E> backward pointer dispatch.
// Retail 29B shape push 0 plus lea eax,[ebp-1] plus 3ปลาย pushes plus call
// plus add esp,0x14 proven by probe of copy_backward for this 0x14 stride.
// Calls rowed backward copy 0x0054115F via its 5-arg random_access overload.
// Evidence: callee row Rva0054103EUninitCopyBwd.cpp; caller 0x00541DDF passes
// 4 args; siblings 0x00541231 forward and 0x00541214 share the shape.
#include <algorithm>

struct Region2D
{
	Region2D(const Region2D &that);
	Region2D &operator=(const Region2D &that);
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};

class Rva0054103E
{
public:
	Rva0054103E(const Rva0054103E &that);
	Rva0054103E &operator=(const Rva0054103E &that);

private:
	int m_00;
	Region2D m_04;
};

template Rva0054103E *_STL::__copy_backward_ptrs(Rva0054103E *, Rva0054103E *, Rva0054103E *, const _STL::__false_type &);
