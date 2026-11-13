// cl: /MD /EHsc
// ??0Rva005AFE3F@@QAE@PAX@Z, retail 0x005AFE86, 85 bytes.
// Chain ctor: stores vtable 0x00C728B8, arg at +4, zeroes +8..+20,
// then appends this to global list via Get 0x00381452 (returns 0x00E02310)
// and append 0x005A0B4C. Base 0x005AFE86 calls derived 0x005D57D3.
// EH state 0 covers the listener base, whose destructor the unwind reaches at
// 0x0057C03B (it restores table 0x00C6FFFC at +0). Evidence: callers
// 0x005AF9F4 0x005D509C 0x005D57DA, callees rowed, vtable store.

int Rva00381452Get(void);

struct Rva002BA8F1Listener
{
	char opaque[4];
};

#include "../../Include/Common/Rva005A0B4CList.h"

struct Rva005AFD89Param;
class AsciiString;
class UnicodeString;
class GameWindow;

// Retail table 0x00C6FFFC: two __purecall slots. The destructor is not in the
// table; it only restores it.
class Rva005AFE3FBase
{
public:
	virtual void rva005AFD89(int id, const Rva005AFD89Param *p) = 0;
	virtual void rva005AFCEC(int id) = 0;
	~Rva005AFE3FBase() {}
};

// Retail table 0x00C728B8, six slots: 0x005AFD89, 0x005AFCEC, the deleting
// destructor 0x005AFEDB, two __purecall slots and the shared `ret 4` 0x0047A69C.
// Slot 3 is the PopulatePlayerList the derived tables fill; slots 4 and 5 keep
// slot names (the derived rows at them take a string reference and a window,
// and a string reference).
class Rva005AFE3F : public Rva005AFE3FBase
{
public:
	Rva005AFE3F(void *p);
	virtual void rva005AFD89(int id, const Rva005AFD89Param *p);
	virtual void rva005AFCEC(int id);
	virtual ~Rva005AFE3F();
	virtual bool PopulatePlayerList() = 0;
	virtual bool vslot04(const UnicodeString &text, GameWindow *window) = 0;
	virtual void vslot05(const AsciiString &name) {}

	void *m_04;
	int m_08;
	GameWindow *m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
};

Rva005AFE3F::Rva005AFE3F(void *p)
	: m_04(p)
{
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_20 = 0;
	((Rva005A0B4CList *)(unsigned int)Rva00381452Get())->append((Rva002BA8F1Listener *)(void *)this);
}
