// cl: /MD
// ??0Rva000E771B@@QAE@XZ 0x000E771B 25B
// Default ctor constructing three 16-byte rows at +0x10 via rowed
// vector_constructor_iterator 0x1423 with rowed empty ctor 0x47A6A9.
// The row has no destructor (retail takes ??_H, not ??_L), so it is not
// Region2D (retail exports its empty dtor at 0x000B3FD0); spelled as WWMath
// Vector4 rows (Zero Hour vector4.h: four floats, empty inline ctor).
// Evidence: pushes 0x87A6A9 3 0x10 lea +0x10 call 0x1423 mov eax,esi;
// prev W3DShrubBuffer::rva000E76B8 ends at 0xE771B; caller at 0x000E98C5.

#include "../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"

class Rva000E771B
{
public:
	Rva000E771B();
private:
	char _pad0[0x10];
	Vector4 m_arr[3];
};

Rva000E771B::Rva000E771B()
{
}
