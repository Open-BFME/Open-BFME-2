// cl: /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ??1Rva001DB60F@@UAE@XZ retail 0x001DB60F 91B. Dtor storing vtable 0x007DBA7C
// then clearing a MetaMapRec list at +0xC via rowed dtor 0x001DB48E plus rowed
// operator delete then tailing to rowed SubsystemInterface dtor 0x001B4E74.
// Evidence: vtable store plus rowed callees plus deleting-dtor caller 0x001DB66A.
// Honest address name.
class MetaMapRec
{
public:
	~MetaMapRec();
	MetaMapRec *m_next;
};

// Retail base vtable BD77A0 and destructor 1B4E74 prove the canonical 12-byte subsystem base.
typedef bool Bool;
#include "subsystem_interface.h"

class Rva001DB60F : public SubsystemInterface
{
public:
	virtual ~Rva001DB60F();
private:
	MetaMapRec *m_head;
};

Rva001DB60F::~Rva001DB60F()
{
	while (m_head != 0) {
		MetaMapRec *next = m_head->m_next;
		delete m_head;
		m_head = next;
	}
}
