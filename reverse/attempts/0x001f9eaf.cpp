// ?bfmeStopCW@ParticleSystemManager@@QAEXABVBFMERetailAsciiString@@@Z
// partial score=0.95 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// ?bfmeStopCW@ParticleSystemManager@@QAEXABVBFMERetailAsciiString@@@Z @0x001F9EAF 89B leaf: find in +0x88 map via rowed 0x0041534B reset via 0x001F58D4 deleteInstance plus erase via pinned 0x003A37DC
// evidence: pin bfmeStopCW plus donor BFME1 ParticleSystemManager_bfmeStopCW plus rowed find 0x0041534B plus rowed reset 0x001F58D4 plus pin-only erase 0x003A37DC plus operator delete 0x0002FD60; caller 0x00204C49
#include "ascii_string.h"

class BFMERetailAsciiString;
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

class Rva001F58D4
{
public:
	void rva001F58D4();
};

struct VideoPair
{
	void *a;
	void *b;
};

class Rva000427195
{
public:
	void rva003A37DC(VideoPair p);
};

class ParticleSystemTemplate
{
public:
	virtual void *deleteInstance(int flags);
};

class ParticleSystemManager
{
public:
	void bfmeStopCW(const BFMERetailAsciiString &name);
	void reset();
private:
	unsigned char m_pad[0x88];
	Rva00056F61 m_map;
};

class BFMERetailAsciiString
{
public:
	const char *str() const;
};

// ?bfmeStopCW@ParticleSystemManager@@QAEXABVBFMERetailAsciiString@@@Z present-unmatched
void ParticleSystemManager::bfmeStopCW(const BFMERetailAsciiString &name)
{
	Rva0041534BIter find = ((Rva00056F61 *)&m_map)->rva0041534B((const AsciiString *)&name);
	void *node = find.m_node;
	if (node == 0)
		return;
	((Rva001F58D4 *)this)->rva001F58D4();
	ParticleSystemTemplate *tmpl = *(ParticleSystemTemplate **)((char *)node + 8);
	::operator delete(tmpl ? tmpl->deleteInstance(0) : 0);
	((Rva000427195 *)&m_map)->rva003A37DC(*(VideoPair *)&find);
}
