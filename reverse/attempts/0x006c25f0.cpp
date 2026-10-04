// ?rva006C25F0@Rva006C1F60@@QAEHPAXHHHH00@Z
// partial score=0.7 date=2026-10-04
// cl: /O2 /DNDEBUG /MD
// ?rva006C25F0@Rva006C1F60@@QAEIHHPAPAXPAX@Z @ 0x006C25F0 (246B).
//
// Address-derived member of Rva006C1F60 -- the class already declared by the
// matched Rva006C1F60Finish.cpp, whose +0x4E4 lock pair is the AddRef/Release
// pair used here and whose caller this body continues.
//
// Structure, in retail order:
//   lock = m_lock (+0x4E4); if (lock) AddRef(0x00030DD0)
//   if (!this->rva006C1DC0(a2)) goto release          // rowed member, +0x680 flag
//   arg5 = *(int *)a3;  arg6 = *(int *)a4            // the two int args
//   if (a5 != 2) { gate = m_field67C; }              // +0x67C
//   else if (a6 == 0x0B) goto edit;                  // 0x0B == VT_BOOL-ish
//   else gate = m_field67C;
//   if (gate) goto lookup;
// edit:                                            // arg2's block header walk
//   // header dword at [a2-4]: low bits carry (length-4); bit 1 means "shared"
//   ptr = (h & 2) ? (h & 0x7FFFFFF8) : (h & 0x7FFFFFF8) + 4
//   rva006C2010(this, ptr - 8, a6, arg6, arg5, a2)  // 6 args, ret 0x18
//   goto release
// lookup:
//   if (!m_flag680) goto release;
//   if (!m_hash684.rva006C1850(arg6, &out)) goto release;   // +0x684 hash
//   if (!out) goto release;
//   len = *(unsigned short *)out[0];
//   if (!len) goto release;
//   rva006C2010(this, out[0] + 2, len - 2, a6, arg6, arg5)
//   goto release
// release: if (lock) Release(0x00030DF0); return result
//
// 0x006C2010 is UNROWED: its body is a backward word-wise scan over the source
// block (lengths at [p-2]) followed by a rep-movsd/rep-movsb tail copy, i.e.
// the buffer/offset/length text-substitution helper. It is called with six
// arguments and pops 0x18, so it is declared address-derived here; its real
// identity is not proven.
//
// The result register ebx is zeroed before the validator call and only becomes
// non-zero on the 0x006C2010 returns, so the body returns "did we rewrite".
//
// Identity is address-derived; the class layout is carried from the matched
// Rva006C1F60Finish.cpp and Rva006C1850Rva006C1920.cpp in the same directory.

struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);

typedef int intptr_t;

// Address-derived six-argument text substitution helper (ret 0x18).
// Retail pushes `edi` (arg2, the a2 int) last, so parameter 1 is an int.
int __cdecl rva006C2010(int self, void *dst, int index, int len,
	int arg5, int arg6);

class Rva006C1850
{
public:
	bool rva006C1850(unsigned int key, void **out);
};

class Rva006C1F60
{
public:
	int rva006C25F0(void *a1, int a2, int a3, int a4, int a5, void *a6,
	void *a7);
	bool rva006C1DC0(int flag);
private:
	unsigned char m_pad0[0x4e4];
	Rva00030DD0Lock *m_lock;                                    // +0x4E4
	unsigned char m_pad1[0x514 - 0x4e4 - 4];
	int m_flags;                                                 // +0x514
	unsigned char m_pad2[0x67C - 0x514 - 4];
	int m_field67C;                                              // +0x67C
	int m_flag680;                                               // +0x680
	Rva006C1850 m_hash684;                                      // +0x684
};

int Rva006C1F60::rva006C25F0(void *a1, int a2, int a3, int a4, int a5,
	void *a6, void *a7)
{
	Rva00030DD0Lock *lock = m_lock;
	if (lock)
		Rva00030DD0AddRef(lock);

	int result = 0;
	if (rva006C1DC0((int)a1)) {
		int arg5 = *(int *)a6;
		int arg6 = *(int *)a7;
		int gate = m_field67C;
		if (arg5 == 2 && arg6 == 0x0B) {
			unsigned int header = *(unsigned int *)((char *)a1 - 4);
			if (header & 2) {
				/* shared block: base is the aligned header itself */
				rva006C2010((int)a1,
					(char *)(header & 0x7FFFFFF8u) - 8, arg6, arg5, arg6, arg5);
			} else {
				/* owned block: body sits 4 bytes past the aligned header */
				rva006C2010((int)a1,
					(char *)((header & 0x7FFFFFF8u) + 4) - 8, arg6, arg5,
					arg6, arg5);
			}
		} else if (gate) {
			if (m_flag680) {
				void *out = 0;
				if (m_hash684.rva006C1850(arg6, &out) && out) {
					unsigned int len = *(unsigned short *)*(void **)out;
					if (len)
						result = rva006C2010((int)a1,
							(char *)*(void **)out + 2, (int)len - 2,
							arg6, arg6, arg6);
				}
			}
		}
	}

	if (lock)
		Rva00030DF0Release(lock);
	return result;
}