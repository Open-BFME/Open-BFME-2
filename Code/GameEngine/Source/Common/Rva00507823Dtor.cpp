// cl: /MD /EHsc /DNDEBUG
//
// ??1Rva00507823@@UAE@XZ retail 0x00507823 84B
// Base dtor storing vtable 0x00864010 same as ctor 0x0050775B. Destroys
// two 12B vectors at +0x108 and +0x114 via rowed 0x0002CC70 pin
// ??1RvaVecAscii and filter at +0x120 via rowed ??1Rva00360D26Member
// at 0x00360D26. Evidence: deleting dtor 0x00507807 calls here plus
// derived 0x0050B6ED stores 0x00864D80 then jmps here plus derived
// dtors 0x00508684 and 0x00509564 call here after own members.
// Same EH 1/0/-1 shape as GateOpen Slaughter precedent.

class RvaVecAscii
{
public:
	~RvaVecAscii();

private:
	int m_x[3];
};

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned m_unknown;
};

class Rva00507823
{
public:
	virtual ~Rva00507823();

private:
	unsigned char m_pad04[0x108 - 4];
	RvaVecAscii m_vec108; // +0x108
	RvaVecAscii m_vec114; // +0x114
	Rva00360D26Member m_filter120; // +0x120
};

Rva00507823::~Rva00507823()
{
}
