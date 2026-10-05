// ?rva000F0FCD@Rva000F0FCD@@QAEXHPAG@Z
// partial score=0.7 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
// ?rva000F0FCD@Rva000F0FCD@@QAEXHPAG@Z @0x000F0FCD (67B): three-word
// remap write. Record i (6 bytes: three word indices) is read from the
// table at [[this]+0xC]; each index is mapped through the word table at
// [this+0x20] and stored to out[0..2]. Identity unproven (palette/index
// remap shape); address-derived names, opaque views.
struct Rva000F0FCDRec
{
	unsigned short m_a;
	unsigned short m_b;
	unsigned short m_c;
};

struct Rva000F0FCDData
{
	char m_pad00[0xC];
	Rva000F0FCDRec *m_recs;
};

class Rva000F0FCD
{
public:
	void rva000F0FCD(int i, unsigned short *out);

private:
	Rva000F0FCDData *m_data;
	char m_pad04[0x1C];
	unsigned short *m_remap;
};

void Rva000F0FCD::rva000F0FCD(int i, unsigned short *out)
{
	Rva000F0FCDData *d = m_data;
	Rva000F0FCDRec *r = (Rva000F0FCDRec *)(i * 6 + (int)d->m_recs);
	*out = m_remap[r->m_a];
	++out;
	*out = m_remap[r->m_b];
	out[1] = m_remap[r->m_c];
}
