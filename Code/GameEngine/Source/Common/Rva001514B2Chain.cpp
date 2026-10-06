// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: pointer-chase forwarder.
//
// ?rva001514B2@Rva001514B2@@QAEPAXHH@Z, retail 0x001514B2 (30 bytes).
// Follows this/+0 to +0x14 to +0x8 with early null returns, then tail-jumps
// to the pinned 0x15326D body with the two int args still on the stack.

class Rva0015326D
{
public:
	void *rva0015326D(int a, int b);

	void *m_head;
	char m_pad04[4];
	void *m_f08;
	char m_pad0C[8];
	void *m_f14;

	friend class Rva001514B2;
};

class Rva001514B2
{
public:
	void *rva001514B2(int a, int b);

private:
	Rva0015326D *m_head;
};

// ?rva001514B2@Rva001514B2@@QAEPAXHH@Z
void *Rva001514B2::rva001514B2(int a, int b)
{
	Rva0015326D *p = m_head;
	if (p && (p = (Rva0015326D *)p->m_f14) && (p = (Rva0015326D *)p->m_f08)) {
		return p->rva0015326D(a, b);
	}
	return p;
}
