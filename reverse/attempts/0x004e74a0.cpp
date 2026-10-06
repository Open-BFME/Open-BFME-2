// ?rva004E74A0@Rva004E7277@@QAEPAV1@PAPAV1@@Z
// partial score=0.7 date=2026-10-06
// cl: /O1 /MD /EHsc
//
// ?rva004E74A0@Rva004E7277@@QAEPAV1@PAPPAV1@@Z @0x004E74A0 64B.
// Clone factory on Rva004E7277: operator-new a 0xC instance, init it from
// this through the rowed rva004E7392 when allocation succeeds, publish to
// the out slot and return it. Retail 0x004E74A0..0x004E74E0.

void *operator new(unsigned int size);

class Rva004E7277
{
public:
	void *rva004E7392(Rva004E7277 *arg);
	Rva004E7277 *rva004E74A0(Rva004E7277 **out);

private:
	void *m_00;
	void *m_04;
	int m_08;
	char m_pad0C[0x40 - 0x0C];
	int m_40;
};

// ?rva004E74A0@Rva004E7277@@QAEPAV1@PAPPAV1@@Z
Rva004E7277 *Rva004E7277::rva004E74A0(Rva004E7277 **out)
{
	Rva004E7277 *t = (Rva004E7277 *)operator new(0xC);
	if (t != 0)
		t->rva004E7392(this);
	*out = t;
	return t;
}
