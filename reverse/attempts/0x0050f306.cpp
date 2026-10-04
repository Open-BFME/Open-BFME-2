// ?rva0050F306@Rva0050F0AB@@QAEXXZ
// partial score=0.93 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc
//
// ?rva0050F306@Rva0050F0AB@@QAEXXZ @0x0050F306 154B: Rva0050F0AB refresh via vtable slot1 plus Player+0x94 plus records via rowed 0x002A8F24 plus format via rowed 0x006CB5D0 plus 0x0050F041; callers at 0x0050FCC8 0x0050FF50; class from prev/next Rva0050F0AB
#include "unicode_string.h"

struct Player90
{
	int m_00;
	int m_04;
};
struct Player
{
	char m_pad[0x90];
	Player90 m_90;
};
class Rva002A8F24;
class Rva002A8AB1Record;
class Rva0050F041
{
public:
	void rva0050F041(int v, const UnicodeString &s);
};

class Rva002A8F24
{
public:
	void *rva002A8AB1(void *p);
	void *rva002A8F24(Player *p);
};

extern Rva002A8F24 *g_00DFEEF8;
extern const unsigned short g_00C65578[];

class Rva0050F0AB
{
public:
	virtual void pad0();
	virtual int pad1();
	void rva0050F306();
private:
	char m_pad04[0x60];
	Player *m_64;
	unsigned int m_68;
	unsigned int m_6c;
	int m_70;
	char m_pad74[0x78 - 0x74];
	void *m_78;
	void *m_7c;
};

// ?rva0050F306@Rva0050F0AB@@QAEXXZ present-unmatched
void Rva0050F0AB::rva0050F306()
{
	int v = pad1();
	Player90 *p = &m_64->m_90;
	if (p)
		v += p->m_04;
	Rva002A8AB1Record *rec = (Rva002A8AB1Record *)g_00DFEEF8->rva002A8AB1((void *)m_64);
	if (rec)
	{
		void *r = g_00DFEEF8->rva002A8F24(m_64);
		v += *(int *)(*(char **)((char *)r + 0xc) + 0x14);
	}
	if (v != m_70 || m_70 == -1)
	{
		UnicodeString buf;
		buf.format(g_00C65578, v);
		((Rva0050F041 *)this)->rva0050F041(1, buf);
		m_70 = v;
	}
}
