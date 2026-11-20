// cl: /O1 /G7 /arch:SSE /MD /EHsc
//
// ?rva005D0034@Rva005D078B@@UAEXHHH@Z, retail 0x005D0034 (77 bytes, RET 0x0C):
// the only slot of the listener vtable 0x00C75570 that Rva005D078B (and its
// identical twin Rva005D078B) install on their +0x10 base, the base the
// constructor appends to TheLivingWorldLogic's +0x6C list. When the event's
// second word is TheLivingWorldLogic's +0x98 value and its third word is the
// +0x14 value of the object the base keeps at +0x04, that object's +0x1C
// holder is given a new 8-byte callback on it (vtable 0x00C752A8; holder
// replacement rowed 0x00575674). The event word names are not known.


// The callback's owner pointer lives in Rva005CF872, and Rva005D1255 installs
// vtable 0x00C752A8 (??_GRva005D1255@@UAEPAXI@Z + ?Update@Rva005D1255@@UAEXXZ).
class Rva005CF872
{
public:
	Rva005CF872(void *p) : owner(p) {}
	virtual ~Rva005CF872() {}
	virtual void Update() {}
	void *owner;
};

class Rva005D1255 : public Rva005CF872
{
public:
	Rva005D1255(void *p) : Rva005CF872(p) {}
	virtual ~Rva005D1255();
	virtual void Update();
};

// The +0x1C holder is replaced through its rowed setter 0x00575674.
#include "../../../Include/Common/Rva00575674.h"

class Rva005D0034Target
{
public:
	unsigned char m_pad00[0x14];
	int m_objectID;				// +0x14
	unsigned char m_pad18[0x1C - 0x18];
	Rva00575674 m_callbackHolder;			// +0x1C
};

struct Rva005D0034LogicView
{
	unsigned char m_pad00[0x98];
	int m_98;				// +0x98
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva005CF8A1
{
public:
	Rva005CF8A1(void *p);
	virtual ~Rva005CF8A1();
	virtual void slot1();
protected:
	Rva005D0034Target *m_target;		// +0x04
	char m_pad08[0x10 - 8];
};

class Rva005D0C31Second
{
public:
	virtual void rva005D0034(int a, int b, int c) = 0;
};

class Rva005D078B : public Rva005CF8A1, public Rva005D0C31Second
{
public:
	Rva005D078B(void *p);
	virtual ~Rva005D078B();
	virtual void rva005D0034(int a, int worldValue, int objectID);
};

void Rva005D078B::rva005D0034(int a, int worldValue, int objectID)
{
	if (worldValue == ((Rva005D0034LogicView *)TheLivingWorldLogic)->m_98 && objectID == m_target->m_objectID)
		m_target->m_callbackHolder.rva00575674((Object *)new Rva005D1255(m_target));
}
