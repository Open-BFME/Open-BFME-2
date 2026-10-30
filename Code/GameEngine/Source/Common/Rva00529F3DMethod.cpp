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
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class PlayerList;
extern PlayerList *ThePlayerList;
// PlayerList's relationship check 0x002A7DDE (BfmeThreeHundredTwentyFour.cpp).
class Rva002A7DDEArg;
class Rva002A7DDE
{
public:
	bool rva002A7DDE(Rva002A7DDEArg *arg);
};

struct BfmeMsgDN;

// Rva004E7392 sits below the root of table 0x00BE5838 (target facts): that
// table is [??_G 0x00215E42, five __purecall slots], and slot 0 of
// 0x00BFD010 is the shared deleting dtor 0x00406B1D, which calls 0x004059AC:
// mov [ecx],0x00BE5838 / ret. With the empty base destructor expanded, the
// own table store dies and only the root's remains. (Its copy ctor 0x004E7392
// first runs the base copy 0x004E72C0, storing 0x00BFCFF8, another dead
// intermediate store; Rva004E7392Copy.cpp models that step, this view does
// not.) The root takes InGameUICreateMouseoverHint.cpp's spelling, which binds
// the same table to the same class (its TooltipRecord); C01's Rva00215E42
// defines its ctor and dtor out of line, so an inline view under that name
// would duplicate them.
class TooltipBase
{
public:
	virtual ~TooltipBase() {}
};

// The class is compiled without inlining: its scalar deleting destructor
// (retail 0x00406B1D, shared) calls ~Rva004E7392 (0x004059AC) out of line.
// The ctor and destructor are defined after the region, so the bodies still
// expand them and the destructor expands the base's.
#pragma inline_depth(0)
struct Rva004E7392 : public TooltipBase
{
	Rva004E7392(int objectID, int b);
	virtual ~Rva004E7392();
	int m_04;
	int m_08;
};
#pragma inline_depth()
inline Rva004E7392::Rva004E7392(int objectID, int b)
{
	m_04 = objectID;
	m_08 = b;
}
inline Rva004E7392::~Rva004E7392() {}

class ControlBar
{
public:
	void bfmeShowDN(BfmeMsgDN *msg);
};
extern ControlBar *TheControlBar;
class BfmeThingGX;
class Rva00405A50
{
public:
	void rva00405C04(BfmeThingGX *thing);
};

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
				((Rva002A7DDE *)ThePlayerList)->rva002A7DDE((Rva002A7DDEArg *)object))
			{
				Rva004E7392 msg(m_30, 0);
				((Rva00405A50 *)TheControlBar)->rva00405C04(reinterpret_cast<BfmeThingGX *>(&msg));
			}
		}
	}
}
