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

#include "../../Include/GameClient/Rva00056F61.h"

void *Rva00056F61::rva00056F61(const AsciiString *key)
{
	unsigned hash = Rva00055041AsciiHash(key);
	unsigned count = (unsigned)(((char *)m_endBuckets - (char *)m_beginBuckets) >> 2);
	// Retail reloads the bucket pointer after computing its count.
	Rva00056F61Node *cur = (*(Rva00056F61Node ** volatile *)&m_beginBuckets)[hash % count];
	while (cur != 0) {
		if (((const StringBase<char> *)&cur->m_name)->compare(*(const StringBase<char> *)key) == 0)
			break;
		cur = cur->m_next;
	}
	return cur;
}
