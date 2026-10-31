// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??1Rva002E4049@@UAE@XZ, retail 0x002E4049..0x002E40DB (146 bytes, EH):
// the base-object destructor the rowed scalar deleting destructor
// 0x002E424F calls (pinned there under a non-virtual spelling). Layout read
// off the body: the rowed base Rva00330C50 (vbptr at +4, non-virtual part
// 0x38 bytes, destructor 0x002E3E51), a second polymorphic base at +0x38,
// a chain of owned objects at +0x3C (each unlinked and destroyed through a
// global ::delete), two AsciiStrings at +0x40/+0x4C, and the virtual base
// at +0x60 behind its vtordisp. Tables: 0x00C04C7C, 0x00C04C78, 0x00C04C5C.
// Identities are not established; names stay address-derived.
#include "ascii_string.h"

#include "../../../Libraries/Include/Lib/Region2D.h"
struct Rva0030B72CPoint {
 Rva0030B72CPoint() {}
 __forceinline Rva0030B72CPoint(const Rva0030B72CPoint &other):x(other.x),y(other.y) {}
 float x,y;
};

class VBase00C6EE28
{
public:
	~VBase00C6EE28() {}
	virtual int slot0() const = 0;
	virtual Rva0030B72CPoint slot1(int index) const = 0;
	virtual int slot2() const = 0;
	virtual Region2D slot3() = 0;
	virtual float slot4() const = 0;
	virtual float slot5() const = 0;
	virtual Rva0030B72CPoint slot6() const = 0;
};

class Rva00330C50 : public virtual VBase00C6EE28
{
public:
	virtual ~Rva00330C50();
	virtual int slot0() const;
	virtual Rva0030B72CPoint slot1(int index) const;
	virtual int slot2() const;
	virtual Region2D slot3();
	virtual float slot4() const;
	virtual float slot5() const;
	virtual Rva0030B72CPoint slot6() const;
private:
	void *m_08;
	unsigned char m_pad0C[0x38 - 0x0C];
};

class Rva002E4049Second
{
public:
	virtual void s0() {}
};

class Rva002E4049 : public Rva00330C50, public Rva002E4049Second
{
public:
	virtual ~Rva002E4049();
private:
	Rva002E4049 *m_next;		// +0x3C
	AsciiString m_name40;		// +0x40
	unsigned char m_pad44[8];
	AsciiString m_name4C;		// +0x4C
	unsigned char m_pad50[0x0C];
};

Rva002E4049::~Rva002E4049()
{
	Rva002E4049 *node = m_next;
	while (node)
	{
		Rva002E4049 *next = node->m_next;
		node->m_next = 0;
		::delete node;
		node = next;
	}
}
