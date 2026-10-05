// ?rva006C39F0@Rva006C39F0Owner@@QAE_NIIIPAX@Z
// partial score=0.98 date=2026-10-05
// ?rva006C39F0@Rva006C39F0Owner@@QAE_NIIIPAX@Z
// cl: /O2 /DNDEBUG /MD
// ?rva006C39F0@Rva006C39F0Owner@@QAE_NIIIPAX@Z @ 0x006C39F0 (191B, ret 0x10).
//
// Delayed-free hash insert in the debug allocator. Arg1 key, arg2 altLen,
// arg3 allocSize, arg4 buffer.
//
// Retail, read off the disassembly:
//   - `this` stays in ecx and is spilled to its frame home with
//     mov [esp+4],ecx right after the tracking-byte test, so ebx is free
//     to carry a persistent byte preset to 1 (mov bl,1) that doubles as the
//     true-return constant for the tracking-off and key-found exits (mov al,bl)
//     and as the "we allocated the run" flag (xor bl,bl at 0x6C3A42).
//   - &m_table is taken into ebp (lea ebp,[ecx+0x684]) and the three member
//     calls all take it or the spilled this as their receiver, which is what
//     keeps this out of a callee-save.
//   - the chain walk is a DO-WHILE over node->m_next: retail tests the first
//     node before entry at 0x6C3A28 and the loop body only re-reads m_next
//     (mov edx,[edx+8] / test edx,edx / jne back), so the while form emits
//     an extra test on entry.
//   - `owned` has retail's exact lifecycle: preset to 1 at entry (mov bl,1 at
//     0x6C3A9F keeps it 1 through the tracking test), cleared to 0 right after
//     the chain walk (xor bl,bl at 0x6C3A42), and set back to 1 only after a
//     successful allocation (mov bl,1 at 0x6C3A6E). So it is false on the
//     direct-buffer path and true only when this body allocated the run.
//   - on a miss the run is the caller's buffer, or a fresh allocation from
//     0x006C3940 in which case the trailing two-byte length word is written
//     at BOTH ends (mov word ptr [esi],di / mov word ptr [edi+esi-2],0) only
//     once the allocation pointer is known non-null. The insert length
//     differs per path, and this is the load-bearing asymmetry: arg1 -- which
//     doubles as the hash key and is loaded once into edi at 0x6C3A13 and
//     still live for the chain compare at 0x6C3A30 -- is the length the
//     direct-buffer path inserts under, because the buffer!=0 branch at
//     0x6C3A46 reaches the shared insert at 0x6C3A70 without reloading edi.
//     Only the allocated path reloads edi, with arg2 at 0x6C3A6A. arg3 is
//     allocSize and is what sizes the run and both length words.
//   - a failed insert releases the run through 0x006C1A50, but only when
//     this body allocated it (test bl,bl / je skips the release).
//
// 0x006C3940 (alloc), 0x006C21C0 (insert) and 0x006C1A50 (release) are all
// thiscall and all ret 4, so they take one stack argument each.
struct Rva006C17B0Node
{
	unsigned int m_key;
	unsigned char m_unaccessed4[4];
	Rva006C17B0Node *m_next;
};

class Rva006C17B0
{
public:
	Rva006C17B0Node **m_array;
	unsigned char m_pad4[4];
	unsigned int m_prime;

	bool rva006C21C0(unsigned int len, void *buf);
};

class Rva006C39F0Owner
{
public:
	void *rva006C3940Alloc(unsigned int size);
	void rva006C1A50Free(void *run);

	bool rva006C39F0(unsigned int key, unsigned int altLen, unsigned int allocSize, void *buffer);

	unsigned char m_unaccessed[0x680];
	unsigned char m_tracking;
	unsigned char m_pad681[3];
	Rva006C17B0 m_table;
};

// ?rva006C39F0@Rva006C39F0Owner@@QAE_NIIIPAX@Z present-unmatched
bool Rva006C39F0Owner::rva006C39F0(unsigned int key, unsigned int runLen,
                                  unsigned int insertLen, void *buffer)
{
	unsigned char owned = 1;
	if (m_tracking)
	{
		Rva006C17B0 *table = &m_table;
		if (table->m_array)
		{
			unsigned int k = key;
			Rva006C17B0Node *node = table->m_array[(k >> 3) % table->m_prime];
			if (node)
			{
				do
				{
					if (node->m_key == k)
						goto done;
					node = node->m_next;
				} while (node);
			}
		}
		owned = 0;
		{
			void *run = buffer;
			unsigned int len = buffer ? key : insertLen;
			if (!run)
			{
				if (!runLen)
					return false;
				run = rva006C3940Alloc(runLen);
				if (!run)
					return false;
				*(unsigned short *)run = (unsigned short)runLen;
				*(unsigned short *)((unsigned char *)run + runLen - 2) = 0;
				owned = 1;
			}
			if (table->rva006C21C0(len, run))
				return true;
			if (owned)
				rva006C1A50Free(run);
			return false;
		}
	}
done:
	return owned != 0;
}
