// cl: /MD
//
// ?rva001E3591@Rva001E3591@@QAE_NXZ, retail 0x001E3591, 37 bytes.
// Guarded validity check over the 0x20 family (sibling of the readers at 0x001E34FA and
// 0x001E3511 in Rva001E34FA.cpp): +4 must be set, +0x10 selects Outer, +8 selects Inner
// (or Outer itself), valid when the selected +0x20 differs from 0x7fffffff. Owner
// identity unproven, honest Rva name. Own TU because it needs /arch:SSE, which the
// sibling readers do not use.

struct Rva001E3511Inner
{
	int m_pad00[8]; // +0x00..+0x1F
	int m_val20; // +0x20
};

struct Rva001E3511Outer
{
	int m_pad00[2]; // +0x00..+0x07
	Rva001E3511Inner *m_p08; // +0x08
	int m_pad0C[5]; // +0x0C..+0x1F
	int m_val20; // +0x20
};

class Rva001E3591
{
public:
	bool rva001E3591();
private:
	int m_pad00; // +0x00
	int m_p04; // +0x04 (compared to 0)
	int m_pad08[2]; // +0x08..+0x0F
	Rva001E3511Outer *m_p10; // +0x10
};

bool Rva001E3591::rva001E3591()
{
	if (m_p04 == 0)
		return false;
	Rva001E3511Outer *p = m_p10;
	if (!p)
		return false;
	Rva001E3511Inner *q = p->m_p08;
	if (!q)
		q = reinterpret_cast<Rva001E3511Inner *>(p);
	return q->m_val20 != 0x7fffffff;
}
