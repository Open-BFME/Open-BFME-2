// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
#include "ascii_string.h"

// ??0BfmeQuickMatchScreenBase@@QAE@XZ, retail 0x00538C0E, 81 bytes.
// Default ctor of BfmeQuickMatchScreenBase (vtable 0x00839608, same as rowed
// ctor 0x0040FD38 / 0x00470620 in BfmeQuickMatchScreenBaseConstructor.cpp).
// Evidence: vtable store at [this], AsciiString member at +0x04 set to
// "EmptyLayout" via rowed StringBase<char>::set 0x000055F5, remaining fields
// +0x08..+0x20 zeroed matching sibling layout (m_bfme08..m_bfme20 plus bool
// at +0x14). Caller at 0x00317734. No donor; layout from sibling TUs.

class BfmeQuickMatchScreenBase
{
public:
	virtual void bfmeSlot0();
	virtual void bfmeSlot1();
	virtual void bfmeSlot2();
	virtual void bfmeSlot3();
	virtual void rva00538AB0(bool flag);
	virtual void slot5();
	virtual void add(void *payload);
	BfmeQuickMatchScreenBase();

private:
	AsciiString m_slot; // +0x04
	int m_08; // +0x08
	int m_0c; // +0x0C
	int m_10; // +0x10
	bool m_14; // +0x14
	char m_pad15[3];
	int m_18; // +0x18
	int m_1c; // +0x1C
	int m_20; // +0x20
};

BfmeQuickMatchScreenBase::BfmeQuickMatchScreenBase()
{
	m_slot.set("EmptyLayout");
	m_08 = 0;
	m_0c = 0;
	m_10 = 0;
	m_14 = false;
	m_18 = 0;
	m_1c = 0;
	m_20 = 0;
}
