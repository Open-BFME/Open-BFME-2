// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002B7D91@Glo012F1028Type@@QAEXXZ, retail 0x002B7D91 (85 bytes). Same owner as the rowed
// Glo012F1028Type::j_00008c0b (Glo012F1028TypeClearEntries.cpp, 0x002B7D50, its +0xD8 list): the second
// owning pointer list, at +0x8C. Every entry goes through the null-guarded deleteInstance(0) plus
// operator delete path, the list is cleared with the rowed pointer-vector erase (0x0031BD55) and the
// count word at +0x98 is zeroed.
#include <vector>

class Glo012F1028Entry
{
public:
	virtual void *deleteInstance(int flags);
};

class Glo012F1028Type
{
public:
	void rva002B7D91();

private:
	char m_pad[0x8C];
	_STL::vector<Glo012F1028Entry *> m_owned;	// +0x8C
	int m_count;					// +0x98
};

void Glo012F1028Type::rva002B7D91()
{
	for (unsigned int i = 0; i < m_owned.size(); ++i)
		::operator delete(m_owned[i] ? m_owned[i]->deleteInstance(0) : 0);
	_STL::vector<void *> &raw = (_STL::vector<void *> &)m_owned;
	raw.erase(raw.begin(), raw.end());
	m_count = 0;
}
