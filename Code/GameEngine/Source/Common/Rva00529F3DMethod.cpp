// cl: /DNDEBUG /MD /EHsc
// ?rva00529F3D@Rva00529F3D@@QAEXH@Z @0x00529F3D 110B.
// Target evidence: ret 4, reads this+0x30, calls the address-pinned
// GameLogic::findObjectByID at 0x00049DC5, checks its result through the
// ThePlayerList receiver at VA 0x00DFEEE8 via 0x002A7DDE, then passes a local
// message to ControlBar::bfmeShowDN at 0x00405C04 using VA 0x00E01CFC.
// Layout evidence for BfmeMsgDN is carried by the matched sibling at
// 0x00567A27 and its donor constructor: virtual dtor, pointer/int fields.
// The method and the checker identity remain address-derived/inferred.
#include <stddef.h>

class Object;
class GameLogic
{
public:
	Object *findObjectByID(int id);
};
extern GameLogic *TheGameLogic;

class PlayerList;
extern PlayerList *ThePlayerList;
class Rva005C38EChecker
{
public:
	bool Check(void *object);
};

struct BfmeMsgDN
{
	BfmeMsgDN(int a, int b)
	{
		m_04 = a;
		m_08 = b;
	}
	virtual ~BfmeMsgDN() {}
	int m_04;
	int m_08;
};

class ControlBar
{
public:
	void bfmeShowDN(BfmeMsgDN *msg);
};
extern ControlBar *TheControlBar;

class Rva00529F3D
{
public:
	void rva00529F3D(int argument);
private:
	char m_pad00[0x30];
	int m_30;
};

void Rva00529F3D::rva00529F3D(int argument)
{
	(void)argument;
	if (m_30 != 0)
	{
		Object *object = TheGameLogic->findObjectByID(m_30);
		if (object != NULL)
		{
			if (ThePlayerList != NULL &&
				((Rva005C38EChecker *)ThePlayerList)->Check(object))
			{
				BfmeMsgDN msg(m_30, 0);
				TheControlBar->bfmeShowDN(&msg);
			}
		}
	}
}
