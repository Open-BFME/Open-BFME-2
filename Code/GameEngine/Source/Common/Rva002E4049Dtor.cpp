// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??1Rva002E4049@@UAE@XZ, retail 0x002E4049..0x002E40DB (146 bytes, EH):
// the base-object destructor the rowed scalar deleting destructor
// 0x002E424F calls (pinned there under a non-virtual spelling). Layout read
// off the body: the rowed base Rva002E3E51 (vbptr at +4, non-virtual part
// 0x38 bytes, destructor 0x002E3E51), a second polymorphic base at +0x38,
// a chain of owned objects at +0x3C (each unlinked and destroyed through a
// global ::delete), two AsciiStrings at +0x40/+0x4C, and the virtual base
// at +0x60 behind its vtordisp. Tables: 0x00C04C7C, 0x00C04C78, 0x00C04C5C.
// Identities are not established; names stay address-derived.
#include "ascii_string.h"

class VBase00C6EE28
{
public:
	virtual void s0();
};

class Rva002E3E51 : public virtual VBase00C6EE28
{
public:
	virtual ~Rva002E3E51();
	virtual void s0();
private:
	void *m_08;
	unsigned char m_pad0C[0x38 - 0x0C];
};

class Rva002E4049Second
{
public:
	virtual void s0();
};

class Rva002E4049 : public Rva002E3E51, public Rva002E4049Second
{
public:
	virtual ~Rva002E4049();
private:
	Rva002E4049 *m_next3C;		// +0x3C
	AsciiString m_name40;		// +0x40
	unsigned char m_pad44[8];
	AsciiString m_name4C;		// +0x4C
	unsigned char m_pad50[0x0C];
};

Rva002E4049::~Rva002E4049()
{
	Rva002E4049 *node = m_next3C;
	while (node)
	{
		Rva002E4049 *next = node->m_next3C;
		node->m_next3C = 0;
		::delete node;
		node = next;
	}
}
