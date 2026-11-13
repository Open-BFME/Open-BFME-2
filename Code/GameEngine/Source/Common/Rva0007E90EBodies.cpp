// cl: /O1 /DNDEBUG /MD
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

#include "../../Include/Common/Rva0007E90ECallee.h"

class Rva0007E90EElem
{
public:
	int m_0;
	int m_ref;
	unsigned char m_pad[0xA0 - 8];
	unsigned char m_flag;
};

class Rva0007E90EHost
{
public:
	void rva0007E90E(int name);
	unsigned char m_pad[0x100];
	Rva0007E90ECallee *m_100;
	int m_104;
	Rva0007E90EElem **m_start;
	Rva0007E90EElem **m_end;
};

void Rva0007E90EHost::rva0007E90E(int name)
{
	if (m_100 != 0)
		m_100->rva000FF5E6(name);
	Rva0007E90EElem **pp = m_start;
	while (pp != m_end) {
		Rva0007E90EElem *element = *pp;
		if (element != 0)
			element->m_ref++;
		element->m_flag = 1;
		ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)element);
		++pp;
	}
}
