// cl: /MD /EHsc
// ?Rva00567B6DAdd@@YAXPAVRva005C3F02@@PBUPayload@Rva005677B9@@@Z, retail 0x00567B6D, 106 bytes.
// Caller 0x00568021 passes container in first arg and 2-dword payload in second; twin new-0x10 plus refcount-add pattern of 0x005CE2BA family.

#include "../../../Libraries/Source/Apt/AptRefTarget.h"
inline TreeHintRef00217D4C::~TreeHintRef00217D4C()
{
	if (m_ptr)
		ReleaseTreeHintRef00217D4C(m_ptr);
}



class Rva005677B9 : public TargetRef00217D4C
{
public:
	struct Payload { int v[2]; };
	Rva005677B9(const Payload *src) throw();
	virtual ~Rva005677B9();
private:
	Payload m_data;
};

#include "../../Include/Common/Rva005C3A37Elem.h"

class Rva005C3F02
{
public:
	void rva005C3E31(TreeHintRef00217D4C ref);
private:
	int m_pad00;
	Rva005C3A37Elem *m_elem;
};

void __cdecl Rva00567B6DAdd(Rva005C3F02 *dst, const Rva005677B9::Payload *src)
{
	Rva005677B9 *p = new Rva005677B9(src);
	TreeHintRef00217D4C tmp((TargetRef00217D4C *)p);
	dst->rva005C3E31(tmp);
}
