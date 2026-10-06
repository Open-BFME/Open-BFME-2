// cl: /O1 /DNDEBUG /MD
// ?rva005D20E5@Rva005D20E5@@QAEXXZ @0x005D20E5 44B.
// Empty 0x00B3FD0 (reuses pinned empty); if +0x14 is 0 return; else calls
// pinned 0x005CCB5B (this-only void), then pinned 0x002BF6A7 via +0x10
// with +0x14, then virtual slot +0x1C on this with +0x14. Ret void,
// this only. Address-derived.
class Rva000B3FD0Empty
{
public:
	void rva000B3FD0Empty();
};

class Rva005CCB5B
{
public:
	void rva005CCB5B();
};

class Rva002BF6A7
{
public:
	void rva002BF6A7(int a);
};

class Rva005D20E5
{
public:
	void rva005D20E5();
	virtual void _s0();
	virtual void _s1();
	virtual void _s2();
	virtual void _s3();
	virtual void _s4();
	virtual void _s5();
	virtual void _s6();
	virtual void rva005D20E5Slot(int a);
protected:
	unsigned char m_pad[0x0C];
	Rva002BF6A7 *m_10;
	int m_14;
};

void Rva005D20E5::rva005D20E5()
{
	((Rva000B3FD0Empty *)this)->rva000B3FD0Empty();
	if (m_14 == 0)
		return;
	((Rva005CCB5B *)this)->rva005CCB5B();
	m_10->rva002BF6A7(m_14);
	rva005D20E5Slot(m_14);
}
