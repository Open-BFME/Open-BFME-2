// cl: /EHsc /MD /DNDEBUG
// ??0Rva005F86FE@@QAE@PAX0@Z @0x005F86FE 73B
// Constructor: own vtable 0x00C79CB8, heap member at +4 allocated via rowed
// operator new 0x0002FDA0 (0x2C bytes) and constructed by the rowed 0x005F8671
// when non-null; the init return (or null) lands in +4. Same
// new-plus-conditional-init EH shape as 0x005F3E93/0x005F830A; states stay 0.
// 0x005F8671 is rowed as ??0Rva005F86C3@@QAE@HH@Z (Rva005F86C3Constructor.cpp);
// the pointer arguments pass through as ints.
class Rva005F86C3
{
public:
	Rva005F86C3(int a1, int a2);
private:
	char m_pad[0x2C];
};

#include "../../Include/Common/Rva005F86FE.h"

Rva005F86FE::Rva005F86FE(void *a1, void *a2)
	: m_04(new Rva005F86C3((int)a1, (int)a2))
{
}
