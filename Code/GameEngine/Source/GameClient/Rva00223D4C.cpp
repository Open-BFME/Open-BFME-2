// cl: /Ireference/shims/bfme2_ascii /MD /GX-
// ?OnCommand@AptPlayer@@QAEXPBDH@Z @0x00223D4C 65B
// Null-guard const char* then AsciiString temp over arg slot to rowed find 0x00056F61 at +0xC then releaseBuffer then invoke 0x0057CC15 via node+8 with one int. Table at +0xC node {next+0 name+4 ref+8} so +8 is Rva0057CC15Ref.
// Evidence: same shape as rowed sibling 0x00223D8D but table at +0xC and single-int invoke; callees rowed 0x00037BA0 0x00056F61 0x00036410 0x0057CC15; caller 0x000A91EB; ret 8 two args.
#include "ascii_string.h"

class Rva0057CC15Ref
{
public:
	void invoke(int v);
};

class Rva00056F61
{
public:
	void *rva00056F61(const AsciiString *key);
};

class AptPlayer
{
public:
	void OnCommand(const char *name, int v);
	char m_pad[0xC];
	Rva00056F61 m_table;
};

void AptPlayer::OnCommand(const char *name, int v)
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
	((Rva0057CC15Ref *)((char *)node + 8))->invoke(v);
}
