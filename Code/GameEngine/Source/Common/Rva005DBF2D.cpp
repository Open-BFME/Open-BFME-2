// cl: /DNDEBUG /MD
//
// ?sentAPingPacket@PortNegotiationSchema@@QAE_NGG@Z @0x005DBF2D 95B.
// PortNegotiationSchema float bump notify: element +8 += 1.0f, stamp
// timeGetTime()+g_00DD35C4 into +0x718[y], then list at +0x04 forEach
// with notify 0x001FF3A9. Evidence: caller 0x005A6FAD; callees rowed
// 0x005DB98E/0x005DBE6A/0x001FF3A9; neighbours 0x005DBEEB/0x005DC3C1;
// same forEach cast shape as Rva005DC3C1.cpp; 1.0f is a compiler
// literal per Elem precedent, not an extern.
class Rva005DBE6AListener
{
public:
	virtual void notify(void *, int, int);
};

class Rva005DBE6AList
{
public:
	void forEach(void (Rva005DBE6AListener::*notify)(void *, int, int), void *arg, int value, int extra);
private:
	Rva005DBE6AListener **m_begin;
	Rva005DBE6AListener **m_end;
	Rva005DBE6AListener **m_capacity;
	unsigned int m_index;
};

class Rva001FF3A9
{
public:
	virtual void rva001FF3A9();
};

struct Elem005DB98E
{
	float m_00;
	float m_04;
	float m_08;
};

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
extern int g_00DD35C4;

class PortNegotiationSchema
{
public:
	void *peekPing(unsigned short x, unsigned short y);
	bool sentAPingPacket(unsigned short x, unsigned short y);
private:
	char m_pad00[4];
	Rva005DBE6AList m_list;
	char m_pad14[0x718 - 0x14];
	int m_718[9];
};

bool PortNegotiationSchema::sentAPingPacket(unsigned short x, unsigned short y)
{
	Elem005DB98E *elem = (Elem005DB98E *)peekPing(x, y);
	if (!elem)
		return false;
	elem->m_08 += 1.0f;
	m_718[y] = timeGetTime() + g_00DD35C4;
	m_list.forEach((void (Rva005DBE6AListener::*)(void *, int, int))&Rva001FF3A9::rva001FF3A9, this, x, y);
	return true;
}
