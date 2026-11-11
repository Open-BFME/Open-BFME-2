// cl: /MD /EHsc
//
// ?rva005C3E31@Rva005C3F02@@QAEXUTreeHintRef00217D4C@@@Z @0x005C3E31 (72B)

#include "../../../Libraries/Source/Apt/AptRefTarget.h"
inline TreeHintRef00217D4C::~TreeHintRef00217D4C()
{
	if (m_ptr) {
		ReleaseTreeHintRef00217D4C(m_ptr);
	}
}



#include "../../Include/Common/Rva005C3A37Elem.h"

class Rva005C3F02
{
public:
	void rva005C3E31(TreeHintRef00217D4C ref);

private:
	int m_pad00;
	Rva005C3A37Elem *m_elem;
};

void Rva005C3F02::rva005C3E31(TreeHintRef00217D4C ref)
{
	m_elem->Add(ref);
}
