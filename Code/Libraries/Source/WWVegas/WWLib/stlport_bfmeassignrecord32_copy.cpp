// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0BfmeAssignRecord32@@QAE@ABU0@@Z @ 0x00173731 (85B): implicit copy ctor of
// the 32-byte assignable record (Rva00087A93 s at +0, int at +4, six more at
// +8). Layout proven by the rowed dtor at 0x0017330A, the pinned assignment
// operator at 0x00173499, the Destroy loop at 0x00173AE0 and the deleting dtor
// at 0x00173500, plus the 0x20 stride in callers. Copies s inline via inc,
// int directly, then six elements via EH vector-copy 0x006299C4 with copy
// ctor 0x0007E380 and dtor 0x0007B724. Callers include 0x001737EF, 0x00173841
// and 0x00173AB3.
// ??$_Construct@UBfmeAssignRecord32@@U1@@_STL@@YAXPAUBfmeAssignRecord32@@ABU1@@Z
// @ 0x001737EF (45B): null-guarded placement copy that calls the 85B copy
// above. Callers at 0x0017382F, 0x0017399A and 0x0017403C.
// ??0Rva00087A93@@QAE@ABV0@@Z @ 0x0007E380 (20B): refcounted-holder copy
// (inc dword at +4) inlined for s above and passed as the vector-copy
// callback. Matches the rowed dtor ??1Rva00087A93@@QAE@XZ at 0x0007B724.
#include <vector>

class Rva00087A93 {
	struct Data {
		virtual void slot();
		int ref;
	};
	Data *m_data;
public:
	Rva00087A93(const Rva00087A93 &o) : m_data(o.m_data) { if (m_data) ++m_data->ref; }
	~Rva00087A93();
};

struct BfmeAssignRecord32 {
	Rva00087A93 s;
	int x;
	Rva00087A93 arr[6];
	~BfmeAssignRecord32();
};

template void _STL::_Construct<BfmeAssignRecord32, BfmeAssignRecord32>(BfmeAssignRecord32 *, const BfmeAssignRecord32 &);
