// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??1Rva00282500@@UAE@XZ, RVA 0x00282500, 174 bytes.
// Dtor of unknown class with vtable 0x007FB21C: unlinks +0x18/+0x1c node
// via g_Va00DFEC54 head, clears TerrainLogic+0x56c tree, then member dtors.
// Evidence: callees all rowed (0x00280AB6, 0x00360D26, 0x00036410 x5);
// caller 0x00282B9F 28B; vtable store at [this].
#include "ascii_string.h"

extern int g_Va00DFEC54;

class Rva0027F4CB
{
public:
	void rva00280AB6();
private:
	void *m_00Head;
	int m_04Flag;
};

class Rva00360D26Member
{
public:
	~Rva00360D26Member();
private:
	unsigned m_unknown;
};

class TerrainLogic
{
public:
	unsigned char m_pad[0x56c];
	Rva0027F4CB m_tree;
};

extern TerrainLogic *TheTerrainLogic;

class Rva00282500
{
public:
	virtual ~Rva00282500();
private:
	unsigned char m_pad04[0x4];
	AsciiString m_08;
	unsigned char m_pad0C[0xC];
	Rva00282500 *m_prev;
	Rva00282500 *m_next;
	unsigned char m_pad20[0x30];
	AsciiString m_50;
	AsciiString m_54;
	AsciiString m_58;
	unsigned char m_pad5C[0x8];
	AsciiString m_64;
	unsigned char m_pad68[0x54];
	Rva00360D26Member m_bc;
};

Rva00282500::~Rva00282500()
{
	if (m_next)
		m_next->m_prev = m_prev;
	if (m_prev)
		m_prev->m_next = m_next;
	else
		g_Va00DFEC54 = (int)m_next;
	if (TheTerrainLogic)
		TheTerrainLogic->m_tree.rva00280AB6();
}
