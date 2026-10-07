// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// ??0Rva00224C95@@QAE@XZ @0x00224C95 (71B): default ctor zeroing +0/+4,
// forcing +0xC bits, table init at +0x10 via pinned 0x00224C76, flag byte
// (and 0xF4, or 4) at +0x24; returns this. TRUE BOUNDARY 0x224C95: the range
// list entry 0x224CA0 is 11 bytes inside the body (past the EH prolog
// mov/call plus push ecx/push esi); Ghidra splits FUN_00624c95 (10B prolog
// chunk) from FUN_00624ca0. Structure mirrors landed 0x002231E7: init-list
// POD stores, state 0, guarded body call with state 1, no state reset.
// The unwind guard comes from the +0 AsciiString member (inline dtor with a
// release call); the +0x10 table is 20 bytes of POD whose init() is pinned.
// Evidence: next-function prolog at 0x00224CDB; caller region 0x00224Bxx;
// address-derived.
#include "ascii_string.h"

class Rva00224C95Table
{
public:
	void init();
	~Rva00224C95Table() {}
private:
	char m_pad[20];
};

class Rva00224C95
{
public:
	Rva00224C95();
private:
	AsciiString m_a; // +0x00 same string pair as rowed Rva0022494F
	AsciiString m_b; // +0x04
	int m_08; // +0x08
	int m_state; // +0x0C forced all-bits
	Rva00224C95Table m_table; // +0x10
	unsigned char m_flags; // +0x24
};

Rva00224C95::Rva00224C95() : m_a(), m_b()
{
	m_state |= -1;
	m_08 = 0;
	m_table.init();
	m_flags = (unsigned char)((m_flags & 0xF4) | 4);
}
