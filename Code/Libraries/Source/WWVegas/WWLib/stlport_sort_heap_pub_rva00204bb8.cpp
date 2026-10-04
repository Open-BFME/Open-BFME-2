// cl: /O1 /G7 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// ??$sort_heap@PAHVRva00204BB8@@@_STL@@YAXPAH0VRva00204BB8@@@Z @0x0021DDFC 58B
// Public sort_heap over int keys with rowed thiscall comparator Rva00204BB8 at 0x00204BB8.
// Loops the rowed pop_heap 0x0021D9E0. Evidence: 58B loop shape; callee rowed;
// neighbours 0x0021DD81 and 0x0021DE36 share flags; unblocks 0x0021E44B.
#include <algorithm>

class Rva00204BB8
{
public:
	bool operator()(int a, int b) const;
};

template void _STL::sort_heap<int *, Rva00204BB8>(int *, int *, Rva00204BB8);
