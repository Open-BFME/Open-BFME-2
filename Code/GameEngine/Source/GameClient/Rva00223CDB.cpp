// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva00223CDB@Rva00223CDB@@QAEHPBVAsciiString@@@Z @0x00223CDB 39B
// Find-int over table at +0x5c via rowed Iter find 0x0041534B.
// Evidence: add ecx 0x5c then call rowed Rva00056F61::rva0041534B with hidden
// Iter out {node table}; null node returns -1 else int at node+8. Same shape
// as sibling 0x00223A9F but or eax -1 fallthrough. Callers 0x0022472A 11B and
// 0x0022486C; landing unblocks 0x00224818.
#include "ascii_string.h"

struct Rva0041534BIter
{
	void *m_node;
	void *m_table;
};

class Rva00056F61
{
public:
	Rva0041534BIter rva0041534B(const AsciiString *key);
};

class Rva00223CDB
{
public:
	int rva00223CDB(const AsciiString *key);

	char m_pad[0x5c];
	Rva00056F61 m_table;
};

int Rva00223CDB::rva00223CDB(const AsciiString *key)
{
	Rva0041534BIter it = m_table.rva0041534B(key);
	if (it.m_node == 0)
		return -1;
	return *(int *)((char *)it.m_node + 8);
}
