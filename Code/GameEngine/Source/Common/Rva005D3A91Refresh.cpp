// cl: /MD /EHsc
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
inline TreeHintRef00217D4C::~TreeHintRef00217D4C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
// The functor's result is the rowed invoke 0x005D388B's one-word value; here
// it is the reference it is assigned to.
struct Rva005D388BValue : TreeHintRef00217D4C
{
};
class Rva005D388BRef
{
public:
	Rva005D388BValue invoke();
	void *m_op;
};
class Rva001FF3A9
{
public:
	void rva001FF3A9(const TreeHintRef00217D4C &v);
};
class Rva005D3A91
{
public:
	void rva005D3A91();
private:
	char m_00[0x18];
	void *m_18;
	TreeHintRef00217D4C m_1C;
	char m_pad20[0x24 - 0x20];
	Rva005D388BRef m_24;
};
void Rva005D3A91::rva005D3A91()
{
	if (m_18 == 0)
		return;
	if (m_24.m_op == 0)
		return;
	m_1C = m_24.invoke();
	if (m_1C.m_ptr == 0)
		return;
	((Rva001FF3A9 *)m_18)->rva001FF3A9(m_1C);
}
