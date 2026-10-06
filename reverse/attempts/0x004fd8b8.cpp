// ?rva004FD8B8@Rva004FD6F9@@QAEXABVAsciiString@@AAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@Z
// partial score=0.88 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// ?rva004FD8B8@Rva004FD6F9@@QAEXABVAsciiString@@AAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@Z @0x004FD8B8 150B
// Evidence: same this as rowed rva004FD6F9 0x004FD6F9 (calls it with esi);
// this+0x44/+0x48 AsciiString array walk; out vector erase/push_back ScienceType;
// TheLivingWorldLogic+0xB0 find 0x0020F442 then per-element 0x00210390 filter.
#include "ascii_string.h"

enum ScienceType
{
	SCIENCE_FIRST = 0
};

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector
{
public:
	T *_M_start;
	T *_M_finish;
	T *_M_end;
	T *erase(T *first, T *last);
	void push_back(const T &val);
};
}

class LivingWorldLogic
{
public:
	unsigned char m_pad[0xb0];
	class Rva0020F442 *m_ptrB0;
};

extern LivingWorldLogic *TheLivingWorldLogic;

class Rva0020F442
{
public:
	AsciiString *rva0020F442(const AsciiString &key);
};

class Rva00210390
{
public:
	void *rva00210390(const AsciiString *key);
};

struct Payload
{
	unsigned char m_pad[0x12c];
	ScienceType m_science;
};

class Rva004FD6F9
{
public:
	unsigned char m_pad00[0x38];
	StringBase<char> *m_begin38;
	StringBase<char> *m_end3C;
	unsigned char m_pad40[0x44 - 0x40];
	StringBase<char> *m_begin44;
	StringBase<char> *m_end48;
	bool rva004FD6F9(const StringBase<char> &val);
	void rva004FD8B8(const AsciiString &name, _STL::vector<ScienceType, _STL::allocator<ScienceType> > &out);
};

void Rva004FD6F9::rva004FD8B8(const AsciiString &name, _STL::vector<ScienceType, _STL::allocator<ScienceType> > &out)
{
	out.erase(out._M_start, out._M_finish);
	if (m_begin44 == m_end48)
		return;
	AsciiString *found = TheLivingWorldLogic->m_ptrB0->rva0020F442(name);
	if (!found)
		return;
	unsigned int count = (unsigned int)(m_end48 - m_begin44);
	for (unsigned int i = 0; i < count; ++i)
	{
		Rva00210390 *table = (Rva00210390 *)found;
		void *payload = table->rva00210390((const AsciiString *)&m_begin44[i]);
		if (!payload)
			continue;
		if (!rva004FD6F9(m_begin44[i]))
			continue;
		out.push_back(((Payload *)payload)->m_science);
	}
}
