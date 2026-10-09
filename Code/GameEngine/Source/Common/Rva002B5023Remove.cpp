// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002B5023@Rva002B5023Owner@@QAEXPAVGlo012F1028Entry@@@Z, retail 0x002B5023 (80 bytes, ret 4). Owner
// unproven (address token; same neighbourhood as the rowed Rva002B4FEB). Removes one entry from the owning
// pointer list at +0xCC/+0xD0: find it (the folded 4-byte find, rowed under its int spelling at 0x0020E873),
// free it through the null-guarded deleteInstance(0) plus operator delete path of Glo012F1028Type, and erase
// the slot with the rowed single-element pointer-vector erase (0x001FF51F).
#include <vector>

class Glo012F1028Entry
{
public:
	virtual void *deleteInstance(int flags);
};

class Rva002B5023Owner
{
public:
	void rva002B5023(Glo012F1028Entry *entry);

private:
	char m_pad[0xCC];
	_STL::vector<void *> m_entries;		// +0xCC
};

void Rva002B5023Owner::rva002B5023(Glo012F1028Entry *entry)
{
	Glo012F1028Entry *key = entry;
	void **last = m_entries.end();
	void **found = (void **)_STL::find((int *)m_entries.begin(), (int *)last, (const int &)key);
	if (found != last) {
		Glo012F1028Entry *victim = (Glo012F1028Entry *)*found;
		::operator delete(victim ? victim->deleteInstance(0) : 0);
		m_entries.erase(found);
	}
}
