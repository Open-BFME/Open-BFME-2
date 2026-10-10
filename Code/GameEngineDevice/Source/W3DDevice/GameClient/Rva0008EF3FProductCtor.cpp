// cl: /O1 /G7 /DNDEBUG /MD /Ireference/shims/moduledata
// ??0Rva0008EF3FProduct@@QAE@XZ retail 0x0008EF3F 66B.
//
// The 0xAC0-byte product of game client vtable 0x00BC4738 factory 0x0004C492
// (W3DGameClientFactories.cpp). Target facts: it calls the rowed
// ??0InGameUI@@QAE@XZ 0x002A61A9, stores its own vptrs 0x00BC7A88/+0x0C
// 0x00BC7A78/+0x10 0x00BC7A64 over InGameUI's three bases, clears two
// 25-pointer arrays at +0x9F0/+0xA54 in one loop and then +0xAB8/+0xABC; the
// object ends at 0xAC0, the factory's allocation size.
//
// Donor inference (Zero Hour W3DInGameUI.cpp, not asserted as the target
// name): this is W3DInGameUI::W3DInGameUI -- MAX_MOVE_HINTS is 25 and the
// fields are m_moveHintRenderObj/m_moveHintAnim then the building placement
// anchor and arrow. The class keeps the ledger's address-derived name.

#include "Common/Snapshot.h"

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init();
#define SLOT(N) virtual void slot##N();
	SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07) SLOT(08)
#undef SLOT
	virtual void reset();	// slot 9
	virtual void update();	// slot 10

private:
	char m_opaque04[0xC - 0x4];
};

// The five-slot interface at +0x10 (InGameUICtor.cpp).
class InGameUIInterface10
{
public:
#define SLOT(N) virtual void slot##N() = 0;
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04)
#undef SLOT
};

class InGameUI : public SubsystemInterface, public Snapshot, public InGameUIInterface10
{
public:
	InGameUI();
	virtual ~InGameUI();
	virtual void init();
	virtual void reset();
	virtual void update();

private:
	char m_opaque14[0x9F0 - 0x14];
};

class Rva0008EF3FProduct : public InGameUI
{
public:
	Rva0008EF3FProduct();
	virtual ~Rva0008EF3FProduct();
	virtual void init();
	virtual void reset();
	virtual void update();

private:
	enum { MAX_MOVE_HINTS = 25 };

	void *m_moveHintRenderObj[MAX_MOVE_HINTS];	// +0x9F0
	void *m_moveHintAnim[MAX_MOVE_HINTS];		// +0xA54
	void *m_buildingPlacementAnchor;			// +0xAB8
	void *m_buildingPlacementArrow;				// +0xABC
};

Rva0008EF3FProduct::Rva0008EF3FProduct()
{
	int i;

	for (i = 0; i < MAX_MOVE_HINTS; i++)
	{
		m_moveHintRenderObj[i] = 0;
		m_moveHintAnim[i] = 0;
	}

	m_buildingPlacementAnchor = 0;
	m_buildingPlacementArrow = 0;
}

// ?init@Rva0008EF3FProduct@@UAEXXZ @0x0008F0BB 5B: SubsystemInterface slot 1
// of the product's vtable 0x00BC7A88, extending nothing: a tail jump to the
// rowed InGameUI::init 0x0029E2DE (Zero Hour's W3DInGameUI::init has the same
// body; donor inference only).
void Rva0008EF3FProduct::init()
{
	InGameUI::init();
}

// ?update@Rva0008EF3FProduct@@UAEXXZ @0x0008F0C0 and
// ?reset@Rva0008EF3FProduct@@UAEXXZ @0x0008F0C5, 5B each: slots 10 and 9 of
// the same vtable, tail jumps to the rowed InGameUI::update 0x002A1582 and
// InGameUI::reset 0x002A5EE6 (Zero Hour's W3DInGameUI::update and ::reset
// only call the base; donor inference only).
void Rva0008EF3FProduct::update()
{
	InGameUI::update();
}

void Rva0008EF3FProduct::reset()
{
	InGameUI::reset();
}
