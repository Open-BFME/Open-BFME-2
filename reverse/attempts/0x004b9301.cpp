// ?rva004B9301@Rva004B9301@@QAEXXZ
// partial score=0.93 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
// ?rva004B9301@Rva004B9301@@QAEXXZ
// retail 0x004B9301 68B. Vtable slot 1 of table 0x00859664 (neighbours
// validate/Is_Valid). Thiscall void method reaching Object through this-8,
// toggling bit 0x40000000 (dword 0x118 / byte 0x11B high byte) based on
// Player+0x33B, then tail to rowed Object::rva0028AE6D 0x0028AE6D.
// Callees rowed: getControllingPlayer 0x0028AFA9, rva0028AE6D 0x0028AE6D.
class Player
{
public:
	unsigned char m_pad[0x33B];
	unsigned char m_33B;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	void rva0028AE6D();
	unsigned char m_pad00[0x118];
	union
	{
		unsigned int m_118;
		unsigned char m_118b[4];
	};
};

class Rva004B9301
{
public:
	void rva004B9301();
};

void Rva004B9301::rva004B9301()
{
	Object *o = *(Object **)((char *)this - 8);
	Player *p = o->getControllingPlayer();
	o = *(Object **)((char *)this - 8);
	if (p->m_33B != 0)
	{
		unsigned int mask = 0x40000000;
		if (o->m_118 & mask)
			return;
		o->m_118 |= mask;
	}
	else
	{
		if ((o->m_118b[3] & 0x40) == 0)
			return;
		o->m_118b[3] &= 0xBF;
	}
	o->rva0028AE6D();
}
