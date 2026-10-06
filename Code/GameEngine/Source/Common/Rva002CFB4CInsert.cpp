// cl: /Ireference/shims/bfme2_ascii /MD
// stlport
// ?rva002CFB4C@Rva002CFB4C@@QAEPAXPBX@Z @0x002CFB4C 68B via bucket insert plus create
// Evidence: thiscall ret4 takes pair at offset0 AsciiString; rowed bucketIndex 0x00223149 plus pin rva00212858 0x00212858 on Rva000427195; rowed create 0x002CF9DC; caller 0x002CFEEC passes pair and uses return+4
#include <map>
#include "ascii_string.h"
struct NoCaseTreeValue4
{
	unsigned char m_data[4];
};
class Rva000427195
{
public:
	void rva00212858(unsigned int v);
	int bucketIndex(const AsciiString *name);
	void *createNode(const _STL::pair<const AsciiString, NoCaseTreeValue4> *src);
};
class Rva002CFB4C
{
public:
	void *rva002CFB4C(const void *src);
private:
	void *m_unused00;
	void **m_begin;
	void **m_end;
	char m_pad0C[4];
	int m_size;
};
void *Rva002CFB4C::rva002CFB4C(const void *src)
{
	((Rva000427195 *)this)->rva00212858((unsigned int)(m_size + 1));
	int idx = ((Rva000427195 *)this)->bucketIndex((const AsciiString *)src);
	void *old = m_begin[idx];
	void *node = ((Rva000427195 *)this)->createNode((const _STL::pair<const AsciiString, NoCaseTreeValue4> *)src);
	*(void **)node = old;
	m_begin[idx] = node;
	++m_size;
	return (char *)node + 4;
}
