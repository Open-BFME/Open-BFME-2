// cl: /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /MD /EHsc
// ??1Rva002DAC58@@UAE@XZ @0x002DAC58 128B: dtor with two node lists plus SubsystemInterface.
// Evidence: vptr 0x00C03D64 store, lists at +0xC/+0x10 with virtual slot0 get(0) plus global delete row 0x2FD60, base dtor row 0x1B4E74, deleting dtor caller 0x002DACD8 28B, neighbour Rva002DB311Dtor /O1 /MD /EHsc.

// BFME2 SubsystemInterface (12-byte base, 14-slot vtable 0x00BD77A0; ctor
// 0x001B4E63 / dtor 0x001B4E74 rowed as ??0/??1SubsystemInterface) from the
// subsystem shim, so this unit emits the retail 14-slot vtable 0x00C03D64.
typedef bool Bool;
#include "subsystem_interface.h"

struct Rva002DAC58Node
{
	virtual void *get(int v);
	char m_pad04[0xC];
	Rva002DAC58Node *m_next;
};

class Rva002DAC58 : public SubsystemInterface
{
public:
	virtual ~Rva002DAC58();
	// Retail vtable 0x00C03D64 slots 1/9/10 (init/reset/update) are the folded
	// empty body at 0x000B3FD0.
	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}
private:
	Rva002DAC58Node *m_list0C;
	Rva002DAC58Node *m_list10;
};

Rva002DAC58::~Rva002DAC58()
{
	while (m_list0C)
	{
		Rva002DAC58Node *next = m_list0C->m_next;
		void *p = m_list0C ? m_list0C->get(0) : 0;
		::operator delete(p);
		m_list0C = next;
	}
	while (m_list10)
	{
		Rva002DAC58Node *next = m_list10->m_next;
		void *p = m_list10 ? m_list10->get(0) : 0;
		::operator delete(p);
		m_list10 = next;
	}
}
