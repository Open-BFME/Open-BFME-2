// ?rva006C2510@Rva006C1F60@@QAEIPADHPAPAD@Z
// partial score=0.95 date=2026-10-05
// ?rva006C2510@Rva006C1F60@@QAEIPADHPAPAD@Z

// cl: /O2 /MD /EHsc
// ?rva006C2510@Rva006C1F60@@QAEIPADHPAPAD@Z, retail 0x006C2510, 214 bytes.
// Unlock lane: landing it makes 0x006C26F0 and 0x006C4730 ready.
// Evidence: lock at +0x4e4 with AddRef 0x00030DD0 / Release 0x00030DF0 (same
// layout as Rva006C1F60::rva006C1EB0); hash find at +0x684 via 0x006C1850
// (key>>3)%bucketCount row; trailing-length helper 0x006C1FE0 stdcall row;
// ret 0xC three args; thiscall (reads ecx first).
// Same class as Rva006C1F60 (lock at +0x4e4), extended to +0x684 hash.
// The lock is taken through the same RAII guard the matched siblings 0x006C1E20
// and 0x006C3840 use: it parks `this` in esi and the lock in edi, and emits the
// tail-jump release, which retail's `mov ecx,edi` / call 0x00030DF0 / `mov eax,
// esi` epilogue proves.
struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);

class Rva00030DD0Guard
{
public:
	Rva00030DD0Guard(Rva00030DD0Lock *lock) : m_lock(lock)
	{
		if (m_lock != 0)
			Rva00030DD0AddRef(m_lock);
	}
	~Rva00030DD0Guard()
	{
		if (m_lock != 0)
			Rva00030DF0Release(m_lock);
	}

private:
	Rva00030DD0Lock *m_lock;
};

struct Rva006C1850Node
{
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
		char *p = base;
		unsigned int h = *(unsigned int *)(base - 4);
		unsigned int size;
		if ((h & 2) == 0)
			size = (h & 0x7ffffff8) + 4;
		else
			size = h & 0x7ffffff8;
		unsigned short trail = *(unsigned short *)(size + p - 10);
		if (out != 0) {
			// Retail keeps the chunk base and the size separate so the tail
			// length indexes off the base and the two lea forms come out in
			// source order: base minus the length, then plus size - 10.
			char *const body = p - trail;
			*out = body + (size - 10);
			result = trail + 2;
		} else {
			result = trail + 2;
		}
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
