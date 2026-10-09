// cl: /Ireference/shims/bfme2_ascii /EHsc /O1 /arch:SSE /G7
// ??0Rva005D0643@@QAE@PAXH@Z @ 0x005D0AD5 137B. Constructor of the opaque
// Rva005D0643 (pinned dtor 0x005D0643, scalar deleting dtor 0x005D08E1,
// vtable 0x00C75538). Target evidence: first base owner at +4, two listener
// bases at +8 (vtable 0x00C62A14) and +0xC (0x00C62A20), final vtables
// 0x00C75538/0x00C7552C/0x00C75524, timeGetTime at +0x10, second argument at
// +0x14, byte at +0x18 cleared; the +8 base joins TheLivingWorldLogic's list at
// +0x2C and the +0xC base the one at +0x3C (rowed append 0x005A0B4C).
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

struct Rva002BA8F1Listener;

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *p);
};

class LivingWorldLogic
{
public:
	char m_pad[0x2C];
	Rva005A0B4CList m_list2C;
	char m_pad3[0x3C - 0x2C - sizeof(Rva005A0B4CList)];
	Rva005A0B4CList m_list3C;
};
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva005D0643B1
{
public:
	Rva005D0643B1(void *owner) : m_04(owner) {}
	virtual ~Rva005D0643B1() {}
private:
	void *m_04;
};

class Rva005D0643B2
{
public:
	virtual ~Rva005D0643B2() {}
};

class Rva005D0643B3
{
public:
	virtual ~Rva005D0643B3() {}
};

class Rva005D0643 : public Rva005D0643B1, public Rva005D0643B2, public Rva005D0643B3
{
public:
	Rva005D0643(void *owner, int value);
	virtual ~Rva005D0643();
private:
	unsigned long m_10;
	int m_14;
	bool m_18;
};

Rva005D0643::Rva005D0643(void *owner, int value)
	: Rva005D0643B1(owner)
{
	m_10 = timeGetTime();
	m_14 = value;
	m_18 = false;
	TheLivingWorldLogic->m_list2C.append((Rva002BA8F1Listener *)static_cast<Rva005D0643B2 *>(this));
	TheLivingWorldLogic->m_list3C.append((Rva002BA8F1Listener *)static_cast<Rva005D0643B3 *>(this));
}
