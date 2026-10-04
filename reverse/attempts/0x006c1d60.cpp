// ?rva006C1D60@Rva006C1D60@@QAE_NI_N@Z
// partial score=0.97 date=2026-10-05
// ?rva006C1D60@Rva006C1D60@@QAE_NI_N@Z
// cl: /EHsc /DNDEBUG /DWIN32 /MD
//
// ?rva006C1D60@Rva006C1D60@@QAE_NI_N@Z 0x006C1D60 (93B, chain from 0x006C18A0)
// Enable-guarded hash-table find-then-remove wrapper around Rva006C1850.
// Retail keeps the m_enabled test as a COLD forward branch to a shared tail
// (`mov al,[ecx+0x680]; test al,al; je <end>`), reproduced only by the outer
// `if (m_enabled) { ... }` form.
struct Rva006C1850Node
{
	unsigned int m_key;
	void *m_value;
	Rva006C1850Node *m_next;
};
class Rva006C1850
{
public:
	bool rva006C18A0(unsigned int key, bool freeValue);
	friend class Rva006C1D60;
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
class Rva006C1D60
{
public:
	bool rva006C1D60(unsigned int key, bool freeValue);
private:
	unsigned char m_pad[0x680];
	bool m_enabled;
	unsigned char m_pad681[3];
	Rva006C1850 m_table;
};
// ?rva006C1D60@Rva006C1D60@@QAE_NI_N@Z present-unmatched
bool Rva006C1D60::rva006C1D60(unsigned int key, bool freeValue)
{
	if (m_enabled)
	{
		Rva006C1850 *t = &m_table;
		Rva006C1850Node **table = t->m_table;
		if (table != 0)
		{
			int h = (key >> 3) % t->m_bucketCount;
			Rva006C1850Node *node = table[h];
			while (node != 0 && node->m_key != key)
				node = node->m_next;
			if (node != 0)
			{
				if (t->rva006C18A0(key, freeValue))
					return true;
			}
		}
		return false;
	}
	return false;
}
