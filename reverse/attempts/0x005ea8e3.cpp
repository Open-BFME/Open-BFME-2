// ?rva005EA8E3@Rva005EA8E3@@QAEXHH@Z
// partial score=0.9579 date=2026-10-06
// ?rva005EA8E3@Rva005EA8E3@@QAEXHH@Z
// partial score=0.9579 date=2026-10-05
// ?rva005EA8E3@Rva005EA8E3@@QAEXHH@Z
// partial score=0.99 date=2026-10-05
// cl: /O1 /G7 /DNDEBUG /MD /EHs-c-
// ?rva005EA8E3@Rva005EA8E3@@QAEXHH@Z @0x005EA8E3 55B thiscall bounded clear via ranges
// model=space-bunny-alpha
// Clears Rva002BED91 at elem+0x20 for index j in range i when 0<=j<count; sizes 0xC and 0x24 match siblings; callers 0x005EA990 0x005EA9A1
// Retail (55B): pushes esi, tests j, then indexes this at (i*0xC + this + 0x1C),
// loads end/begin into eax, idiv 0x24 via the edi push/pop pair, bounds-checks j,
// reloads begin, scales j by 0x24, calls Rva002BED91 at begin + j*0x24 + 0x20.
// 53 of 55 bytes match; the only residual is a two-instruction scheduler tie
// (retail reloads begin into eax before scaling j, cl does the reverse).
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva002BED91
{
public:
	void clear();
private:
	void *m_ptr;
};

struct Rva005EA8E3Elem
{
	char m_pad[0x20];
	Rva002BED91 m_holder; // +0x20, stride 0x24
};

struct Rva005EA8E3Range
{
	Rva005EA8E3Elem *m_begin; // +0
	Rva005EA8E3Elem *m_end;   // +4
	int m_pad;
};

class Rva005EA8E3
{
public:
	void rva005EA8E3(int i, int j);
private:
	char m_pad[0x1c];
	Rva005EA8E3Range m_ranges[2]; // +0x1c, stride 0xC
};

// ?rva005EA8E3@Rva005EA8E3@@QAEXHH@Z present-unmatched
void Rva005EA8E3::rva005EA8E3(int i, int j)
{
	if (j < 0)
		return;
	Rva005EA8E3Range *r = &m_ranges[i];
	int count = (int)((char *)r->m_end - (char *)r->m_begin) / 36;
	if ((unsigned int)j >= (unsigned int)count)
		return;
	_ReadWriteBarrier();
	Rva005EA8E3Elem *begin = r->m_begin;
	begin[j].m_holder.clear();
}
