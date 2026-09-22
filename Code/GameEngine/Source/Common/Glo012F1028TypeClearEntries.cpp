// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?j_00008c0b@Glo012F1028Type@@QAEXXZ, retail 0x002B7D50, 65 bytes.
// Shard TU (home TU Glo012F1024ItemRun.cpp keeps the file-unit decls plus the
// rowed run body; this shard owns the clear-entries body only).
//
// Shape, all retail-measured: thiscall homes this in edi and materializes
// &m_entries in ebx; the pointer range [m_begin, m_end) is walked with the
// finish reloaded from +0xDC every trip; each slot frees through the
// null-guarded deleteInstance-plus-operator-delete free path (the same free
// path as Radar::deleteListResources: virtual slot 0 takes a zero word and
// whatever it returns goes to ??3, with a test-and-branch around the
// virtual); the tail clears the range with the rowed vector<void*>::erase
// (0x0031BD55) via an alias pin. The mixed access (loop limits through this,
// erase arguments through the ebx pointer) is load-bearing: reading the tail
// through this emits push [edi+0xDC] instead of retail's push [ebx+4].

class Glo012F1028Entry
{
public:
	virtual void *deleteInstance(int flags);
};

class Glo012F1028EntryList
{
public:
	Glo012F1028Entry **m_begin;
	Glo012F1028Entry **m_end;
	Glo012F1028Entry **erase(Glo012F1028Entry **first, Glo012F1028Entry **last);
};

class Glo012F1028Type
{
public:
	void j_00008c0b(void);
private:
	char m_pad[0xD8];
	Glo012F1028EntryList m_entries; // +0xD8
};

// ?j_00008c0b@Glo012F1028Type@@QAEXXZ
void Glo012F1028Type::j_00008c0b(void)
{
	Glo012F1028EntryList *entries = &m_entries;
	for (Glo012F1028Entry **entry = m_entries.m_begin; entry != m_entries.m_end; ++entry)
		::operator delete(*entry ? (*entry)->deleteInstance(0) : 0);
	entries->erase(entries->m_begin, entries->m_end);
}
