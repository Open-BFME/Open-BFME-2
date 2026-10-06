// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?rva00242F1A@Rva00242F1A@@QAEPAXPBX@Z, retail 0x00242f1a, 68 bytes. Banked partial (score 0.99) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Hashtable insert twin of 0x002237C7 via pinned resize 0x00212858 then rowed bucket 0x00223149 then rowed create 0x00240D0F then link and return node+4.
// Evidence: chain lane calls just-landed 0x00240D0F; same 68B shape as Rva00223591::rva002237C7; caller 0x002460C3.
#include "ascii_string.h"

class Rva000427195
{
public:
	void rva00212858(unsigned int n);
	int bucketIndex(const AsciiString *name);
};

class Rva00240D0F
{
public:
	void *rva00240D0F(const void *obj);
};

class Rva00242F1A
{
public:
	void *rva00242F1A(const void *arg);
private:
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

void *Rva00242F1A::rva00242F1A(const void *arg)
{
	((Rva000427195 *)this)->rva00212858(m_numElements + 1);
	int b = ((Rva000427195 *)this)->bucketIndex((const AsciiString *)arg);
	void *old = m_beginBuckets[b];
	void *n = ((Rva00240D0F *)this)->rva00240D0F(arg);
	*(void **)n = old;
	m_beginBuckets[b] = n;
	++m_numElements;
	return (char *)n + 4;
}
