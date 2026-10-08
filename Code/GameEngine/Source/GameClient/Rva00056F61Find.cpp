// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva00056F61@Rva00056F61@@QAEPAXPBVAsciiString@@@Z, retail 0x00056F61 (61B).
// Hash-mod-count find over the bucket vector. Same shape as the rowed
// ?bucketIndex@Rva000427195@@QAEHPBVAsciiString@@@Z at 0x00223149 (identical
// prolog through div) plus a linked-list walk comparing the node name at +4
// via rowed ?compare@?$StringBase@D@@QBEHABV1@@Z. Node {next+0 name+4} and
// table {unused+0 begin+4 end+8} read off the disassembly and the
// EvaBucketIndex/EvaBucketAdvance archaeology notes. Callers at 0x001DEACA
// (Eva event INI parse), 0x00216F6D (BannerMen lookup) and 0x000A8200 prove
// a shared AsciiString-keyed table; owner unproven so honest-address name.

#include "ascii_string.h"


unsigned int __stdcall Rva00055041AsciiHash(const AsciiString *name);

struct Rva00056F61Node
{
	Rva00056F61Node *m_next;
	AsciiString m_name;
};

class Rva00056F61
{
public:
	// The verified hash/compare chain only reads key and bucket storage. It
	// allocates nothing and invokes no application callback or C++ throw.
	__declspec(nothrow) void *rva00056F61(const AsciiString *key);
	void *m_unused;
	// The begin field reads twice with different scheduling: the count
	// computation folds it into a direct `sub ecx,[esi+4]` (single use, no
	// homing) while the bucket fetch re-fetches it (`mov eax,[esi+4]` plus
	// indexed `mov esi,[eax+edx*4]`). A single spelling serves only one side,
	// so the union carries both: the plain member for count, the volatile
	// member for the fetch (EvaBucketAdvance precedent).
	union {
		Rva00056F61Node **m_begin;
		Rva00056F61Node ** volatile m_beginVolatile;
	};
	Rva00056F61Node **m_end;
};

void *Rva00056F61::rva00056F61(const AsciiString *key)
{
	unsigned hash = Rva00055041AsciiHash(key);
	unsigned count = (unsigned)(((char *)m_end - (char *)m_begin) >> 2);
	Rva00056F61Node *cur = m_beginVolatile[hash % count];
	while (cur != 0) {
		if (((const StringBase<char> *)&cur->m_name)->compare(*(const StringBase<char> *)key) == 0)
			break;
		cur = cur->m_next;
	}
	return cur;
}
