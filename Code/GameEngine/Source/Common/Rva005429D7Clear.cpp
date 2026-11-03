// cl: /MD /Oi-
// ?rva005429D7@Rva005429D7@@QAEPAV1@XZ @0x005429D7 29B
// Clear 0x104 record: dword +0 then clear80 helpers at +4 and +0x84 then return this. Evidence: retail bytes unlock lane plus callees 0x001EAE6F clear80 rows and callers 0x00542B24 0x00542BA1.
#include "../../Include/Common/Rva001EAE6FHelper.h"

class Rva005429D7
{
public:
	Rva005429D7 *rva005429D7();
private:
	int m_00;
	Rva001EAE6FHelper m_04;
	Rva001EAE6FHelper m_84;
};

Rva005429D7 *Rva005429D7::rva005429D7()
{
	m_00 = 0;
	m_04.clear80();
	m_84.clear80();
	return this;
}
