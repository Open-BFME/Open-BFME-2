// cl: /MD
// ??1Rva002E3E51@@UAE@XZ @0x002E3E51 47B:
// Base dtor storing vtable 0x00C04C28 at [this], second vtable 0x00C04C0C
// at base+4 and link at base, then frees buffer at +8 via rowed free.
// Called by 0x002E4049 and deleting dtor 0x002E422C. Owner unproven.
extern "C" void __cdecl free(void *block);

class Rva002E3E51
{
public:
	virtual ~Rva002E3E51();
private:
	void *volatile m_04;
	void *m_08;
};

Rva002E3E51::~Rva002E3E51()
{
	void *q1 = *(void **)((char *)m_04 + 4);
	*(const void **)((char *)q1 + (int)this + 4) = (const void *)0x00C04C0C;
	void *q2 = *(void **)((char *)m_04 + 4);
	*(void **)((char *)q2 + (int)this) = (char *)q2 - 0x38;
	void *buf = m_08;
	if (buf != 0)
		free(buf);
}
