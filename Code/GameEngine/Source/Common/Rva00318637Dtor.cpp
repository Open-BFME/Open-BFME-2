// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva00318637@@UAE@XZ retail 0x00318637 110B
// Called by the rowed scalar deleting dtor 0x0031861B (vtable 0x00C0C734#0).
// Own vptrs at +0 and +0x0C; the 8-byte record array at +0x30 (x5) runs the
// vector dtor iterator with the rowed element dtor VA 0x0050F149 (gen-uw pin
// name), then the AsciiString at +0x20, the rowed pool member dtor 0x00360D26
// at +0x1C, the inline Snapshot base vptr restore (0x00BBB554) at +0x0C and
// the rowed base dtor ??1GameEngineDeletingBase@@UAE@XZ 0x001B4E74.
#include "ascii_string.h"

class Rva00360D26Member
{
public:
	~Rva00360D26Member();
private:
	void *m_ptr;
};

class Gen_uw_0010f149
{
public:
	~Gen_uw_0010f149();
private:
	void *m_ptr;
	int m_value;
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[8];
};

class Rva00318637Snapshot
{
public:
	virtual ~Rva00318637Snapshot() {}
private:
	char m_pad04[0x1C - 0x10];
};

class Rva00318637 : public GameEngineDeletingBase, public Rva00318637Snapshot
{
public:
	virtual ~Rva00318637();
private:
	Rva00360D26Member m_filter1C; // +0x1C
	AsciiString m_name20; // +0x20
	char m_pad24[0x30 - 0x24];
	Gen_uw_0010f149 m_records30[5]; // +0x30
};

Rva00318637::~Rva00318637()
{
}
