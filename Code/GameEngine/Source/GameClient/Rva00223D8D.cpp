// cl: /Ireference/shims/bfme2_ascii /MD /GX-
// ?rva00223D8D@Rva00223D8D@@QAEXPBDHHHH@Z @0x00223D8D 74B
// Chain from 0x0022297B: null-guard const char* then AsciiString temp over arg slot to rowed find 0x00056F61 at +0x34 then releaseBuffer then invoke 0x0022297B via node+8 with four ints. Table at +0x34 node {next+0 name+4 ref+8} so +8 is Rva0022297BRef.
// Evidence: callees rowed 0x00037BA0 0x00056F61 0x00036410 0x0022297B; caller 0x000AA645; offsets +0x34/+8 from disasm; ret 0x14 five args.
#include "ascii_string.h"

class Rva0022297BRef
{
public:
	void invoke(int a, int b, int c, int d);
};

class Rva00056F61
{
public:
	void *rva00056F61(const AsciiString *key);
};

class Rva00223D8D
{
public:
	void rva00223D8D(const char *name, int a, int b, int c, int d);
	char m_pad[0x34];
	Rva00056F61 m_table;
};

void Rva00223D8D::rva00223D8D(const char *name, int a, int b, int c, int d)
{
	if (name == 0)
		return;
	void *node;
	{
		AsciiString tmp(name);
		node = m_table.rva00056F61(&tmp);
	}
	if (node == 0)
		return;
	((Rva0022297BRef *)((char *)node + 8))->invoke(a, b, c, d);
}
