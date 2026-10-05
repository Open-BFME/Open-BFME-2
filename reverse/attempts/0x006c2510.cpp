// ?rva006C2510@Rva006C1F60@@QAEIPADHPAPAD@Z
// partial score=0.99 date=2026-10-05
// cl: /O2 /MD /EHsc
// ?rva006C2510@Rva006C1F60@@QAEIPADHPAPAD@Z @ 0x006C2510 (215B)
// Unlock lane: landing it makes 0x006C26F0 and 0x006C4730 ready.
// Evidence: lock at +0x4e4 with AddRef 0x00030DD0 / Release 0x00030DF0 (same
// layout as Rva006C1F60::rva006C1EB0); hash find at +0x684 via 0x006C1850
// (key>>3)%bucketCount row; trailing-length helper 0x006C1FE0 stdcall row;
// ret 0xC three args; thiscall (reads ecx first). Retail 0x006C2510 (215B).
// Same class as Rva006C1F60 (lock at +0x4E4), extended to +0x684 hash.
//
// THE SHAPE THAT IS EXACT, and why the previous banks could not see it.
// Retail materialises base and size as two SEPARATE registers across the
// out!=0 arm:
//
//   8b 74 24 18   mov  esi,[esp+0x18]   ; out
//   85 f6         test esi,esi
//   8b c8         mov  ecx,eax          ; size
//   8b c2         mov  eax,edx          ; base
//   66 8b 54 08 f6 mov dx,[eax+ecx-0xa] ; trail, INDEXED by the 32-bit size
//   74 0b         je   0x6c2573
//   0f b7 fa      movzx edi,dx
//   2b c7         sub  eax,edi
//   8d 44 08 f6   lea  eax,[eax+ecx-0xa]
//   89 06         mov  [esi],eax
//   0f b7 f2      movzx esi,dx
//   83 c6 02      add  esi,2
//
// Every earlier attempt (three passes, 4x4 load/store spellings crossed with
// forceinline helper splits) emitted 213B: VC7 folds the trailing-word load
// into ONE SIB displacement `mov cx,[eax+edx-0xa]` with the word zero-extended
// into ecx, because the ONLY use of `size` is that displacement and a
// displacement never needs a register. That saves the two `mov`s and the
// `movzx`, which is exactly why it is two bytes short.
//
// What changes the decision is giving `size` a second, LONGER-LIVED use: the
// named `off = size - 10` below is consumed by BOTH the trail load and the body
// store, so it is live ACROSS the load and the allocator must give it a
// register. VC7 then keeps size in ecx, reloads base into eax and emits the
// indexed form; it still folds `off` into the -0xa displacement, so the `off`
// local costs nothing.
//
// The store is spelled `(base - trail) + off`, which is retail's own
// reassociation -- `sub eax,edi` then `lea eax,[eax+ecx-0xa]`. The
// `base + off - trail` spelling gives the same bytes.
//
// Both arms return trail+2; only the store is conditional, and retail
// duplicates the `movzx/add 2` per arm while sharing one jmp. Do not collapse
// the two arms into a single `result = trail + 2` after a guarded store -- that
// is 208B (verified): it drops the je target's block and shortens both arms.
struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);

class Rva006C1850Node
{
public:
	unsigned int m_key;
	void *m_value;
	Rva006C1850Node *m_next;
};

class Rva006C1850
{
public:
	bool rva006C1850(unsigned int key, void **out);
private:
	Rva006C1850Node **m_table;
	int m_pad04;
	unsigned int m_bucketCount;
	int m_pad0C;
	int m_count;
	int m_pad14;
	void (__cdecl *m_freeFn)(void *block, void *allocator);
	void *m_allocator;
};

unsigned int __stdcall Rva006C1FE0(char *base, int length, char **bodyOut);

class Rva006C1F60
{
public:
	unsigned int rva006C2510(char *base, int type, char **out);
private:
	unsigned char m_pad0[0x4e4];
	Rva00030DD0Lock *m_lock;
	unsigned char m_pad1[0x514 - 0x4e4 - 4];
	int m_flags;
	unsigned char m_pad2[0x534 - 0x514 - 4];
	float m_scale;
	unsigned int m_min;
	unsigned int m_max;
	unsigned char m_pad3[0x67c - 0x540];
	unsigned int m_67c;
	unsigned char m_680;
	unsigned char m_pad680[3];
	Rva006C1850 m_hash;
};

// ?rva006C2510@Rva006C1F60@@QAEIPADHPAPAD@Z present-unmatched
// Both arms return trail+2. The store happens only when out!=0; retail tests
// the out pointer (test esi,esi) and the je skips the body store, not the
// result. `bp = base - 10` is what forces the trailing-word load to index off
// `size` rather than fold into one SIB displacement, giving retail's 215B.
unsigned int Rva006C1F60::rva006C2510(char *base, int type, char **out)
{
	Rva00030DD0Lock *lock = m_lock;
	if (lock != 0)
		Rva00030DD0AddRef(lock);
	unsigned int result = 0;
	unsigned int eff = (unsigned int)type;
	if (eff == 2)
		eff = m_67c;
	if (eff == 0) {
		unsigned int h = *(unsigned int *)(base - 4);
		unsigned int size;
		if ((h & 2) == 0)
			size = (h & 0x7ffffff8) + 4;
		else
			size = h & 0x7ffffff8;
		char *bp = (char *)base - 10;
		unsigned short trail = *(const unsigned short *)(bp + size);
		if (out != 0) {
			*out = (bp - trail) + size;
			result = trail + 2;
		}
		else
			result = trail + 2;
	} else {
		if (m_680 == 0)
			goto done;
		void *found = 0;
		if (!m_hash.rva006C1850((unsigned int)base, &found))
			goto done;
		if (found == 0)
			goto done;
		char *val = *(char **)found;
		unsigned short len = *(unsigned short *)val;
		if (len == 0)
			goto done;
		result = Rva006C1FE0(val + 2, (int)len - 2, out);
	}
done:
	if (lock != 0)
		Rva00030DF0Release(lock);
	return result;
}