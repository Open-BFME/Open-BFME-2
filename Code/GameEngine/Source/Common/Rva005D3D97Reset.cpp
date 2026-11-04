// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// StrategicHUD::SelectionUIImpl::rva005D3D97 retail 0x005D3D97 62B.
// Target evidence (native body + WorldBuilder debug twin 0x15AA9A0): two virtual calls (vtable +0x24, then +0x10),
// m_20 (+0x20) cleared, then a zeroed TreeHintRef00217D4C temp assigned into the ref at +0x24 through the rowed
// operator= 0x002174A4; the temp's unwind action is the only dtor reference (retail elides the normal-path release).
// Structural inference: the callee row body is written inline+noinline in this TU so cl knows operator= does not
// modify the temp (visible-callee lever); the ref is bound to a local reference before the assignment.
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
__forceinline TreeHintRef00217D4C::~TreeHintRef00217D4C()
{
	if (m_ptr)
		ReleaseTreeHintRef00217D4C(m_ptr);
}
inline __declspec(noinline) TreeHintRef00217D4C &TreeHintRef00217D4C::operator=(const TreeHintRef00217D4C &other)
{
	if (this != &other)
	{
		if (other.m_ptr)
			++other.m_ptr->references;
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
		m_ptr = other.m_ptr;
	}
	return *this;
}


namespace StrategicHUD
{
class SelectionUIImpl;
}
class StrategicHUD::SelectionUIImpl
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void s8();
	virtual void s9();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	void rva005D3D97();
private:
	char m_pad04[0x1C];
	int m_20;
	TreeHintRef00217D4C m_aptRef;
};

void StrategicHUD::SelectionUIImpl::rva005D3D97()
{
	s9();
	s4();
	m_20 = 0;
	TreeHintRef00217D4C temp;
	TreeHintRef00217D4C &dst = m_aptRef;
	dst = temp;
}
