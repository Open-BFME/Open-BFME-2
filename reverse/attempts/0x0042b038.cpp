// ?rva0042B038@Rva0042B038@@QAEXPAX000@Z
// partial score=0.93 date=2026-10-04
// cl: /O2 /EHsc /MD /Oy-
// ?rva0042B038@Rva0042B038@@QAEXPAXPAXPAXPAX@Z, retail 0x0042B038 (48B).
// Unlock: missing callee of 0x0042B068; landing makes 0x0042B068 ready.
// Calls rowed ?Rva00239D02Insert@@YGPAPAXPAPAXPAX0@Z 0x00239D02; caller 0x0042B07D;
// neighbours 0x004296C2 and 0x0042C083 share Common dir; __thiscall ret 0x10.
void **__stdcall Rva00239D02Insert(void **out, void *pos, void **allocArg);

struct Rva0042B038Node
{
	void *m_next;
	int m_pad04;
	void *m_field08;
};

class Rva0042B038
{
public:
	void rva0042B038(void *pos, void *start, void *end, void *extra);
};

 // ?rva0042B038@Rva0042B038@@QAEXPAX000@Z present-unmatched
void Rva0042B038::rva0042B038(void *pos, void *start, void *end, void *extra)
{
	Rva0042B038Node *cur = (Rva0042B038Node *)start;
	(void)extra;
	while (cur != (Rva0042B038Node *)end) {
		Rva00239D02Insert((void **)&start, pos, (void **)&cur->m_field08);
		cur = (Rva0042B038Node *)cur->m_next;
	}
}
