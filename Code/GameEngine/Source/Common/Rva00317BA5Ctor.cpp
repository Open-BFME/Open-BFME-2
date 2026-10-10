// cl: /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /EHsc
//
// ??0Rva00317BBB@@QAE@XZ at 0x00317BA5, 22 bytes.
// Ctor beside rowed dtor ??1Rva00317BBB@@UAE@XZ at 0x00317BBB: the rowed
// SubsystemInterface base ctor 0x001B4E63, then zero +0x0C, then vtable
// 0x00C0C62C, then return this.
// Evidence: vtable store plus base ctor call plus dtor row plus caller
// at 0x0022E82D. Retail vtable 0x00C0C62C is the 14-slot SubsystemInterface
// table (base 0x00BD77A0) with slot 0 = ??_GRva00317BBB 0x00317C18 and slots
// 1/9/10 (init/reset/update) = the folded empty body 0x000B3FD0; the class
// view matches Rva00317BBBDtor.cpp's so both units emit the same vtable.
typedef bool Bool;
#include "subsystem_interface.h"

struct ListNode;

class Rva00317BBB : public SubsystemInterface
{
public:
	Rva00317BBB();
	virtual ~Rva00317BBB();
	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}
private:
	ListNode *m_head;
};

Rva00317BBB::Rva00317BBB()
	: m_head(0)
{
}
