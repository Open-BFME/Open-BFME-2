// cl: /DNDEBUG /MD /EHsc
// ?rva00529F3D@Rva00529F3D@@QAEXH@Z @0x00529F3D 110B.
// Target evidence: ret 4, reads this+0x30, calls the address-pinned
// GameLogic::findObjectByID at 0x00049DC5, checks its result through the
// ThePlayerList receiver at VA 0x00DFEEE8 via 0x002A7DDE, then passes a local
// message to ControlBar::bfmeShowDN at 0x00405C04 using VA 0x00E01CFC.
// The temporary installs VA 0x00BFD010, independently owned by the
// Rva004E7392 copy constructor at RVA 0x004E7392, with fields at +4/+8.
// The superficially similar 0x00567A27 temporary instead uses VA 0x00C6CED8.
// BfmeMsgDN is only the existing opaque receiver-argument spelling here.
// The method and the checker identity remain address-derived/inferred.
#include <stddef.h>

class Object;
// Zero Hour's GameCommon.h spells the id an enum; retail's 0x00049DC5 row takes it.
enum ObjectID { INVALID_ID = 0, FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff };
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class PlayerList;
extern PlayerList *ThePlayerList;
class Rva005C38EChecker
{
public:
	bool Check(void *object);
};

struct BfmeMsgDN;

struct Rva004E7392
{
	Rva004E7392(int a, int b)
	{
		m_04 = a;
		m_08 = b;
	}
	virtual ~Rva004E7392() {}
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
		Object *object = TheGameLogic->findObjectByID((ObjectID)m_30);
		if (object != NULL)
		{
			if (ThePlayerList != NULL &&
				((Rva005C38EChecker *)ThePlayerList)->Check(object))
			{
				Rva004E7392 msg(m_30, 0);
				TheControlBar->bfmeShowDN(reinterpret_cast<BfmeMsgDN *>(&msg));
			}
		}
	}
}
