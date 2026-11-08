// cl: /DNDEBUG /MD
// stlport
// ??$_Construct@VRva0054000B@@V1@@_STL@@YAXPAVRva0054000B@@ABV1@@Z @0x00540070 18B
// Null-guarded placement copy over the 40-byte element whose copy ctor is the
// rowed ??0Rva0054000B@@QAE@ABV0@@Z at 0x00540036 in Rva0053FDE6Init.cpp.
// Same 18B frameless shape as rowed _Construct 0x001DD3AA. Evidence: callee
// rowed; callers are the 0x28-stride copy loops at 0x005400B4 and 0x005400DA.
#include <stddef.h>

class Rva0054000B {
public:
	Rva0054000B(const Rva0054000B &that);
};

namespace _STL
{

template <class T1, class T2>
void _Construct(T1 *p, const T2 &value);

template <>
void _Construct<Rva0054000B, Rva0054000B>(Rva0054000B *p, const Rva0054000B &value)
{
	if (p)
		p->Rva0054000B::Rva0054000B(value);
}

}
