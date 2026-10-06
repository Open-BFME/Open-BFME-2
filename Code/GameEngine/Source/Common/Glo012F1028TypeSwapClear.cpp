// cl: /DNDEBUG /MD /EHsc
//
// ?rva002B7D03@Glo012F1028Type@@QAEXXZ, retail 0x002B7D03, 77 bytes.
// Swap-clear sibling of ?j_00008c0b@Glo012F1028Type@@QAEXXZ (0x002B7D50, 65B
// in Glo012F1028TypeClearEntries.cpp): swaps the two adjacent entry lists at
// +0xCC/+0xD8 via the rowed vector<BfmeE12> swap (0x00567ECD), then frees the
// +0xD8 list through the same null-guarded deleteInstance(0)-plus-??3 path
// and clears it with the pinned Glo012F1028EntryList::erase (0x0031BD55).
// Evidence: same push-ebx/esi/edi thiscall shape, same lea ebx,[edi+0xD8] plus
// lea ecx,[edi+0xCC] swap head, same cmp-vs-[edi+0xDC] loop and push-[ebx+4]/
// push-[ebx] erase tail as the 65B sibling; caller 0x002BC653.

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
	Glo012F1028Entry **m_cap;
	Glo012F1028Entry **erase(Glo012F1028Entry **first, Glo012F1028Entry **last);
};

struct BfmeE12 { float x, y, z; };
namespace _STL
{
template <class T> class allocator;
template <class T, class A> class vector
{
public:
	void swap(vector &);
};
}

class Glo012F1028Type
{
public:
	void rva002B7D03(void);
private:
	char m_pad[0xCC];
	Glo012F1028EntryList m_tmp; // +0xCC
	Glo012F1028EntryList m_entries; // +0xD8
};

void Glo012F1028Type::rva002B7D03(void)
{
	Glo012F1028EntryList *entries = &m_entries;
	reinterpret_cast<_STL::vector<BfmeE12, _STL::allocator<BfmeE12> > *>(&m_tmp)->swap(*reinterpret_cast<_STL::vector<BfmeE12, _STL::allocator<BfmeE12> > *>(entries));
	for (Glo012F1028Entry **entry = m_entries.m_begin; entry != m_entries.m_end; ++entry)
		::operator delete(*entry ? (*entry)->deleteInstance(0) : 0);
	entries->erase(entries->m_begin, entries->m_end);
}
