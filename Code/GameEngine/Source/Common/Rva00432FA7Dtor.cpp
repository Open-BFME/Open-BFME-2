// cl: /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /MD
// ??1Rva00432FA7@@UAE@XZ @0x00432FEF 54B: virtual dtor with two-list cleanup.
// Evidence: vtable 0x0083CA30 slot0 ??_G 0x0043312E; ctor 0x00432FA7 same vtable; tail-jmp to rowed ??1SubsystemInterface@@UAE@XZ 0x001B4E74; callers 0x00433131.

// Retail base vtable BD77A0 and destructor 1B4E74 prove the canonical 12-byte subsystem base.
typedef bool Bool;
#include "subsystem_interface.h"

struct Rva00432FA7Node
{
	char m_pad[0x14];
	Rva00432FA7Node *m_next;
	int m_18;
};

class Rva00432FA7 : public SubsystemInterface
{
	Rva00432FA7Node *m_0C;
	int m_10;
	Rva00432FA7Node *m_14;
	int m_18;
	int m_1C;
	float m_20;
	float m_24;
	float m_28;
public:
	virtual ~Rva00432FA7();
};

Rva00432FA7::~Rva00432FA7()
{
	for (int i = 0; i < 2; i++) {
		Rva00432FA7Node *head;
		if (i != 0)
			head = m_0C;
		else
			head = m_14;
		while (head) {
			Rva00432FA7Node *next = head->m_next;
			head->m_next = 0;
			head->m_18 = 0;
			head = next;
		}
	}
}
