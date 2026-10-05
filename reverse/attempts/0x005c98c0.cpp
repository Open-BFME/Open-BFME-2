// ?rva005C98C0@Rva005C98C0@@QAEPAXH@Z
// partial score=0.93 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?rva005C98C0@Rva005C98C0@@QAEPAXH@Z @0x005C98C0 54B.
// Null-guarded forward via g_009FEF10 +0xb0 rowed rva0020FAB4 returning pointer
// checked at +0x1a2. Evidence: rowed rva0020FAB4 0x0020FAB4; global g_009FEF10;
// callers at 0x005C9AE8 0x005C9B13 0x005C9B38; unblocks 0x005C9B31 0x005C9B0C
// 0x005C9ADD. Row ?rva0020FAB4@Rva0020EE29@@QAEXHH@Z declares void but retail
// uses the return as a pointer tested and read at +0x1a2; declared here as
// returning pointer per code use.
struct Rva0020FAB4Ret
{
	char m_pad[0x1a2];
	unsigned char m_1a2;
};

class Rva0020EE29
{
public:
	Rva0020FAB4Ret *rva0020FAB4(int a1, int a2);
};

class Rva002BA8F1Logic
{
public:
	char m_pad[0xb0];
	Rva0020EE29 *m_b0;
};

extern Rva002BA8F1Logic *g_009FEF10;

extern "C" void _WriteBarrier(void);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_WriteBarrier, _ReadWriteBarrier)

class Rva005C98C0
{
public:
	void *rva005C98C0(int id);
private:
	char m_pad00[0x1c];
	int m_1c;
};

// ?rva005C98C0@Rva005C98C0@@QAEPAXH@Z present-unmatched
void *Rva005C98C0::rva005C98C0(int id)
{
	if (!g_009FEF10 || !g_009FEF10->m_b0) {
		_WriteBarrier();
		return 0;
	}
	Rva0020EE29 *host = g_009FEF10->m_b0;
	Rva0020FAB4Ret *p = host->rva0020FAB4(id, m_1c);
	if (!p)
		return 0;
	if (p->m_1a2 != 0)
		return p;
	_ReadWriteBarrier();
	return 0;
}
