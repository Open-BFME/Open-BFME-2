// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva002ADD31@Rva002ADD31@@QAEPAXPBX@Z retail 0x002ADD31 68B
// Evidence: hashtable insert same 68B shape as sibling 0x002CFB4C via pin resize 0x00212858 plus rowed bucketIndex 0x00223149 plus thiscall NewNode 0x002ACFD6; buckets at +4 count at +0x10 return node+4; caller 0x002AE4C5
#include "ascii_string.h"

class Rva000427195
{
public:
	void rva00212858(unsigned int v);
	int bucketIndex(const AsciiString *name);
	void *rva002ACFD6(const void *src);
};

class Rva002ADD31
{
public:
	void *rva002ADD31(const void *src);
private:
	void *m_unused00;
	void **m_begin;
	void **m_end;
	char m_pad0C[4];
	int m_size;
};

void *Rva002ADD31::rva002ADD31(const void *src)
{
	((Rva000427195 *)this)->rva00212858((unsigned int)(m_size + 1));
	int idx = ((Rva000427195 *)this)->bucketIndex((const AsciiString *)src);
	void *old = m_begin[idx];
	void *node = ((Rva000427195 *)this)->rva002ACFD6(src);
	*(void **)node = old;
	m_begin[idx] = node;
	++m_size;
	return (char *)node + 4;
}
