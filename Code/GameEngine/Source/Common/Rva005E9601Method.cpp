// cl: /O1 /MD
// Range-34 dump lane: 36B plain method at 0x005E9601 (ret).
// Runs the pinned 0x005F977D helper; when the +0x10 byte is set and the
// pinned 0x005FA854 member check on +0xC passes, tail-jumps through vtable
// slot 8 (third virtual, never defined in this unit). All identities
// unproven (address-derived).
struct Rva005E9601M0C
{
	int m_pad;
	bool check();
};

class Rva005E9601
{
public:
	virtual void v00();
	virtual void v01();
	virtual void vfunc();
	char m_pad04[8];
	Rva005E9601M0C m0c;
	char m_byte10;
	void helper977D();
	void rva005E9601();
};

void Rva005E9601::rva005E9601()
{
	helper977D();
	if (m_byte10 == 0)
		return;
	if (!m0c.check())
		return;
	vfunc();
}
