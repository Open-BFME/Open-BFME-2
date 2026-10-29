// cl: /DNDEBUG /MD
//
// ??0Rva0007671F@@QAE@XZ @0x0007671F (22B).
// Honest address ctor for a 0x40 class whose first (and only) member is a
// four-element array of 16-byte rows at +0. Retail pushes element ctor VA
// 0x87A6A9 (the folded 3B empty ctor at 0x47A6A9, rowed as Vector4's among
// others), count 4, stride 0x10, and calls rowed vector_constructor_iterator
// at 0x1423. The element has no destructor: retail takes ??_H, not the
// destructor-aware ??_L, so it is not Region2D (whose empty dtor retail
// exports at 0x000B3FD0). Callers construct 0x40 locals via this ctor
// (0x0014D44C, 0x0007C1AE, 0x0007C220) and use them in Matrix4::Multiply
// chains, so the rows are WWMath Vector4s (Zero Hour vector4.h: four floats,
// empty inline ctor).
#include "Vector4Data.h"
class Rva0007671F
{
public:
	Rva0007671F();
private:
	Vector4 m_arr[4];
};
Rva0007671F::Rva0007671F()
{
}
