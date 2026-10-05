// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ?rva0059E32F@Rva0059E32F@@QAEXPAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z at 0x0059E32F (97B). Collect ModuleData list via Logic+0xb0 lookup.
// Evidence: rowed vector erase 0x0031BD55 reserve 0x002B712E push_back 0x004DFCB0; g_009FEF10 via Rva002BA8F1Logic+0xb0 to rowed Rva002104B6 lookup; this+0x1c/0x20 begin/end like Rva0059E2FD.
#include "ascii_string.h"

class ModuleData;

namespace _STL {
template <typename T> class allocator {};
template <typename T, typename A> class vector
{
public:
	T *erase(T *, T *);
	void reserve(unsigned int);
	void push_back(const T &);
	void *_M_start;
	void *_M_finish;
	void *_M_end;
};
}

class Rva002104B6
{
public:
	void *rva002104B6(void *a1);
};

class Rva002BA8F1Logic
{
public:
	unsigned char m_pad[0xb0];
	Rva002104B6 *m_b0;
};
extern Rva002BA8F1Logic *g_009FEF10;

class Rva0059E32F
{
public:
	void rva0059E32F(_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > *out);
private:
	unsigned char m_pad[0x1c];
	StringBase<char> *m_begin;
	StringBase<char> *m_end;
};

void Rva0059E32F::rva0059E32F(_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > *out)
{
	((_STL::vector<void *, _STL::allocator<void *> > *)out)->erase((void **)out->_M_start, (void **)out->_M_finish);
	out->reserve(m_end - m_begin);
	for (StringBase<char> *p = m_begin, *e = m_end; p != e; ++p) {
		const ModuleData *found = (const ModuleData *)g_009FEF10->m_b0->rva002104B6(p);
		if (found)
			out->push_back(found);
	}
}
