// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva002245FF@Rva002245FF@@QAEXHABVAsciiString@@@Z @0x002245FF 77B
// Indexed erase wrapper over array at +0xdc stride 0x28 via rowed erase 0x00223736.
// Evidence: chain lane calls rowed 0x00223736 plus rowed StringBase copy 0x000365F0 plus rowed releaseBuffer 0x00036410 with EH prolog; callers at 0x00523F8C 0x00524477.
#include "ascii_string.h"

class Rva00223591
{
public:
	int rva00223736(const AsciiString *key);
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

struct Slot002245FF
{
	Rva00223591 table;
	char m_pad[0x14];
};

class Rva002245FF
{
public:
	void rva002245FF(int idx, const AsciiString &key);
private:
	char m_pad[0xdc];
	Slot002245FF m_slots[8];
};

void Rva002245FF::rva002245FF(int idx, const AsciiString &key)
{
	AsciiString tmp(key);
	Rva00223591 *tbl = &m_slots[idx].table;
	tbl->rva00223736(&tmp);
}
